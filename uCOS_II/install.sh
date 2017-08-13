#!/bin/bash

LPATH=~/Arduino/libraries/uCOS_II

echo -e "Installing uCOS-II library..."
if [ -d ${LPATH} ];then
	read -p  "Are you sure to overwrite uCOS-II? [y/n]" yn
	case $yn in
		[Yy]* ) 
			cp -rf * ${LPATH}
			if [ $? -gt 0 ];then
				echo -e "Failed to install uCOS-II library for Arduino."
				exit 1
			fi;;
        	   * ) echo -e "Canceled.";;
	esac
	exit 0
fi
mkdir -p ${LPATH}
cp -rf * ${LPATH}
if [ $? -gt 0 ];then
	echo -e "Failed to install uCOS-II library for Arduino."
	exit 1
fi
echo -e "Successfully installed."
exit 0
