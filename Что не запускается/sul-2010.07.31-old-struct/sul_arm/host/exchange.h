
#ifndef _EXCHANGE_H_
#define _EXCHANGE_H_

//---------------------------------------------------------------------------------------

enum {
    dma_token_sign = 0x77,
};

//---------------------------------------------------------------------------------------

struct dma_token {
    unsigned char sign;
    unsigned char size;
    unsigned char code;
    unsigned char data;
    unsigned char dcrc;
    unsigned char tcrc;
};

struct adc_param {
        unsigned long buffer_size;	// ADC buffer size (number of samples)
        unsigned long sample_rate;	// ADC sampling frequency
};

//---------------------------------------------------------------------------------------

struct adc_result {
        unsigned long mean;
        unsigned long rms;
};

//---------------------------------------------------------------------------------------

struct adc_buffer {
        unsigned long  buffer_size;	// ADC buffer size (number of samples)
};

//---------------------------------------------------------------------------------------

enum {

   set_adc_param    = 0x1,	//!<
   start_adc        = 0x2,	//!<
   get_adc_result   = 0x3,	//!<
   get_adc_buffer   = 0x4,	//!<

    usart_debug_msg = 0x55,	//!<
};

//---------------------------------------------------------------------------------------

unsigned char token_crc(struct dma_token *token);
unsigned char data_crc(unsigned char *data, int size);
void init_dma_token(struct dma_token *token, unsigned char data, unsigned char *buffer, int size);
int check_dma_token(struct dma_token *token);
int check_dma_transactions(struct dma_token *token, unsigned char *buffer, int size);

#endif //_EXCHANGE_H_
