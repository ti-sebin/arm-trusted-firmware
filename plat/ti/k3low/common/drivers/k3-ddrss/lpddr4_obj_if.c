// SPDX-License-Identifier: BSD-3-Clause
/*
 * Cadence DDR Driver
 *
 * Copyright (C) 2012-2026 Cadence Design Systems, Inc.
 * Copyright (C) 2018-2026 Texas Instruments Incorporated - https://www.ti.com/
 */

#include "lpddr4_obj_if.h"

lpddr4_obj *lpddr4_getinstance(void)
{
	static lpddr4_obj driver = {
		.probe				= lpddr4_probe,
		.init				= lpddr4_init,
		.start				= lpddr4_start,
		.readreg			= lpddr4_readreg,
		.writereg			= lpddr4_writereg,
		.writectlconfigex		= lpddr4_writectlconfigex,
		.writephyconfigex		= lpddr4_writephyconfigex,
		.writephyindepconfigex		= lpddr4_writephyindepconfigex,
		.checkctlinterrupt		= lpddr4_checkctlinterrupt,
		.ackctlinterrupt		= lpddr4_ackctlinterrupt,
		.checkphyindepinterrupt		= lpddr4_checkphyindepinterrupt,
		.ackphyindepinterrupt		= lpddr4_ackphyindepinterrupt,
	};

	return &driver;
}
