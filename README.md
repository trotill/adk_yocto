# ADAKTA Development Kit SDK 

# Yocto distribution for ADK and ADK6ull

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

$: git clone https://github.com/trotill/adk_yocto.git  
$: cd adk_yocto/ 
For pyro release: 
$: git checkout origin/pyro_adk -b pyro_adk  
For thud release: 
$: git checkout origin/thud_adk -b thud_adk 
For ADK  
$: MACHINE=adakta-adk DISTRO=fslc-x11 source setup-environment ADK/  
For ADK6ull  
$: MACHINE=adakta_nano6ull DISTRO=fslc-framebuffer source setup-environment ADK6ull/  

2) Create your distro or compile the demo:

core-image-minimal-xfce (ADK only)  
core-image-adakta-net  
core-image-minimal  
core-image-sato  
core-image-x11 (ADK only)  
For example: 
$: bitbake core-image-adakta-net  

3) Flash ADK/tmp/deploy/core-image-adakta-net-adakta-adk.sdcard.gz (for ADK) or  
     ADK6ull/tmp/deploy/core-image-adakta-net-adakta_nano6ull.sdcard.gz (for ADK6ull) to microSD card  

3.1) Windows: You can do it by using usb-image-tools
http://www.alexpage.de/usb-image-tool/download/  
3.2) Linux: Use dd+gunzip  
For ADK     $: gunzip -c core-image-adakta-net-adakta-adk.sdcard.gz | sudo dd of=/dev/<you device> bs=4M  
For ADK6ull $: gunzip -c core-image-adakta-net-adakta_nano6ull.sdcard.gz | sudo dd of=/dev/<you device> bs=4M  
 
Prebuild releases, ready for use - https://github.com/trotill/adk_yocto/releases