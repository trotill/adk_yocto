FILESEXTRAPATHS_prepend := "${THISDIR}/${P}:${THISDIR}/${P}-${KERNEL_DEFCONFIG_TYPE}:"

require recipes-bsp/u-boot/u-boot.inc

DESCRIPTION = "u-boot for Adakta boards."
LICENSE = "GPLv2+"
LIC_FILES_CHKSUM = "file://Licenses/README;md5=a2c678cfd4a4d97135585cad908541c6"
COMPATIBLE_MACHINE = "(adakta-adk|adakta-emx|adakta_nano6ull|adakta_dp6ull)"

PROVIDES = "u-boot"

PV = "201707"
#"${UBOOT_MACHINE}"
#"v2016.03+git${SRCPV}"

SRCREV = "c6fd0550aa8625bb088922dcc772bf55b98a24b0"
SRCBRANCH = "boundary-v2017.07"

# ${@bb.utils.contains_any("KERNEL_DEFCONFIG_TYPE", "emx","file://0001-Add-adakta-emx6-support.patch","",d)}
SRC_URI = "git://github.com/boundarydevices/u-boot-imx6.git;branch=${SRCBRANCH} \
		   ${@bb.utils.contains_any("KERNEL_DEFCONFIG_TYPE", "adk","file://0001-adk-support.patch","",d)} \
		   ${@bb.utils.contains_any("KERNEL_DEFCONFIG_TYPE", "adkstand","file://0001-adk-support.patch","",d)} \
		   ${@bb.utils.contains_any("KERNEL_DEFCONFIG_TYPE", "emx","file://0001-Add-adakta-emx6-support.patch","",d)} \
		   ${@bb.utils.contains_any("KERNEL_DEFCONFIG_TYPE", "adakta_nano6ull","file://0001-Add-adakta-nano6ull-module-support-nand-correct.patch","",d)} \
		   ${@bb.utils.contains_any("KERNEL_DEFCONFIG_TYPE", "adakta_dp6ull","file://dp6ull_support.patch","",d)} \
		   ${@bb.utils.contains_any("KERNEL_DEFCONFIG_TYPE", "emxstand","file://0001-Add-adakta-emx6-support.patch","",d)}"


S = "${WORKDIR}/git"

DEPENDS += "bc-native dtc-native"
PACKAGE_ARCH = "${MACHINE_ARCH}"
