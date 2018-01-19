# ADK (Adakta Development Kit) Yocto distribution
  
System build Linux kernel, u-boot, rootfs e.t.c  
  
Software support for NXP i.MX6 series:  
<a href="https://adakta.ru/eng/products/system-on-module-ADAKTA-mx6-iMX6">System on Module based on NXP iMX6<a>  
<a href="https://adakta.ru/eng/products/ADAKTA-AMX6-server">ADAKTA Development Kit server (AMX6)<a>  
<a href="https://adakta.ru/eng/products/ADAKTA-AMX6-media">ADAKTA Development Kit media (AMX6)<a>  
<a href="https://adakta.ru/eng/products/ADAKTA-AMX6-miniPC">ADAKTA Development Kit miniPC (AMX6)<a>  
  
Software support for NXP i.MX6 series:  
<a href="https://adakta.ru/eng/products/system-on-module-ADAKTA-iMX6ull-nano6">System on Module based on NXP iMX6ull<a>  
<a href="https://adakta.ru/eng/products/ADK-board-ADAKTA-mx6ull">ADAKTA Development Kit mx6ull (ADK6ull)<a>  
  
How use?  
  
$: git clone git@github.com:trotill/adk_yocto.git  
$: cd adk_yocto/  
$: git checkout origin/pyro_adk -b pyro_adk  
$: MACHINE=adakta-adk DISTRO=fslc-x11 source setup-environment build/  
  
Then create your own distro or compile a demo:  
core-image-minimal  
core-image-minimal-xfce  
core-image-sato  
core-image-x11  
  
For example  
$: bitbake core-image-minimal  
  
Flash build/tmp/deploy/core-image-minimal-adk.sdcard.gz to uSD card.  
  
This can be done using usb-image-tools (for Windows)  
http://www.alexpage.de/usb-image-tool/download/  
  
or dd+gunzip for Linux  
$: gunzip -c core-image-minimal-adk.sdcard.gz | sudo dd of=/dev/<you device> bs=4M  
