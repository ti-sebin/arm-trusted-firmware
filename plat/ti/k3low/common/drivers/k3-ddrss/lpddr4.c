// SPDX-License-Identifier: BSD-3-Clause
/*
 * Cadence DDR Driver
 *
 * Copyright (C) 2012-2026 Cadence Design Systems, Inc.
 * Copyright (C) 2018-2026 Texas Instruments Incorporated - https://www.ti.com/
 */

#include <errno.h>

#include <common/bl_common.h>
#include <common/debug.h>
#include <libfdt.h>

#include "cps_drv_lpddr4.h"
#include "lpddr4.h"
#include "lpddr4_if.h"
#include "lpddr4_structs_if.h"

uint32_t lpddr4_pollctlirq(const lpddr4_privatedata *pd, lpddr4_intr_ctlinterrupt irqbit, uint32_t delay)
{
	uint32_t result = 0U;
	uint32_t timeout = 0U;
	bool irqstatus = false;

	do {
		if (++timeout == delay) {
			result = (uint32_t)EIO;
			break;
		}
		result = lpddr4_checkctlinterrupt(pd, irqbit, &irqstatus);
	} while ((irqstatus == (bool)false) && (result == (uint32_t)0));

	return result;
}

static uint32_t lpddr4_pollphyindepirq(const lpddr4_privatedata *pd, lpddr4_intr_phyindepinterrupt irqbit, uint32_t delay)
{
	uint32_t result = 0U;
	uint32_t timeout = 0U;
	bool irqstatus = false;

	do {
		if (++timeout == delay) {
			result = (uint32_t)EIO;
			break;
		}
		result = lpddr4_checkphyindepinterrupt(pd, irqbit, &irqstatus);
	} while ((irqstatus == (bool)false) && (result == (uint32_t)0));

	return result;
}

static uint32_t lpddr4_pollandackirq(const lpddr4_privatedata *pd)
{
	uint32_t result = 0U;

	result = lpddr4_pollphyindepirq(pd, LPDDR4_INTR_PHY_INDEP_INIT_DONE_BIT, LPDDR4_CUSTOM_TIMEOUT_DELAY);
	if (result != (uint32_t)0) {
		return result;
	}

	result = lpddr4_ackphyindepinterrupt(pd, LPDDR4_INTR_PHY_INDEP_INIT_DONE_BIT);
	if (result != (uint32_t)0) {
		return result;
	}

	result = lpddr4_pollctlirq(pd, LPDDR4_INTR_MC_INIT_DONE, LPDDR4_CUSTOM_TIMEOUT_DELAY);
	if (result != (uint32_t)0) {
		return result;
	}

	result = lpddr4_ackctlinterrupt(pd, LPDDR4_INTR_MC_INIT_DONE);

	return result;
}

static uint32_t lpddr4_startsequencecontroller(const lpddr4_privatedata *pd)
{
	uint32_t result = 0U;
	uint32_t regval = 0U;
	lpddr4_ctlregs *ctlregbase = (lpddr4_ctlregs *)pd->ctlbase;
	lpddr4_infotype infotype;

	regval = CPS_FLD_SET(LPDDR4__PI_START__FLD, CPS_REG_READ(&(ctlregbase->LPDDR4__PI_START__REG)));
	CPS_REG_WRITE((&(ctlregbase->LPDDR4__PI_START__REG)), regval);

	regval = CPS_FLD_SET(LPDDR4__START__FLD, CPS_REG_READ(&(ctlregbase->LPDDR4__START__REG)));
	CPS_REG_WRITE(&(ctlregbase->LPDDR4__START__REG), regval);

	if (pd->infohandler != (lpddr4_infocallback)NULL) {
		infotype = LPDDR4_DRV_SOC_PLL_UPDATE;
		pd->infohandler(pd, infotype);
	}

	result = lpddr4_pollandackirq(pd);

	return result;
}

volatile uint32_t *lpddr4_addoffset(volatile uint32_t *addr, uint32_t regoffset)
{
	volatile uint32_t *local_addr = addr;
	volatile uint32_t *regaddr = &local_addr[regoffset];

	return regaddr;
}

