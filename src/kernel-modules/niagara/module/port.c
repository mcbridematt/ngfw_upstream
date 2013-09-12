#include "niagara_module.h"
#include "cpld.h"
#include "cpu.h"

#include "ixgbe.h"


static int fiber_port_status(int card, int port)
{
	switch (cards[card].product_id) { // TODO. not elegant, but nothing better for now
	case N32285_ID:
	case N32710_ID:
	default:
		return (cpld_read(card, F_SR) & (1 << port)) ? 1 : 0;
	case N2282_ID:
		return (cpld_read(card, CTL_0) & (1 << port)) ? 1 : 0;
	}
}

static int phy_read(uint8_t *hw, uint8_t offset, uint16_t *value)
{
	uint32_t val = 0, i;

	val = PHY_RD_OP | PHY_ADDR_MSK | (PHY_REG_MSK & (offset << 16));

	N22XX_WRITE_REG(hw, MDI_CTL, val);

	for (i = 0; i < MAX_PHY_RETRY; i++) {
		udelay(60);
		val = N22XX_READ_REG(hw, MDI_CTL);
		if (val & PHY_RDY_MSK) {
			*value = 0x0FFFF & val;
			return 0;
		}
	}
	return -1;
}
static int phy_write(uint8_t *hw, uint8_t offset, uint16_t value)
{
	uint32_t val = 0, i;

	val = PHY_WR_OP | PHY_ADDR_MSK | (PHY_REG_MSK & (offset << 16)) | (value & 0x0FFFF);

	N22XX_WRITE_REG(hw, MDI_CTL, val);

	for (i = 0; i < MAX_PHY_RETRY; i++) {
		udelay(60);
		val = N22XX_READ_REG(hw, MDI_CTL);
		if (val & PHY_RDY_MSK)
			return 0;
	}
	return -1;
}



int port_get(int card, int segment, int port)
{
	uint16_t phy_stat;
	port += segment * 2;
	if (is_fiber(card))
		return fiber_port_status(card, port);
	if((cards[card].flags&F_DRIVER)==F_IXGBE){ 
		return 1;
	}
	if (phy_read(hw_port[card][port], PHY_STATUS, &phy_stat)) {
		DBG("Error in phy_read");
		return -1;
	}
	return (phy_stat & MII_SR_LINK_STATUS) ? 1 : 0;
}

int port_set(int card, int segment, int port, int up)
{
	uint16_t val = 0;
	uint32_t led = 0;

	if (is_fiber(card)) {
		unsigned char current_mode[] = {
			CURRENT_MODE_REG_A,
			CURRENT_MODE_REG_B,
			CURRENT_MODE_REG_C,
			CURRENT_MODE_REG_D,
		};
		val = cpld_read(card, current_mode[segment]);
		if (up)
			val |= 1 << port;
		else
			val &= ~(1 << port);
		cpld_write(card, current_mode[segment], val);
		return 0;
	}
	phy_read(hw_port[card][segment * 2 + port], PHY_CTL_REG, &val);
	if (up) {
		val &= ~PHY_PWR_DWN_MSK; /* disable pwr down*/
		led = N22XX_READ_REG(hw_port[card][segment * 2 + port], LED_CTL);
		led &= ~(0xF);
		led |= 0x2;
		N22XX_WRITE_REG(hw_port[card][segment * 2 + port], LED_CTL, led);
	} else {
		val |= PHY_PWR_DWN_MSK; /* set pwr down*/
		led = N22XX_READ_REG(hw_port[card][segment * 2 + port], LED_CTL);
		N22XX_WRITE_REG(hw_port[card][segment * 2 + port], LED_CTL, led | 0x0F);
	}
	phy_write(hw_port[card][segment * 2 + port], PHY_CTL_REG, val);
	return 0;
}
