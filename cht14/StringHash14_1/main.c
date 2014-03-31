#include <stdio.h>
#include <stdlib.h>

//依据：
///     (a+b)%m = (a%m + b)%m.
///     (a*b)%m = a%m * b%m.
//Notice:
///     a与M的取值不能一样或者很相近，127 128 128 127 127 127 128 128，否则hash出的地址只根据单词最后一个字母变化。
static char S[15] = "averylongkey";

int Hash(char *S, int M)
{
    int h = 0,a = 127;
    for(; *S != '\0'; S++)
    {
        h = (a*h + *S)%M;
    }
    return h;
}

int main()
{
    printf("Hash 'averylongkey' =%d\n",Hash(S, 1023));
    printf("s[12]=%d\ts[13]=%d\n",S[11],S[12]);
    return 0;
}
