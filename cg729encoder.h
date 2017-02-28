#ifndef CG729ENCODER_H
#define CG729ENCODER_H
extern "C"
{
#include "va_g729a.h"
}

class CG729Encoder
{
public:
    CG729Encoder();
    ~CG729Encoder();
    void encode(short *src,unsigned char *dst);

private:
    void initial();

};

#endif // CG729ENCODER_H
