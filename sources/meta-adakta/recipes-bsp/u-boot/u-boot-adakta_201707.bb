require recipes-bsp/u-boot/u-boot.inc

DESCRIPTION = "u-boot for Adakta ADK boards."
LICENSE = "GPLv2+"
LIC_FILES_CHKSUM = "file://Licenses/README;md5=a2c678cfd4a4d97135585cad908541c6"
COMPATIBLE_MACHINE = "(adakta-adk)"

PROVIDES = "u-boot"

PV = "201707"
#"${UBOOT_MACHINE}"
#"v2016.03+git${SRCPV}"

SRCREV = "c6fd0550aa8625bb088922dcc772bf55b98a24b0"
SRCBRANCH = "boundary-v2017.07"
SRC_URI = "git://github.com/boundarydevices/u-boot-imx6.git;branch=${SRCBRANCH} \
		   file://0001-adk-support.patch"

S = "${WORKDIR}/git"

PACKAGE_ARCH = "${MACHINE_ARCH}"
