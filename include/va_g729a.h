#define  L_FRAME_COMPRESSED 10
#define  L_FRAME            80

void va_g729a_init_encoder();
void va_g729a_encoder(short *speech, unsigned char *bitstream);
void va_g729a_init_decoder();
void va_g729a_decoder(unsigned char *bitstream, short *synth_short, int bfi);
