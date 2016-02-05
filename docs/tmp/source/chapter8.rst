.. _chapter8:

==============
Chapter 8: CI
==============

The purpose of this Virtual Machine is to provide Continuous Integration Toolchain services to users and computers on your network.


Overview
--------

The workflow of the CI (Continuous integration) Process involves ``Git``, ``Gerrit``, and ``Jenkins`` processes. CI VM implements this process.
List of software used is as under:

* Git
* Gerrit 
* Jenkins


Configuration Details
---------------------

The VM is configured according to parameters defined in the tables as under.

+--------------------------------------------------------+
| | Network Connectivity for Virtual Machine             |
+=============+==========================================+
| IP ADDRESS  | | 192.168.100.19                         |
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
|GIT          |TCP	    |?         | | ?                                           |
+-------------+-------------+----------+-----------------------------------------------+
|GERRIT	      |TCP	    |?         | | ?                                           |
+-------------+-------------+----------+-----------------------------------------------+
|JENKINS      |TCP	    |8080?     | | ?                                           |
+-------------+-------------+----------+-----------------------------------------------+


Functions of Virtual Machine
----------------------------

* Provides Git SCM Services via Gerrit gating code review system
* Provides Gerrit gating system
* Provides Jenkins job execution and CI system
* Integrates with SMTP VM for sending job status as per the workflows defined
* Integrates with the TRAC Bug Tracking system (TRAC VM) to create tickets (bug reports) based on test results from automated build


