#
# An example of a multilib image
#
# This example includes a lib32 version of bash into an otherwise standard
# sato image. It assumes a "lib32" multilib has been enabled in the user's
# configuration (see the example conf files for examples of this.)
#

require recipes-fsl/images/fsl-image-multimedia-full.bb

IMAGE_INSTALL += " packagegroup-fonts-truetype packagegroup-core-x11-base"
#IMAGE_LINGUAS = " "
#IMAGE_INSTALL_append += " kernel-modules kernel"

# First include a base image to base things off
#inherit core-image

inherit populate_sdk_qt5

#REQUIRED_DISTRO_FEATURES = "x11"

QT_EXTRA = "\
	qtbase \
	qtconnectivity \
	qtconnectivity-tools \
	qtdeclarative \
	qtmultimedia \
	qtquickcontrols \
	qtquickcontrols2 \
	qtgraphicaleffects \
	qtcharts \
	qtsvg \
	qtsensors \
    qtbase-plugins \
    "

FS_PROGS = "\
	e2fsprogs-e2fsck \
	e2fsprogs-mke2fs \
	parted \
	dosfstools \
	mtd-utils \ 
	mtd-utils-ubifs \ 
	mtd-utils-misc \
"

IMAGE_FEATURES +="ssh-server-openssh "
CORE_IMAGE_EXTRA_INSTALL += "usb-modeswitch usb-modeswitch-data ppp-minconn ppp-password ppp-radius ppp-tools ppp-oa ppp-oe ppp-winbind ppp-l2tp lsof usbutils pciutils proftpd curl bridge-utils tcpdump iptables iproute2 ppp screen libnl jsoncpp psmisc sysstat coreutils ntp i2c-tools dnsmasq mc nano wget tzdata-posix sqlite rpm util-linux dpkg haveged htop rsync "

CORE_IMAGE_EXTRA_INSTALL += "${QT_EXTRA}"
CORE_IMAGE_EXTRA_INSTALL += "${FS_PROGS}"