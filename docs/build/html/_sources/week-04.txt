.. _week-04:


Week - 4 Linux IoT Training
***************************

Task - 1: SDN - Scripting 
=========================

As we have concluded our week-3 by establishing the IoT Systems Networks through commands and have to think how we can implement it using bash scripts. Why Bash Scripts?

Now, we have got that how the things are working, but did not done in professional way. Secondly, if we have to work on some different machine, having the VMS, then we have to perform all this procedure again. It sounds not good.

We have performed a task 1 time, then why we do the same again and waste time. Lets do it in professional way.

#. Create a .conf file that contains the names of domains (VM machines). Because every user or client doesn't have the same name as we used. The .conf should look like this

**#VM-Domains.conf**

``HOSTS = Router_name,H1,H2, H3,H4,. . .``

What is the benefit of using Router name at 1st position, we will discussed it later.

#. Read the all domain names and check its status whether it is ON or OFF? You can use (Hint: man virsh dominfo). Based on the state, you should take step to ON it.

**#Boot.sh**

- Start all VMS by reading names from .conf.

- Add the hosts and ports of router to corresponding switch/bridge.

For scripting you should have solid grip on the **“Regular Expressions”**. Because you have to extract out useful information from files, have to edit it and have to perform different functions.

**Hint-1:** have excessive use of “grep”, “cut”, “sed” commands. Do read them in detail.

**Hint-2:** /etc/network/ . . . This directory will be used many times.

#. Instead of giving full path to .xml files, use dumpxml (read it carefully, what it do) . Because, in different computer the path to .xml files might be different. And your script will not work properly.

You should write such script that can run on any machine. Not just on your own local.

#. Create the required switches and add corresponding VMS or host to it. For Example:

``SW-1  = [H1,H2 and eth0 of router]`` 

**Hint:** Read man `brctl` because you have create/delete bridges, add/delete interfaces.

#. Write shutoff.sh to off all the domains when need. Otherwise you will have to shutdown 20 VMS manually. (Its the power of scripting).

#. Now we have to test whether domains under same switch can communicate or not.
	
**Hint:**  Ping command will help you a lot. Read it.

#. Using ping, the message received properly to the destination or not. It should work fine.

**Debugging challenge:** Now the Challenge begins, they are not communicating within the same bridge. Why? As everything is just looking fine from frontal view

Task - 2: Figure Out the Problem 
================================

Figure out, what is going wrong and where? Look into each KVM, their Macs, IP's (broadcast, net masks etc), vnets. Use ifconfig, read xml's. . . Its too irritating but we have to do it. 

What was the problem –-> After 1 day of debugging, we have found that when a VM starts it goes into default virbr0. We know it from the first very first day. But, we were doing was that we deleted it from virbr0 and add it in SW-1 / SW-2 etc, their macs somehow changes. And the change was very minor, only  1st octet, whose consequence was that, machine pings to some unknown mac address. Hence, host became unreachable.

Task - 3: Fix It Now
====================

I think its obvious now, what will be the next task. “How to Fix it”.
The solution might be that somehow we edit the .XMLs of VMS in a way that our domain automatically added to bridges (SW-1, 2 ) etc. despite of adding to virbr0.

We edit the XMLs in following fashion:

========================================
**Before:**
=========================================    

</controller> 
    <interface type='network'> 
      <mac address='52:54:00:0c:cf:7c'/> 
      <source network='default'/>

=========================================
**After:**
========================================

</controller> 
    <interface type='bridge'> 
      <mac address='52:54:00:0c:cf:7c'/> 
      <source bridge='SW-1'/> 

=========================================  

It works fine, now each domain/NIC automatically added to its corresponding switch/bridge. 
We also configure the IP's and net masks of switches to an un-useable IP addresses in order to ssh from host working machine (Ubuntu 14.04.3).
Yes, all the things were working properly.

Task - 4: Inter-subnet communication  
====================================

Uptil now, we have checked the the intra-subnet communication. Now check, is our script is working fine for inter-subnet communication.

Things to learn here:
- ARP cache			http://www.thegeekstuff.com/2012/01/arp-cache-poisoning/
		
- What is function of router     http://www.thegeekstuff.com/2012/04/route-examples/

- What is routing table. 
- What steps are involved for inter-subnet communication
- What are the chances of hacking

**Hint:** Before moving onward just ON the ip-forwarding on router VM.

``Echo 1 >  /proc/sys/net/ipv4/ip-forwarding``

Check, now all subnets can communicate with each other subnet.

Task - 5: Different possibilities for communication in sub-netted network
=========================================================================

Case - I: Intra-Subnet
----------------------

- H1 (subnet-1) ---> H2 (subnet-1)	Communication through bridge

- Broadcast ARP request

- ARP reply by the required IP host H2 having its MAC address.

Case - II: Inter-Subnet But Different Switches
----------------------------------------------

- H1 (subnet-1) SW-1 ---> H2 (subnet-2) SW-2	Communication through Router

- Broadcast ARP request

- No reply 

Handed Over to router (Gateway) –----> subnet mask & IP (See Routing Table) –--> Get network interface (eth-1) –--> SW2 (Broadcast and get reply) 

