#
# Copyright (c) 2026, Texas Instruments Inc. All rights reserved.
#
# SPDX-License-Identifier: BSD-3-Clause
#

DTB_FILE_NAME ?= k3-am62l-evm.dtb

BL1_SOURCES             +=      \
                                ${PLAT_PATH}/board/${TARGET_BOARD}/board_config.c   \
