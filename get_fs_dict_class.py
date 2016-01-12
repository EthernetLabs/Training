#!/usr/bin/python

__author__ = "Ahmer Malik"
__copyright__ = "Copyright (C) 2016 Linux IoT"
__revision__ = "$Id$"
__version__ = "0.1"

import os
class get_dict_size_class:
        fs_dict = {}

        def __init__(self, dir_name, dest_txt , dict_txt):
                self.dir_name = dir_name
                self.dest_txt = dest_txt
                self.dict_txt = dict_txt
        

        def write_dir_list(self):
                fs = os.listdir(self.dir_name)
                fd = open(self.dest_txt, 'w')
                for each_item in fs:
                        fd.write(each_item)
                        fd.write("\n")          
                fd.close()

        def write_dict(self):
                fd_2 = open(self.dict_txt, 'w')
                for line in open(self.dest_txt, 'r'):
                        line = '/'+line[:-1]
                        a = os.stat(line)
                        A = a[6]/1024
                        get_dict_size_class.fs_dict[line] = A
                        fd_2.write(line + ":" + str(A)  + "\n")
                fd_2.close()



FS = get_dict_size_class('/','/home/ahmer/Techknox/Python Exercises/fs_list_2','/home/ahmer/Techknox/Python Exercises/fs_dict_2')
FS.write_dir_list()
FS.write_dict()


