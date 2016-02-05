#!/bin/bash
#
# Author: Weqaar Janjua (wjanjua@marlysys.com)
#
# Copyrights: Marlysys
#
# Date: 20 MAY 2015
#
# Version: 0.1
#
# Description:
# Script for setting up RSA Key-pairs

MARLYSYS_USERNAME="marlysys"

export DEBIAN_FRONTEND=noninteractive

echo "Setting up RSA Keys..."
if [ ! -f ~/.ssh/id_rsa.pub ]; then
	ssh-keygen -t rsa -N '' -f ~/.ssh/id_rsa -C "${MARLYSYS_USERNAME}@ci.marlysys.com"
fi
cp ~/.ssh/id_rsa.pub ~/vmbuilder/file_cache/authorized_keys

