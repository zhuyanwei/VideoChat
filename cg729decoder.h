#ifndef CG729DECODER_H
#define CG729DECODER_H
extern "C"
{
#include "va_g729a.h"
}

class CG729Decoder
{
public:
    CG729Decoder();
    ~CG729Decoder();
    void decode(unsigned char *src,short *dst,int bad_frame);

private:
    void initial();

};

#endif // CG729DECODER_H
