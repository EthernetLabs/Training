.. _week-12:

Week 11-12 Linux IoT Training
*****************************

.. _GW_frame_:
.. figure::  images/GW_FRAME_LIT.png
   :align:   center

   **Frame Structure for WSN Gateway Firmware**

Frame Definition
================


===========================     ========== ========= ============== ============= =========== =============== ======== =============== ========== ======== === =========
Description			Network-ID Source-ID Destination-ID Physical-Type Device-Type Type-Of-Message Priority Sequence-Number PDU-Length PDU-Type PDU Encrytion 
Field				NET-ID     SRC-ID    DEST-ID        PHY-TYPE      DEV-TYPE    TOM             PRIO     SEQNUM          PDU-L       PDU-T   PDU ECC
Variable (V) / Fixed Length     F          F         F              F             F           F               F        F               F           F       V   V
Byte Length                     2          2         2              1             1           1               1        2               1           1       80  2

===========================     ========== ========= ============== ============= =========== =============== ======== =============== ========== ======== === =========

Total Length: 16 - 96 Bytes                                         


Valid PHY-TYPE Values
=====================

========     ================   ==============================================
PHY-TYPE     Description	PDU
========     ================   ==============================================
Z            ZigBee: 802.15.4   
W            Wireless: 802.11
E            Ethernet: 802.3    - P : PIR 
                                - A : Acoustic
                                - S : Siesmic
                                - V=Video   

========     ================   ==============================================


Valid DEV-TYPE Values
=====================

========     ================   
DEV-TYPE     Description
========     ================   
S            Sensor
R            Router
G            Gateway
C            Client-Computer

========     =================


Valid TOM Values
================

================	===========================================  =======================================================================================
TOM     		Description				     PDU
================	===========================================  =======================================================================================
T			Time Synchronization
I			Sequence Number & Increment Synchronization  
P			Type Of Power Source                         - B : Battery
								     - M : Main
B			Battery Information (%)			     
H			Heart-Beat
S			State Of Device                              - O : OFF 
								     - N : ON 
								     - D : DEBUG 
								     - L : GPS Locking 
                                                                     - F : GPS Lock Fail 
                                                                     - S : SLEEP 
                                                                     - W : WAKEUP 
R			Registration / Authentication                
W			Wireless                                     - S : Strength 
								     - I : Internal Antenna 
                                                                     - E : Externel Antenna 
                                                                     - T : Transciever Power

================	===========================================  =======================================================================================


Valid SEQNUM Values
===================

========  ================================================
SEQNUM    Description
========  ================================================
S         Start Sequence Number (randomly generated) 0-255
I         Increment in Sequence Number (random) 0-25

========  ================================================







