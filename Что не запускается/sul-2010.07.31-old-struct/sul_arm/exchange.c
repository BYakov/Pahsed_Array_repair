
#include "exchange.h"

//--------------------------------------------------------------------------------------------

unsigned char token_crc(struct dma_token *token)
{
    unsigned int i = 0;
    unsigned char crc = 0;
    unsigned char *p = (unsigned char *)token;

    for(i=0; i<sizeof(struct dma_token) - 1; ++i) {
        crc += p[i];
    }

    return crc;
}

//--------------------------------------------------------------------------------------------

unsigned char data_crc(unsigned char *data, int size)
{
    unsigned int i = 0;
    unsigned char crc = 0;

    for(i=0; i<size; ++i) {
        crc += data[i];
    }

    return crc;
}

//--------------------------------------------------------------------------------------------

void init_dma_token(struct dma_token *token, unsigned char *data, int size)
{
	token->sign = dma_token_sign;
	token->dcrc = data_crc(data,size);
    token->tcrc = token_crc(token);
}

//--------------------------------------------------------------------------------------------

int check_dma_token(struct dma_token *token)
{
    if(token->sign != dma_token_sign)
        return -1;
    if(token->tcrc != token_crc(token))
        return -2;

    return 0;
}

//--------------------------------------------------------------------------------------------

int check_dma_transactions(struct dma_token *token, unsigned char *data, int size)
{
    if(token->sign != dma_token_sign)
        return -1;
    if(token->tcrc != token_crc(token))
        return -2;
	if(token->dcrc != data_crc(data,size))
		return -3;

    return 0;
}

//--------------------------------------------------------------------------------------------
