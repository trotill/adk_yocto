DESCRIPTION = "A XFCE stand image."


IMAGE_INSTALL = "packagegroup-core-boot libstdc++  ${CORE_IMAGE_EXTRA_INSTALL} \
    kernel-modules \
"

REQUIRED_DISTRO_FEATURES = "x11"

IMAGE_LINGUAS = " "



export IMAGE_BASENAME = "stand-image-xfce"

# First include a base image to base things off
inherit core-image

IMAGE_FEATURES +="ssh-server-openssh"

# Now add the multilib packages we want to install
CORE_IMAGE_EXTRA_INSTALL += "nano lsof usbutils pciutils proftpd glib-2.0 iptables jsoncpp ppp stand udev-extraconf udev-rules-imx"


ROOTFS_POSTPROCESS_COMMAND_append = " change_bgimage; "

change_bgimage() {
	cp ${WORKDIR}/rootfs/etc/stand/init.d/stand ${WORKDIR}/rootfs/etc/init.d/stand 
	ln -s ../init.d/stand ${WORKDIR}/rootfs/etc/rc5.d/S96stand
}


