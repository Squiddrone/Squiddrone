#ifndef SRC_MCU_CONFIG_SPI_CONFIG_H_
#define SRC_MCU_CONFIG_SPI_CONFIG_H_

#ifdef __cplusplus
	extern "C" {
#endif

extern SPI_HandleTypeDef hspi1;

void MX_SPI1_Init(void);

#ifdef __cplusplus
	}
#endif

#endif 