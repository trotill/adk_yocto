# Adapted from linux-imx.inc, copyright (C) 2013, 2014 O.S. Systems Software LTDA
# Released under the MIT license (see COPYING.MIT for the terms)

FILESEXTRAPATHS_prepend := "${THISDIR}/${P}:${THISDIR}/${P}-${KERNEL_DEFCONFIG_TYPE}:"

#bbwarn FILESEXTRAPATHS_prepend ${FILESEXTRAPATHS_prepend}

SUMMARY = "Linux kernel for ADK additions"

SRC_URI += "file://defconfig \
		   file://0001-Add-Adakta-kernel-support.patch \
           ${@bb.utils.contains_any("KERNEL_DEFCONFIG_TYPE", "adkstand","file://0002-Add-ADK-stand-support.patch","",d)} \
"

