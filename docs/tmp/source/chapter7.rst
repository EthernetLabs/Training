.. _chapter7:

===============
Chapter 7: TRAC
===============

The purpose of this Virtual Machine is to provide Bug Tracking services to users and computers on your network.


Overview
--------

The VM provides an interface to Git, an integrated Wiki and convenient reporting facilities.

Software used is ``Trac`` by Edgewall Software.


Configuration Details
---------------------

The VM is configured according to parameters defined in the tables as under.

+--------------------------------------------------------+
| | Network Connectivity for Virtual Machine             |
+=============+==========================================+
| IP ADDRESS  | | 192.168.100.17                         |
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
|TRAC         |TCP	    |80/443    | | /etc/apache2/sites-available/trac.conf      |
+-------------+-------------+----------+-----------------------------------------------+
|MYSQL	      |TCP	    |3306      | | /etc/mysql/conf.d/marlysys.cnf              |
+-------------+-------------+----------+-----------------------------------------------+


Functions of Virtual Machine
----------------------------

* Provides Issue and Bug Tracking services
* Provides Wiki services
* Integrates with SMTP service on SMTP VM to generate emails based on workflows configured
* Uses MySQL VM (described in Chapter 6 of this document) for storing data
* Authenticates with LDAP using the LDAP-Server VM described in Chapter 7 of this document
* A script is provided to create tickets ``~/Ticket2Trac.py``, run with ``-h`` parameter for Help


Access the VM Web Console to configure TRAC, password is set as the default ``pAssw0rd`` on first boot.

Logon to the URL using a web browser: `http://192.168.100.17/trac/ <http://192.168.100.17/trac/>`_

Provide the username and password with the defaults ``hdumcke`` and ``pAssw0rd``, when prompted for by the web browser.

You should be able to login successfully.

