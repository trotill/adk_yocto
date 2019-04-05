/*
 * Copyright (C) 2010-2011 Freescale Semiconductor, Inc.
 *
 * Configuration settings for the Adakta ADK
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */ 

#ifndef __CONFIG_H
#define __CONFIG_H

#include "mx6_common.h"
#ifndef CONFIG_BOARD_TYPE
#undef CONFIG_SYS_BOARD
#endif

#define CONFIG_MACH_TYPE	3769


#define CONFIG_IMX_HDMI
#define CONFIG_PHY_MICREL_KSZ9031
#define CONFIG_PHY_MICREL_KSZ90X1

#define CONFIG_SYS_FSL_USDHC_NUM	2
#define CONFIG_USB_MAX_CONTROLLER_COUNT 2

#define I2C_MASK	7



#ifdef CONFIG_BOARD_TYPE
#undef CONFIG_SYS_BOARD
#define CONFIG_SYS_BOARD CONFIG_BOARD_TYPE
#endif
/*#include <config_distro_defaults.h>*/

#define CONFIG_MISC_INIT_R
#define CONFIG_BOARD_LATE_INIT

#ifndef CONFIG_SYS_MALLOC_LEN
/* Size of malloc() pool */
#define CONFIG_SYS_MALLOC_LEN		(12 * 1024 * 1024)
#endif

#define CONFIG_MXC_UART
#ifndef CONFIG_MXC_UART_BASE
#define CONFIG_MXC_UART_BASE		UART2_BASE
#endif

/* Secure boot (HAB) support */
#ifdef CONFIG_SECURE_BOOT
#define CONFIG_CSF_SIZE			0x2000
#define CONFIG_SYS_FSL_SEC_COMPAT	4
#define CONFIG_CMD_DEKBLOB
#endif

/* SPL magic */
#ifdef CONFIG_SPL
#define CONFIG_SPL_FRAMEWORK
#define CONFIG_SPL_TEXT_BASE		0x00908400
#define CONFIG_SPL_PAD_TO 0x400
#define CONFIG_SPL_START_S_PATH		"arch/arm/cpu/armv7"
#define CONFIG_SPL_STACK		0x0091FFB8

#define CONFIG_SPL_LIBCOMMON_SUPPORT
#define CONFIG_SPL_LIBGENERIC_SUPPORT
#define CONFIG_SPL_SERIAL_SUPPORT
#define CONFIG_SPL_USB
#define CONFIG_SPL_WATCHDOG_SUPPORT
#define CONFIG_SPL_GPIO_SUPPORT

/* SPI flash. */
#define CONFIG_SPL_SPI_SUPPORT
#define CONFIG_SPL_SPI_FLASH_SUPPORT
#define CONFIG_SPL_SPI_LOAD
#define CONFIG_SPL_SPI_BUS		0
#define CONFIG_SPL_SPI_CS		0
#define CONFIG_SYS_SPI_U_BOOT_OFFS	0x20000

#define CONFIG_SPL_BOARD_INIT
#define CONFIG_SYS_SPL_MALLOC_START	0x00916000
#define CONFIG_SYS_SPL_MALLOC_SIZE	0x2000
#endif

/* I2C Configs */
#ifdef I2C_MASK
#define CONFIG_SYS_I2C
#define CONFIG_SYS_I2C_MXC
#if (I2C_MASK & 1)
#define CONFIG_SYS_I2C_MXC_I2C1
#endif
#if (I2C_MASK & 2)
#define CONFIG_SYS_I2C_MXC_I2C2
#endif
#if (I2C_MASK & 4)
#define CONFIG_SYS_I2C_MXC_I2C3
#endif

#define CONFIG_SYS_I2C_SPEED		100000
#define CONFIG_I2C_EDID
#endif

/* MMC Configs */
#ifdef CONFIG_SYS_FSL_USDHC_NUM
#define CONFIG_SYS_FSL_ESDHC_ADDR	0
#endif

#ifdef CONFIG_CMD_SF
#ifndef CONFIG_FSL_QSPI
#define CONFIG_MXC_SPI
#endif
#define CONFIG_SF_DEFAULT_BUS  0
#ifndef CONFIG_SF_DEFAULT_CS
#define CONFIG_SF_DEFAULT_CS   0
#endif
#define CONFIG_SF_DEFAULT_SPEED 25000000
#define CONFIG_SF_DEFAULT_MODE (SPI_MODE_0)
#endif



#ifdef CONFIG_PHY_MICREL_KSZ9031
#define CONFIG_PHYLIB
#define CONFIG_FEC_MXC
#define CONFIG_PHY_MICREL

#ifndef CONFIG_FEC_MXC_PHYADDR
#define CONFIG_FEC_MXC_PHYADDR		6
#endif

