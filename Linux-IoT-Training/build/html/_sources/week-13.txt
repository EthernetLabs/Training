.. _week-13:

Week-13 LINUX IoT Training
***************************

DATABASE CREATION , MANAGEMENT AND BACKUPS 
==========================================

On ZMQ client on one of the virtual machines VM-1 that stores the IoT Gateway Messages in a queue. Create a mysql database named “LITdb” in another VM-2 (IP = 192.168.122.10). Write a code in python in VM-1 that can connect to remote database at VM-2 and can create a table “LITFRAME” so that remote database can be updated according to the IoT Gateway Messages. We need one more VM named as VM-3 that will work as BACKUP DATABASE. Hence, it is necessary that VM-3 should sync its database with VM-2 database. If somehow, VM-2 shuts off, VM-3 will receive data and update its database, so that whenever, VM-2 wakes-up it should recover all the important messages that it have misses during the die-off period.   

.. _is_sweaty:
.. figure::  images/DATABASE_MANAGEMENT_TOPPLOGY.png
   :align:   center

Database Configuration
+++++++++++++++++++++++

VM – 1 (IP:192.168.122.13)
--------------------------

#. Install MySQL.
#. Write a python code named ZMQ_Client that receives messages from IoT Gateway. Store it in a 	queue. Then, update the local database based on that queue.
#. Code is provided on github. https://github.com/LinuxIoT/python-dev

 
VM – 2 (IP: 192.168.122.10)
---------------------------

#.Install MySQL

#. Start with editing mysql config file.
	`vim /etc/mysql/my.cnf`
	`bind-address           = 0.0.0.0`

#. Restart mysql server.
	`service mysql restart`

#. Create a database named as “ LITdb”.
	- mysql -u root -p
	- CREATE DATABASE LITdb;
	- USE LITdb;
	- Change Privileges or give privileges to remote user.
	   https://easyengine.io/tutorials/mysql/remote-access/

#. Test at remote station (VM-1) by executing following command that it can access the database 	or not.
	`mysql -h HOST -u USERNAME -pPASSWORD`

Configuring, Attacking and Securing VRRP on Linux
=================================================

We will configure VIRTUAL - IP = 192.168.122.12
http://louwrentius.com/configuring-attacking-and-securing-vrrp-on-linux.html

What is Keepalived
==================
Keepalived is a routing software written in C. The main goal of this project is to provide simple and robust facilities for load-balancing and high-availability to Linux system and Linux based infrastructures.
http://keepalived.org/

**What is the requirement for installing or running Load-Balancer like keepalived or Linux-HA?**
 Load balancing in HAProxy and Keepalived at the same time also requires the ability to bind to an IP address that are nonlocal, meaning that it is not assigned to a device on the local system. This allows a running load balancer instance to bind to a an IP that is not local for failover. 
To enable, edit the line in /etc/sysctl.conf that reads net.ipv4.ip_nonlocal_bind to the following: 
net.ipv4.ip_nonlocal_bind = 1
sysctl -p
https://access.redhat.com/documentation/en-US/Red_Hat_Enterprise_Linux/7/html/Load_Balancer_Administration/s1-initial-setup-forwarding-VSA.html

**ISCSI Initiator settings:**
https://help.ubuntu.com/lts/serverguide/iscsi-initiator.html
https://www.howtoforge.com/using-iscsi-on-ubuntu-10.04-initiator-and-target

 
VM – 3 (IP: 192.168.122.11)
===========================

Same Procedure with VM-3 as we done for VM-2.
 
   
VM – 4 (IP: 192.168.122.9)
==========================

- The two dominant IP storage protocols used in virtualization
	→ NFS
	→ ISCSI

**What is iSCSI?**

It is a network storage protocol above TCP/IP. This protocol encapsulates SCSI data into TCP packets.
https://www.howtoforge.com/iscsi_on_linux

**ISCSI – Target Installation – SERVER:**

Follow this link for server installation:
https://www.howtoforge.com/using-iscsi-on-ubuntu-10.04-initiator-and-target

sudo apt-get update
sudo apt-get install iscsitarget iscsitarget-source iscsitarget-dkms

**→ iscsitaget-source failed -  FiX**

http://installion.co.uk/ubuntu/precise/universe/i/iscsitarget-source/install/index.html

