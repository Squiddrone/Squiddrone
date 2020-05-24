#ifndef MOCK_MCU_CONFIG_I2C_CONFIG_H_
#define MOCK_MCU_CONFIG_I2C_CONFIG_H_

#ifdef __cplusplus
	extern "C" {
#endif

extern I2C_HandleTypeDef hi2c2;

void MX_I2C2_Init(void);

#ifdef __cplusplus
	}
#endif

#endif 