#define CONFIG_MII
#define CONFIG_FEC_MAC_FUSE
#ifndef IMX_FEC_BASE
#define IMX_FEC_BASE			ENET_BASE_ADDR
#endif

#define CONFIG_FEC_XCV_TYPE		RGMII
#define CONFIG_ETHPRIME			"FEC"

#endif

/*
 * SATA Configs
 */
#ifdef CONFIG_CMD_SATA
#define CONFIG_DWC_AHSATA
#define CONFIG_SYS_SATA_MAX_DEVICE	1
#define CONFIG_DWC_AHSATA_PORT_ID	0
#define CONFIG_DWC_AHSATA_BASE_ADDR	SATA_ARB_BASE_ADDR
#define CONFIG_LBA48
#define CONFIG_LIBATA
#endif

/* USB gadget support */
#ifdef CONFIG_CI_UDC
#define CONFIG_USBD_HS
#define CONFIG_USB_ETHER
#define CONFIG_USB_ETH_CDC
#define CONFIG_NETCONSOLE
#endif

/* USB Configs */
#ifdef CONFIG_USB_MAX_CONTROLLER_COUNT
#define CONFIG_USB_HOST_ETHER
#define CONFIG_USB_ETHER_ASIX
#define CONFIG_USB_ETHER_MCS7830
#define CONFIG_USB_ETHER_SMSC95XX
#define CONFIG_EHCI_HCD_INIT_AFTER_RESET	/* For OTG port */
#ifndef CONFIG_MXC_USB_PORTSC
#define CONFIG_MXC_USB_PORTSC	(PORT_PTS_UTMI | PORT_PTS_PTW)
#endif
#ifndef CONFIG_MXC_USB_FLAGS
#define CONFIG_MXC_USB_FLAGS	0
#endif
#define CONFIG_SYS_USB_EVENT_POLL_VIA_CONTROL_EP
#endif

/* Framebuffer and LCD */
#ifdef CONFIG_VIDEO
#define CONFIG_VIDEO_BMP_RLE8
#define CONFIG_SPLASH_SCREEN
#define CONFIG_SPLASH_SCREEN_ALIGN
#define CONFIG_VIDEO_BMP_GZIP
#define CONFIG_SYS_VIDEO_LOGO_MAX_SIZE (6 * 1024 * 1024)
#define CONFIG_BMP_16BPP
#define CONFIG_CMD_FBPANEL

#define CONFIG_VIDEO_IPUV3

#endif

#ifndef CONFIG_PREBOOT
#define CONFIG_PREBOOT                 ""
#endif

#ifdef CONFIG_CMD_SATA
#define DISTRO_BOOT_DEV_SATA(func) func(SATA, sata, 0)
#else
#define DISTRO_BOOT_DEV_SATA(func)
#endif

#ifdef CONFIG_CMD_MMC
#if (CONFIG_SYS_FSL_USDHC_NUM == 1)
#define DISTRO_BOOT_DEV_MMC(func) func(MMC, mmc, 0)
#elif (CONFIG_SYS_FSL_USDHC_NUM == 2)
#define DISTRO_BOOT_DEV_MMC(func) func(MMC, mmc, 0) func(MMC, mmc, 1)
#else
#define DISTRO_BOOT_DEV_MMC(func) func(MMC, mmc, 0) func(MMC, mmc, 1) func(MMC, mmc, 2)
#endif
#else
#define DISTRO_BOOT_DEV_MMC(func)
#endif

#ifndef FASTBOOT_FLASH_MMC_DEV
#if (CONFIG_SYS_FSL_USDHC_NUM == 1)
#define FASTBOOT_FLASH_MMC_DEV   0
#elif (CONFIG_SYS_FSL_USDHC_NUM == 2)
#define FASTBOOT_FLASH_MMC_DEV   1
#else
#define FASTBOOT_FLASH_MMC_DEV   2
#endif
#endif

#ifdef CONFIG_USB_STORAGE
#define DISTRO_BOOT_DEV_USB(func) func(USB, usb, 0)
#else
#define DISTRO_BOOT_DEV_USB(func)
#endif

#ifndef CONSOLE
#if CONFIG_MXC_UART_BASE == UART2_BASE
#define CONSOLE	"ttymxc1"
#elif CONFIG_MXC_UART_BASE == UART1_BASE
#define CONSOLE	"ttymxc0"
#endif
#endif

#if defined(CONFIG_VIDEO) && !defined(NOVIDEO_CONSOLE)
#define STDOUT_SERIAL	"setenv stdout serial;"
#define STDOUT_VIDEO		"setenv stdout serial,vga; "
#define STDIN_USBKBD		"setenv stdin serial,usbkbd;"
#else
#define STDOUT_SERIAL
#define STDOUT_VIDEO
#define STDIN_USBKBD
#endif

