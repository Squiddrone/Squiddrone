#ifndef TESTS_MOCK_LIBRARIES_STM32G4XX_HAL_DEF_H_
#define TESTS_MOCK_LIBRARIES_STM32G4XX_HAL_DEF_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef enum
{
  HAL_OK = 0x00U,
  HAL_ERROR = 0x01U,
  HAL_BUSY = 0x02U,
  HAL_TIMEOUT = 0x03U
} HAL_StatusTypeDef;

#ifdef __cplusplus
}
#endif

#endif