#! /usr/bin/python

import sys
import string
import ConfigParser
import os


# Will implement more functionality later, too lazy right now
class ConfigManager(ConfigParser.RawConfigParser):
	def __init__(self, *args, **kwargs):
		ConfigParser.RawConfigParser.__init__(self, *args, **kwargs)

	def __getitem__(self, key):
		return ConfigSection(self,key)

class ConfigSection:
	def __init__(self, mger, name):
		self.mger = mger
		self.name = name

	def __getitem__(self, key):
		return self.mger.get(self.name, key)

	def __setitem__(self, key, value):
		self.mger.set(self.name, key, value)

