/*
 ***************************************************************************
 * Ralink Tech Inc.
 * 4F, No. 2 Technology 5th Rd.
 * Science-based Industrial Park
 * Hsin-chu, Taiwan, R.O.C.
 *
 * (c) Copyright, Ralink Technology, Inc.
 *
 *  This program is free software; you can redistribute  it and/or modify it
 *  under  the terms of  the GNU General  Public License as published by the
 *  Free Software Foundation;  either version 2 of the  License, or (at your
 *  option) any later version.
 *
 *  THIS  SOFTWARE  IS PROVIDED   ``AS  IS'' AND   ANY  EXPRESS OR IMPLIED
 *  WARRANTIES,   INCLUDING, BUT NOT  LIMITED  TO, THE IMPLIED WARRANTIES OF
 *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN
 *  NO  EVENT  SHALL   THE AUTHOR  BE    LIABLE FOR ANY   DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 *  NOT LIMITED   TO, PROCUREMENT OF  SUBSTITUTE GOODS  OR SERVICES; LOSS OF
 *  USE, DATA,  OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 *  ANY THEORY OF LIABILITY, WHETHER IN  CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 *  THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *  You should have received a copy of the  GNU General Public License along
 *  with this program; if not, write  to the Free Software Foundation, Inc.,
 *  675 Mass Ave, Cambridge, MA 02139, USA.
 *
 *
 ***************************************************************************
 */

#ifndef __RALINK_GPIO_H__
#define __RALINK_GPIO_H__

#include <linux/config.h>

#define NAME			"ralink_gpio" 	//driver name
#define RALINK_GPIO_DEVNAME	"gpio"		//nodename
#define GPIO_DEV		"/dev/gpio"	//userlevel devname

#if 0 /* BASE SDK CONFIG */
#define GPIO_LED_WAN_GREEN      12
#define GPIO_LED_WAN_ORANGE     14
#define GPIO_LED_SEC_GREEN      13
#define GPIO_WPS_LED_ORANGE  	13
#define GPIO_WPS_LED_GREEN   	13
//power led
#define GPIO_POWER_LED		9
#else  /* FOR ACORP PRODUCT SECTION */
#define GPIO_LED_WAN_GREEN      12
#define GPIO_LED_WAN_ORANGE     12
#define GPIO_LED_SEC_GREEN      13
//only one LED in WR-150N/300N for WPS
#define GPIO_WPS_LED_ORANGE  	14
#define GPIO_WPS_LED_GREEN   	14
//power led
#define GPIO_POWER_LED		9
#endif

/* Firmware update indicators */
#define GPIO_MTD_LED1	GPIO_LED_SEC_GREEN
#define GPIO_MTD_LED2	GPIO_WPS_LED_GREEN

/* VPN tx/rx led */
#ifdef CONFIG_RALINK_GPIO_LED
#define GPIO_VPN_LED1	GPIO_WPS_LED_GREEN
#endif

#define RALINK_GPIO_HAS_5124	1
//#define RALINK_GPIO_HAS_9524	1

/*
 * ioctl commands
 */
#define	RALINK_GPIO_SET_DIR		0x01
#define RALINK_GPIO_SET_DIR_IN		0x11
#define RALINK_GPIO_SET_DIR_OUT		0x12
#define	RALINK_GPIO_READ		0x02
#define	RALINK_GPIO_WRITE		0x03
#define	RALINK_GPIO_SET			0x21
#define	RALINK_GPIO_CLEAR		0x31
#define	RALINK_GPIO_READ_BIT		0x04
#define	RALINK_GPIO_WRITE_BIT		0x05
#define	RALINK_GPIO_READ_BYTE		0x06
#define	RALINK_GPIO_WRITE_BYTE		0x07
#define	RALINK_GPIO_READ_INT		0x02 //same as read
#define	RALINK_GPIO_WRITE_INT		0x03 //same as write
#define	RALINK_GPIO_SET_INT		0x21 //same as set
#define	RALINK_GPIO_CLEAR_INT		0x31 //same as clear
#define RALINK_GPIO_ENABLE_INTP		0x08
#define RALINK_GPIO_DISABLE_INTP	0x09
#define RALINK_GPIO_REG_IRQ		0x0A
#define RALINK_GPIO_LED_SET		0x41

