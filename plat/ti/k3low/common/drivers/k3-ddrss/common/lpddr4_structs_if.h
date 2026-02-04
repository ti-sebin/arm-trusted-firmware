/* SPDX-License-Identifier: BSD-3-Clause */
/*
 * Cadence DDR Driver
 *
 * Copyright (C) 2012-2026 Cadence Design Systems, Inc.
 * Copyright (C) 2018-2026 Texas Instruments Incorporated - https://www.ti.com/
 */

#ifndef LPDDR4_STRUCTS_IF_H
#define LPDDR4_STRUCTS_IF_H

#include "inttypes.h"

#include "lpddr4_if.h"

struct lpddr4_config_s {
	struct lpddr4_ctlregs_s *ctlbase;
	lpddr4_infocallback infohandler;
	lpddr4_ctlcallback ctlinterrupthandler;
	lpddr4_phyindepcallback phyindepinterrupthandler;
};

struct lpddr4_privatedata_s {
	struct lpddr4_ctlregs_s *ctlbase;
	lpddr4_infocallback infohandler;
	lpddr4_ctlcallback ctlinterrupthandler;
	lpddr4_phyindepcallback phyindepinterrupthandler;
};

#endif  /* LPDDR4_STRUCTS_IF_H */
