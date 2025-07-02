#include "stego.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void encode_message(unsigned char *data, int size, const char *message) {
    int msg_len = strlen(message);
    if ((msg_len + 2) * 8 > size) {
        fprintf(stderr, "Message too long\n");
        exit(1);
    };

    for (int i = 0; i < 16; i++) {
        int bit = (msg_len >> (15 - i)) & 1;
        data[i] = (data[i] & 0xFE) | bit;
    };

    for (int i = 0; i < msg_len; i++) {
        unsigned char ch = message[i];
        for (int j = 0; j < 8; j++) {
            int bit = (ch >> (7 - j)) & 1;
            data[16 + i * 8 + j] = (data[16 + i * 8 + j] & 0xFE) | bit;
        }
    }
}

void decode_message(unsigned char *data, int size, char *out, int max_len) {
    int msg_len = 0;

    for (int i = 0; i < 16; i++) {
        msg_len = (msg_len << 1) | (data[i] & 1);
    }

    if (msg_len >= max_len) {
        fprintf(stderr, "Message too long to decode safely\n");
        exit(1);
    }

    for (int i = 0; i < msg_len; i++) {
        unsigned char ch = 0;
        for (int j = 0; j < 8; j++) {
            ch = (ch << 1) | (data[16 + i * 8 + j] & 1);
        };
        out[i] = ch;
    };
    out[msg_len] = '\0';
}