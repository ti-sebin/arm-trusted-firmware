/* SPDX-License-Identifier: BSD-3-Clause */
/*
 * Cadence DDR Driver - Minimal Macros
 *
 * Copyright (C) 2012-2026 Cadence Design Systems, Inc.
 * Copyright (C) 2018-2026 Texas Instruments Incorporated - https://www.ti.com/
 *
 * This file contains only the macros actually used by the AM62L DDR driver.
 * Reduced from 6,796 macros to 80 macros (1.2% of original).
 */

#ifndef LPDDR4_MACROS_H_
#define LPDDR4_MACROS_H_

/* Controller Register Field Masks */
#define LPDDR4__DENALI_CTL_0__DRAM_CLASS_MASK                        0x00000F00U
#define LPDDR4__DENALI_CTL_0__START_MASK                             0x00000001U
#define LPDDR4__DENALI_CTL_337__INT_STATUS_LOWPOWER_MASK             0xFFFF0000U
#define LPDDR4__DENALI_CTL_341__INT_STATUS_BIST_MASK                 0x00FF0000U
#define LPDDR4__DENALI_CTL_341__INT_STATUS_MISC_MASK                 0x0000FFFFU
#define LPDDR4__DENALI_CTL_342__INT_STATUS_DFI_MASK                  0x000000FFU
#define LPDDR4__DENALI_CTL_342__INT_STATUS_FREQ_MASK                 0x00FF0000U
#define LPDDR4__DENALI_CTL_342__INT_STATUS_INIT_MASK                 0xFF000000U
#define LPDDR4__DENALI_CTL_343__INT_STATUS_PARITY_MASK               0x0000FF00U
#define LPDDR4__DENALI_CTL_345__INT_ACK_LOWPOWER_MASK                0xFFFF0000U
#define LPDDR4__DENALI_CTL_349__INT_ACK_BIST_MASK                    0x00FF0000U
#define LPDDR4__DENALI_CTL_350__INT_ACK_FREQ_MASK                    0x00FF0000U
#define LPDDR4__DENALI_CTL_350__INT_ACK_INIT_MASK                    0xFF000000U
#define LPDDR4__DENALI_CTL_351__INT_ACK_PARITY_MASK                  0x0000FF00U

/* PI Register Field Masks */
#define LPDDR4__DENALI_PI_0__PI_START_MASK                           0x00000001U
#define LPDDR4__DENALI_PI_3__PI_NORMAL_LVL_SEQ_MASK                  0x01000000U
#define LPDDR4__DENALI_PI_4__PI_INIT_LVL_EN_MASK                     0x00000001U

/* Driver-level field masks (for CPS_FLD_MASK token concatenation) */
#define LPDDR4__DRAM_CLASS__FLD_MASK                                 0x00000F00U
#define LPDDR4__START__FLD_MASK                                      0x00000001U
#define LPDDR4__INT_STATUS_LOWPOWER__FLD_MASK                        0xFFFF0000U
#define LPDDR4__INT_STATUS_BIST__FLD_MASK                            0x00FF0000U
#define LPDDR4__INT_STATUS_MISC__FLD_MASK                            0x0000FFFFU
#define LPDDR4__INT_STATUS_DFI__FLD_MASK                             0x000000FFU
#define LPDDR4__INT_STATUS_FREQ__FLD_MASK                            0x00FF0000U
#define LPDDR4__INT_STATUS_INIT__FLD_MASK                            0xFF000000U
#define LPDDR4__INT_STATUS_PARITY__FLD_MASK                          0x0000FF00U
#define LPDDR4__INT_ACK_LOWPOWER__FLD_MASK                           0xFFFF0000U
#define LPDDR4__INT_ACK_BIST__FLD_MASK                               0x00FF0000U
#define LPDDR4__INT_ACK_FREQ__FLD_MASK                               0x00FF0000U
#define LPDDR4__INT_ACK_INIT__FLD_MASK                               0xFF000000U
#define LPDDR4__INT_ACK_PARITY__FLD_MASK                             0x0000FF00U
#define LPDDR4__PI_START__FLD_MASK                                   0x00000001U
#define LPDDR4__PI_NORMAL_LVL_SEQ__FLD_MASK                          0x01000000U
#define LPDDR4__PI_INIT_LVL_EN__FLD_MASK                             0x00000001U

/* Driver-level macros - Basic Configuration */
#define LPDDR4__START__REG                                           DENALI_CTL_0

/* Driver-level macros - Interrupt Status */
#define LPDDR4__INT_STATUS_MASTER__REG                               DENALI_CTL_334
#define LPDDR4__INT_STATUS_TIMEOUT__REG                              DENALI_CTL_336
#define LPDDR4__INT_STATUS_LOWPOWER__REG                             DENALI_CTL_337
#define LPDDR4__INT_STATUS_TRAINING__REG                             DENALI_CTL_339
#define LPDDR4__INT_STATUS_USERIF__REG                               DENALI_CTL_340
#define LPDDR4__INT_STATUS_BIST__REG                                 DENALI_CTL_341
#define LPDDR4__INT_STATUS_MISC__REG                                 DENALI_CTL_341
#define LPDDR4__INT_STATUS_DFI__REG                                  DENALI_CTL_342
#define LPDDR4__INT_STATUS_FREQ__REG                                 DENALI_CTL_342
#define LPDDR4__INT_STATUS_INIT__REG                                 DENALI_CTL_342
#define LPDDR4__INT_STATUS_MODE__REG                                 DENALI_CTL_343
#define LPDDR4__INT_STATUS_PARITY__REG                               DENALI_CTL_343

/* Driver-level macros - Interrupt Acknowledge */
#define LPDDR4__INT_ACK_TIMEOUT__REG                                 DENALI_CTL_344
#define LPDDR4__INT_ACK_LOWPOWER__REG                                DENALI_CTL_345
#define LPDDR4__INT_ACK_TRAINING__REG                                DENALI_CTL_347
#define LPDDR4__INT_ACK_USERIF__REG                                  DENALI_CTL_348
#define LPDDR4__INT_ACK_BIST__REG                                    DENALI_CTL_349
#define LPDDR4__INT_ACK_MISC__REG                                    DENALI_CTL_349
#define LPDDR4__INT_ACK_DFI__REG                                     DENALI_CTL_350
#define LPDDR4__INT_ACK_FREQ__REG                                    DENALI_CTL_350
#define LPDDR4__INT_ACK_INIT__REG                                    DENALI_CTL_350
#define LPDDR4__INT_ACK_MODE__REG                                    DENALI_CTL_351
#define LPDDR4__INT_ACK_PARITY__REG                                  DENALI_CTL_351

/* Driver-level macros - PI (PHY Independent) */
#define LPDDR4__PI_START__REG                                        DENALI_PI_0
#define LPDDR4__PI_NORMAL_LVL_SEQ__REG                               DENALI_PI_3
#define LPDDR4__PI_INIT_LVL_EN__REG                                  DENALI_PI_4
#define LPDDR4__PI_INT_STATUS__REG                                   DENALI_PI_83
#define LPDDR4__PI_INT_ACK__REG                                      DENALI_PI_84

#endif /* LPDDR4_MACROS_H_ */
