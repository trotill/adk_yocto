DESCRIPTION = "Stand software for little manufacturers"
LICENSE = "CLOSED"
DEPENDS = "jsoncpp"

SRC_URI = "file://CMakeLists.txt \
		   file://src/basic.h \
		   file://src/gpio.cxx \
		   file://src/gpio.h \
		   file://src/memadmin.h \
		   file://src/memadmin.cxx \
		   file://src/minilib.h \
		   file://src/minilib.cxx \
           file://src/stand.cxx \           
           file://src/stand.h \
           file://src/tty.cxx \
           file://src/tty.h \
           file://src/types.h \
           file://test \
           file://examples \
           file://bg \
           file://init.d \
           file://xdg \
          "

S = "${WORKDIR}"

inherit cmake

do_install() {
    install -d ${D}${bindir}
    install -m 0755 stand ${D}${bindir}
    install -d ${D}${sysconfdir}/stand
    cp -r ${S}/test ${D}${sysconfdir}/stand 
    cp -r ${S}/examples ${D}${sysconfdir}/stand 
    cp -r ${S}/bg ${D}${sysconfdir}/stand 
    cp -r ${S}/init.d ${D}${sysconfdir}/stand 
    cp -r ${S}/xdg ${D}${sysconfdir}/stand
    ln -s ${KERNEL_DEFCONFIG_TYPE}.json ${D}${sysconfdir}/stand/examples/stand.json
}


