#!/usr/bin/python

# Add os class because we have to use its method of listing directory. (os.listdir) 
import os

__author__ = "Ahmer Malik"
__copyright__ = "Copyright (C) 2016 Linux IoT"
__revision__ = "$Id$"
__version__ = "0.2"

"""
	This class is for getting the dictionary (name_subdirectories : size in KB) of whatever directory you need. The dictionary will be in the form of txt file and you have to specify the path (where you want to store txt). 

How to use this class	-->	get_dict_size_class(Path (Directory for you want dictionary) , Path (listing subdirectories in txt file), Path (dictionary txt file))
   
 """
class get_dict_size_class:
	# Declare the dictionary
        fs_dict = {}

	# Constructor initiallize the data
        def __init__(self, dir_name, dest_txt , dict_txt):
                self.dir_name = dir_name
                self.dest_txt = dest_txt
                self.dict_txt = dict_txt
        
	# This function is used for getting list of sub-directories
        def write_dir_list(self):
		# To get list of sub-directories
                fs = os.listdir(self.dir_name)
		# open a file at desired place to store the list
                fd = open(self.dest_txt, 'w')
                for each_item in fs:
                        fd.write(each_item)
                        fd.write("\n")          
                fd.close()
	# This function is used for getting dictionary (sub-directory : size in KB) of sub-directories
        def write_dict(self):
                fd_2 = open(self.dict_txt, 'w')
                for line in open(self.dest_txt, 'r'):
                        line = '/'+line[:-1] # becuase we have to remove the '\n' character from the list we get from file. [line[:-1] remove last character] 
                        a = os.stat(line)  # stats of the subdirectory.
                        A = a[6]/1024		# size is at 6th index in the stat list. /1024 for coverting B -> KB
                        get_dict_size_class.fs_dict[line] = A
                        fd_2.write(line + ":" + str(A)  + "\n")  # Write in the dictionary file.
                fd_2.close()





