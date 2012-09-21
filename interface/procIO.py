#! /usr/bin/python

import sys
import socket
import string
import os
import subprocess
import re
import threading
import irc
try:
    from Queue import Queue, Empty
except ImportError:
    from queue import Queue, Empty  # python 3.x

def Write( strang, proc ):
    proc.stdin.write(strang)
    proc.stdin.flush()
    return
    
def Read( proc ):
    old_stdin = sys.stdin
    sys.stdin = proc.stdout
    str = raw_input()
    sys.stdin = old_stdin
    return str

def ReadNoWait( out, queue):
    for line in iter(out.readline, b''):
        queue.put(line)