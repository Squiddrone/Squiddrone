#ifndef SRC_MCU_CONFIG_CORDIC_CONFIG_H_
#define SRC_MCU_CONFIG_CORDIC_CONFIG_H_

#ifdef __cplusplus
	extern "C" {
#endif

extern CORDIC_HandleTypeDef hcordic;

void MX_CORDIC_Init(void);

#ifdef __cplusplus
	}
#endif

#endif 