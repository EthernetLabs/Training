.. _week-02:

===================================
	Week - 2 Linux IoT Training
===================================

Task - 1: Signals and Traps
---------------------------

Learn different types of signals in Linux. Figure out which signals cannot be trapped. The trap-able signals were caught and performed a certain action on trapping. 

**Code:** Write a shell script that can continuously printing a “Hello-World” while it has not been caught or trapped by any or the terminate signal.

check shell script `click here <https://github.com/Ahmer-444/personal-repo/blob/master/signal-trap.sh>`_

Task - 2: Process Scheduling
----------------------------

How to schedule a process that it can run on specific times and days. Learn the man page of Crontab command in Linux. 

**Code:** Write a shell script that prints your name 100 times in .txt file specifically on every Friday. The process should execute in background.
 
.. note:: Read about special character "&" in bash

Task - 3: IPC (Pipes and FIFO's)
--------------------------------

Read about Pipes and FIFO, how they work in IPC's. The basic commands in bash for using them.

**Code:** Write a shell script to make your own output file descriptor with fd=3. It is used when 1 process writes to a pipe and another process reads to it later on.
Check shell script `click here  <https://github.com/Ahmer-444/personal-repo/blob/master/own_output_fd.sh>`_

Task - 4: Job Control Commands
------------------------------

What is job. What is the difference between job and process. Learn the basic commands in bash that are used for job control. 

Practice these commands in various scenarios.

Task - 5: Message Queues
------------------------

Read about the message queues that for what purpose they are use. Read the man pages for the different commands that are used for handling messages like mq_send, mq_receive.

Task - 6: Shared Memories
--------------------------

Learn about the benefits of shared memory and the what logical errors and flaws might cause when different processes are using same shared memory simultaneously. What techniques are used to avoid the these errors.

**Code:** Write a code to create a shared memory. A process should write a complete alphabets from A – Z on this shared memory and waits for the other process to write '*' on its 1st entry to complete its execution. Like a server is waiting for a message from client to perform a certain task.

Check shell script `click here <https://github.com/Ahmer-444/personal-repo/tree/master/Shared_Memory_Client_Server>`_

Task - 7: Process & Process Management
--------------------------------------

Learn about the process what it is? How an OS identify a process. How different processes are handled by OS ? What is priority of a process? How CPU deals with the process based on their priorities. Learn all the concepts related to process in OS. (Recommended books by instructor). 

**Practice:** All the commands related to process and priorities under different scenarios. 


Task - 8: Fork and Exec
-----------------------

How a process can start a new process. This new process is called the child process. What is the difference between exec and fork command. 

**Code:** Write a code that uses fork and exec commands. It clears the main difference between both. Sketch down the situations  which exec command is useful and where fork is better to use.

Task - 9: Semaphores
--------------------

What are semaphores. What is their advantage and why they are used for process handling in the scenarios where different process has access to the shared resources.

**Code:** Write a code that if a  process P1 is using the shared resource, no other process or P2 could not use that resource until P1 has not allowed.

Task - 10: Case Study (Mars Rover )
-----------------------------------

What happened to the MARS ROVER on the mars in its early stages. What was the fault occurred that forces engineers to rethink. State that fault. How they have fixed it out? 

**Code:**

**Part - 1:** (Priority Inversion): Mimic the same situation myself that how I can code that faulty program to see, can it really malfunctioned a system and force it to restart. How that unexpected restart would have lost a lot of useful data or information.
 
**Part - 2:** (Priority Inheritance): Now solve the problem as it was solved for Mars Rover.

To check c codes for Semaphores, Priority settings, Priority Inversion, Priority Inheritance  `click here <https://github.com/Ahmer-444/personal-repo/tree/master/Priority_Inversion>`_

Task - 11: Virtual Memory Management 
------------------------------------

Learn what is the benefit of virtual memory. Why the OS's use virtual memory. What is Paging? How virtual address is mapped into physical address. Learn about the page fault, page tables. What is the disadvantage of long page tables. How this issue can be resolved up to reasonable extent.


Useful Resources:
-----------------

**Message-Queues**

http://menehune.opt.wfu.edu/

http://linux.die.net/man/7/mq

https://www.cs.cf.ac.uk/Dave/

**FIFO/Pipes**

https://linuxprograms.

**Process Scheduling (Crontab)**

http://www.cyberciti.biz/faq/

**Process and Process Management**

Read chapter 1.1 of Linux Performance and Tuning Guidelines

Chapter 5 - Process Management of Book: linux-system-

/proc (Virtual file system):

http://www.tldp.org/LDP/Linux-

**Difference between bin and sbin**

http://blog.taylormcgann.com/

**MARS PathFinder**

http://research.microsoft.com/

http://research.microsoft.com/

**Shared Memory**

https://www.cs.cf.ac.uk/Dave/

**Fork()**

http://www.csl.mtu.edu/cs4411.

Dont use printf for fork(). use write instead.

**SSH**

http://www.linuxhowtos.org/

http://www.slashroot.in/

**Virtual Address to Physical Address**

http://www.cs.umd.edu/class/