First, check that the universe repository is enabled by inspecting '/etc/apt/sources.list' with your favourite editor.
You will need to use sudo to ensure that you have permissions to edit the file.
sudo gedit /etc/apt/sources.list
If universe is not included then modify the file so that it does.
deb http://us.archive.ubuntu.com/ubuntu precise main universe
After any changes you should run this command to update your system.
`sudo apt-get update`
`You can now install the package like this.`
`sudo apt-get install iscsitarget-source`


**Again ERROR:**

user@ubuntu:~$ sudo service iscsitarget restart
 * Removing iSCSI enterprise target devices:           [ OK ]
 * Starting iSCSI enterprise target service            FATAL: Module iscsi_trgt not found.

**HOW TO FIX:**
 
http://sysadmin.wikia.com/wiki/Server_side_iscsi_linux

The error is normal, because we still didn't build the module to use for iSCSI. So, let's do it. To install this new kernel module, you will need to install two packages : 
# apt-get install module-assistant debhelper
And now, you are able to build the new kernel module to enable iSCSI target. Let's build the kernel module with this command : 
# m-a a-i iscsitarget
If all goes properly, we, now, have to load this new kernel module. Let's do it with this command : 
# modprobe iscsi_trgt
You can known configure your iSCSI target on Debian here. 




**Differences Between NFS and iSCSI**

https://www.usenix.org/legacy/events/fast04/tech/full_papers/radkov/radkov_html/node5.html
http://www.infoworld.com/article/2616802/infrastructure-storage/your-fateful-decision--nfs-or-iscsi-.html

NFS and iSCSI provide fundamentally different data sharing semantics. NFS is inherently suitable for data sharing, since it enable files to be shared among multiple client machines. In contrast, a block protocol such as iSCSI supports a single client for each volume on the block server. Consequently, iSCSI permits applications running on a single client machine to share remote data, but it is not directly suitable for sharing data across machines. It is possible, however, to employ iSCSI in shared multi-client environments by designing an appropriate distributed file system that runs on multiple clients and accesses data from block server. 
The implications of caching are also different in the two scenarios. In NFS, the file system is located at the server and so is the file system cache (hits in this cache incur a network hop). NFS clients also employ a cache that can hold both data and meta-data. To ensure consistency across clients, NFS v2 and v3 require that client perform consistency checks with the server on cached data and meta-data. The validity of cached data at the client is implementation-dependent--in Linux, cached meta-data is treated as potentially stale after 3 seconds and cached data after 30 seconds. Thus, meta-data and data reads may trigger a message exchange (i.e., a consistency check) with the server even in the event of a cache hit. NFS v4 can avoid this message exchange for data reads if the server supports file delegation. From the perspective of writes, both data and meta-data writes in NFS v2 are synchronous. NFS v3 and v4 supports asynchronous data writes, but meta-data updates continue to be synchronous. Thus, depending on the version, NFS has different degrees of write-through caching. 
In iSCSI, the caching policy is governed by the file system. Since the file system cache is located at the client, both data and meta-data reads benefit from any cached content. Data updates are asynchronous in most file systems. In modern file systems, meta-data updates are also asynchronous, since such systems use log-based journaling for faster recovery. In the ext3 file system, for instance, meta-data is written asynchronously at commit points. The asynchrony and frequency of these commit points is a trade-off between recovery and performance (ext3 uses a commit interval of 5 seconds). Thus, when used in conjunction with ext3, iSCSI supports a fully write-back cache for data and meta-data updates. 
Observe that the benefits of asynchronous meta-data update in iSCSI come at the cost of lower reliability of data and meta-data persistence than in NFS. Due to synchronous meta-data updates in NFS, both data and meta-data updates persist across client failure. However, in iSCSI, meta-data updates as well as related data may be lost in case client fails prior to flushing the journal and data blocks to the iSCSI server. 

Network Filesystem - NFS
=========================
 
https://linuxconfig.org/how-to-configure-nfs-on-linux
- `apt-get install nfs-common (Both Server and Client)`

**Server**
- `apt-get install nfs-kernel-server (Server)`
- `echo '/home/nfs/ *(ro,sync)' > /etc/exports` 
- `vim /home/nfs/nfs-test-files`
- `sudo service  nfs-kernel-server restart`

**Client**

- `mkdir /home/nfs_local`
- `mount IP-Address:/home/nfs /home/nfs_local`