uint32_t lpddr4_probe(const lpddr4_config *config, uint16_t *configsize)
{
	if ((configsize == NULL) || (config == NULL)) {
		return EINVAL;
	}

	*configsize = (uint16_t)(sizeof(lpddr4_privatedata));
	return 0U;
}

uint32_t lpddr4_init(lpddr4_privatedata *pd, const lpddr4_config *cfg)
{
	if ((pd == NULL) || (cfg == NULL)) {
		return EINVAL;
	}

	lpddr4_ctlregs *ctlregbase = (lpddr4_ctlregs *)cfg->ctlbase;
	pd->ctlbase = ctlregbase;
	pd->infohandler = (lpddr4_infocallback)cfg->infohandler;
	pd->ctlinterrupthandler = (lpddr4_ctlcallback)cfg->ctlinterrupthandler;
	pd->phyindepinterrupthandler = (lpddr4_phyindepcallback)cfg->phyindepinterrupthandler;
	return 0U;
}

uint32_t lpddr4_start(const lpddr4_privatedata *pd)
{
	uint32_t result = 0U;

	if (pd == NULL) {
		return EINVAL;
	}

	result = lpddr4_enablepiinitiator(pd);
	if (result != (uint32_t)0) {
		return result;
	}

	result = lpddr4_startsequencecontroller(pd);

	return result;
}

uint32_t lpddr4_readreg(const lpddr4_privatedata *pd, lpddr4_regblock cpp, uint32_t regoffset, uint32_t *regvalue)
{
	if ((pd == NULL) || (regvalue == NULL)) {
		return EINVAL;
	} else if ((cpp != LPDDR4_CTL_REGS) &&
			(cpp != LPDDR4_PHY_REGS) &&
			(cpp != LPDDR4_PHY_INDEP_REGS)) {
		return EINVAL;
	}

	lpddr4_ctlregs *ctlregbase = (lpddr4_ctlregs *)pd->ctlbase;

	if (cpp == LPDDR4_CTL_REGS) {
		if (regoffset >= LPDDR4_INTR_CTL_REG_COUNT) {
			return EINVAL;
		} else {
			*regvalue = CPS_REG_READ(lpddr4_addoffset(&(ctlregbase->DENALI_CTL_0), regoffset));
		}
	} else if (cpp == LPDDR4_PHY_REGS) {
		if (regoffset >= LPDDR4_INTR_PHY_REG_COUNT) {
			return EINVAL;
		} else {
			*regvalue = CPS_REG_READ(lpddr4_addoffset(&(ctlregbase->DENALI_PHY_0), regoffset));
		}

	} else {
		if (regoffset >= LPDDR4_INTR_PHY_INDEP_REG_COUNT) {
			return EINVAL;
		} else {
			*regvalue = CPS_REG_READ(lpddr4_addoffset(&(ctlregbase->DENALI_PI_0), regoffset));
		}
	}

	return 0U;
}

uint32_t lpddr4_writereg(const lpddr4_privatedata *pd, lpddr4_regblock cpp, uint32_t regoffset, uint32_t regvalue)
{
	if (pd == NULL) {
		return EINVAL;
	} else if ((cpp != LPDDR4_CTL_REGS) &&
			(cpp != LPDDR4_PHY_REGS) &&
			(cpp != LPDDR4_PHY_INDEP_REGS)) {
		return EINVAL;
	}

	lpddr4_ctlregs *ctlregbase = (lpddr4_ctlregs *)pd->ctlbase;

	if (cpp == LPDDR4_CTL_REGS) {
		if (regoffset >= LPDDR4_INTR_CTL_REG_COUNT) {
			return EINVAL;
		} else {
			CPS_REG_WRITE(lpddr4_addoffset(&(ctlregbase->DENALI_CTL_0), regoffset), regvalue);
		}
	} else if (cpp == LPDDR4_PHY_REGS) {
		if (regoffset >= LPDDR4_INTR_PHY_REG_COUNT) {
			return EINVAL;
		} else {
			CPS_REG_WRITE(lpddr4_addoffset(&(ctlregbase->DENALI_PHY_0), regoffset), regvalue);
		}
	} else {
		if (regoffset >= LPDDR4_INTR_PHY_INDEP_REG_COUNT) {
			return EINVAL;
		} else {
			CPS_REG_WRITE(lpddr4_addoffset(&(ctlregbase->DENALI_PI_0), regoffset), regvalue);
		}
	}

	return 0U;
}

