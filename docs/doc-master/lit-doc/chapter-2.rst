.. _chapter-2:


WIRELESS SENSOR NETWORK
***********************

The first and foremost requirement of WSN is to have the **Development Boards** integrated with sensors that can sense the different parameters you desired like **temperature, pressure and light intensity** etc. It should be wireless protocol compatible like **WIFI - 802.10.11 or ZigBee 802.15.4**. Now each development board will be consider as 1 **wireless sensor node (SN)**. Hence, we should have 10 development boards to make WSN. As it's our initial step in IoT, we will first use emulated development boards in order save time and money. After successful completion, we will deploy it on hardware.

The second requirement of WSN is to decide an RTOS that provide us an C - API for writing and managing user-space applications on the wireless nodes. 

FIT IoT-LAB
===========

Now, need of hour is to search an IoT emulated platform that can help us to deploy, run and manage our network infrastructure. `IoT-LAB <https://www.iot-lab.info/>`_ best suits us. We have selected `M3 <https://www.iot-lab.info/hardware/m3/>`_ development board as sensor nodes. M3 is also compatible with RIOT-OS.   

To download IoT-LAB: ``git clone https://github.com/iot-lab/iot-lab.wiki.git``

Let's start exploring IoT-LAB by following the `tutorials <https://www.iot-lab.info/tutorials/>`_


RIOT – OS
=========

We will be using `RIOT <http://www.riot-os.org/>`_ on our development boards because it provides C API interface and small memory footprint.

The `reason <http://www.riot-os.org/#features>`_ why we used RIOT-OS. Let's `Download <https://github.com/RIOT-OS/RIOT>`_ RIOT and start exploring RIOT by compiling its example programs. 

UDP Server in RIOT
==================

How to create multiple network interfaces in RIOT.

**Create**

- Run the RIOT/dist/tools/tapsetup/tapsetup.sh as follows
	tapsetup -c 2 (Create 2 interfaces i-e tap0 & tap1)

- If we compile RIOT for native cpu and include nativenet module.
	Make (default: native)

- How to run RIOT on a specific interface.

- Do “Up” the network interfaces using ``sudo ip link set dev tap0 up``

- Enter into examples directory, then make copy of gnrc_networking directory. Compile (make) the module & run it as ``make term PORT=tap0``

- Do “ifconfig” to see the ipv6 of the interface.

- Start the server as folows: ``udp server start 13377(port number)``. 

- Send data over the port ``udp send <ip-address of tap0> 13377 HELLO-RIOT``.

**Sniffing Packets** 

- Run the wireshark & select the interface you want to sniff. (tap0)
- On your host machine, check the ipv6 of the interface tap0.
- Now check the ipv6 in RIOT shell. There will be the difference of 1 in last octet.
- udp send <ip-address of tap0 at host> 13377 HELLO-RIOT

What You Understand
===================

RIOT
----

1. Write an user-space application in RIOT using its C-API.
2. Compile it for the native board first.
3. Run it on your Linux (native board) and test is it working?
4. If yes, then our application is ready to run on the specific board M3.
5. Compile the application for M3 or you may skip this step over to IoT-LAB.
6. If you want to compile for M3 using RIOT, download and install GCC toolchain for MSP430 according to the information provided on the website http://sourceforge.net/projects/mspgcc/.

IoT-LAB
-------

After the development has been done, test your application on test-bed (emulated M3 boards) provided by IoT-LAB.

1. Make new experiment.
2. Select the machine you required (M3).
3. Select one of servers to login into the device.  
4. Total number of machines you required.
5. Upload the firmware app.elf that was compiled by RIOT.
6. Start using your application.


