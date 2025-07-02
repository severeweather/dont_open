#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "stego.h"
#include "stb_image.h"
#include "stb_image_write.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MSG_LEN 1024

int main(int argc, char **argv) {
    if (argc < 3) {
        printf("Usage:\n");
        printf("    Encode: %s encode input.png output.png \"message\"\n", argv[0]);
        printf("    Decode: %s decode input.png\n", argv[0]);
        return 1;
    }

    const char *mode = argv[1];
    const char *input_path = argv[2];

    int w, h, channels;
    unsigned char *data = stbi_load(input_path, &w, &h, &channels, 3);
    if (!data) {
        fprintf(stderr, "Failed to load image: %s\n", input_path);
        return 1;
    }
    int size = w * h * 3;

    if (strcmp(mode, "encode") == 0) {
        if (argc < 5) {
            fprintf(stderr, "Missing output path or message\n");
            stbi_image_free(data);
            return 1;
        }
        const char *output_path = argv[3];
        const char *message = argv[4];

        encode_message(data, size, message);

        if (!stbi_write_png(output_path, w, h, 3, data, w * 3)) {
            fprintf(stderr, "Failed to write image: %s\n", output_path);
            stbi_image_free(data);
            return 1;
        }

        printf("Message encoded and saved to %s\n", output_path);
    }
    else if (strcmp(mode, "decode") == 0) {
        char msg[MAX_MSG_LEN];
        decode_message(data, size, msg, MAX_MSG_LEN);
        printf("Расшифрованное сообщение: %s\n", msg);
    }
    else {
        fprintf(stderr, "Unknown mode: %s\n", mode);
        stbi_image_free(data);
        return 1;
    }

    stbi_image_free(data);
    return 0;
}