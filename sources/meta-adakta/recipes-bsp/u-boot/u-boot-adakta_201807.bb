FILESEXTRAPATHS_prepend := "${THISDIR}/${P}:${THISDIR}/${P}-${KERNEL_DEFCONFIG_TYPE}:"

require recipes-bsp/u-boot/u-boot.inc

DESCRIPTION = "u-boot for Adakta boards."
LICENSE = "GPLv2+"
LIC_FILES_CHKSUM = "file://Licenses/README;md5=30503fd321432fc713238f582193b78e"
COMPATIBLE_MACHINE = "(adakta-adk|adakta-emx|adakta_nano6ull|adakta_dp6ull)"

PROVIDES += "u-boot"

PV = "201807"

BOOT_TOOLS = "imx-boot-tools"


#"${UBOOT_MACHINE}"
#"v2016.03+git${SRCPV}"

SRCREV = "ca185fc7406207da613c728935f534a4054674f1"
SRCBRANCH = "boundary-v2018.07"

# ${@bb.utils.contains_any("KERNEL_DEFCONFIG_TYPE", "emx","file://0001-Add-adakta-emx6-support.patch","",d)}
SRC_URI = "git://github.com/boundarydevices/u-boot-imx6.git;branch=${SRCBRANCH} \
		   ${@bb.utils.contains_any("KERNEL_DEFCONFIG_TYPE", "adkstand","file://git","",d)} \
		   ${@bb.utils.contains_any("KERNEL_DEFCONFIG_TYPE", "adk","file://git","",d)} \
		   ${@bb.utils.contains_any("KERNEL_DEFCONFIG_TYPE", "emx","file://git","",d)} \
		   ${@bb.utils.contains_any("KERNEL_DEFCONFIG_TYPE", "adakta_nano6ull","file://adakta_nano6ull_support.patch","",d)} \
		   ${@bb.utils.contains_any("KERNEL_DEFCONFIG_TYPE", "adakta_dp6ull","file://dp6ull_support.patch","",d)} \
		   ${@bb.utils.contains_any("KERNEL_DEFCONFIG_TYPE", "emxstand","file://0001-Add-adakta-emx6-support.patch","",d)}"


S = "${WORKDIR}/git"


DEPENDS += "bc-native dtc-native bison-native"
PACKAGE_ARCH = "${MACHINE_ARCH}"
