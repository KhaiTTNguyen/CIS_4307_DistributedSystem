import rpyc
import sys

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

    def exposed_get_answer(self): # this is an exposed method
        return 42

    exposed_the_real_answer_though = 43     # an exposed attribute

    def get_question(self):  # while this method is not exposed
        return "what is the airspeed velocity of an unladen swallow?"
'''

'''
A RAFT RPC server class.

Please keep the signature of the is_leader() method unchanged (though
implement the body of that function correctly.  You will need to add
other methods to implement ONLY the leader election part of the RAFT
protocol.
'''

# RaftNode.is_leader()
# WARNING!!!!!!!!!!!!!!!! 
# change your code so that it supports a third command-line argument, namely the port number used by that node. 
# 

# $ python3 raftnode.py <path to config file> <node #> <port>

class RaftNode(rpyc.Service):
	

	"""
        Initialize the class using the 'config file' provided and also initialize
        any datastructures you may need.
	"""
	def __init__(self, config):
		pass
		# process config file
		# N: 5
		# node0: localhost:5001
		# node1: localhost:5002
		# node2: localhost:5003
		# node3: localhost:5004
		# node4: localhost:5005


		with open(config, 'r') as f:
			data = f.readlines()
			print(str(data))


	'''
        x = is_leader(): returns True or False, depending on whether
        this node is a leader

        As per rpyc syntax, adding the prefix 'exposed_' will expose this
        method as an RPC call

        CHANGE THIS METHOD TO RETURN THE APPROPRIATE RESPONSE
	'''
	# assign timeout range
	# start timer - use threading.Timer(time, startFunction) - startFunction will be exec'ed once time expires
	def NodeBegin(self):
		return

	def beginElection(self):
		return

	def check_state_file(self, fname):
		return

	def is_non_zero_file(self, fpath):
		return

	# naming must start with exposed_
	def exposed_is_leader(self):
		return False
	
	def update_state_file(self, fname):
		return

	def get_vote(self, a, b):
		return 
	
	def leaderLoop(self):	# stop_leader set() / clear()
		return
	
	def exposed_AppendEntries(self, term ,leaderId):
		return

	def exposed_RequestVote(self, term, candidateId):
		return

	

if __name__ == '__main__':
	from rpyc.utils.server import ThreadPoolServer
	server = ThreadPoolServer(RaftNode(sys.argv[1]), port = 6000)
	server.start()

