.. _chapter2:

==============
Chapter 2: DNS
==============

The purpose of this Virtual Machine is to provide Domain Name Services to other VMs, and users of Work Package 1 on your network.


Overview
--------

The DNS software used is ``BIND`` by ISC. 


Configuration Details
---------------------

The VM is configured according to parameters defined in the tables as under.


+--------------------------------------------------------+
| | Network Connectivity for Virtual Machine             |
+=============+==========================================+
| IP ADDRESS  | | 192.168.100.11                         |
|             | |                                        |
|             | | Alternate address may be assigned at   |
|             | | build time as a parameter to script    |
|             |   ``build.sh``                           |
+-------------+------------------------------------------+
| MAC ADDRESS | | Randomly generated at the time of      |
|             | | provisioning                           |
+-------------+------------------------------------------+


+--------------------------------------------------------------------------+
| | Network Services                                                       |
+=============+=============+==========+===================================+
| **Service** | **Protocol**|**Port**  | **Configuration Files**           |
+-------------+-------------+----------+-----------------------------------+
|SSH	      |TCP	    |22	       | | /etc/ssh/sshd_config            |
+-------------+-------------+----------+-----------------------------------+
|DNS	      |UDP	    |53	       | | /etc/bind/named.conf            |
|             |             |          | | /etc/bind/named.conf.options    |
|             |             |          | | /etc/bind/named.conf.local      |
|             |             |          | | /etc/bind/zones/*               |
+-------------+-------------+----------+-----------------------------------+


Functions of Virtual Machine
----------------------------

* Perform DNS lookups
* Act as an SOA for locally defines Zones
* Optionally Integrate with other secondary DNS Servers on the network, this requires additional configuration