#ifndef SPLASH_FLASH
#define SPLASH_FLASH	"c2000"
#endif


#define RAM_BASE	0x10000000
#define RAM_SCRIPT	"10008000"
#define RAM_KERNEL	"10800000"
#define RAM_RAMDISK	"12800000"
#define RAM_FDT	"13000000"


#ifndef SKIP_FUSES
#ifndef FUSE1

#if defined(CONFIG_MX6Q) || defined(CONFIG_MX6S) || defined(CONFIG_MX6DL)
#define FUSE1		"0 5"
#define FUSE1_VAL		"18000030"	/* CS1 */
#define FUSE2		"0 6"
#define FUSE2_VAL		"00000010"
#endif
#endif

#ifndef FUSE_MAC1A

#define FUSE_MAC1A		"4 3"
#define FUSE_MAC1A_VAL	"00000019"
#define FUSE_MAC1B		"4 2"

#endif
#endif

#ifdef FUSE1
#define FUSE1_STR		"fuse1=" FUSE1 "\0"
#define FUSE1_VAL_STR	"fuse1_val=" FUSE1_VAL "\0"
#else
#define FUSE1_STR		""
#define FUSE1_VAL_STR	""
#endif

#ifdef FUSE2
#define FUSE2_STR		"fuse2=" FUSE2 "\0"
#define FUSE2_VAL_STR	"fuse2_val=" FUSE2_VAL "\0"
#else
#define FUSE2_STR		""
#define FUSE2_VAL_STR	""
#endif

#ifdef FUSE_MAC1A
#define FUSE_MAC1A_STR	"fuse_mac1a=" FUSE_MAC1A "\0"
#define FUSE_MAC1A_VAL_STR	"fuse_mac1a_val=" FUSE_MAC1A_VAL "\0"
#define FUSE_MAC1B_STR	"fuse_mac1b=" FUSE_MAC1B "\0"
#else
#define FUSE_MAC1A_STR	""
#define FUSE_MAC1A_VAL_STR	""
#define FUSE_MAC1B_STR	""
#endif

#ifndef BOOT_TARGET_DEVICES
#define BOOT_TARGET_DEVICES(func) \
	DISTRO_BOOT_DEV_MMC(func) \
	DISTRO_BOOT_DEV_SATA(func) \
	DISTRO_BOOT_DEV_USB(func)
#endif

#define BOOTENV_EXTRA_BOOT_SCRIPTS " 6x_bootscript "

#include <config_distro_bootcmd.h>

#ifdef LOG_LEVEL
#define LOG_LEVEL_STR "loglevel=" LOG_LEVEL "\0"
#else
#define LOG_LEVEL_STR ""
#endif

#ifdef CMA
#define LOG_CMA_STR "cma=" CMA "\0"
#else
#define LOG_CMA_STR ""
#endif

#define ENV_SETTINGS \
	"clearenv=if sf probe || sf probe ; then " \
		"sf erase 0xc0000 0x2000 && " \
		"echo restored environment to factory default ; fi\0" \
	LOG_CMA_STR \
	"console=" CONSOLE "\0" \
	"dfu_alt_info=u-boot raw 0x0 0xc0000\0" \
	"fdt_addr=" RAM_FDT "\0" \
	"fdt_high=0xffffffff\0" \
	FUSE1_STR \
	FUSE1_VAL_STR \
	FUSE2_STR \
	FUSE2_VAL_STR \
	FUSE_MAC1A_STR \
	FUSE_MAC1A_VAL_STR \
	FUSE_MAC1B_STR \
	"initrd_high=0xffffffff\0" \
	"dtbname=imx6qd-adk.dtb\0" \
	"loadsplash=if sf probe ; then sf read ${splashimage} ${splashflash} ${splashsize} ; fi\0" \
	LOG_LEVEL_STR \
	"net_fuses=dhcp " RAM_SCRIPT " prog_fuses.scr && source " RAM_SCRIPT "\0" \
	"net_program=next=prog_fuses.scr; run net_upgradeu\0" \
	"net_upgradeu=dhcp " RAM_SCRIPT " net_upgradeu.scr && source " RAM_SCRIPT "\0" \
	"rundfu=dfu 0 sf 0:0:25000000:0\0" \
	"otg_fuses=run usbnetwork; tftp " RAM_SCRIPT " prog_fuses.scr && source " RAM_SCRIPT "\0" \
	"otg_program=next=prog_fuses.scr; run otg_upgradeu\0" \
	"otg_upgradeu=run usbnetwork; tftp " RAM_SCRIPT " net_upgradeu.scr && source " RAM_SCRIPT "\0" \
	"program=next=prog_fuses.scr; run upgradeu\0" \
	"scriptaddr=" RAM_SCRIPT "\0" \
	"splashflash=" SPLASH_FLASH "\0" \
	"uboot_defconfig=" CONFIG_DEFCONFIG "\0" \
	"upgradeu=setenv boot_scripts upgrade.scr; boot\0" \
	"usb_pgood_delay=2000\0" \
	"usbnet_devaddr=00:19:b8:00:00:02\0" \
	"usbnet_hostaddr=00:19:b8:00:00:01\0" \
	"usbnetwork=setenv ethact usb_ether; " \
		"setenv ipaddr 10.0.0.2; " \
		"setenv netmask 255.255.255.0; " \
		"setenv serverip 10.0.0.1;\0" \
	"usbrecover=run usbnetwork;" \
		"setenv bootargs console=${console},115200; " \
		"tftpboot " RAM_KERNEL " 10.0.0.1:uImage-${board}-recovery && " \
		"tftpboot " RAM_RAMDISK " 10.0.0.1:uramdisk-${board}-recovery.img && " \
		"bootm " RAM_KERNEL " " RAM_RAMDISK "\0" \
	BOOTENV

