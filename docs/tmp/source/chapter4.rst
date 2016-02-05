.. _chapter4:

================
Chapter 4: MySQL
================

The purpose of this Virtual Machine is to provide MySQL Database Back-end services to other VMs.


Overview
--------

The RDBMS software used is ``MySQL``.


Configuration Details
---------------------

The VM is configured according to parameters defined in the tables as under.

+--------------------------------------------------------+
| | Network Connectivity for Virtual Machine             |
+=============+==========================================+
| IP ADDRESS  | | 192.168.100.37                         |
|             | |                                        |
|             | | Alternate address may be assigned at   |
|             | | build time as a parameter to script    |
|             |   ``build.sh``                           |
+-------------+------------------------------------------+
| MAC ADDRESS | | Randomly generated at the time of      |
|             | | provisioning                           |
+-------------+------------------------------------------+


+-------------------------------------------------------------------------------+
| | Network Services                                                            |
+=============+=============+==========+========================================+
| **Service** | **Protocol**|**Port**  | **Configuration Files**                |
+-------------+-------------+----------+----------------------------------------+
|SSH	      |TCP	    |22	       | | /etc/ssh/sshd_config                 |
+-------------+-------------+----------+----------------------------------------+
|MYSQL	      |TCP	    |3306      | | /etc/mysql/conf.d/marlysys.cnf       |
+-------------+-------------+----------+----------------------------------------+


Functions of Virtual Machine
----------------------------

* Provides MySQL Service


Access the VM Console to setup MySQL username and password, a dialog is displayed on first boot.

The default database is set as ``trac``.

