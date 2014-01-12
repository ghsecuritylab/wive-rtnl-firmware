/*
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */
#ifndef CSR_REG_TEST
#define CSR_REG_TEST

#include "csr_netlink.h"

#define CHIPNAME0_3	0xa0300000
#define CHIPNAME4_7	0xa0300004
#define CHIPID		0xa030000c
#define CPUCFG		0xa0300010

#define IGNORE_VALUE 	0x5a5a5a5a
/* addr def_val reserved_bits write_mask write_value */
RT2880_CSR_MSG csr_msg_table[] = {
	/* System Controller */
  {CSR_WRITE, "CHIPNAM0_3", 	0xa0300000, 0x38325452, 0xffffffff, 	0x38325452},
  {CSR_WRITE, "CHIPNAM4_7", 	0xa0300004, 0x20203038, 0xffffffff, 	0x20203038},
//  {CSR_READ, "CHIPID", 		0xa030000c, 0x00000101, 0xffffffff, 	0},
  {CSR_READ, "CHIPID", 		0xa030000c, 0x00000104, 0xffffffff, 	0},
  {CSR_READ, "CPUCFG", 		0xa0300010, 0x021100c4, 0xffffffff, 	0 /*0xfff*/},
  {CSR_WRITE, "ERRSTAT", 	0xa0300014, 0x00000000, 0x1f00, 	0xffffffff},
  {CSR_WRITE, "TESTSTAT", 	0xa0300018, IGNORE_VALUE, 0xffffffff, 	0xffffffff},
  {CSR_WRITE, "TESTSTAT2", 	0xa030001c, IGNORE_VALUE, 0xffffffff, 	0xffffffff},
// #if 0
  {CSR_READ, "BADDINFO", 	0xa0300020, 0x00000000, 0, 		0x3},
  {CSR_READ, "BADDADDR", 	0xa0300024, 0x00000000, 0, 		0},
  {CSR_READ, "BADIINFO", 	0xa0300028, 0x00000000, 0x1, 		0},
  {CSR_READ, "BADIADDR", 	0xa030002c, 0x00000000, 0, 		0},

  {CSR_READ, "RSTCTRL", 	0xa0300034, 0x00000000, 0, 		0},
  {CSR_READ, "RSTSTAT", 	0xa0300038, 0x00000000, 0, 		0},
  {CSR_READ, "GPIOMODE", 	0xa0300060, /* 0x00000000 */ IGNORE_VALUE, 0, 		0},
  {CSR_READ, "PCIPDMA_STAT", 	0xa0300064, 0x00000000, 0, 		0},
// #endif
  {CSR_READ, "RSTSTAT", 	0xa0300038, IGNORE_VALUE, 0, 0},
  {CSR_WRITE, "PLLCFG", 	0xa0300040, 0x00000000, 0xffff0007, 	0xffffffff},
  {CSR_WRITE, "PLLSTAT", 	0xa0300044, 0x00000000, 0, 0x1},
  {CSR_WRITE, "DLLCFG", 	0xa0300048, 0x00000001, 0, 0xffffffff},
  {CSR_READ, "DLLSTAT", 	0xa030004c, 0x00000000, 0, 0x1},
  
  	/* Timer */
  {CSR_WRITE, "TMRSTAT", 	0xa0300100, IGNORE_VALUE, 0, 0xffffffff},
  {CSR_WRITE, "TMR0LOAD", 	0xa0300110, IGNORE_VALUE, 0, 0xffffffff},
  {CSR_WRITE, "TMR0VAL", 	0xa0300114, IGNORE_VALUE, 0, 0xffffffff},
  {CSR_WRITE, "TMR0CTL", 	0xa0300118, IGNORE_VALUE, 0, 0xffffffff},
  {CSR_WRITE, "TMR1LOAD", 	0xa0300120, IGNORE_VALUE, 0, 0xffffffff},
  {CSR_WRITE, "TMR1VAL", 	0xa0300124, IGNORE_VALUE, 0, 0xffffffff},
  {CSR_WRITE, "TMR1CTL", 	0xa0300128, IGNORE_VALUE, 0, 0xffffffff},
  
  	/* Interrupt Controller */
  {CSR_READ, "IRQ0STAT", 	0xa0300200, 0x00000000, 0, 0 /*0xffffffff*/ },
  {CSR_READ, "IRQ1STAT", 	0xa0300204, 0x00000000, 0, 0 /*0xffffffff*/ },
  {CSR_READ, "INTTYPE", 	0xa0300220, 0x00000000, 0, 0 /*0xffffffff*/ },
  {CSR_WRITE, "INTRAW", 	0xa0300230, IGNORE_VALUE, 0, 0xffffffff},
  {CSR_WRITE, "INTENA", 	0xa0300234, IGNORE_VALUE, 0, 0xffffffff},
  {CSR_READ,  "INTDIS", 	0xa0300238, IGNORE_VALUE, 0, 0 /*0xffffffff*/ },
  
  	/* UART	*/
  {CSR_WRITE, "RBR", 		0xa0300500, IGNORE_VALUE, 0, 0xffffffff},
  {CSR_WRITE, "TBR", 		0xa0300504, IGNORE_VALUE, 0, 0xffffffff},
  {CSR_WRITE, "IER", 		0xa0300508, IGNORE_VALUE, 0, 0xffffffff},
  {CSR_WRITE, "IIR", 		0xa030050C, IGNORE_VALUE, 0, 0xffffffff},
  {CSR_WRITE, "FCR", 		0xa0300510, IGNORE_VALUE, 0, 0xffffffff},
  {CSR_WRITE, "LCR", 		0xa0300514, IGNORE_VALUE, 0, 0xffffffff},
  {CSR_WRITE, "MCR", 		0xa0300518, IGNORE_VALUE, 0, 0xffffffff},
  {CSR_WRITE, "LSR", 		0xa030051c, IGNORE_VALUE, 0, 0xffffffff},
  {CSR_WRITE, "MSR", 		0xa0300520, IGNORE_VALUE, 0, 0xffffffff},
  {CSR_WRITE, "SCRATCH", 	0xa0300524, IGNORE_VALUE, 0, 0xffffffff},
  {CSR_WRITE, "DL", 		0xa0300528, IGNORE_VALUE, 0, 0xffffffff},
  {CSR_WRITE, "DLLO", 		0xa030052c, IGNORE_VALUE, 0, 0xffffffff},
  {CSR_WRITE, "DLHI", 		0xa0300530, IGNORE_VALUE, 0, 0xffffffff},
  
	/* Programming I/O */  
  {CSR_READ, "PIOINT", 		0xa0300600, 0x00000000, 0, 0},
  {CSR_WRITE, "PIOEDGE",	0xa0300604, IGNORE_VALUE, 0, 0xffffffff},
  {CSR_WRITE, "PIORMASK",	0xa0300608, IGNORE_VALUE, 0, 0xffffffff},
  {CSR_WRITE, "PIOFMASK",	0xa030060C, IGNORE_VALUE, 0, 0xffffffff},
// #if 0
  {CSR_READ, "PIODATA",		0xa0300620, IGNORE_VALUE, 0, 0},
// #endif
  {CSR_WRITE, "PIODIR", 	0xa0300624, IGNORE_VALUE, 0, 0xffffffff},
  {CSR_WRITE, "PIOPOL", 	0xa0300628, IGNORE_VALUE, 0, 0xffffffff},
  {CSR_WRITE, "PIOSET", 	0xa030062C, 0x00000000, 0, 0xffffffff},
  {CSR_WRITE, "PIORESET", 	0xa0300630, 0x00000000, 0, 0xffffffff},
  {CSR_WRITE, "PIOTOG", 	0xa0300634, 0x00000000, 0, 0xffffffff},

/* define in 0.18 beta, update by bobtseng --- removed in real asic version, 2006.11.21.*/  
#if 0
  {CSR_WRITE, "PIOSET", 	0xa030062c, 0x00000000, 0, 0xffffffff},
  {CSR_WRITE, "PIORESET", 	0xa0300630, 0x00000000, 0, 0xffffffff},
  {CSR_WRITE, "PIOTOG", 	0xa0300634, 0x00000000, 0, 0xffffffff},
  {CSR_WRITE, "PIOPWM0", 	0xa0300680, 0x00000000, 0, 0xffffffff},
  {CSR_WRITE, "PIOPWM1", 	0xa0300684, 0x00000000, 0, 0xffffffff},
  {CSR_WRITE, "PIOPWM2", 	0xa0300688, 0x00000000, 0, 0xffffffff},
  {CSR_WRITE, "PIOPWM3", 	0xa030068c, 0x00000000, 0, 0xffffffff},
#endif
/* end of update */  

#if 0	/* useless */  
  {CSR_WRITE, "BTNINT", 	0xa0300640, 0x00000000, 0, 0xffffffff},
  {CSR_WRITE, "BTNEDGE",	0xa0300644, 0x00000000, 0, 0xffffffff},
  {CSR_WRITE, "BTNRMASK",	0xa0300648, 0x00000000, 0, 0xffffffff},
  {CSR_WRITE, "BTNFMASK",	0xa030064c, 0x00000000, 0, 0xffffffff},
  {CSR_WRITE, "PIODATA2",	0xa0300660, 0x00000000, 0, 0xffffffff},
  {CSR_WRITE, "PIOPOL2", 	0xa0300664, 0x00000000, 0, 0xffffffff},
  {CSR_WRITE, "LEDCFG", 	0xa0300668, 0x00000000, 0, 0xffffffff},
#endif

	/* LCD Controller */
  {CSR_WRITE, "LCDSTAT",	0xa0300800, 0xbaddbadd, 0, 0xffffffff},
  {CSR_WRITE, "LCDINT",		0xa0300804, 0xbaddbadd, 0, 0xffffffff},
  {CSR_WRITE, "LCDINTEN",	0xa0300808, 0xbaddbadd, 0, 0xffffffff},
  {CSR_WRITE, "LCDXFG",		0xa0300820, 0xbaddbadd, 0, 0xffffffff},
  {CSR_WRITE, "LCDPARAM",	0xa0300824, 0xbaddbadd, 0, 0xffffffff},
  {CSR_WRITE, "CTLDATAR",	0xa0300830, 0xbaddbadd, 0, 0xffffffff},
  {CSR_WRITE, "DISPDATAR",	0xa0300834, 0xbaddbadd, 0, 0xffffffff},
  
  	/* I2C Interface Controller */
  {CSR_WRITE, "CONFIG",		0xa0300900, IGNORE_VALUE, 0, 0xffffffff},
  {CSR_WRITE, "CLKDIV",		0xa0300904, IGNORE_VALUE, 0, 0xffffffff},
  {CSR_WRITE, "DEVADDR",	0xa0300908, IGNORE_VALUE, 0, 0xffffffff},
  {CSR_WRITE, "ADDR",		0xa030090c, IGNORE_VALUE, 0, 0xffffffff},
  {CSR_WRITE, "DATAOUT",	0xa0300910, IGNORE_VALUE, 0, 0xffffffff},
  {CSR_WRITE, "DATAIN",		0xa0300914, 0x00000000, 0, 0xffffffff},
  {CSR_WRITE, "STATUS",		0xa0300918, IGNORE_VALUE, 0, 0xffffffff},
  {CSR_WRITE, "STARTXFR",	0xa030091c, 0x00000000, 0, 0xffffffff},
  {CSR_WRITE, "BYTECNT",	0xa0300920, IGNORE_VALUE, 0, 0xffffffff},  
  
  	/* Real Time Clock */
  {CSR_WRITE, "RTCCTL",		0xa0300a00, 0xbaddbadd, 0, 0xffffffff},
  {CSR_WRITE, "RTCINT",		0xa0300a04, 0xbaddbadd, 0, 0xffffffff},
  {CSR_WRITE, "YEAR",		0xa0300a08, 0xbaddbadd, 0, 0xffffffff},
  {CSR_WRITE, "TIME",		0xa0300a10, 0xbaddbadd, 0, 0xffffffff},
  {CSR_WRITE, "TIMEALRM",	0xa0300a14, 0xbaddbadd, 0, 0xffffffff},
  {CSR_WRITE, "RTCPER",		0xa0300a18, 0xbaddbadd, 0, 0xffffffff},
  	
  	/* SPI Interface Controller */
  {CSR_READ, "SPIRAW",		0xa0300b00, 0x00000000, 0, 0},
  {CSR_READ, "SPIINT",		0xa0300b04, 0x00000000, 0, 0},
  {CSR_READ, "SPIMSK",		0xa0300b08, 0x00000000, 0, 0},
  {CSR_WRITE, "SPICFG",		0xa0300b10, IGNORE_VALUE, 0, 0xffffffff},
  {CSR_WRITE, "SPIDIR",		0xa0300b14, IGNORE_VALUE, 0, 0xffffffff},
  {CSR_WRITE, "SPICTL",		0xa0300b18, 0x00000000, 0, 0xffffffff},
  {CSR_WRITE, "SPIDATA",	0xa0300b20, IGNORE_VALUE, 0, 0xffffffff},
  {CSR_WRITE, "SPIRDATA",	0xa0300b24, 0x00000000, 0, 0xffffffff},
  	
  	/* UART Lite */
  {CSR_READ, "RBR", 		0xa0300c00, IGNORE_VALUE, 0, 0},
  {CSR_READ, "TBR", 		0xa0300c04, IGNORE_VALUE, 0, 0},
  {CSR_READ, "IER", 		0xa0300c08, IGNORE_VALUE, 0, 0},
  {CSR_READ, "IIR", 		0xa0300c0C, 0x000000c1, 0, 0},
  {CSR_READ, "FCR", 		0xa0300c10, 0x00000081, 0, 0},
  {CSR_READ, "LCR", 		0xa0300c14, 0x00000013, 0, 0},
  {CSR_READ, "MCR", 		0xa0300c18, 0x00000000, 0, 0},
  {CSR_READ, "LSR", 		0xa0300c1c, IGNORE_VALUE, 0, 0},
  {CSR_READ, "DL", 		0xa0300c28, IGNORE_VALUE, 0, 0},
  {CSR_READ, "DLLO", 		0xa0300c2c, IGNORE_VALUE, 0, 0},
  {CSR_READ, "DLHI", 		0xa0300c30, IGNORE_VALUE, 0, 0},
  {CSR_READ, "IFCTL", 		0xa0300c34, IGNORE_VALUE, 0, 0},
  	
  	/* Memory Controller */
  {CSR_READ, "SDRAM_CFG0", 	0xa0300300, IGNORE_VALUE, 0, 0},
  {CSR_READ, "SDRAM_CFG1", 	0xa0300304, IGNORE_VALUE, 0, 0},
  {CSR_READ, "FLASH_CFG0", 	0xa0300308, IGNORE_VALUE, 0, 0},
  {CSR_READ, "FLASH_CFG1", 	0xa030030C, 0x0511ffa1, 0, 0},
  
  	/* PCI Host Controller */
  {CSR_READ, "PCICFG", 		0xa0440000, IGNORE_VALUE, 0, 0},
  {CSR_READ, "PCIRAW",		0xa0440004, IGNORE_VALUE, 0, 0},
#if 0
  {CSR_READ, "PCIINT",		0xa0440008, 0x00000000, 0, 0},
  {CSR_READ, "PCIMSK",		0xa044000c, IGNORE_VALUE, 0, 0xffffffff},
#endif
  {CSR_READ, "BAR0SETUP",	0xa0440010, IGNORE_VALUE, 0, 0xffffffff},
  {CSR_READ, "BAR1SETUP", 	0xa0440014, 0x00000000, 0, 0xffffffff},
  {CSR_READ, "IMBASEBAR0",	0xa0440018, 0x00000000, 0, 0xffffffff},
  {CSR_READ, "IMBASEBAR1", 	0xa044001c, 0x00000000, 0, 0xffffffff},
  {CSR_READ, "CFGADDR",		0xa0440020, IGNORE_VALUE, 0, 0xffffffff},
  {CSR_READ, "CFGDATA",		0xa0440024, 0x00000000, 0, 0xffffffff},
  {CSR_READ, "MEMBASE",		0xa0440028, 0x20000000, 0, 0},
  {CSR_READ, "IOBASE",		0xa044002c, IGNORE_VALUE, 0, 0},
  {CSR_READ, "ARBCTL",		0xa0440080, IGNORE_VALUE, 0, 0xffffffff},
  
  	/* Frame Engine Global */
  {CSR_READ, "MDIO_ACCESS",	0x00400000, IGNORE_VALUE, 0, 0},
  {CSR_READ, "MDIO_CFG",	0x00400004, IGNORE_VALUE, 0, 0},
  {CSR_READ, "FE_DMA_CLO",	0x00400008, IGNORE_VALUE, 0, 0},
  {CSR_READ, "FE_RST_GLO",	0x0040000c, IGNORE_VALUE, 0, 0},
  {CSR_READ, "FE_INT_STATUS",	0x00400010, IGNORE_VALUE, 0, 0},
  {CSR_READ, "FE_INT_ENABLE", 	0x00400014, IGNORE_VALUE, 0, 0},
  {CSR_READ, "FC_DROP_STA",	0x00400018, IGNORE_VALUE, 0, 0},
  {CSR_READ, "FOE_TS_T", 	0x0040001c, IGNORE_VALUE, 0, 0},
  	
  	/* GDMA Related */
  {CSR_READ, "GDMA1_FWD_CFG",	0x00400020, IGNORE_VALUE, 0, 0},
  {CSR_READ, "GDMA1_SCH_CFG",	0x00400024, IGNORE_VALUE, 0, 0},
  {CSR_READ, "GDMA1_SHRP_CFG",	0x00400028, IGNORE_VALUE, 0, 0},
  {CSR_READ, "GDMA1_MAC_ADRL",	0x0040002c, IGNORE_VALUE, 0, 0},
  {CSR_READ, "GDMA1_MAC_ADRH",	0x00400030, IGNORE_VALUE, 0, 0},
  	
  	/* PSE Related */
  {CSR_READ, "dummy",		0x00400040, IGNORE_VALUE, 0, 0},
  {CSR_READ, "PSE_FQFC_CFG",	0x00400040, 0x80504000, 0, 0},
  {CSR_READ, "GDMA1_FC_CFG",	0x00400044, 0x1c101010, 0, 0},
  {CSR_READ, "GDMA_FC_CFG",	0x00400048, 0x1c101010, 0, 0},
  {CSR_READ, "dummy",		0x0040004c, IGNORE_VALUE, 0, 0},
  {CSR_READ, "CDMA_OQ_STA",	0x0040004c, 0x00000000, 0, 0},
  {CSR_READ, "GDMA1_OQ_STA",	0x00400050, 0x00000000, 0, 0},
  {CSR_READ, "PPE_OQ_STA", 	0x00400054, 0x00000000, 0, 0},
  {CSR_READ, "PSE_IQ_STA",	0x00400058, 0x00000000, 0, 0},
  {CSR_READ, "FQ_STA", 		0x00400060, 0x00000000, 0, 0},
#if 0  	
  	/* CDMA Related */
  {CSR_READ, "CDMA_CSG_CFG",	0x00400080, 0x81000000, 0, 0},
  {CSR_READ, "CDMA_SCH_CFG",	0x00400084, 0x00003210, 0, 0},
  {CSR_READ, "dummy",		0x00400088, 0x00000000, 0, 0},
  {CSR_READ, "PPPOE_SID_0001",	0x00400088, 0x00000000, 0, 0},
  {CSR_READ, "PPPOE_SID_0203",	0x0040008c, 0x00000000, 0, 0},
  {CSR_READ, "PPPOE_SID_0405",	0x00400090, 0x00000000, 0, 0},
  {CSR_READ, "PPPOE_SID_0607",	0x00400094, 0x00000000, 0, 0},
  {CSR_READ, "PPPOE_SID_0809",	0x00400098, 0x00000000, 0, 0},
  {CSR_READ, "PPPOE_SID_1011",	0x0040009c, 0x00000000, 0, 0},
  {CSR_READ, "PPPOE_SID_1213",	0x004000a0, 0x00000000, 0, 0},
  {CSR_READ, "PPPOE_SID_1415",	0x004000a4, 0x00000000, 0, 0},
  {CSR_READ, "VLAN_ID_0001",	0x004000a8, 0x00000000, 0, 0},
  {CSR_READ, "VLAN_ID_0203",	0x004000ac, 0x00000000, 0, 0},
  {CSR_READ, "VLAN_ID_0405",	0x004000b0, 0x00000000, 0, 0},
  {CSR_READ, "VLAN_ID_0607",	0x004000b4, 0x00000000, 0, 0},
  {CSR_READ, "VLAN_ID_0809",	0x004000b8, 0x00000000, 0, 0},
  {CSR_READ, "VLAN_ID_1011",	0x004000bc, 0x00000000, 0, 0},
  {CSR_READ, "VLAN_ID_1213",	0x004000c0, 0x00000000, 0, 0},
  {CSR_READ, "VLAN_ID_1415",	0x004001c4, 0x00000000, 0, 0},
#endif  	
  	/* PDMA Related */
  {CSR_READ, "PDMA_GLO_CFG",	0x00400100, IGNORE_VALUE, 0, 0},
  {CSR_READ, "PDMA_RST_IDX",	0x00400104, IGNORE_VALUE, 0, 0},
  {CSR_READ, "PDMA_SCH_CFG",	0x00400108, IGNORE_VALUE, 0, 0},
  {CSR_READ, "DELAY_INT_CFG",	0x0040010c, IGNORE_VALUE, 0, 0},
  {CSR_READ, "TX_BASE_PTR0",	0x00400110, IGNORE_VALUE, 0, 0},
  {CSR_READ, "TX_MAX_CNT0",	0x00400114, IGNORE_VALUE, 0, 0},
  {CSR_READ, "TX_CTX_IDX0",	0x00400118, IGNORE_VALUE, 0, 0},
  {CSR_READ, "TX_DTX_IDX0",	0x0040011c, IGNORE_VALUE, 0, 0},
  {CSR_READ, "TX_BASE_PTR1",	0x00400120, IGNORE_VALUE, 0, 0},
  {CSR_READ, "TX_MAX_CNT1",	0x00400124, IGNORE_VALUE, 0, 0},
  {CSR_READ, "TX_CTX_IDX1",	0x00400128, IGNORE_VALUE, 0, 0},
  {CSR_READ, "TX_DTX_IDX1",	0x0040012c, IGNORE_VALUE, 0, 0},
  {CSR_READ, "RX_BASE_PTR0",	0x00400130, IGNORE_VALUE, 0, 0},
  {CSR_READ, "RX_MAX_CNT0",	0x00400134, IGNORE_VALUE, 0, 0},
  {CSR_READ, "RX_CALC_IDX0",	0x00400138, IGNORE_VALUE, 0, 0},
  {CSR_READ, "RX_DRX_IDX0",	0x0040013c, IGNORE_VALUE, 0, 0}
};

#define MAX	(sizeof(csr_msg_table)/sizeof(struct rt2880_csr_msg))

char* cmd_option[] = {"-r", "-w", "-csrtest" };

enum option_type {CMD_READ = 0, CMD_WRITE = 1, CMD_CSRTEST = 2};

#endif
