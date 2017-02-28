#include "cg729decoder.h"

CG729Decoder::CG729Decoder()
{ 
    initial();
}

CG729Decoder::~CG729Decoder()
{
//    close();
}

void CG729Decoder::initial()
{
    va_g729a_init_decoder();
}

void CG729Decoder::decode(unsigned char *src,short *dst,int bad_frame)
{
    va_g729a_decoder(src, dst, bad_frame);
}
