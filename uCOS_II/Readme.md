*********************************************************************************************************
#                                                uC/OS-II
#                                          The Real-Time Kernel


                              (c) Copyright 1992-2013, Micrium, Weston, FL
                                           All Rights Reserved

 
 By      : Jean J. Labrosse
 Version : V2.92.10

 LICENSING TERMS:
 ---------------
   uC/OS-II is provided in source form for FREE evaluation, for educational use or for peaceful research.
 If you plan on using  uC/OS-II  in a commercial product you need to contact Micrium to properly license
 its use in your product. We provide ALL the source code for your convenience and to help you experience
 uC/OS-II.   The fact that the  source is provided does  NOT  mean that you can use it without  paying a
 licensing fee.
*********************************************************************************************************

MicroC/OS for Arduino boards based on ARM Cortex M3 like Arudino Due.
This source code should be used just for education or research according to uC/OS-II's licensing terms.


* OS_TASK_TMR_PRIO is defined as priority 15 in cfg/oscfg.h

2017.08.04
Revised by HongKyun, Gibartes

*********************************************************************************************************

# Install uCOS-II library for Ardunino IDE in Linux

* Method 1)
  
  Download file and unzip uCOS-II directory to ~/Arduino/libraries 
  
  or type below command unless downloaded file with git-clone
  
  cd uCOS-II-Arduino_Due-master/uCOS_II ; bash install.sh ; cd -
  
* Method 2)
  
  just copy one line command as follows :
  
  git clone https://github.com/Gibartes/uCOS-II-Arduino_Due.git ;
  cd uCOS-II-Arduino_Due/uCOS_II ; bash install.sh ; cd -
  
  
  
  
# Install uCOS-II library for Ardunino IDE in Windows

  Copy or unzip uCOS-II folder to C:\Users\\[Your ID]\Documents\Arduino\libraries
  

# Usage

  just include ucos_ii.h
  
  \#include <ucos_ii.h>

