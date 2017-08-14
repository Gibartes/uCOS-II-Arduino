
# uCOS-II-Arduino_Due

MicroC/OS for Arduino boards based on ARM Cortex M3 like Arudino Due. This source code should be used just for education or research according to uC/OS-II's licensing terms.

Of course, you can use this source codes for other boards as downloading generic version (uCOS-II_generic file). 

2017.08.04 Revised by HongKyun, Gibartes

email : konm2000@hotmail.com

*********************************************************************************************************

# Install uCOS-II library for Ardunino IDE in Linux

   
* Method 1)
  
  Download file and unzip uCOS-II directory to ~/Arduino/libraries 
  
  or type below command unless downloaded file with git-clone
  
  cd uCOS-II-Arduino-master/uCOS_II ; bash install.sh ; cd -
  
* Method 2)
  
  Just copy one line command as follows :
  
  git clone https://github.com/Gibartes/uCOS-II-Arduino.git ;
  cd uCOS-II-Arduino/uCOS_II ; bash install.sh ; cd -
  
    
  
# Install uCOS-II library for Ardunino IDE in Windows

  Copy or unzip uCOS-II folder to C:\Users\\[Your ID]\Documents\Arduino\libraries
  

# Usage

  Just include ucos_ii.h
  
  \#include <ucos_ii.h>

*********************************************************************************************************
