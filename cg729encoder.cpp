#include "cg729encoder.h"

CG729Encoder::CG729Encoder()
{ 
    initial();
}

CG729Encoder::~CG729Encoder()
{
//    close();
}

void CG729Encoder::initial()
{
    va_g729a_init_encoder();
}

void CG729Encoder::encode(short *src,unsigned char *dst)
{
    va_g729a_encoder(src, dst);
}
