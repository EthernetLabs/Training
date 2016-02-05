.. _chapter-1:

LINUX IOT - LIT
***************

INTRODUCTION
------------

LIT is an open source project on **Internet of Things (IoT)**. It consist of **Wireless Sensor Network (WSN)**, a **gateway (GW)** device, a **Web-Service** for the end users or clients.

WSN consists of 8 sensor nodes, that gathers different sensing information from its environment like light intensity, pressure, distance etc. There are two routers in WSN for the nodes that are out of sight for any sending node.  All the nodes in WSN are functional under **Real – Time Operating System (RTOS)**. The GW device is based on Linux, that gathers information for each node in the WSN. We will build our own Network Stack for the communication in WSN. The other task of GW is to pass the information to a web-service that is also running under Linux OS.

Web service will reshape the information in readable form, so that the end-user can read it using his web-browser. From here, the project can be extended in a way that user/client can be able to perform a certain task based on the information. For example, a sensor node SN1 that is mounted in a room tells the user that its 45 degrees temperature in the room. Now, user can send a command to **ON** the AC. After 30 minutes, he checked that temperature is normal 25 degrees now. He can **OFF** the AC, if he desires.

The LIT architecture shown below, clearly describes the flow of the project and also provide a little insight to each component of the architecture.

.. _ARCH:
.. figure::  images/LIT_ARCH.png
   :align:   center
 
   LIT Project Architure
   
