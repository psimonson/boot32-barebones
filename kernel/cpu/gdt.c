/*
 * gdt.c - Source file for Global Descriptor Table (GDT).
 *
 * Author: Philip R. Simonson
 * Date: 12/20/2020
 *
 *********************************************************************
 */

#include "gdt.h"
#include "helper.h"

// Processor GDTR register points to base of GDT.
struct gdtr {
	u16_t m_limit;
	u32_t m_base;
};

// Global descriptor table is an array of descriptors.
static struct gdt_descriptor _gdt[MAX_DESCRIPTORS];
static struct gdtr _gdtr;

/* ------------------------- Private Functions ------------------------- */

/* Install GDTR through inline assembler.
 */
static void gdt_install(void)
{
	__asm__ __volatile__("lgdtl (%0)" : : "r"(&_gdtr));
}

/* ------------------------- Public Functions -------------------------- */

/* Setup a descriptor in the GDT.
 */
void gdt_set_descriptor(u32_t i, u64_t base, u64_t limit, u8_t access,
	u8_t grand)
{
	if(i > MAX_DESCRIPTORS) return;

	// Null out descriptor table.
	memset((void*)&_gdt[i], 0, sizeof(struct gdt_descriptor));

	// Set limit and base addresses
	_gdt[i].base_low = (u16_t)(base & 0xffff);
	_gdt[i].base_mid = (u8_t)((base >> 16) & 0xff);
	_gdt[i].base_high = (u8_t)((base >> 24) & 0xff);
	_gdt[i].limit = (u16_t)(limit & 0xffff);

	// Set flags and grandularity bytes.
	_gdt[i].flags = access;
	_gdt[i].grand = (u8_t)((limit >> 16) & 0x0f);
	_gdt[i].grand |= grand & 0xf0;
}
/* Return a descriptor.
 */
struct gdt_descriptor *i86_gdt_get_descriptor(int i)
{
	return (i > MAX_DESCRIPTORS) ? 0 : &_gdt[i];
}
/* Initialize the GDT.
 */
void i86_gdt_init(void)
{
	// Set up gdtr
	_gdtr.m_limit = (sizeof(struct gdt_descriptor) * MAX_DESCRIPTORS) - 1;
	_gdtr.m_base = (u32_t)&_gdt[0];

	// Set NULL descriptor.
	gdt_set_descriptor(0, 0, 0, 0, 0);

	// Set default code descriptor.
	gdt_set_descriptor(1, 0, 0xffffffff,
		I86_GDT_DESC_READWRITE | I86_GDT_DESC_EXEC_CODE |
		I86_GDT_DESC_CODEDATA | I86_GDT_DESC_MEMORY,
		I86_GDT_GRAND_4K | I86_GDT_GRAND_32BIT | I86_GDT_GRAND_LIMITHI_MASK);

	// Set default data descriptor.
	gdt_set_descriptor(2, 0, 0xffffffff,
		I86_GDT_DESC_READWRITE | I86_GDT_DESC_CODEDATA | I86_GDT_DESC_MEMORY,
		I86_GDT_GRAND_4K | I86_GDT_GRAND_32BIT | I86_GDT_GRAND_LIMITHI_MASK);

	// Install GDT.
	gdt_install();
}
