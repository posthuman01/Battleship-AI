#! /usr/bin/python

import sys
import socket
import string
import os
import subprocess
import re
import threading
import irc
import irc.message
import procIO
try:
    from Queue import Queue, Empty
except ImportError:
    from queue import Queue, Empty  # python 3.x


class irc_server_thread(threading.Thread):
    def __init__(self, connection, proc, daemon=True):
        self.connection = connection
        self.Dexecuting = False
        self.proc = proc
        threading.Thread.__init__(self)
        self.daemon = daemon

    def run(self):
        print "Server thread"
        self.Dexecuting = True
        while True:
            line = self.connection.get_next_line()
            msg = irc.message.irc_server_message(strang = line)
            if(self.handle_server_message(msg) == False):
                self.Dexecuting = False
                print "/Server thread"
                return   

    def handle_server_message(self, msg):
        if(msg.command == "PING"):
            self.connection.s.send("PONG "+msg.sender+"\n")
            print "PONG "+msg.sender
            return True
        elif(msg.message == "$4COCK"):
            self.connection.quit(do_action = True)
            procIO.Write("COMMAND:" + msg.sender + ":" + msg.recipient + ":QUIT\n", self.proc)
            return False
        procIO.Write(msg.msg_type + ":"  + msg.sender + ":"+ msg.recipient + ":" + msg.message + "\n", self.proc)
        return True     

class msg_read_thread(threading.Thread):
    def __init__(self, qu, out, daemon=True):
        self.qu = qu
        self.out = out
        threading.Thread.__init__(self)
        self.daemon = daemon

    def run(self):
        while True:
            procIO.ReadNoWait(self.out, self.qu)