#ifndef STEGO_H
#define STEGO_H

void encode_message(unsigned char *data, int size, const char *message);
void decode_message(unsigned char *data, int size, char *out, int max_len);

#endif