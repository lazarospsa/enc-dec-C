#include <stdio.h>

char *encode(char *str)
{
    int i = 0;

    while (str[i] != '\0')
    {
        str[i] = str[i] - 30; // Subtract 30 From Charcter
        i++;
    }
    return (str);
}

char *decode(char *str)
{
    int i = 0;

    while (str[i] != '\0')
    {
        str[i] = str[i] + 30; // Subtract 30 From Charcter
        i++;
    }
    return (str);
}

void main()
{

    char *str;

    printf("\nEnter the String to be Encode : ");
    scanf("%s", str);

    str = encode(str);
    printf("\nEncoded String : %s \n", str);

    str = decode(str);
    printf("\nDecoded String : %s \n", str);

    return 0;
}