/* Miscellaneous configurable options */
#define CONFIG_SYS_MEMTEST_START       RAM_BASE
#define CONFIG_SYS_MEMTEST_END	       (RAM_BASE + 0x00010000)
#define CONFIG_SYS_MEMTEST_SCRATCH     (RAM_BASE + 0x00800000)
#define CONFIG_SYS_ALT_MEMTEST

/* Physical Memory Map */
#define CONFIG_NR_DRAM_BANKS	       1
#if defined(CONFIG_MX51) || defined(CONFIG_MX53)
#define PHYS_SDRAM		       CSD0_BASE_ADDR
#else
#define PHYS_SDRAM		       MMDC0_ARB_BASE_ADDR
#endif

#define CONFIG_RESET_CAUSE_ADDR	       (PHYS_SDRAM + 0x80)

#define CONFIG_SYS_SDRAM_BASE	       PHYS_SDRAM
#define CONFIG_SYS_INIT_RAM_ADDR       IRAM_BASE_ADDR
#define CONFIG_SYS_INIT_RAM_SIZE       IRAM_SIZE

#define CONFIG_SYS_INIT_SP_OFFSET \
	(CONFIG_SYS_INIT_RAM_SIZE - GENERATED_GBL_DATA_SIZE)
#define CONFIG_SYS_INIT_SP_ADDR \
	(CONFIG_SYS_INIT_RAM_ADDR + CONFIG_SYS_INIT_SP_OFFSET)

/* Environment organization */
#define CONFIG_ENV_SIZE			(8 * 1024)

#define CONFIG_ENV_OFFSET		(768 * 1024)
#define CONFIG_ENV_SECT_SIZE		(8 * 1024)
#define CONFIG_ENV_SPI_BUS		CONFIG_SF_DEFAULT_BUS
#define CONFIG_ENV_SPI_CS		CONFIG_SF_DEFAULT_CS
#define CONFIG_ENV_SPI_MODE		CONFIG_SF_DEFAULT_MODE
#define CONFIG_ENV_SPI_MAX_HZ		CONFIG_SF_DEFAULT_SPEED

/*
 * PCI express
 */
/* #define CONFIG_CMD_PCI */
#ifdef CONFIG_CMD_PCI
#define CONFIG_PCI
#define CONFIG_PCI_PNP
#define CONFIG_PCI_SCAN_SHOW
#define CONFIG_PCIE_IMX
#endif

#define CONFIG_CMD_UNZIP

#ifdef CONFIG_CI_UDC
#define CONFIG_USB_GADGET_VBUS_DRAW	2

#define CONFIG_USB_FUNCTION_FASTBOOT
#define CONFIG_ANDROID_BOOT_IMAGE
#define CONFIG_FASTBOOT
#define CONFIG_CMD_FASTBOOT
#define CONFIG_FASTBOOT_BUF_ADDR   CONFIG_SYS_LOAD_ADDR
#define CONFIG_FASTBOOT_BUF_SIZE   0x26000000
#define CONFIG_FASTBOOT_FLASH
#define CONFIG_FASTBOOT_FLASH_MMC_DEV   FASTBOOT_FLASH_MMC_DEV
#define CONFIG_CMD_GPT
#define CONFIG_CMD_PART

/* USB Device Firmware Update support */
#define CONFIG_DFU_SF
#define CONFIG_SYS_DFU_DATA_BUF_SIZE	0xc0000
#define DFU_MANIFEST_POLL_TIMEOUT	25000
#endif

#define CONFIG_EXTRA_ENV_SETTINGS ENV_SETTINGS 
#endif