uint32_t lpddr4_writectlconfigex(const lpddr4_privatedata *pd, const uint32_t regvalues[], uint16_t regcount)
{
	uint32_t result = 0U;
	uint32_t aindex;
	uint32_t reg_val;

	if ((pd == NULL) || (regvalues == (uint32_t *)NULL)) {
		return EINVAL;
	}

	/* Iterate over the config data to convert from device node
	 * format to CPU format.
	 */
	for (aindex = 0; aindex < regcount; aindex++) {
		reg_val = fdt32_to_cpu(regvalues[aindex]);
		result = (uint32_t)lpddr4_writereg(pd, LPDDR4_CTL_REGS, aindex,
							   reg_val);
	}

	return result;
}

uint32_t lpddr4_writephyindepconfigex(const lpddr4_privatedata *pd, const uint32_t regvalues[], uint16_t regcount)
{
	uint32_t result = 0U;
	uint32_t aindex;
	uint32_t reg_val;

	if ((pd == NULL) || (regvalues == (uint32_t *)NULL)) {
		return EINVAL;
	}

	/* Iterate over the config data to convert from device node
	 * format to CPU format.
	 */
	for (aindex = 0; aindex < regcount; aindex++) {
		reg_val = fdt32_to_cpu(regvalues[aindex]);
		result = (uint32_t)lpddr4_writereg(pd, LPDDR4_PHY_INDEP_REGS, aindex,
							   reg_val);
	}

	return result;
}

uint32_t lpddr4_writephyconfigex(const lpddr4_privatedata *pd, const uint32_t regvalues[], uint16_t regcount)
{
	uint32_t result = 0U;
	uint32_t aindex;
	uint32_t reg_val;

	if ((pd == NULL) || (regvalues == (uint32_t *)NULL)) {
		return EINVAL;
	}

	/* Iterate over the config data to convert from device node
	 * format to CPU format.
	 */
	for (aindex = 0; aindex < regcount; aindex++) {
		reg_val = fdt32_to_cpu(regvalues[aindex]);
		result = (uint32_t)lpddr4_writereg(pd, LPDDR4_PHY_REGS, aindex,
							   reg_val);
	}

	return result;
}

uint32_t lpddr4_checkphyindepinterrupt(const lpddr4_privatedata *pd, lpddr4_intr_phyindepinterrupt intr, bool *irqstatus)
{
	uint32_t result = 0;
	uint32_t phyindepirqstatus = 0;

	result = lpddr4_intr_phyint_sf(pd, intr, irqstatus);
	if ((result == (uint32_t)0) && ((uint32_t)intr < WORD_SHIFT)) {
		lpddr4_ctlregs *ctlregbase = (lpddr4_ctlregs *)pd->ctlbase;

		phyindepirqstatus = CPS_REG_READ(&(ctlregbase->LPDDR4__PI_INT_STATUS__REG));
		*irqstatus = (bool)(((phyindepirqstatus >> (uint32_t)intr) & LPDDR4_BIT_MASK) > 0U);
	}
	return result;
}

uint32_t lpddr4_ackphyindepinterrupt(const lpddr4_privatedata *pd, lpddr4_intr_phyindepinterrupt intr)
{
	uint32_t result = 0U;
	uint32_t regval = 0U;

	result = lpddr4_intr_ack_phyint_sf(pd, intr);
	if ((result == (uint32_t)0) && ((uint32_t)intr < WORD_SHIFT)) {
		lpddr4_ctlregs *ctlregbase = (lpddr4_ctlregs *)pd->ctlbase;

		regval = ((uint32_t)LPDDR4_BIT_MASK << (uint32_t)intr);
		CPS_REG_WRITE(&(ctlregbase->LPDDR4__PI_INT_ACK__REG), regval);
	}

	return result;
}
