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

LICENSE = "MIT"

# First include a base image to base things off
inherit core-image

IMAGE_FEATURES +="ssh-server-openssh"

CORE_IMAGE_EXTRA_INSTALL += "usb-modeswitch usb-modeswitch-data dnsmasq lsof usbutils pciutils proftpd curl wireless-tools  iptables iproute2 tcpdump ppp screen libnl mtd-utils mtd-utils-ubifs mtd-utils-jffs2 mtd-utils-misc jsoncpp bridge-utils psmisc sysstat coreutils ntp net-snmp net-snmp-server openvpn xl2tpd strongswan ppp-l2tp ppp-minconn ppp-password ppp-radius ppp-tools ppp-oa ppp-oe ppp-winbind pptp-linux" 

