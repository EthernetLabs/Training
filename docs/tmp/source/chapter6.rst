.. _chapter6:

======================
Chapter 6: LDAP Client
======================

The purpose of this Virtual Machine is to provide the client for Directory Access Protocol for testing the LDAP Server Authentication.


Overview
--------

The goal of this LDAP Client is to demonstrate a User accessing the web GUI authenticated against an LDAP server. The apache proxy server running on the VM authenticates a test user ‘hdumcke’ against the LDAP Server described in :ref:`chapter 5`. The http server may act as http proxy to Gerrit service.

List of Software used is as under:
* Apache ``Httpd``
* Apache LDAP Module ``mod_auth_ldap``
* Apache AUTHNZ_LDAP Module ``mod_authnz_ldap``


Configuration Details
---------------------

The VM is configured according to parameters defined in the tables as under.

+--------------------------------------------------------+
| | Network Connectivity for Virtual Machine             |
+=============+==========================================+
| IP ADDRESS  | | 192.168.100.7                          |
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
|LDAP Client  |TCP	    |80        | | /etc/apache2/sites-available/auth-ldap.conf |
+-------------+-------------+----------+-----------------------------------------------+


Functions of Virtual Machine
----------------------------

* Provides client for access to LDAP Directory services
* Demonstrates LDAP authentication over HTTP Protocol, users accessing the web GUI will be authenticated against the LDAP server


Access the VM Web Console to configure LDAP, username is set to ``hdumcke`` and password is set to the default ``pAssw0rd``.

Logon to the URL using a web browser: `http://192.168.100.7/auth-ldap/ <http://192.168.100.7/auth-ldap/>`_

Provide the username and password with the defaults, when prompted for by the web browser.

You should be able to login successfully.

