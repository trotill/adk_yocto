# Adapted from linux-imx.inc, copyright (C) 2013, 2014 O.S. Systems Software LTDA
# Released under the MIT license (see COPYING.MIT for the terms)

FILESEXTRAPATHS_prepend := "${THISDIR}/${P}:${THISDIR}/${P}-${KERNEL_DEFCONFIG_TYPE}:"

#bbwarn FILESEXTRAPATHS_prepend ${FILESEXTRAPATHS_prepend}

SUMMARY = "Linux kernel for Nano6ULL additions"

SRC_URI += "file://defconfig \
		   file://0001-Add-adakta-nano6ull-support.patch \
"

COMPATIBLE_MACHINE = "(adakta_nano6ull)"
