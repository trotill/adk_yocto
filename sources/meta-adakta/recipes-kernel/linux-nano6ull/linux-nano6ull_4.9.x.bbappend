# Adapted from linux-imx.inc, copyright (C) 2013, 2014 O.S. Systems Software LTDA
# Released under the MIT license (see COPYING.MIT for the terms)

FILESEXTRAPATHS_prepend := "${THISDIR}/${P}:${THISDIR}/${P}-${KERNEL_DEFCONFIG_TYPE}:"

#bbwarn FILESEXTRAPATHS_prepend ${FILESEXTRAPATHS_prepend}

SUMMARY = "Linux kernel for Nano6ULL additions"
#KERNEL_DEFCONFIG_TYPE = "adakta_nano6ull"

SRC_URI += "file://defconfig \
		   ${@bb.utils.contains_any("KERNEL_DEFCONFIG_TYPE", "adakta_nano6ull", "file://ksz8081rna_blink_led.patch" , "", d)} \
		   ${@bb.utils.contains_any("KERNEL_DEFCONFIG_TYPE", "adakta_nano6ull", "file://git" , "", d)} \
		   ${@bb.utils.contains_any("KERNEL_DEFCONFIG_TYPE", "adakta_nano6ull_stand", "file://ksz8081rna_blink_led.patch" , "", d)} \
		   ${@bb.utils.contains_any("KERNEL_DEFCONFIG_TYPE", "adakta_nano6ull_stand", "file://git" , "", d)} \
"

COMPATIBLE_MACHINE = "(adakta_nano6ull)"