#ifdef RALINK_GPIO_HAS_5124
#define	RALINK_GPIO3924_SET_DIR		0x51
#define RALINK_GPIO3924_SET_DIR_IN	0x13
#define RALINK_GPIO3924_SET_DIR_OUT	0x14
#define	RALINK_GPIO3924_READ		0x52
#define	RALINK_GPIO3924_WRITE		0x53
#define	RALINK_GPIO3924_SET		0x22
#define	RALINK_GPIO3924_CLEAR		0x32

#define	RALINK_GPIO5140_SET_DIR		0x61
#define RALINK_GPIO5140_SET_DIR_IN	0x15
#define RALINK_GPIO5140_SET_DIR_OUT	0x16
#define	RALINK_GPIO5140_READ		0x62
#define	RALINK_GPIO5140_WRITE		0x63
#define	RALINK_GPIO5140_SET		0x23
#define	RALINK_GPIO5140_CLEAR		0x33
#endif

#ifdef RALINK_GPIO_HAS_9524
#define	RALINK_GPIO3924_SET_DIR		0x51
#define RALINK_GPIO3924_SET_DIR_IN	0x13
#define RALINK_GPIO3924_SET_DIR_OUT	0x14
#define	RALINK_GPIO3924_READ		0x52
#define	RALINK_GPIO3924_WRITE		0x53
#define	RALINK_GPIO3924_SET		0x22
#define	RALINK_GPIO3924_CLEAR		0x32

#define	RALINK_GPIO7140_SET_DIR		0x61
#define RALINK_GPIO7140_SET_DIR_IN	0x15
#define RALINK_GPIO7140_SET_DIR_OUT	0x16
#define	RALINK_GPIO7140_READ		0x62
#define	RALINK_GPIO7140_WRITE		0x63
#define	RALINK_GPIO7140_SET		0x23
#define	RALINK_GPIO7140_CLEAR		0x33

#define	RALINK_GPIO9572_SET_DIR		0x71
#define RALINK_GPIO9572_SET_DIR_IN	0x17
#define RALINK_GPIO9572_SET_DIR_OUT	0x18
#define	RALINK_GPIO9572_READ		0x72
#define	RALINK_GPIO9572_WRITE		0x73
#define	RALINK_GPIO9572_SET		0x24
#define	RALINK_GPIO9572_CLEAR		0x34
#endif

/*
 * Address of RALINK_ Registers
 */
#define RALINK_SYSCTL_ADDR		RALINK_SYSCTL_BASE	// system control
#define RALINK_REG_GPIOMODE		(RALINK_SYSCTL_ADDR + 0x60)

#define RALINK_IRQ_ADDR			RALINK_INTCL_BASE
#define RALINK_REG_INTENA		(RALINK_IRQ_ADDR + 0x34)
#define RALINK_REG_INTDIS		(RALINK_IRQ_ADDR + 0x38)

#define RALINK_PRGIO_ADDR		RALINK_PIO_BASE // Programmable I/O
#define RALINK_REG_PIOINT		(RALINK_PRGIO_ADDR + 0)
#define RALINK_REG_PIOEDGE		(RALINK_PRGIO_ADDR + 0x04)
#define RALINK_REG_PIORENA		(RALINK_PRGIO_ADDR + 0x08)
#define RALINK_REG_PIOFENA		(RALINK_PRGIO_ADDR + 0x0C)
#define RALINK_REG_PIODATA		(RALINK_PRGIO_ADDR + 0x20)
#define RALINK_REG_PIODIR		(RALINK_PRGIO_ADDR + 0x24)
#define RALINK_REG_PIOSET		(RALINK_PRGIO_ADDR + 0x2C)
#define RALINK_REG_PIORESET		(RALINK_PRGIO_ADDR + 0x30)
#define RALINK_REG_PIOTOGGLE		(RALINK_PRGIO_ADDR + 0x34)

#if defined (RALINK_GPIO_HAS_5124)

