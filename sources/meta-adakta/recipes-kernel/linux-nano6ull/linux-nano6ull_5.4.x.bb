# Adapted from linux-imx.inc, copyright (C) 2013, 2014 O.S. Systems Software LTDA
# Released under the MIT license (see COPYING.MIT for the terms)

require recipes-kernel/linux/linux-imx.inc

DEPENDS += "lzop-native bc-native"
LOCALVERSION = "-fslc"

LIC_FILES_CHKSUM = "file://COPYING;md5=bbea815ee2795b2f4230826c0c6b8814"
SUMMARY = "Linux kernel for Nano6ULL"


SRC_URI = "git://github.com/Freescale/linux-fslc.git;branch=${SRCBRANCH} \
		   file://defconfig \
		   file://git"

SRCBRANCH = "5.4.x+fslc"
SRCREV = "97bd7598fd01b865b833f68cf1e8d7d371762c11"
FILES_${KERNEL_PACKAGE_NAME}-base = "${nonarch_base_libdir}/modules/${KERNEL_VERSION}/modules.order ${nonarch_base_libdir}/modules/${KERNEL_VERSION}/modules.builtin ${nonarch_base_libdir}/modules/${KERNEL_VERSION}/modules.builtin.modinfo"
COMPATIBLE_MACHINE = "(adakta_nano6ull)"