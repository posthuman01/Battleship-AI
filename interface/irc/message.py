#! /usr/bin/python

import sys
import socket
import string
import os
import subprocess
import re
import threading
try:
    from Queue import Queue, Empty
except ImportError:
    from queue import Queue, Empty  # python 3.x


class irc_client_message(object):
    match_strings = (r"^([^:]+):([^:]+):(.*)$" , )
    compiled_regexes = (re.compile(match_strings[0]) ,)

    def __init__(self, strang=None, msg_type="PRIVMSG", recipient=None, params=None, message=None):
        self.msg_type = msg_type
        self.message = message
        self.params = params
        self.parsed = False
        if(strang != None):
            self.parsed = self.parse_string(strang)

    def parse_string(self, strang):
        #print strang
        matches = irc_client_message.compiled_regexes[0].match(strang)
        if(matches == None or len(matches.groups("")) < 3):
            print "ERROR irc_client_message:<" + strang + ">"
            self.parsed = False
            return False
        groups = matches.groups("")
        self.msg_type = groups[0]
        params = groups[1].split(' ')
        self.recipient = params[0]
        self.params = params[1:]
        self.message = groups[2]
        self.parsed = True
        return True

class irc_server_message(object):
    match_strings = (r"^([^ :]*) {0,1}:([^ ]+) {0,1}([^:]*):{0,1}([^\n]*)$", r"^([^ !]+)")
    compiled_regexes = (re.compile(match_strings[0]), re.compile(match_strings[1]) )

    def __init__(self, strang=None, command="", sender="", msg_type="", recipient="", message="", extra_params=""):
        self.command = command
        self.sender = sender
        self.msg_type = msg_type
        self.recipient = recipient
        self.message = message
        self.extra_params = extra_params
        if(strang != None):
            self.parse_string(strang)

    def parse_string(self, strang):
        matches = irc_server_message.compiled_regexes[0].match(strang)
        if(matches == None):
            print "ERROR " + strang
            return self
        self.command = matches.group(1)
        self.sender = irc_server_message.compiled_regexes[1].match(matches.group(2)).group(1)
        params = matches.group(3).split(' ')
        length = len(params)
        if(length > 0):
            self.msg_type = params[0]
            if(length > 1):
                self.recipient = params[1]
                if(length > 2):
                    self.extra_params = params[2:length-1]
        self.message = matches.group(4)
        return self
