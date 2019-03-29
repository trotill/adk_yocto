#
# An example of a multilib image
#
# This example includes a lib32 version of bash into an otherwise standard
# sato image. It assumes a "lib32" multilib has been enabled in the user's
# configuration (see the example conf files for examples of this.)
#

IMAGE_INSTALL = "packagegroup-core-boot libstdc++ ${CORE_IMAGE_EXTRA_INSTALL}"
IMAGE_LINGUAS = " "
IMAGE_INSTALL_append += " kernel-modules kernel"

# First include a base image to base things off
inherit core-image

IMAGE_FEATURES +="ssh-server-openssh"
CORE_IMAGE_EXTRA_INSTALL += "usb-modeswitch usb-modeswitch-data ppp-minconn ppp-password ppp-radius ppp-tools ppp-oa ppp-oe ppp-winbind ppp-l2tp lsof usbutils pciutils proftpd curl bridge-utils tcpdump  pptp-linux xl2tpd wireless-tools iptables iproute2 ppp screen libnl mtd-utils mtd-utils-ubifs mtd-utils-jffs2 mtd-utils-misc jsoncpp psmisc sysstat coreutils ntp net-snmp net-snmp-server openvpn strongswan i2c-tools spitools spidev-test dnsmasq lua mysql-python mc nano wget tzdata-posix nodejs sqlite redis rpm util-linux dosfstools dpkg haveged ntfs-3g hostapd wpa-supplicant gstreamer1.0-rtsp-server gstreamer1.0-plugins-good gstreamer1.0-plugins-base gstreamer1.0 htop" 
#gstreamer1.0-plugins-imx