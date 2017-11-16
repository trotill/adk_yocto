# adk_yocto

# ADK (Adakta Development Kit) Yocto distribution
  
System build Linux kernel, u-boot, rootfs e.t.c  
  
Software support for devices:  
https://adakta.ru/eng/products/system-on-module-ADAKTA-mx6-iMX6  
https://adakta.ru/eng/products/ADAKTA-AMX6-server  
https://adakta.ru/eng/products/ADAKTA-AMX6-media  
https://adakta.ru/eng/products/ADAKTA-AMX6-miniPC  
  
How use?  
  
$: git clone git@github.com:trotill/adk_yocto.git  
$: cd adk_yocto/  
$: git checkout origin/pyro_adk -b pyro_adk  
$: MACHINE=adakta-adk DISTRO=fslc-x11 source setup-environment build/  
  
Then create your own distro or compile a demo:  
core-image-minimal-xfce  
core-image-minimal  
core-image-sato  
core-image-x11  
  
For example  
$: bitbake core-image-minimal  
  
Flash build/tmp/deploy/core-image-minimal-adk.sdcard.gz to uSD card.  
  
This can be done using usb-image-tools (for Windows)  
http://www.alexpage.de/usb-image-tool/download/  
  
or dd+gunzip for Linux  
$: gunzip -c core-image-minimal-adk.sdcard.gz | sudo dd of=/dev/<you device> bs=4M  
