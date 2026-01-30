/* SPDX-License-Identifier: BSD-3-Clause */
/*
 * Cadence DDR Driver
 *
 * Copyright (C) 2012-2026 Cadence Design Systems, Inc.
 * Copyright (C) 2018-2026 Texas Instruments Incorporated - https://www.ti.com/
 */

#ifndef LPDDR4_IF_H
#define LPDDR4_IF_H

#include <inttypes.h>
#include <stdbool.h>

#include <lpddr4_16bit_if.h>

typedef struct lpddr4_config_s lpddr4_config;
typedef struct lpddr4_privatedata_s lpddr4_privatedata;

typedef enum {
	LPDDR4_CTL_REGS		= 0U,
	LPDDR4_PHY_REGS		= 1U,
	LPDDR4_PHY_INDEP_REGS	= 2U
} lpddr4_regblock;

typedef enum {
	LPDDR4_DRV_NONE				= 0U,
	LPDDR4_DRV_SOC_PLL_UPDATE		= 1U,
	LPDDR4_DRV_SOC_PHY_REDUCED_FREQ		= 2U,
	LPDDR4_DRV_SOC_PHY_DATA_RET_ASSERT	= 3U,
	LPDDR4_DRV_SOC_PHY_DATA_RET_DEASSERT	= 4U
} lpddr4_infotype;

typedef void (*lpddr4_infocallback)(const lpddr4_privatedata *pd, lpddr4_infotype infotype);

typedef void (*lpddr4_ctlcallback)(const lpddr4_privatedata *pd, lpddr4_intr_ctlinterrupt ctlinterrupt, uint8_t chipselect);

typedef void (*lpddr4_phyindepcallback)(const lpddr4_privatedata *pd, lpddr4_intr_phyindepinterrupt phyindepinterrupt, uint8_t chipselect);

uint32_t lpddr4_probe(const lpddr4_config *config, uint16_t *configsize);

uint32_t lpddr4_init(lpddr4_privatedata *pd, const lpddr4_config *cfg);

uint32_t lpddr4_start(const lpddr4_privatedata *pd);

uint32_t lpddr4_readreg(const lpddr4_privatedata *pd, lpddr4_regblock cpp, uint32_t regoffset, uint32_t *regvalue);

uint32_t lpddr4_writereg(const lpddr4_privatedata *pd, lpddr4_regblock cpp, uint32_t regoffset, uint32_t regvalue);

uint32_t lpddr4_writectlconfigex(const lpddr4_privatedata *pd, const uint32_t regvalues[], uint16_t regcount);

uint32_t lpddr4_writephyconfigex(const lpddr4_privatedata *pd, const uint32_t regvalues[], uint16_t regcount);

uint32_t lpddr4_writephyindepconfigex(const lpddr4_privatedata *pd, const uint32_t regvalues[], uint16_t regcount);

uint32_t lpddr4_checkctlinterrupt(const lpddr4_privatedata *pd, lpddr4_intr_ctlinterrupt intr, bool *irqstatus);

uint32_t lpddr4_ackctlinterrupt(const lpddr4_privatedata *pd, lpddr4_intr_ctlinterrupt intr);

uint32_t lpddr4_checkphyindepinterrupt(const lpddr4_privatedata *pd, lpddr4_intr_phyindepinterrupt intr, bool *irqstatus);

uint32_t lpddr4_ackphyindepinterrupt(const lpddr4_privatedata *pd, lpddr4_intr_phyindepinterrupt intr);
#endif  /* LPDDR4_IF_H */
