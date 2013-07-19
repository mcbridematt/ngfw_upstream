#include "niagara_module.h"
#include "cpld.h"
#include "lock.h"

DECLARE_LOCK(cpu)

static int cpu_wait(int hw)
{
	uint8_t stat;
	int timeout = 0;

	for (;; ) {
		stat = cpld_read(hw, CSR);
		if ((stat & 0x08) == 0) return 0;
		if (++timeout == 10000) break;
		udelay(10);
	}
	MSG("CPLD timeout!");
	return -1;
}



uint8_t cpu_read(int hw, uint8_t offset)
{
	uint8_t res;

	cpu_lock(hw);
	cpld_write(hw, AVR_ADDR, offset);
	cpld_write(hw, CSR, 0x8);
	cpu_wait(hw);
	res = cpld_read(hw, HOST_DAT);
	cpu_unlock(hw);
	return res;
}

uint8_t cpu_write(int hw, uint8_t offset, uint8_t value)
{
	uint8_t res;

	cpu_lock(hw);
	cpld_write(hw, AVR_ADDR, offset);
	cpld_write(hw, AVR_DAT, value);
	cpld_write(hw, CSR, 0xC);
	res = cpu_wait(hw);
	cpu_unlock(hw);
	return res;
}
