import rpyc
import sys
import os
import threading
from random import randint
import time
import socket

'''
RPyC service model 
import rpyc

class MyService(rpyc.Service):
    def on_connect(self, conn):
        # code that runs when a connection is created
        # (to init the service, if needed)
        pass

    def on_disconnect(self, conn):
        # code that runs after the connection has already closed
        # (to finalize the service, if needed)
        pass

    def exposed_get_response(self): # this is an exposed method
        return 42

    exposed_the_real_response_though = 43     # an exposed attribute

    def get_question(self):  # while this method is not exposed
        return "what is the airspeed velocity of an unladen swallow?"
'''

'''
A RAFT RPC server class.
Please keep the signature of the is_leader() method unchanged (though
implement the body of that function correctly.  You will need to add
other methods to implement ONLY the leader election part of the RAFT
protocol.

this is an rpyc Service
'''
class RaftNode(rpyc.Service):

	"""
		Initialize the class using the config file provided and also initialize
		any datastructures you may need.
	"""
	def __init__(self, config, server_no):
		
		# process config file
		config_file = os.path.realpath(config)
		file = open(config_file, 'r')
		content = file.read() # read into a full string
		file.close()

		file_lines_list = content.split("\n")
		
		confdict = {}
		for element in file_lines_list:
			node_name, ip_addr = element.split(': ')
			confdict.update({node_name: ip_addr})

		# set variabes for constructor : my ID, leaderID
		self.num_servers = int(confdict["N"])
		self.majority = (self.num_servers // 2) + 1 # raft is k-fault tolertant, w/ group size N = 2k+1
		del confdict["N"]
		del confdict["node"+str(int(server_no))]			# cross out current node
		self.server_list = []
		for node_name, ip_addr  in confdict.items():
			self.server_list.append(ip_addr)

		# leader & voting related variables
		self.leaderID = None
		self.ID = server_no
		self.vote = 0

		# set logFile for persistent storage
		self.logFile = open(os.path.join("./tmp", "node" + str(server_no) + ".txt"), "a") # create log file for booted server
		self.logFile.close()
		if self.is_non_zero_file(self.logFile.name):
			self.currentTerm, self.votedFor = self.check_state_file(self.logFile.name)
			self.currentTerm = int(self.currentTerm)
			self.votedFor = int(self.votedFor)
		else:
			self.currentTerm = -1
			self.votedFor = None
		self.fileLock = threading.Lock()

		# since each server is ran on a thread, locks needed for mutual exclusion
		self.voteLock = threading.Lock()
		self.appendLock = threading.Lock()

		# flag to KEEP / INITIATE new leader
		self.stop_leader = threading.Event()	# Event = flag set() | true -- clear() | false -- wait() | blocks till flag = true.
		
		# thread for life of node, 1 thread/node
		self.timerThread = threading.Thread(target=self.enterFollowerState)
		self.timerThread.start()

	# assign timeout range
	# start timer - use threading.Timer(time, startFunction) - startFunction will be exec'ed once time expires
	def enterFollowerState(self):
		while True:
			election_timeout = randint(30, 70)
			election_timeout = election_timeout / 10
			self.Voted = False
			self.stop_leader.clear() # set to false
			self.electionTimeoutThread = threading.Timer(float(election_timeout), self.enterCandidateState) # threading.Timer - A thread that executes a function after election_timeout expires.
			self.electionTimeoutThread.start()	
			self.electionTimeoutThread.join()

	def enterCandidateState(self):
		print("Turned into candidate")
		self.fileLock.acquire()
		self.currentTerm += 1
		self.votedFor = self.ID
		self.Voted = True
		self.update_log_file(self.logFile.name)
		self.fileLock.release()
		
		self.vote = 1
		server_threads_list = []
		# print("Server list is:" + str(self.server_list))

		for n in range(self.num_servers-1):
			address, port = self.server_list[n].split(':')
			# ask localhost:60001, ...  for votes 
			askOtherServerThread = threading.Thread(target=self.get_vote, args=(address, port), kwargs={})
			server_threads_list.append(askOtherServerThread)
			askOtherServerThread.start()

		for thread in server_threads_list:
			thread.join()
		
		# after gett all votes back
		if self.vote >= self.majority:
			self.leaderID = self.ID
			self.leaderLoop()
		else:
			print("Not getting majority. Turns back to candidate")
			pass

	def get_vote(self, address, port):
		try:
			conn = rpyc.connect(address, port).root
			print("Connected")
			term, response = conn.requestVote(self.currentTerm, self.ID)
		except ConnectionRefusedError:
				term, response = (self.currentTerm, False)
		except EOFError:
			term, response = (self.currentTerm, False)
		except socket.error:
			term, response = (self.currentTerm, False)

		# get responses from a Follower	
		if response :
			self.vote += 1

	# helper funcs for persistent storage files
	def is_non_zero_file(self, fpath):
		return os.stat(fpath).st_size != 0

	def check_state_file(self, fname):
		last = ''
		with open(fname, "r") as f:
			lines = f.read().splitlines()
			last = lines[-1]
		return tuple(last.split(','))

	def update_log_file(self, fname):
		with open(fname, 'a') as fp:
			fp.write(str(self.currentTerm) + ',' + str(self.votedFor) + '\n')

	def leaderLoop(self):
		while True:
			if self.stop_leader.is_set():
				#print("leader break event!")
				self.stop_leader.clear()
				break
			vote = 1
			for n in range(self.num_servers-1):
				try:
					address, port = self.server_list[n].split(':')
					conn = rpyc.connect(address, port).root
					term, response = conn.appendEntries(self.currentTerm, self.ID)
				except ConnectionRefusedError:
					term, response = (self.currentTerm, False)
				except EOFError:
					term, response = (self.currentTerm, False)
				except socket.error:
					term, response = (self.currentTerm, False)
				if response:
					vote += 1
			if vote < self.majority: # no longer a leader
				break
		# print("Entered election timeout period")
		# self.enterFollowerState()

	'''
	if the name starts with exposed_, the attribute will be remotely accessible, 
	otherwise it is only locally accessible. Here, we allow the clients to call is_leader
	'''
	def exposed_is_leader(self):
		if self.leaderID == self.ID:
			return True
		else:
			return False

	def exposed_appendEntries(self, term, leaderId):
		if term < self.currentTerm:
			return (self.currentTerm, False)
		else:
			self.appendLock.acquire()
			self.electionTimeoutThread.cancel()		# stop timer thread
			self.stop_leader.set()			# if receive this, meaning there is another leader running, stop yourself
			self.currentTerm = term
			self.leaderID = leaderId
			self.appendLock.release()
			print("\n" + str(self.leaderID) + " is my leader with term: " + str(term) + " and my ID is " + str(self.ID))
			return (self.currentTerm, True)

	def exposed_requestVote(self, term, candidateId):
		if term > self.currentTerm and not self.Voted:
			self.voteLock.acquire()
			self.electionTimeoutThread.cancel()		# stop timer thread
			self.currentTerm = term
			self.votedFor = candidateId
			self.update_log_file(self.logFile.name)
			self.Voted = True
			self.voteLock.release()
			return(self.currentTerm, True)
		else:
			return (self.currentTerm, False)

'''
expose Service to the world, we need to start a server.

passing in a RaftNode instance, all incoming connections will 
use this instance as their shared root object
'''
if __name__ == '__main__':
	from rpyc.utils.server import ThreadPoolServer # same as ThreadSerever but some reusability feature
	server = ThreadPoolServer(RaftNode(sys.argv[1], sys.argv[2]), port = int(sys.argv[3]))
	server.start()
