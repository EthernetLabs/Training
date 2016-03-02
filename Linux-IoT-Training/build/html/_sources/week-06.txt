.. _week-06:

Week - 6 Linux IoT Training
***************************

For better understanding OSI model, read the `OSI Model Analogy <http://www.tcpipguide.com/free/t_UnderstandingTheOSIReferenceModelAnAnalogy.htm>`_

Task - 1: Basic Overview on TCP-IP Protocol Suite
================================================

TCP-IP is considered as 4 layer system. 

========================		================================
Application 				Telnet, FTP, e-mail, etc. 
Transport 				TCP, UDP 
Network 				IP, ICMP, IGMP 
Link 					device driver and interface card
========================		================================

**Link Layer: Media Details**

Hardware details for physically connecting or interfacing with cable or any other media.

**Network Layer**

Routing or forwarding of packets intra or inter networks.

**Transport Layer**

Control flow of data between two hosts.
The major difference between network layer and transport layer is that transport layer decide how and what data has to be transmitted (connection or connectionless) while network layer decide which route  should be taken to deliver the message to destination.
 
**What is Internet?**

Internet is collection of different networks that uses the same protocol suite. Router is a special purpose hardware device that is used to connect two or more networks. Hence, Internet is totally inter-connected using routers. 


**What is the worth of Internet? Why a whole country uses the same network doesn't make sense?**

If there was only one network in Pakistan or any other country, then all the companies will have a central administration that can make too mess and security problems. Now, each company has 	its own network, and has administration rights as well.

**Routers**

One special thing about routers that they provide connections to many different type of physical networks e.g. Token Ring, Ethernet etc. The Figure below explains it up to reasonable extent. 

One of the goal of Internet is to hide the all the details of physical layout of Internet from applications.  
     
**Bridges**

Another way to connection is bridge. Bridge is link-layer device while the router is network-layer device. Bridges make multiple LAN's appear to the upper layer as single LAN. 

**Encapsulation**

An application sends data using TCP, the data is sent down the protocol stack. Each layers adds its information to the data in the form of headers. The unit of data that TCP sends to IP, is called TCP segment. IP sends to network interface (link layer), is called IP datagram. The stream of bits that flow across the Ethernet, is called frame.

A physical property of Ethernet frame is that its data size must between 46 – 1500 bytes. 

**DATA-LINK LAYER**

**Purpose**

#. Send or receive IP datagrams for IP module.

#. ARP request and reply

#. RARP requests and reply

ARP and RARP is basically the map between the 32-bit IP address and 48-bit MAC address.

Task - 2: NETWORK LAYER
=======================

Every device that communicate over a network has an logical address. It is called IP address or layer-3 address. This address should be unique because it is the identity of a user in a particular network. Hence Network layer has following jobs:

#. Logical Addressing

#. Forwarding and Routing

#. Datagram Encapsulation

#. Fragmentation and Reassembling

The normal size of IP header is 20 bytes.


IP Header (Big Endian Ordering)
-------------------------------

Note: For machines that use little endian format, should convert headers in network byte order (command: htons in c).   

=============================	       =======		==================================================================================================================

**4B - 0**
	IP version 			0:3 		4

	Header Length			4:7		maximum (4*15 = 60 bytes) 	Normal  (4*5 = 20)
	
	Type of Service			8:15		0x00 (Delay, Throughput , Reliability Services)
	
	Total Datagram Lentgh		16:31		Data + Header
	
**4B - 1**
	Identification 			0:15		Number each datagram, usually increments during fragmentation
	
	Flag				16:18		0 normally
	
	Flag Offset			19:31		0

**4B - 3**
	Time To Live			0:7		Set upper limit on routers through which datagram can pass. It decrements at every router and datagram thrown away 							  when counter reaches to 0 and sender is notified by an ICMP message.

	Protocol			8:15		For demultiplexing at destination, what type of data 	

	Header Checksum			16:31		Checksum calculated for the Header, stored here

**4B - 4**
	Source IP			0:31

**4B – 5**
	Destination IP 			0:31 


**4B – 6**
	Options

=============================	       =======		==================================================================================================================

**i. Options**
	
Security and Handling  Restrictions – Military Applications

**ii. Record Route – Each router record its IP address**

Ping gives us an opportunity to look at the IP record route (RR) option. Most versions of ping have -R option to enable the record feature. This causes every router that handles the IP datagram (contains ICMP echo request message) to add its IP address to a list in the options. When datagram reaches to final destination, a list IP addresses should be copied into the outgoing ICMP echo reply, and all routers on the return path add their IP address into the list. When PING receives echo reply, prints the list of IP addresses.

**Problem**
	
The biggest problem in using this feature is that we have limited room in IP header for list of IP addresses. A maximum header length can be (4 * 15 = 60 bytes). 20 bytes are reserved for normal IP header, 3 bytes for RR option overhead. Hence, 60 - 20 - 3 = 37 bytes remaining. Therefore, only 37/4 = 9 IP addresses can be stored in the IP list.

**Code:**

*Option:*	Type. For RR code = 7

*Len:*		Total number of bytes for RR option. In this case len = 39.

*ptr:* 		pointer → IP address (4,8,12, . . .)  

**iii. Time Stamp**

 
Before going to next option. We should know what is source routing?

**What is Source Routing?**

Normally, IP routing is dynamic with each router making decisions about next hop, where to send the IP datagram. Applications have no control on this and are normally not concerned with it. The idea behind the source routing is, sender specifies the route. 
  
**iv. Loose Source Routing**

IP datagram should at least traverse from the IP addresses specifies by the sender. But, it can also pass through other router between two specified IP addresses in the list.  

**v. Strict Source Routing**

IP datagram could not pass through other routers. 

