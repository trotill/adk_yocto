# Adapted from linux-imx.inc, copyright (C) 2013, 2014 O.S. Systems Software LTDA
# Released under the MIT license (see COPYING.MIT for the terms)

require recipes-kernel/linux/linux-imx.inc
require recipes-kernel/linux/linux-dtb.inc

SUMMARY = "Linux kernel for ADK"


SRC_URI = "git://github.com/boundarydevices/linux-imx6.git;branch=${SRCBRANCH} \
"

LOCALVERSION = "-2.0.0-ga+yocto"
SRCBRANCH = "boundary-imx_4.9.x_2.0.0_ga"
SRCREV = "a141bcc882fbba6c2d80d467fa54ac07b37b6f04"
DEPENDS += "lzop-native bc-native"
COMPATIBLE_MACHINE = "(adakta-adk)"
