.. _appendix:

APPENDIX
********

Create Development KVM's
========================

Write a bash script that can create a KVM with a particular name, size and location using VM-Builder.

We have to create 3 KVM's for our development in IoT.

**→ PYTHON-DEV**		Python Development
**→ C-DEV**		   	C Development
**→ RIOTOS-DEV**		RIOT OS Development

Also make three repositories with the same name as kvm's have, on git-hub.

VM-Script
+++++++++

# Author: Ahmer Malik

# Company: Techknox System

# Version: 0.1

# Description:This script is used create a kvm using VM-builder. Follow the link for understanding : https://www.howtoforge.com/creating-virtual-machines-for-xen-kvm-vmware-workstation-6-vmware-server-with-vmbuilder-on-ubuntu-8.10-p2

#!/bin/bash 

# Name of KVM you want to build

VM_NAME=c-dev

# Path of KVM, where to build

_PATH=scripted_kvms/$VM_NAME

mkdir -p $_PATH/mytemplates/libvirt/

cp /etc/vmbuilder/libvirt/* $_PATH/mytemplates/libvirt/

echo root 1000 > $_PATH/vmbuilder.partition

echo swap 500 >> $_PATH/vmbuilder.partition

echo /var 5000 >> $_PATH/vmbuilder.partition

echo passwd -e ahmer > $_PATH/boot.sh

echo apt-get update --apt-get install -qqy --force-yes openssh-server >> $_PATH/boot.sh

sudo chmod +x $_PATH/boot.sh

cd $_PATH

# Commands used to create the Ubuntu:Trusty KVM
vmbuilder kvm ubuntu --suite=trusty --flavour=virtual --arch=amd64 --mirror=http://de.archive.ubuntu.com/ubuntu -o --tmpfs=- --libvirt=qemu:///system --ip=192.168.7.2  --part=vmbuilder.partition --templates=mytemplates --user=ahmer --name=ahmer --pass=ahmer --addpkg=vim-nox --addpkg=unattended-upgrades --addpkg=acpid --addpkg=linux-image-generic --firstboot=/home/ahmer/Techknox/Make_Your_KVM_script/$_PATH/boot.sh --mem=512 --cpus=1 --hostname=$VM_NAME 

Snapshots
=========

Schedule a process that runs daily at specific time and take the snapshots of all of your working KVM's. We will use **crontab** for scheduling purposes as we have done it our earlier labs. 

**What is a snapshot?**

Keeping the backup of anything, is called snapshot.


**What are different types of snapshots for qcow2 images?**

**→ VM State Snapshot**

	This will save the guest/domain state to a file. So, if you take a snapshot including VM state, we 	can then shut off that guest and use the freed up memory for other purposes on the host or for 	other guests. Internally this calls qemu monitor’s ‘savevm’ command. Note that this only takes 	care of VM state(and not disk snapshot).
	
	`virsh list (shows the list off all running guests)`
	
	**To save the state**
	
	`virsh save VM_NAME BACKUP_VM_NAME`

	**To restore the state**
	
	`virsh restore BACKUP_VM_NAME`

**→ Internal snapshot**

 	A type of snapshot, where a single QCOW2 file will hold both the **saved state** and the **delta** since that saved point. **Internal snapshots** are very handy because it’s only a single file where 	all the snapshot info. is captured, and easy to copy/move around the machines.

	**Create Snapshot**

	`virsh snapshot-create-as VM_NAME VM_NAME-DEV` 
	
	**Internal Snapshot Details**

	`virsh snapshot-list VM_NMAE`
	
	`qemu-img info ~/Techknox/Make_Your_KVM_script/scripted_kvms/python-dev/ubuntu-	kvm/tmpq0JMWS.qcow2` 

	**Delete Snapshot**

	`virsh snapshot-delete VM_NAME VM_NAME-DEV`

	**Revert Snapshot** - To Start Guest From the Saved State.
	
	`virsh snapshot-revert python-dev snap-python-dev`

For better understanding follow the following link:

http://kashyapc.com/2011/10/04/snapshotting-with-libvirt-for-qcow2-images/

https://kashyapc.fedorapeople.org/virt/lc-2012/snapshots-handout.html

 IPV6:
http://www.tutorialspoint.com/ipv6/ipv6_address_types.htm

