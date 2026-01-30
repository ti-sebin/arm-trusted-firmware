/* SPDX-License-Identifier: BSD-3-Clause */
/*
 * Cadence DDR Driver
 *
 * Copyright (C) 2012-2026 Cadence Design Systems, Inc.
 * Copyright (C) 2018-2026 Texas Instruments Incorporated - https://www.ti.com/
 */

#ifndef lpddr4_obj_if_h
#define lpddr4_obj_if_h

#include "lpddr4_if.h"

typedef struct lpddr4_obj_s {
	uint32_t (*probe)(const lpddr4_config *config, uint16_t *configsize);
	uint32_t (*init)(lpddr4_privatedata *pd, const lpddr4_config *cfg);
	uint32_t (*start)(const lpddr4_privatedata *pd);
	uint32_t (*readreg)(const lpddr4_privatedata *pd, lpddr4_regblock cpp, uint32_t regoffset, uint32_t *regvalue);
	uint32_t (*writereg)(const lpddr4_privatedata *pd, lpddr4_regblock cpp, uint32_t regoffset, uint32_t regvalue);
	uint32_t (*writectlconfigex)(const lpddr4_privatedata *pd, const uint32_t regvalues[], uint16_t regcount);
	uint32_t (*writephyconfigex)(const lpddr4_privatedata *pd, const uint32_t regvalues[], uint16_t regcount);
	uint32_t (*writephyindepconfigex)(const lpddr4_privatedata *pd, const uint32_t regvalues[], uint16_t regcount);
	uint32_t (*checkctlinterrupt)(const lpddr4_privatedata *pd, lpddr4_intr_ctlinterrupt intr, bool *irqstatus);
	uint32_t (*ackctlinterrupt)(const lpddr4_privatedata *pd, lpddr4_intr_ctlinterrupt intr);
	uint32_t (*checkphyindepinterrupt)(const lpddr4_privatedata *pd, lpddr4_intr_phyindepinterrupt intr, bool *irqstatus);
	uint32_t (*ackphyindepinterrupt)(const lpddr4_privatedata *pd, lpddr4_intr_phyindepinterrupt intr);
} lpddr4_obj;

extern lpddr4_obj *lpddr4_getinstance(void);

#endif  /* lpddr4_obj_if_h */