#define RALINK_REG_PIO3924INT		(RALINK_PRGIO_ADDR + 0x38)
#define RALINK_REG_PIO3924EDGE		(RALINK_PRGIO_ADDR + 0x3C)
#define RALINK_REG_PIO3924RENA		(RALINK_PRGIO_ADDR + 0x40)
#define RALINK_REG_PIO3924FENA		(RALINK_PRGIO_ADDR + 0x44)
#define RALINK_REG_PIO3924DATA		(RALINK_PRGIO_ADDR + 0x48)
#define RALINK_REG_PIO3924DIR		(RALINK_PRGIO_ADDR + 0x4C)
#define RALINK_REG_PIO3924SET		(RALINK_PRGIO_ADDR + 0x54)
#define RALINK_REG_PIO3924RESET		(RALINK_PRGIO_ADDR + 0x58)
#define RALINK_REG_PIO3924TOGGLE	(RALINK_PRGIO_ADDR + 0x5C)

#define RALINK_REG_PIO5140INT		(RALINK_PRGIO_ADDR + 0x60)
#define RALINK_REG_PIO5140EDGE		(RALINK_PRGIO_ADDR + 0x64)
#define RALINK_REG_PIO5140RENA		(RALINK_PRGIO_ADDR + 0x68)
#define RALINK_REG_PIO5140FENA		(RALINK_PRGIO_ADDR + 0x6C)
#define RALINK_REG_PIO5140DATA		(RALINK_PRGIO_ADDR + 0x70)
#define RALINK_REG_PIO5140DIR		(RALINK_PRGIO_ADDR + 0x74)
#define RALINK_REG_PIO5140SET		(RALINK_PRGIO_ADDR + 0x7C)
#define RALINK_REG_PIO5140RESET		(RALINK_PRGIO_ADDR + 0x80)
#define RALINK_REG_PIO5140TOGGLE	(RALINK_PRGIO_ADDR + 0x84)

#elif defined (RALINK_GPIO_HAS_9524)

#define RALINK_REG_PIO3924INT		(RALINK_PRGIO_ADDR + 0x38)
#define RALINK_REG_PIO3924EDGE		(RALINK_PRGIO_ADDR + 0x3C)
#define RALINK_REG_PIO3924RENA		(RALINK_PRGIO_ADDR + 0x40)
#define RALINK_REG_PIO3924FENA		(RALINK_PRGIO_ADDR + 0x44)
#define RALINK_REG_PIO3924DATA		(RALINK_PRGIO_ADDR + 0x48)
#define RALINK_REG_PIO3924DIR		(RALINK_PRGIO_ADDR + 0x4C)
#define RALINK_REG_PIO3924SET		(RALINK_PRGIO_ADDR + 0x54)
#define RALINK_REG_PIO3924RESET		(RALINK_PRGIO_ADDR + 0x58)
#define RALINK_REG_PIO3924TOGGLE	(RALINK_PRGIO_ADDR + 0x5C)

#define RALINK_REG_PIO7140INT		(RALINK_PRGIO_ADDR + 0x60)
#define RALINK_REG_PIO7140EDGE		(RALINK_PRGIO_ADDR + 0x64)
#define RALINK_REG_PIO7140RENA		(RALINK_PRGIO_ADDR + 0x68)
#define RALINK_REG_PIO7140FENA		(RALINK_PRGIO_ADDR + 0x6C)
#define RALINK_REG_PIO7140DATA		(RALINK_PRGIO_ADDR + 0x70)
#define RALINK_REG_PIO7140DIR		(RALINK_PRGIO_ADDR + 0x74)
#define RALINK_REG_PIO7140SET		(RALINK_PRGIO_ADDR + 0x7C)
#define RALINK_REG_PIO7140RESET		(RALINK_PRGIO_ADDR + 0x80)
#define RALINK_REG_PIO7140TOGGLE	(RALINK_PRGIO_ADDR + 0x84)

