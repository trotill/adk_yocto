DESCRIPTION = "A XFCE stand image."


IMAGE_INSTALL = "packagegroup-core-boot libstdc++ packagegroup-core-x11 ${CORE_IMAGE_EXTRA_INSTALL} \
    packagegroup-xfce-base \
    kernel-modules \
"

REQUIRED_DISTRO_FEATURES = "x11"

IMAGE_LINGUAS = " "



export IMAGE_BASENAME = "stand-image-xfce"

# First include a base image to base things off
inherit core-image

IMAGE_FEATURES +="ssh-server-openssh"

# Now add the multilib packages we want to install
CORE_IMAGE_EXTRA_INSTALL += "nano lsof usbutils pciutils proftpd glib-2.0 iptables jsoncpp ppp xmessage fb-test stand udev-extraconf udev-rules-imx"


ROOTFS_POSTPROCESS_COMMAND_append = " change_bgimage; "

change_bgimage() {
	rm ${WORKDIR}/rootfs/usr/share/backgrounds/xfce/xfce-blue.jpg
	rm ${WORKDIR}/rootfs/usr/share/backgrounds/xfce/xfce-teal.jpg
	rm ${WORKDIR}/rootfs/etc/xdg/xfce4/xfconf/xfce-perchannel-xml/xfce4-session.xml
	ln -s ../../../../etc/stand/bg/bg.jpg ${WORKDIR}/rootfs/usr/share/backgrounds/xfce/xfce-blue.jpg
	ln -s ../../../../etc/stand/bg/bg.jpg ${WORKDIR}/rootfs/usr/share/backgrounds/xfce/xfce-teal.jpg
	cp ${WORKDIR}/rootfs/etc/stand/init.d/stand ${WORKDIR}/rootfs/etc/init.d/stand 
	cp ${WORKDIR}/rootfs/etc/stand/xdg/xfce4-session.xml ${WORKDIR}/rootfs/etc/xdg/xfce4/xfconf/xfce-perchannel-xml/xfce4-session.xml 
	ln -s ../init.d/stand ${WORKDIR}/rootfs/etc/rc5.d/S96stand
}


