/*
 * pic.c - Source file for the Programmable Interrupt Controller (PIC).
 *
 * Author: Philip R. Simonson
 * Date: 12/22/2020
 *
 **************************************************************************
 */

#include "system.h"
#include "ports.h"
#include "pic.h"

// PIC 1 register port addresses.
#define I86_PIC1_REG_COMMAND 0x20
#define I86_PIC1_REG_STATUS 0x20
#define I86_PIC1_REG_DATA 0x21
#define I86_PIC1_REG_IMR 0x21

// PIC 2 register port addresses.
#define I86_PIC2_REG_COMMAND 0xA0
#define I86_PIC2_REG_STATUS 0xA0
#define I86_PIC2_REG_DATA 0xA1
#define I86_PIC2_REG_IMR 0xA2

// Initialization control word 1 bit masks.
#define I86_PIC_ICW1_MASK_IC4 0x1
#define I86_PIC_ICW1_MASK_SNGL 0x2
#define I86_PIC_ICW1_MASK_ADI 0x4
#define I86_PIC_ICW1_MASK_LTIM 0x8
#define I86_PIC_ICW1_MASK_INIT 0x10

// Initialization control word 4 bit masks.
#define I86_PIC_ICW4_MASK_UPM 0x1
#define I86_PIC_ICW4_MASK_AEOI 0x2
#define I86_PIC_ICW4_MASK_MS 0x4
#define I86_PIC_ICW4_MASK_BUF 0x8
#define I86_PIC_ICW4_MASK_SFNM 0x10

// Initialization command 1 control bits.
#define I86_PIC_ICW1_IC4_EXPECT 1
#define I86_PIC_ICW1_IC4_NO 0
#define I86_PIC_ICW1_SNGL_YES 2
#define I86_PIC_ICW1_SNGL_NO 0
#define I86_PIC_ICW1_ADI_CALLINTERVAL4 4
#define I86_PIC_ICW1_ADI_CALLINTERVAL8 0
#define I86_PIC_ICW1_LTIM_LEVELTRIGGERED 8
#define I86_PIC_ICW1_LTIM_EDGETRIGGERED 0
#define I86_PIC_ICW1_INIT_YES 0x10
#define I86_PIC_ICW1_INIT_NO 0

// Initialization command 4 control bits.
#define I86_PIC_ICW4_UPM_86MODE 1
#define I86_PIC_ICW4_UPM_MCSMODE 0
#define I86_PIC_ICW4_AEOI_AUTOEOI 2
#define I86_PIC_ICW4_AEOI_NOAUTOEOI 0
#define I86_PIC_ICW4_MS_BUFFERMASTER 4
#define I86_PIC_ICW4_MS_BUFFERSLAVE 0
#define I86_PIC_ICW4_BUF_MODEYES 8
#define I86_PIC_ICW4_BUF_MODENO 0
#define I86_PIC_ICW4_SFNM_NESTEDMODE 0x10
#define I86_PIC_ICW4_SFNM_NOTNESTED 0

/* Read data byte from PIC.
 */
u8_t i86_pic_read_data(u8_t picno)
{
	if(picno > 1) return 0;

	u8_t reg = (picno == 1) ? I86_PIC2_REG_COMMAND : I86_PIC1_REG_COMMAND;
	return inb(reg);
}
/* Send data byte to PIC.
 */
void i86_pic_send_data(u8_t data, u8_t picno)
{
	if(picno > 1) return;

	u8_t reg = (picno == 1) ? I86_PIC2_REG_COMMAND : I86_PIC1_REG_COMMAND;
	outb(reg, data);
}
/* Send operational command to PIC.
 */
void i86_pic_send_command(u8_t cmd, u8_t picno)
{
	if(picno > 1) return;

	u8_t reg = (picno == 1) ? I86_PIC2_REG_COMMAND : I86_PIC1_REG_COMMAND;
	outb(reg, cmd);
}
/* Initialize PIC.
 */
void i86_pic_init(u8_t base0, u8_t base1)
{
	u8_t icw = 0;

	// Disable hardware interrupts.
	disable();

	// Begin Initialization of PIC.
	icw = (icw & ~I86_PIC_ICW1_MASK_INIT) | I86_PIC_ICW1_INIT_YES;
	icw = (icw & ~I86_PIC_ICW1_MASK_IC4) | I86_PIC_ICW1_IC4_EXPECT;
	i86_pic_send_command(icw, 0);
	i86_pic_send_command(icw, 1);

	// Send initialization control word 2.
	i86_pic_send_data(base0, 0);
	i86_pic_send_data(base1, 1);

	// Send initialization control word 3.
	i86_pic_send_data(0x04, 0);
	i86_pic_send_data(0x02, 1);

	// Send Initialization control word 4.
	icw = (icw & ~I86_PIC_ICW4_MASK_UPM) | I86_PIC_ICW4_UPM_86MODE;
	i86_pic_send_data(icw, 0);
	i86_pic_send_data(icw, 1);
}