#define RALINK_REG_PIO9572INT		(RALINK_PRGIO_ADDR + 0x88)
#define RALINK_REG_PIO9572EDGE		(RALINK_PRGIO_ADDR + 0x8C)
#define RALINK_REG_PIO9572RENA		(RALINK_PRGIO_ADDR + 0x90)
#define RALINK_REG_PIO9572FENA		(RALINK_PRGIO_ADDR + 0x94)
#define RALINK_REG_PIO9572DATA		(RALINK_PRGIO_ADDR + 0x98)
#define RALINK_REG_PIO9572DIR		(RALINK_PRGIO_ADDR + 0x9C)
#define RALINK_REG_PIO9572SET		(RALINK_PRGIO_ADDR + 0xA0)
#define RALINK_REG_PIO9572RESET		(RALINK_PRGIO_ADDR + 0xA4)
#define RALINK_REG_PIO9572TOGGLE	(RALINK_PRGIO_ADDR + 0xA8)

#endif

/*
 * Values for the GPIOMODE Register
 */
#define RALINK_GPIOMODE_I2C		0x01
#define RALINK_GPIOMODE_SPI		0x02
#define RALINK_GPIOMODE_UARTF		0x1C
#define RALINK_GPIOMODE_UARTL		0x20
#define RALINK_GPIOMODE_JTAG		0x40
#define RALINK_GPIOMODE_MDIO		0x80

#if defined(RT3052_ASIC_BOARD)
#define RALINK_GPIOMODE_SDRAM		0x100
#define RALINK_GPIOMODE_RGMII		0x200
#endif

#if defined(RT3352_ASIC_BOARD)
#define RALINK_GPIOMODE_GE1		0x200
#define RALINK_GPIOMODE_LNA_G		0x40000
#define RALINK_GPIOMODE_PA_G		0x100000
#define RALINK_GPIOMODE_SPI_CS1		0x400000
#endif

#if defined(RT3883_ASIC_BOARD)
#define RALINK_GPIOMODE_GE1		0x200
#define RALINK_GPIOMODE_GE2		0x400
#define RALINK_GPIOMODE_PCI		0x1800
#define RALINK_GPIOMODE_LNA_A		0x30000
#define RALINK_GPIOMODE_LNA_G		0xC0000
#endif

#if defined(RT5350_ASIC_BOARD)
#define RALINK_GPIOMODE_EPHY_BT		0xC000
#define RALINK_GPIOMODE_SPI_CS1		0x400000
#endif


// if you would like to enable GPIO mode for other pins, please modify this value
// !! Warning: changing this value may make other features(MDIO, PCI, etc) lose efficacy
#define RALINK_GPIOMODE_DFT		(RALINK_GPIOMODE_UARTF)

/*
 * bit is the unit of length
 */
#ifdef RALINK_GPIO_HAS_5124
#define RALINK_GPIO_NUMBER		52
#else
#define RALINK_GPIO_NUMBER		24
#endif
#define RALINK_GPIO_DATA_MASK		0x00FFFFFF
#define RALINK_GPIO_DATA_LEN		24
#define RALINK_GPIO_DIR_IN		0
#define RALINK_GPIO_DIR_OUT		1
#define RALINK_GPIO_DIR_ALLIN		0
#define RALINK_GPIO_DIR_ALLOUT		0x00FFFFFF

#define RALINK_GPIO(x)			(1 << x)

/*
 * structure used at regsitration
 */
typedef struct {
	unsigned int irq;		//request irq pin number
	pid_t pid;			//process id to notify
} ralink_gpio_reg_info;

#define RALINK_GPIO_LED_LOW_ACT		1
#define RALINK_GPIO_LED_INFINITY	4000
typedef struct {
	int gpio;			//gpio number (0 ~ 23)
	unsigned int on;		//interval of led on
	unsigned int off;		//interval of led off
	unsigned int blinks;		//number of blinking cycles
	unsigned int rests;		//number of break cycles
	unsigned int times;		//blinking times
} ralink_gpio_led_info;

#if defined(__KERNEL__) && !defined(RTL8367_SW)
/*
 * variables used at regsitration
 */
int ralink_gpio_major = 252;
int ralink_gpio_irqnum = 0;
u32 ralink_gpio_intp = 0;
u32 ralink_gpio_edge = 0;
#ifdef RALINK_GPIO_HAS_5124
u32 ralink_gpio3924_intp = 0;
u32 ralink_gpio3924_edge = 0;
u32 ralink_gpio5140_intp = 0;
u32 ralink_gpio5140_edge = 0;
#endif
#ifdef RALINK_GPIO_HAS_9524
u32 ralink_gpio3924_intp = 0;
u32 ralink_gpio3924_edge = 0;
u32 ralink_gpio7140_intp = 0;
u32 ralink_gpio7140_edge = 0;
u32 ralink_gpio9572_intp = 0;
u32 ralink_gpio9572_edge = 0;
#endif

