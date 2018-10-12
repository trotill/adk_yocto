DESCRIPTION = "SPI Loopback Tool for Testing"
SECTION = "testing"
# Taken from the Linux kernel Documentation/spi/spidev_test.c
LICENSE = "GPLv2"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/GPL-2.0;md5=801f80980d171dd6425610833a22dbe6"

SRC_URI = "file://spidev_test.c"

S = "${WORKDIR}"

INSANE_SKIP_${PN} = "ldflags"
INSANE_SKIP_${PN}-dev = "ldflags"

do_compile() {
    ${CC} spidev_test.c -o spidev_test
}

do_install() {
    install -d ${D}${bindir}
    install -m 0755 spidev_test ${D}${bindir}
}

