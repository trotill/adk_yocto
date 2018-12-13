# Adapted from linux-imx.inc, copyright (C) 2013, 2014 O.S. Systems Software LTDA
# Released under the MIT license (see COPYING.MIT for the terms)

FILESEXTRAPATHS_prepend := "${THISDIR}/${P}:${THISDIR}/${P}-${KERNEL_DEFCONFIG_TYPE}:"

#bbwarn FILESEXTRAPATHS_prepend ${FILESEXTRAPATHS_prepend}

SUMMARY = "Linux kernel for Nano6ULL additions"
#KERNEL_DEFCONFIG_TYPE = "adakta_nano6ull"

SRC_URI += "file://defconfig \
		   ${@bb.utils.contains_any("KERNEL_DEFCONFIG_TYPE", "adakta_nano6ull", "file://0001-Add-adakta-nano6ull-support.patch" , "", d)} \
		   ${@bb.utils.contains_any("KERNEL_DEFCONFIG_TYPE", "adakta_nano6ull", "file://0002-Switch-NAND-to-legacy-ecc-mode.patch" , "", d)} \
		   ${@bb.utils.contains_any("KERNEL_DEFCONFIG_TYPE", "adakta_nano6ull", "file://0003-Add_800MHz_support.patch" , "", d)} \
		   ${@bb.utils.contains_any("KERNEL_DEFCONFIG_TYPE", "adakta_nano6ull", "file://0004-Add_900MHz_support.patch" , "", d)} \
		   ${@bb.utils.contains_any("KERNEL_DEFCONFIG_TYPE", "adakta_nano6ull", "file://0005-Add-spidev-to-nano6ull.patch" , "", d)} \
		   ${@bb.utils.contains_any("KERNEL_DEFCONFIG_TYPE", "adakta_nano6ull", "file://0006-Add-adc-nano6ull.patch" , "", d)} \
		   ${@bb.utils.contains_any("KERNEL_DEFCONFIG_TYPE", "adakta_nano6ull_stand", "file://ksz8081rna.patch" , "", d)} \
		   ${@bb.utils.contains_any("KERNEL_DEFCONFIG_TYPE", "adakta_nano6ull_stand", "file://git" , "", d)} \
"

COMPATIBLE_MACHINE = "(adakta_nano6ull)"
