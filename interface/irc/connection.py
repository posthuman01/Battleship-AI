#! /usr/bin/python

import sys
import socket
import string
import os
import subprocess
import re
import threading
import irc
import irc.threads
from irc.message import irc_client_message, irc_server_message
try:
    from Queue import Queue, Empty
except ImportError:
    from queue import Queue, Empty  # python 3.x



class irc_connection(object):
    def __init__(self, host="irc.freenode.net" , port=6667, nick=None, ident="BOT_IDENT", realname="dBOT", owner="Philipp McBadass", channels=[]):
        self.host = host
        self.port = port
        self.nick = nick
        self.ident = ident
        self.realname = realname
        self.owner = owner
        self.channels = channels
        self.s = socket.socket()
        self.joined = False
        self.cached_lines = None

    def connect(self, host=None, port=None):
        self.host = irc_connection.__merge_def_(host, self.host)
        self.port = irc_connection.__merge_def_(port, self.port)
        self.s.connect((self.host, self.port))

    def join(self, channel, key = ""):
        if(self.channels.count(channel) > 0):
            return True
        this_join = False
        while(not this_join):
            self.s.send("JOIN " + channel + " " + key + " \n")
            buff = irc_connection.__receive_buffer_(self.s)
            lines = irc_connection.__split_lines_(buff)
            i = 0
            l = len(lines)
            while(i<l):
                msg = irc_server_message(strang=lines[i])
                if(msg.msg_type == "JOIN"):
                    print "JOINED " + channel
                    this_join = True
                    break
                i += 1          
            if(i != l and this_join == True):
                self.channels.append(channel)     
                self.cached_lines = lines[i+1:]
        return True

    @staticmethod
    def __receive_buffer_(sock, buffer_size=513):
        inp = sock.recv(buffer_size)
        while((len(inp)%buffer_size) == 0):
            inp += sock.recv(buffer_size) # recieve the server messages
        return inp

    @staticmethod
    def __split_lines_(inp, print_lines=True):
        lines = inp.splitlines()
        l = len(lines)
        i = 1
        while (i < l):
            if(lines[i][0] != ":"):
                lines[i-1] = lines[i-1] + "\n" + lines[i]
                del(lines[i])
                l -= 1
                continue
            i += 1
        if(print_lines):
            for line in lines:
                print "<" + line + ">"
        return lines

    @staticmethod
    def __merge_def_(new=None, old=None):
        if(new == None):
            return old
        else:
            return new

    def get_next_line(self):
        line = None
        if(self.cached_lines != None and len(self.cached_lines) > 0):
            line = self.cached_lines[0:1][0]
            del(self.cached_lines[0])
            if(len(self.cached_lines) == 0):
                self.cached_lines = None
        else:
            lines = irc_connection.__split_lines_(irc_connection.__receive_buffer_(self.s))
            if(lines != None and len(lines) > 0):
                line = lines[0:1][0]
                self.cached_lines = lines[1:]
        return line

    def set_connection_password(self, password):
        self.s.send("PASS " + password + " \n")

    def register_nick(self, nick):
        self.nick = nick
        self.s.send("NICK " + nick + "\n")
        return True

    def register_ident(self, ident, realname):
        self.ident = ident
        self.realname = realname
        self.s.send("USER "+self.ident+" "+self.host+" NAME "+self.realname+"\n")
        return True

    def get_next_message(self):
        return irc_server_message(strang = self.get_next_line())

    def send_message(self, msg):
        self.s.send(msg.msg_type + " " + msg.recipient + " :" + msg.message + "\n")

    def quit(self,  message="", do_action=False, action="Quitting!!!"):
        if(do_action):
            for channel in self.channels:
                self.send_message(irc_server_message(msg_type="PRIVMSG", recipient=channel, message = chr(1)+"ACTION " + action + chr(1)))
        self.channels = []
        self.cached_lines = None
        self.s.send("QUIT " + message + " \n")

    def leave_channel(self, channel, message=""):
        if(self.channels.count(channel) > 0):
            self.channels.remove(channel)
            self.s.send("PART " + channel + " " + message + " \n")

    def leave_channels(self, channels, message=""):
        for channel in channels:
            self.leave_channel(channel, message)

    def register_service(self, info, distribution="*"):
        self.s.send("SERVICE " + self.nick + "  * " + distribution + " 0 0 :" + info + " \n")