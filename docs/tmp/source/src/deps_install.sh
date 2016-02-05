#!/bin/bash
#
# Author: Weqaar Janjua (wjanjua@marlysys.com)
#
# Copyrights: Marlysys
#
# Date: 20 MAY 2015
#
# Version: 0.2
#
# Description:
# Script for automated install of dependencies

MARLYSYS_USERNAME="marlysys"

export DEBIAN_FRONTEND=noninteractive
_PKGS=( 'python' 'python-dev' 'apt-cacher-ng' 'python-vm-builder' 'qemu-system' 'openvswitch-ipsec' 'build-essential' 'git' 'm4' 'gcc-multilib' 'libxml2-dev' 'libxslt1-dev' 'python-lxml' 'firefox' 'xvfb' )
for package in "${_PKGS[@]}"; do
	if [ `dpkg -s ${package} >/dev/null 2>&1;echo $?` -ne 0 ]; then
        	echo "required package: ${package} not found, installing..."
        	sudo apt-get -qq -y install ${package} >/dev/null 2>&1
	else
        	echo "required package: ${package} already installed."
     	fi

echo "Initializing Marlysys Git Repositories under /opt/marlysys ..."

cd /opt
if [ -d marlysys ]; then
	sudo rm -rf marlysys >/dev/null 2>&1
	sudo mkdir marlysys
	sudo chown -R `whoami`.`whoami` /opt/marlysys
fi

cd marlysys
git clone ${MARLYSYS_USERNAME}@ci.marlysys.com:/git/tools/kvm-tools.git

done

