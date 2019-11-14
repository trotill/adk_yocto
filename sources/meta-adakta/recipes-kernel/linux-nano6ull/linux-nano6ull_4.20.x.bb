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

SRCBRANCH = "4.20.x+fslc"
SRCREV = "bf414f71d71348bf549d320fa6518b04738dbaa1"

COMPATIBLE_MACHINE = "(adakta_nano6ull)"