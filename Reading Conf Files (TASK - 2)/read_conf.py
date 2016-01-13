#!/usr/bin/python

__author__ = "Ahmer Malik"
__copyright__ = "Copyright (C) 2016 Linux IoT"
__revision__ = "$Id$"
__version__ = "0.1"

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


import ConfigParser
import re
import psutil

num_cpu = 0
pro = 0

# name of conf file to read
conf_file = "STATS.conf"

# Initialize config parameters
_conf = ConfigParser.ConfigParser()
_conf.read(conf_file)

print _conf.get('SYSTEM','STATS')
print _conf.get('DIRS','DIRSIZE')
 

mem = open('/proc/meminfo', 'r')
for line in mem:
        #line = re.search('MemTotal:',line)
        if "MemTotal:" in line:
            st = line 
            print line
            print st.split(' ')[8]

mem_2 = psutil.virtual_memory()
print mem_2[0]/1024
    
cpu = open('/proc/cpuinfo', 'r') #lscpu
for line in cpu:
        if "processor" in line:
            num_cpu += 1
            
print num_cpu
print psutil.cpu_count()

print psutil.pids()


