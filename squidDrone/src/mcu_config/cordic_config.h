/*
 * cordic_config.h
 *
 *  Created on: Dec 31, 2019
 *      Author: aron
 */

#ifndef SRC_MC_CNFIG_CORDIC_CONFIG_H_
#define SRC_MC_CNFIG_CORDIC_CONFIG_H_

#ifdef __cplusplus
	extern "C" {
#endif

extern CORDIC_HandleTypeDef hcordic;

void MX_CORDIC_Init(void);

#ifdef __cplusplus
	}
#endif

#endif 