**Code**
 
		0x83 = loose source routing
		0x87 = strict source routing

IP Routing
----------

It is simple for a host, when destination is directly connected to the host (point-to-point link) or on shared network (Ethernet, Token ring etc). Datagram is sent directly to the destination. Otherwise, the host sends the datagram to default router, and router delivers the datagram to its destination.

In general, IP receives a datagram form TCP, UDP etc to send or from network interface (to forward). IP layer has a routing table in memory, that it searches each time it receives a datagram to send. When a datagram received from network interface, IP first checks, destination IP is its own IP address or IP broadcast address.

IP routing performs the following actions:

#. Search the routing table = = Network ID and Host ID (Complete destination IP). If found send packet directly to the next hop or directly connected interface. PP link are found here.

#. Search the routing table = = Network ID (Ethernet / Token ring).

#. Routing table = = Default.

ARP – Address Resolution Protocol
---------------------------------

APP Cache: IP address →  MAC Address

Ethernet frame (ARP) Type →  0x0806


Understanding: Network Layer
----------------------------

We have ended our last by developing strong concepts on physical and Link Layer. Now, learn the Network Layer in detail.

#. Basic jobs of network Layer

#. IP Datagram Layout

#. Strong Concepts on each field in IP header.

#. Normal Header Length of IP datagram  

#. Options that can be used if desirable.

	- Record Route (with header formats)

	- Time Stamp

	- Loose Source routing

	- Strict Source Routing

#. 	What is difference between Forwarding and Routing.

#. 	Routing Tables and actions they perform

#. 	ARP – Address Resolution Protocol

Task - 3: Raw Sockets
=====================

**What are raw sockets. Why they are used?** 

Raw sockets are low level sockets to send one packet at a time. All the protocol headers are filled by the user, instead of kernel, in order to get strong grip on each protocol header.

**Write a raw socket program that fills the UDP/TCP segment and IP datagram according to our will and transmit over the network to a specific destination. After transmission, sniff that packet using Wire-shark, that same packet is received that we have transmitted over the network.**

**Helpful link:** http://www.tenouk.com/Module43a.html   

Task - 4: Transport Layer
=========================

Transport layer provides the logical communication. Logical communication means process to process as IP layer do communication host to host.

**Analogy**

Lets consider a company “IoT” Head Office with 100 employees in Dublin. A sub-office with 100 employees in Cape Town. Its time, when there was only post service for sending messages in form of letters. Suppose, every day each individual writes a message to an individual in other office. In both office Ali and Akbar respectively has responsibility to receive and send letters from courier service, handed it over to each individual and receive theirs to post.

========================		============================
TCP/IP Stack				Real-Life Stack
========================		============================
Application				Letters in envelopes
Processes                              	Each individual is a process
Hosts                                   Offices
Transport Layer Protocol                Ali & Akbar
Network Layer Protocol 		 	Post Service
========================		============================

Transport Control Protocol - TCP
--------------------------------

Analogy
+++++++

Ali and Akbar are reliable resource, because they take time to analyze how to deliver the letters to the respective individuals without any mistake. Here, time is the constraint.

Networking
++++++++++

**Reference:** The protocols TCP/IP Volume-1 by Stevens – Chapter # 17, 18]

User Datagram Protocol - UDP
----------------------------

Analogy
+++++++

Ahmad or Akram works in the absence of Ali and Akbar. They always remain in haste, and  delivers letters without any analysis or plan. Hence, individuals get their messages instantly. But the drawback is that in haste they do mistakes in proper delivery.

Networking
++++++++++

UDP is connectionless and unreliable transport layer protocol. Its sends the datagram that application writes to IP layer, with no guarantee that it reaches the destination or not.

.. _udp_header:
.. figure::  images/UDP_HEADER.png
   :align:   center

   UDP Header Format

**Port numbers**

Identify the sending and receiving processes. The TCP port numbers are independent of UDP port numbers. If a service can provide both  TCP and UDP, port numbers can be same.

**Length**

UDP header length. The minimum value of this field is 8-bytes.

**Checksum**

UDP checksum field covers both UDP header and data unlike the checksum in IP datagram that only covers datagram header.

With UDP checksum is optional while with TCP checksum is mandatory.

Length of UDP datagram can be odd number of bytes. The solution is to append a pad byte of 0's to the end. For 16 bit word checksum calculation.

Both TCP and UDP include 12 byte pseudo header with UDP datagram, just for checksum calculation.

.. _udp_check_header:
.. figure::  images/UDP_CHECKSUM_HEADER.png
   :align:   center

   UDP Header For Checksum Calculation


Understanding: Transport Layer
------------------------------

#. Relationship between Transport Layer and Network Layer.

#. Difference between them.

#. What is difference between UDP and TCP.

#. UDP Header Format

#. What is the difference between the checksum of IP layer and UDP/TCP layer.

#. What are port numbers and IANA.

#. Basic services of TCP

#. TCP Header

#. What is ISN

#. Sequence number and acknowledgement number.

#. Flags: SYN, FIN, RST, PSH, URG, ACK

#. Connection Establishment Protocols (3 way handshake)

#. Termination Protocol

Task – 5: Socket Programs (TCP – UDP Clients and Servers)
=========================================================

Write a UDP client-server that client sends a string to server and server convert it into capital letters and send back to the client. After successful implementation check the packet in Wire-shark and check your understanding. If server is off, still packet can be sniffed or not by wire-shark that is sent by client. (YES) 

Write same utility using TCP and check your understanding again about.
  
   Note down the following

	- flags that we have learn.

	- Sniff packet when client just started. (See is there 3 way handshake)

	- Clear the results, now sniff when client try to use server utility by sending data.

	- Clear the results, shutdown the server and sniff again. (Terminating protocol should be noticed) 
	
