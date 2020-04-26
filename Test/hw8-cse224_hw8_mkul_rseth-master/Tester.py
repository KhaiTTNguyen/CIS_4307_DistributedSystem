import raftnode
import rpyc
from rpyc.utils.server import ThreadPoolServer
import threading
import time
from random import randint
import os

def main():
    #  use "&" to push process run in background, allowing following cmds to be executed
    bashCommand = "python3 raftnode.py ./config.txt 0 6001 & " \
    + "python3 raftnode.py ./config.txt 1 6002 & " \
    + "python3 raftnode.py ./config.txt 2 6003 & " \
    + "python3 raftnode.py ./config.txt 3 6004 & " \
    + "python3 raftnode.py ./config.txt 4 6005 &"

    os.system(bashCommand)  # os.system() execute the command (a string) in a subshell
   

main()
