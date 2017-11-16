FILESEXTRAPATHS_prepend := "${THISDIR}/${P}:${THISDIR}/${P}-${KERNEL_DEFCONFIG_TYPE}:"

SRC_URI = "file://6x_bootscript-yocto-3.14.txt \
          file://6x_bootscript-mainline.txt \
          file://6x_upgrade.txt \
"