# Adapted from linux-imx.inc, copyright (C) 2013, 2014 O.S. Systems Software LTDA
# Released under the MIT license (see COPYING.MIT for the terms)

require recipes-kernel/linux/linux-imx.inc
require recipes-kernel/linux/linux-dtb.inc

SUMMARY = "Linux kernel for ADK"


SRC_URI = "git://github.com/boundarydevices/linux-imx6.git;branch=${SRCBRANCH} \
"

LOCALVERSION = "-2.0.0-ga+yocto"
SRCBRANCH = "boundary-imx_4.1.15_2.0.0_ga"
SRCREV = "ff4e28b95115d7021c3ea6209b7c2b0b849874e1"
DEPENDS += "lzop-native bc-native"
COMPATIBLE_MACHINE = "(adakta-adk)"
