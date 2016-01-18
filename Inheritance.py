#!/usr/bin/python

class contact:
	all_contacts = []
	
	def __init__ (self, name, email):
		self.name = name
		self.email = email
		contact.all_contacts.append(self)
		

class supplier(contact):
	
	def order(self):
		print ('Hello I have shared the contacts of suppliers\n')


s1 = supplier("Ahmer","ahmer.malik914@gmail.com")
print ( s1.name + ':' + s1.email + '\n')
s2 = supplier("Weqaar","weqaar@gmail.com")
print ( s2.name + ':' + s2.email + '\n')
print s1.all_contacts





