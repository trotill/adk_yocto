# adk_yocto

# Yocto distribution for ADK (ADAKTA Development Kit)

System build Linux kernel, u-boot, rootfs e.t.c.

Software support for NXP i.MX6 series:  
<a href="https://adakta.ru/eng/products/system-on-module-ADAKTA-mx6-iMX6">System on Module based on NXP iMX6<a>  
<a href="https://adakta.ru/eng/products/ADAKTA-AMX6-server">ADAKTA Development Kit server (AMX6)<a>  
<a href="https://adakta.ru/eng/products/ADAKTA-AMX6-media">ADAKTA Development Kit media (AMX6)<a>  
<a href="https://adakta.ru/eng/products/ADAKTA-AMX6-miniPC">ADAKTA Development Kit miniPC (AMX6)<a>  
  
Software support for NXP i.MX6ULL series:  
<a href="https://adakta.ru/eng/products/system-on-module-ADAKTA-iMX6ull-nano6">System on Module based on NXP iMX6ull<a>  
<a href="https://adakta.ru/eng/products/ADK-board-ADAKTA-mx6ull">ADAKTA Development Kit mx6ull (ADK6ull)<a>  
  
How to use?  

1) Clone
$: git clone git@github.com:trotill/adk_yocto.git  
$: cd adk_yocto/  
$: git checkout origin/pyro_adk -b pyro_adk  
$: MACHINE=adakta-adk DISTRO=fslc-x11 source setup-environment build/  

2) Create your distro or compile the demo:
core-image-minimal-xfce  
core-image-minimal  
core-image-sato  
core-image-x11
For example: 
$: bitbake core-image-minimal  

3) Flash build/tmp/deploy/core-image-minimal-adk.sdcard.gz to microSD card  
3.1) Windows: You can do it by using usb-image-tools
http://www.alexpage.de/usb-image-tool/download/  
3.2) Linux: Use dd+gunzip  
$: gunzip -c core-image-minimal-adk.sdcard.gz | sudo dd of=/dev/<you device> bs=4M  
