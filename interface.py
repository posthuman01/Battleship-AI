#! /usr/bin/python

import sys
import socket
import string
import os
import subprocess
import re
import threading
import interface.irc
import interface.irc.connection
import interface.procIO
import interface.config_manage 
import interface.irc.threads
#from interface import irc, procIO, config_manage
try:
    from Queue import Queue, Empty
except ImportError:
    from queue import Queue, Empty  # python 3.x

def main(): 
    Config = interface.config_manage.ConfigManager()
    Config.readfp(open("interface/config.cfg"))
    Section = Config["OVERRIDES"]
    proc = subprocess.Popen(sys.argv[1], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
    
    connection = interface.irc.connection.irc_connection()
    connection.connect(host=Section["host"], port=int(Section["port"]))
    connection.register_nick(Section["nick"])
    connection.register_ident(ident="GHB578645_BOT_IDENT", realname="GHB578645_BOT_REALNAME")
    connection.join(Section["channel"])
    
    qu = Queue()
    
    server_thread = interface.irc.threads.irc_server_thread(connection, proc)
    msg_thread = interface.irc.threads.msg_read_thread(qu, proc.stdout)

    server_thread.start()
    msg_thread.start()
    
    while(server_thread.isAlive()):
        try:
            line = qu.get_nowait()
        except Empty:
            pass
        else:
            msg = interface.irc.message.irc_client_message(strang=line)
            connection.send_message(msg)
    print "/main"
    return 0

if __name__=="__main__":
    sys.exit(main())
