FILESEXTRAPATHS_prepend := "${THISDIR}/${P}:${THISDIR}/${P}-${KERNEL_DEFCONFIG_TYPE}:"
LICENSE = "CLOSED"
DEPENDS = "u-boot-mkimage-native"

SRC_URI = "file://6x_bootscript-adakta.txt \
          file://6x_bootscript-mainline.txt \
          file://6x_upgrade.txt \
"

S = "${WORKDIR}"

inherit deploy

BOOTSCRIPT ??= "${WORKDIR}/6x_bootscript-adakta.txt"
BOOTSCRIPT_use-mainline-bsp ??= "${WORKDIR}/6x_bootscript-mainline.txt"
SOURCEP = "${WORKDIR}/ubootscript/${MACHINE}"
UPGRADESCRIPT = "${WORKDIR}/6x_upgrade.txt"

do_mkimage () {
    # allow deploy to use the ${MACHINE} name to simplify things
    if [ ! -d ${SOURCEP} ]; then
        mkdir -p ${SOURCEP}
    fi

    uboot-mkimage -A arm -O linux -T script -C none -a 0 -e 0 \
                  -n "boot script" -d ${BOOTSCRIPT} \
                  ${SOURCEP}/6x_bootscript

    uboot-mkimage -A arm -O linux -T script -C none -a 0 -e 0 \
                  -n "upgrade script" -d ${UPGRADESCRIPT} \
                  ${SOURCEP}/6x_upgrade
}

addtask mkimage after do_compile before do_install

do_compile[noexec] = "1"

do_install () {
    install -D -m 644 ${SOURCEP}/6x_bootscript \
                      ${D}/6x_bootscript
    install -D -m 644 ${SOURCEP}/6x_upgrade \
                      ${D}/6x_upgrade
}

do_deploy () {
    install -D -m 644 ${D}/6x_bootscript \
                      ${DEPLOYDIR}/6x_bootscript
    install -D -m 644 ${D}/6x_upgrade \
                      ${DEPLOYDIR}/6x_upgrade

    cd ${DEPLOYDIR}
    ln -sf 6x_bootscript 6x_bootscript-${MACHINE}
    ln -sf 6x_upgrade 6x_upgrade-${MACHINE}
}

addtask deploy after do_install before do_build

FILES_${PN} += "/"

PACKAGE_ARCH = "${MACHINE_ARCH}"
COMPATIBLE_MACHINE = "(adakta_dp6ull)"
