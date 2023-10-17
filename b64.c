#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *base64_encode(const unsigned char *strIn, int strLen)
{
    const static char *base64ABC = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    size_t outlen = ((strLen + 3) / 3 * 4 + 1) * 2;
    char *strOut = (char *)malloc(outlen + 2);
    char *pOut = strOut;
    for (size_t i = 0; i < strLen; i += 3)
    {
        long l = (((long)strIn[i]) << 16) | (((i + 1) < strLen) ? (((long)strIn[i + 1]) << 8) : 0) | (((i + 2) < strLen) ? ((long)strIn[i + 2]) : 0);

        *pOut++ = base64ABC[(l >> 18) & 0x3F];
        *pOut++ = base64ABC[(l >> 12) & 0x3F];
        if (i + 1 < strLen)
            *pOut++ = base64ABC[(l >> 6) & 0x3F];
        if (i + 2 < strLen)
            *pOut++ = base64ABC[l & 0x3F];
    }
    switch (strLen % 3)
    {
    case 1:
        *pOut++ = '=';
    case 2:
        *pOut++ = '=';
    }
    *pOut = L'\0';

    return strOut;
}

int main()
{
    const char *ascii = "Hello, world!"; // ASCII source
    char *encodedA = base64_encode((const unsigned char *)ascii, strlen(ascii));
    if (encodedA != NULL)
    {
        printf("Base64 ASCII: %s\n", encodedA);
        free(encodedA);
    }
    const wchar_t *utf16 = L"Hello, world!";
    int len = wcslen(utf16) * 2;
    char *encodedU = base64_encode((const unsigned char *)utf16, len);
    if (encodedU != NULL)
    {
        printf("Base64 UTF16: %s\n", encodedU);
        free(encodedU);
    }
    return 0;
}