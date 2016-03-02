.. _week-14:

Week-14 Linux IoT Training
**************************

System Network Management Protocol - SNMP 
=========================================

#. **What is SNMP? Basic understanding of SNMP.**

http://www.thegeekstuff.com/2012/09/snmp-introduction/
https://www.digitalocean.com/community/tutorials/an-introduction-to-snmp-simple-network-management-protocol

#. **How to Configure SNMP Manager and SNMP Agent in Linux?**

https://www.digitalocean.com/community/tutorials/how-to-install-and-configure-an-snmp-daemon-and-client-on-ubuntu-14-04

Basic Understanding and Configuration of Ansible Tool in Linux
==============================================================

http://www.tecmint.com/install-and-configure-ansible-automation-tool-in-linux/
http://www.tecmint.com/install-and-configure-ansible-automation-tool-in-linux/2/

#. **How to Use Ansible Playbooks to Automate Complex Tasks on Multiple Remote Servers**

http://www.tecmint.com/use-ansible-playbooks-to-automate-complex-tasks-on-multiple-linux-servers/

#. **How to change directory for ansible hosts and playbooks.**

`ansible-playbook -vvv -i ~/Ahmer/Techknox/ansible/hosts ~/Ahmer/Techknox/ansible/playbooks/apache.yml`

What is Linux HA
================

A way for the cluster to communicate about its state and configuration, this is called a cluster messaging layer. 
A way to automatically manage the resources of the cluster, the cluster resource manager (CRM). 
Some kind of middle ware between the resource manager and the actual resources, sometimes called resource agents. 


http://frankgroeneveld.nl/2014/03/23/basic-concepts-of-high-availability-linux/
https://www.howtoforge.com/high_availability_heartbeat_centos

Amazon Web Service (AWS)
========================

Learn AWS in detail as well its cli tool to manage the AWS utilities from command line.
How to manage its EBS, VM instances, Queues etc.

Learn in Detail about Apache
============================

Web-Proxy (Forward & Reverse)
+++++++++++++++++++++++++++++

http://linuxpoison.blogspot.com/2010/01/configuring-apache-as-forward-reverse.html
https://www.digitalocean.com/community/tutorials/how-to-use-apache-http-server-as-reverse-proxy-using-mod_proxy-extension

NGINX
=====

#. **Look into NGINX**

SQUID - A Proxy Server
======================

#. **Basic Understanding of Proxy Web-Server**

http://www.brennan.id.au/11-Squid_Web_Proxy.html

#. **whatis.techtarget.com/definition/Squid-proxy-server**

#. **How to use and configure Squid Proxy Server?**

https://help.ubuntu.com/lts/serverguide/squid.html
http://www.computersecuritystudent.com/UNIX/UBUNTU/1204/lesson12/
https://www.linode.com/docs/networking/squid/squid-http-proxy-ubuntu-12-04
http://www.cyberciti.biz/faq/linux-unix-clearing-squid-proxy-cache-and-recreate-dirs/
http://www.tecmint.com/configure-squid-server-in-linux/

#. **How to ban Particular Websites?**

Vim /etc/squid3/squid.conf

http://www.thegeekstuff.com/2010/09/squid-control-internet-access/

http_port 8020 

visible_hostname LITproxy 

acl client src 192.168.10.19 

acl ban_domains dstdomain "/etc/squid3/ban_domains" 

http_access deny ban_domains client 

http_access allow client 

Icinga - 2
==========

Basic Hands on Experience on Icinga - 2


Jenkins
=======

Basic learning of Jenkins tool for automatic build and deployemnet in a huge network.

- Write a jenkins job for automatic build of our Linux IoT Gateway firmware.

