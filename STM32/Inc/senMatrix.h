#pragma once

#define SEN_MATRIX_ROW          20
#define SEN_MATRIX_COL          20

typedef struct gpioLine_t
{
    GPIO_TypeDef *port;
    uint16_t pin;
} gpioLine_t;

typedef struct adcLine_t
{
    uint32_t ch;
    ADC_HandleTypeDef *adc;
} adcLine_t;

typedef struct senMatrix_t
{
    gpioLine_t rowLine[SEN_MATRIX_ROW];
    gpioLine_t colLine[SEN_MATRIX_COL];
    adcLine_t senLine[SEN_MATRIX_COL];
} senMatrix_t;

void matInit(void);
void matReset(void);
uint16_t matSampleSingle(uint8_t row, uint8_t col);
void matSampleAll(uint16_t samples[SEN_MATRIX_ROW][SEN_MATRIX_COL]);
void sampleAndSendData(void);