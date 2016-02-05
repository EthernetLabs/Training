.. _chapter9:

=========================
Chapter 9: Jenkins Slave
=========================

The purpose of this Virtual Machine is to provide Jenkins CI Slave service to the Jenkins Master service on CI VM.


Overview
--------

Jenkins Slave works with Jenkins Master service running on the CI VM. 

Software used is ``Jenkins``.



Configuration Details
---------------------

The VM is configured according to parameters defined in the tables as under.

+--------------------------------------------------------+
| | Network Connectivity for Virtual Machine             |
+=============+==========================================+
| IP ADDRESS  | | 192.168.100.18                         |
|             | |                                        |
|             | | Alternate address may be assigned at   |
|             | | build time as a parameter to script    |
|             |   ``build.sh``                           |
+-------------+------------------------------------------+
| MAC ADDRESS | | Randomly generated at the time of      |
|             | | provisioning                           |
+-------------+------------------------------------------+


+--------------------------------------------------------------------------------------+
| | Network Services                                                                   |
+=============+=============+==========+===============================================+
| **Service** | **Protocol**|**Port**  | **Configuration Files**                       |
+-------------+-------------+----------+-----------------------------------------------+
|SSH	      |TCP	    |22	       | | /etc/ssh/sshd_config                        |
+-------------+-------------+----------+-----------------------------------------------+
|JENKINS      |TCP	    |8080?     | | ?                                           |
+-------------+-------------+----------+-----------------------------------------------+


Functions of Virtual Machine
----------------------------

* Provides Jenkins build services to Jenkins Master
* Works transparently to the users and applications on the network


You may logon to Jenkins Web UI using a web browser:

`http://192.168.100.18:8080/ <http://192.168.100.18:8080/>`_

