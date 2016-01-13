#!/usr/bin/python

__author__ = "Ahmer Malik"
__copyright__ = "Copyright (C) 2016 Linux IoT"
__revision__ = "$Id$"
__version__ = "0.2"

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
import os

# name of conf file to read
conf_file = "STATS.conf"

# Initialize config parameters
_conf = ConfigParser.ConfigParser()
_conf.read(conf_file)

SYSTEM = _conf.get('SYSTEM','STATS')
DIRS = _conf.get('DIRS','DIRSIZE')

SYSTEM_list = SYSTEM.split(",")
DIRS_list = DIRS.split(",")
print SYSTEM_list
print DIRS_list

"""sys = open('/home/ahmer/stats_info','w')
dirs = open('/home/ahmer/dir_info','w')
"""

def memory_info():
        mem = open('/proc/meminfo', 'r')
        for line in mem:
                if "MemTotal:" in line:
                    st = line 
                    print line
                    print st.split(' ')[8]

        
        mem_2 = psutil.virtual_memory()
        print mem_2[0]/1024

def cpu_info():    
        cpu = open('/proc/cpuinfo', 'r') #lscpu
        num_cpu = 0
        for line in cpu:
                if "processor" in line:
                    num_cpu += 1
            
        print num_cpu
        print psutil.cpu_count()

def process_info():
        print psutil.pids()



SYSTEM_DICT = {'memory': memory_info , 'cpu': cpu_info,
               'processes': process_info } 

for i in SYSTEM_list:
         SYSTEM_DICT.get(i)()
        
for j in DIRS_list:
        a = os.stat(j)
        A = a[6]/1024
        print (j + " = " + str(A) + "KB")