Case - III: Inter-Subnet But Single switch 
------------------------------------------

- H1 (subnet-1) SW-1 ---> H2 (subnet-2) SW-1	Communication not possible

- Broadcast ARP request (127) but didn't reach t0 H2 (130)

- No reply

Case - IV: Inter-Subnet But Single switch (possible by hacker) 
--------------------------------------------------------------

- H1 (subnet-1) SW-1 ---> H2 (subnet-2) SW-1	Communication  possible

- Hacker change the IP and net mask as that of subnet-1 (say 124 – free host IP)

- Broadcast ARP request (127) but  reach to H2 (124)

- Reply

Task - 6: Inter-Router Communication 
====================================

Uptil now, we have only 1 router with 12 interfaces, means 10 departments or 20 hosts are handled by only one router.

Now in order to learn the inter-router communication, split the network into 2 parts. 

.. _inter_router_comm:
.. figure::  images/INTER_ROUTER_COMM_04.png
   :align:   center

   **Inter-Router Communication Architecture**

#. 5 switches should be handled by Router-1 on first PC. 5 switches should be handled by Router-2 on 2nd PC.

#. Both the PC's are interconnected using LAN cable.
    The hierarchy will be like:
	Router-1 ----> EDGE_SWITCH_1 ----> eth0 ----> eth0----> EDGE_SWITCH_2 ----> Router- 2
	(192.168.7.1)	(192.168.7.2)					(192.168.7.3)		(192.168.7.4)

#. Now copy the desired KVM's .xml's and .img's from PC-1 to PC-2 using SCP command.

	SCP -C __________________________________ (because -c will increase the speed up to a reasonable extent).

#. Now, we have to work carefully. Because, the enviroment in the .xlm's was according to the PC-1. Now, we have to edit its path of .img (where domain.img is copied).

**Steps to run a KVM that was running in 1 PC to run it on another PC:**

**- virsh define domain.xml**
  The line that can cause error are most likely to be following in .xml file. Do concentrate on it.
     
			``<type arch='x86_64' machine='pc-i440fx-trusty'>hvm</type>``
  
Just check that PC-2 should have same architecture. Machine variable should be supported otherwise replaced by a supported one. In my case supported machine was not present in PC-2. 

**I got this error:**

  error: internal error: process exited while connecting to monitor: qemu-system-x86_64: -machine pc-i440fx-trusty,accel=kvm,

  Use -machine help to list supported machines!

  Therefore, I replaced the variable with   
			``machine='pc-i440fx-2.0' <emulator>/usr/bin/kvm-spice</emulator>``

Must check the kvm-spice binary should installed on PC-2. Otherwise install it or replace it with installed one.

I have replaced the binary
			 ``<emulator>/usr/bin/kvm</emulator>``
  	
			``<source file='/home/ahmer/VMS/web-server/ubuntu-kvm/tmpgStITZ.qcow2'/>``

Must check your path for the desired .qcow2 or .img

**- Virsh create domain.img**

Now, you are able to use your KVM.

#. Now, SW-1 -------- SW-5 are handled by Router-1 and SW-6 ------- SW10 are handled by Router-2.
    You can easily ping between the hosts of same router and but not to the host of other router.

#. How we can make this communication possible?
    **Hint:** Learn routing tables and route -n
   
    As communication between subnets are done based on the routing table. If you check the routing table in either machine, you will not find the IP addresses of the other router subnets of course. You have to add them manually.

Let's move step by step.

- Check that can you ping 192.168.7.1, 2, 3, 4 from either side? If yes then nice, because you have a successful connection between both the PC's. If not, then problem is that your Ethernet ports are interconnected, hence, no path to access the hosts of other router.

- Now, learn this concept that in order to access PC-2 from PC-1 your gateway is 192.168.7.4, and 192.168.7.1 vice versa.

1. Add 5 routes of Router -2 on Router-1 as follows:

=====================================================================================

	route add -net 192.168.5.236 netmask 255.255.255.240 gw 192.168.7.4  

	route add -net 192.168.6.0 netmask 255.255.255.128 gw 192.168.7.4

  	route add -net 192.168.6.32 netmask 255.255.255.128 gw 192.168.7.4

	route add -net 192.168.6.64 netmask 255.255.255.128 gw 192.168.7.4

	route add -net 192.168.5.72 netmask 255.255.255.128 gw 192.168.7.4

=====================================================================================

Have you checked that all have same gateway. Because, gateway address must present in the broadcast of router-1

2. Similarly, add the routes on the Router-2, all have the gw=192.168.7.1

Now, check that we should be able to communicate over the LAN. I have first time, because after copying the router KVM, I have note change the MACs of the NIC's of router-2. Hence both of the routers were working with same MACs that results in no communication. One more thing, we should kept in mind, IP forwarding variable should be 1, because it can change, when you reboot the Router.

The solution was that change the MACs of Router 2 and must be unique. Check IP forwarding and setting it permanently 1 even after rebooting the KVM.

``Sysctl -a | grep forward``

``vim /etc/sysctl.conf & set IP-forward =1``

Now, you are able to communicate.

**Practice:** Figure out all the variables that are changed automatically when you reboot the system. Add them to rc_local or some other script that runs automatically when a system is booted.


