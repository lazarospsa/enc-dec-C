#include <stdio.h>
#include <string.h>

const char base64_chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

void encode_base64(char *input, char *output)
{
    int i = 0, j = 0;
    unsigned char input_buffer[3], output_buffer[4];

    while (input[i] != '\0')
    {
        int input_length = 0;

        for (int k = 0; k < 3; k++)
        {
            if (input[i] != '\0')
            {
                input_buffer[k] = input[i++];
                input_length++;
            }
            else
            {
                input_buffer[k] = 0;
            }
        }

        output_buffer[0] = (input_buffer[0] & 0xFC) >> 2;
        output_buffer[1] = ((input_buffer[0] & 0x03) << 4) + ((input_buffer[1] & 0xF0) >> 4);
        output_buffer[2] = ((input_buffer[1] & 0x0F) << 2) + ((input_buffer[2] & 0xC0) >> 6);
        output_buffer[3] = input_buffer[2] & 0x3F;

        for (int k = 0; k < 4; k++)
        {
            if (k <= input_length)
            {
                output[j++] = base64_chars[output_buffer[k]];
            }
            else
            {
                output[j++] = '=';
            }
        }
    }

    output[j] = '\0';
}

int find_base64_char_index(char c)
{
    for (int i = 0; i < 64; i++)
    {
        if (base64_chars[i] == c)
        {
            return i;
        }
    }
    return -1;
}

void decode_base64(char *input, char *output)
{
    int i = 0, j = 0;
    unsigned char input_buffer[4], output_buffer[3];

    while (input[i] != '\0')
    {
        for (int k = 0; k < 4; k++)
        {
            if (input[i] != '=')
            {
                input_buffer[k] = find_base64_char_index(input[i++]);
            }
            else
            {
                input_buffer[k] = 0;
                i++;
            }
        }

        output_buffer[0] = (input_buffer[0] << 2) + ((input_buffer[1] & 0x30) >> 4);
        output_buffer[1] = ((input_buffer[1] & 0x0F) << 4) + ((input_buffer[2] & 0x3C) >> 2);
        output_buffer[2] = ((input_buffer[2] & 0x03) << 6) + input_buffer[3];

        for (int k = 0; k < 3; k++)
        {
            if (input[i - 1] != '=')
            {
                output[j++] = output_buffer[k];
            }
            else
            {
                break;
            }
        }
    }

    output[j] = '\0';
}

int main()
{
    char input[1024];
    printf("Enter the message you want to encode: \n");
    fgets(input, sizeof(input), stdin);
    // input[strcspn(input, "\n")] = '\0'; // Remove the trailing newline character.
    // printf("%s \n", input);

    char encoded[1024], decoded[1024];

    encode_base64(input, encoded);
    printf("Encoded: %s\n", encoded);

    decode_base64(encoded, decoded);
    printf("Decoded: %s\n", decoded);

    return 0;
}