/*
 * LED control section
*/

#define RALINK_LED_DEBUG 0
#define RALINK_GPIO_LED_FREQ (HZ/10)
#define RALINK_GPIO_BTN_LONG (2*HZ)
#define RALINK_GPIO_BTN_SHORT (HZ/10)

u32 ra_gpio_led_set = 0;
u32 ra_gpio_led_clr = 0;
#ifdef RALINK_GPIO_HAS_5124
u32 ra_gpio3924_led_set = 0;
u32 ra_gpio3924_led_clr = 0;
u32 ra_gpio5140_led_set = 0;
u32 ra_gpio5140_led_clr = 0;
#endif
#ifdef RALINK_GPIO_HAS_9524
u32 ra_gpio3924_led_set = 0;
u32 ra_gpio3924_led_clr = 0;
u32 ra_gpio7140_led_set = 0;
u32 ra_gpio7140_led_clr = 0;
u32 ra_gpio9572_led_set = 0;
u32 ra_gpio9572_led_clr = 0;
#endif

struct ralink_gpio_led_status_t {
	int ticks;
	unsigned int ons;
	unsigned int offs;
	unsigned int resting;
	unsigned int times;
} ralink_gpio_led_stat[RALINK_GPIO_NUMBER];

int ralink_gpio_led_set(ralink_gpio_led_info led);

#if RALINK_GPIO_LED_LOW_ACT
#define __LED_ON(gpio)      ra_gpio_led_clr |= RALINK_GPIO(gpio);
#define __LED_OFF(gpio)     ra_gpio_led_set |= RALINK_GPIO(gpio);
#define __LED3924_ON(gpio)  ra_gpio3924_led_clr |= RALINK_GPIO((gpio-24));
#define __LED3924_OFF(gpio) ra_gpio3924_led_set |= RALINK_GPIO((gpio-24));
#define __LED5140_ON(gpio)  ra_gpio5140_led_clr |= RALINK_GPIO((gpio-40));
#define __LED5140_OFF(gpio) ra_gpio5140_led_set |= RALINK_GPIO((gpio-40));
#define __LED7140_ON(gpio)  ra_gpio7140_led_clr |= RALINK_GPIO((gpio-40));
#define __LED7140_OFF(gpio) ra_gpio7140_led_set |= RALINK_GPIO((gpio-40));
#define __LED9572_ON(gpio)  ra_gpio9572_led_clr |= RALINK_GPIO((gpio-72));
#define __LED9572_OFF(gpio) ra_gpio9572_led_set |= RALINK_GPIO((gpio-72));
#else
#define __LED_ON(gpio)      ra_gpio_led_set |= RALINK_GPIO(gpio);
#define __LED_OFF(gpio)     ra_gpio_led_clr |= RALINK_GPIO(gpio);
#define __LED3924_ON(gpio)  ra_gpio3924_led_set |= RALINK_GPIO((gpio-24));
#define __LED3924_OFF(gpio) ra_gpio3924_led_clr |= RALINK_GPIO((gpio-24));
#define __LED5140_ON(gpio)  ra_gpio5140_led_set |= RALINK_GPIO((gpio-40));
#define __LED5140_OFF(gpio) ra_gpio5140_led_clr |= RALINK_GPIO((gpio-40));
#define __LED7140_ON(gpio)  ra_gpio7140_led_set |= RALINK_GPIO((gpio-40));
#define __LED7140_OFF(gpio) ra_gpio7140_led_clr |= RALINK_GPIO((gpio-40));
#define __LED9572_ON(gpio)  ra_gpio9572_led_set |= RALINK_GPIO((gpio-72));
#define __LED9572_OFF(gpio) ra_gpio9572_led_clr |= RALINK_GPIO((gpio-72));
#endif
#endif /* __KERNEL__ */

#endif
