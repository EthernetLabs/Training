#!/usr/bin/python
# import the python file having get_dict_size_class
import get_fs_dict_class

__author__ = "Ahmer Malik"
__copyright__ = "Copyright (C) 2016 Linux IoT"
__revision__ = "$Id$"
__version__ = "0.2"

#Create FS object that calls "get_dict_size_class" from "get_fs_dict_class.py"  
FS = get_fs_dict_class.get_dict_size_class('/','/home/ahmer/Techknox/Python Exercises/fs_list_2','/home/ahmer/Techknox/Python Exercises/fs_dict_2')
# Call its method for list
FS.write_dir_list()
# Call its method for creating dictionary 
FS.write_dict()


