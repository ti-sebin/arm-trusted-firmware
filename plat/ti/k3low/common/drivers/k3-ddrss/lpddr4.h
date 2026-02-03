/* SPDX-License-Identifier: BSD-3-Clause */
/*
 * Cadence DDR Driver
 *
 * Copyright (C) 2012-2026 Cadence Design Systems, Inc.
 * Copyright (C) 2018-2026 Texas Instruments Incorporated - https://www.ti.com/
 */

#ifndef LPDDR4_H
#define LPDDR4_H

#include <errno.h>
#include <inttypes.h>
#include <stddef.h>

#include "lpddr4_16bit.h"
#include "lpddr4_16bit_sanity.h"
#include "lpddr4_ctl_regs.h"



#define LPDDR4_BIT_MASK    (0x1U)

#define WORD_SHIFT (32U)


#ifndef LPDDR4_CUSTOM_TIMEOUT_DELAY
#define LPDDR4_CUSTOM_TIMEOUT_DELAY 100000000U
#endif

volatile uint32_t *lpddr4_addoffset(volatile uint32_t *addr, uint32_t regoffset);
uint32_t lpddr4_pollctlirq(const lpddr4_privatedata *pd, lpddr4_intr_ctlinterrupt irqbit, uint32_t delay);

uint32_t lpddr4_enablepiinitiator(const lpddr4_privatedata *pd);

#endif  /* LPDDR4_H */
