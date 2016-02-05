.. _week-03:

***************************
Week - 3 Linux IoT Training
***************************

Task - 1: SSH and SFTP
=====================

Learn why and how to use ssh and sftp in Linux. What is the difference between ssh and sftp. How to manipulate data between host and client. After remotely login into the server, how we can do download data from there using get command.

Task - 2: Kernel Virtual Machines (KVM's)
=========================================

What is a KVM and how virtual machines are beneficial. Build a KVM using Python VM builder and Virt-Mnager. The guest should be on the same OS as host is (in my case Ubuntu 14.04.3) .

How to make virtual machines `follow this <https://www.howtoforge.com/creating-virtual-machines-for-xen-kvm-vmware-workstation-6-vmware-server-with-vmbuilder-on-ubuntu-8.10-p2>`_

Task - 3: IP Addresses and Subnets
==================================

What is an IP address. What is difference between IPV4 and IPV6. Why IPV6 was necessary to introduced. What each octet represents in an IP address. What are subnets and learn about the VLSM and CIDR and present back to the instructor.

Task - 4: IP Addressing Case
============================

Let's assume that IoT Systems has 10 departments. The list of departments are:

==================== 	 ================
DEPARTMENTS  	  	 NO. OF EMPLOYEES
====================	 ================
Software			112
Hardware			60
IT				40
Finance				06
Public Relations		02
Marketing			12
Business development		25
Quality Insurance		20
House Keeping			4
Admin				3
====================	 ================


Each department should have its own subnet. The design of sub-netting should be wise, as the company is well developed and there will be chances to extend it up to little extent only (in term of employees). 


.. _ip-addr-tech:
.. figure::  images/IP_Addressing_Techknox.png
   :align:   center

   IP Addressing for IoT Systems.

Task - 5: Software Defined Network (SDN)
========================================

Now, we have a proper design of subnets for a company. Now, its time to simulate it on our PC. This task is divided into different subtasks:

#. Install 20 KVM's on your host (2 KVM's/Department). I have used different embedded .iso's (tiny core linux, snappy etc), but snappy suits best. Build 20 KVM having 128M RAM, 3.5 G Disk, 1 CPU.

#. Change their IP's according to sub-netting exercise that we have done in previous task. This directory (/etc/network/interfaces.d/eth0) is important for changing IP's.

#.  Reboot all KVM's and check using ifconfig that all the desired changes have been saved or not. If not then might be some issue.

#. Now, install 21st  KVM that will be act as Router. It should be running Ubuntu 14.04.3. Its RAM should be around 1-2 GB.

#. The router should have 10 ports for the communication through a switch to the 10 departments of company. Hence, here is the need to add 10 network interfaces in the Router VM that should be act as 10 ports of the router.

	Shutdown the router VM ---> virsh edit router ---> add 10 network interfaces here (.xml file)
	change:  mac = 0x_____ , slot: each should have different slot.

#. After adding 10 NIC's, start the router domain. Check in host machine using ifconfig  whether 10 macs are added or not.

#. Now, its time to connect each router port to its corresponding subnet through a switch.
	Learn brctl using man page. 
	P1 (router) connects to N1 (Software  –>  Employ 1 (KVM-1) Employ 2 (KVM -2) )

#. Learn the ping command. And check whether each guest of a Network can communicate to or listen to its corresponding Port on router.

In router: ping _IP (N1: E1)____ 


Task - 6: Bash Scripting of SDN Lab 
===================================

All that has been done above should be scripted now. Think how we can efficiently start all the KVM's, check each KVM status. After successful booting of all VM's add the router ports and corresponding network VMS to same switch (bridge).  

 
