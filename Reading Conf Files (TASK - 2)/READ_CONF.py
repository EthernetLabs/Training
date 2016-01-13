#!/usr/bin/python

__author__ = "Ahmer Malik"
__copyright__ = "Copyright (C) 2016 Linux IoT"
__revision__ = "$Id$"
__version__ = "0.3"

"""
    This module is for basic understanding of how to use user defined conf files
    to perform a ceratain action on it.
    This module reads options from STATS.conf file. It has 2 options, "SYSTEM" & "DIRS"
    
    STATS.conf
    [SYSTEM]
     STAT= Which stats required memory,cpu,processes
    [DIRS]
     DIRSIZE = Which directory you need sizes in KB
"""

# To read from conf files
import ConfigParser

# For regular expressions
import re

""" psutil is a cross-platform library for retrieving information on
running processes and system utilization (CPU, memory, disks, network)
in Python.
"""
import psutil
import os

# name of conf file to read
conf_file = "STATS.conf"

# Initialize config parameters
# _conf is an object of Config ConfigParser.ConfigParser()
_conf = ConfigParser.ConfigParser()

# Use the read()method of class to read the .conf file
_conf.read(conf_file)

# Get the "STAT" option from "SYSTEM" section
SYSTEM = _conf.get('SYSTEM','STATS')
# Get the "DIRS" option from "DIRSIZE" section
DIRS = _conf.get('DIRS','DIRSIZE')

# SYSTEM variable is a string
# Make a list of strings seperated by ","
SYSTEM_list = SYSTEM.split(",")
DIRS_list = DIRS.split(",")
print SYSTEM_list
print DIRS_list

sys = open('/home/ahmer/stats_info','w') # Path where to store information files
dirs = open('/home/ahmer/dir_info','w')


def memory_info():
        mem = psutil.virtual_memory()
        m = mem[0]/1024
        sys.write("Memory : " + str(m) + "\n")
def cpu_info():    
        num_cpu = psutil.cpu_count()
        sys.write("CPU''s : " + str(num_cpu) + "\n")
def process_info():
        ps = psutil.pids()
        sys.write("Processes : " + str(ps) + "\n")

# Make a dictionary that is purely mimic of "switch" conditon in c
# Which function should be called based on the strings  
SYSTEM_DICT = {'memory': memory_info , 'cpu': cpu_info,
               'processes': process_info }

# iterate through each strings and called that function
for i in SYSTEM_list:
         SYSTEM_DICT.get(i)()
        
for j in DIRS_list:
        a = os.stat(j)
        A = a[6]/1024
        dirs.write(j + " = " + str(A) + "KB\n")

sys.close()
dirs.close()

