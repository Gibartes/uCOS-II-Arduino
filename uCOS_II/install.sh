#!/bin/bash

echo -e "Installing uCOS-II libraries..."
mkdir ~/Arduino/libraries/uCOS_II
if [ $? -gt 0 ];then
	read -p  "Are you sure to overwrite uCOS_II? [y/n]" yn
	case $yn in
		[Yy]* ) 
			cp -rf * ~/Arduino/libraries/uCOS_II
			if [ $? -gt 0 ];then
				echo -e "Failed to install uCOS_II library for Arduino."
				exit 1
			fi
			break;;
        * ) echo -e "Canceled.";;
	esac
	exit 0
fi
cp -rf * ~/Arduino/libraries/uCOS_II
if [ $? -gt 0 ];then
	echo -e "Failed to install uCOS_II library for Arduino."
	exit 1
fi
echo -e "Successfully installed."
exit 0
