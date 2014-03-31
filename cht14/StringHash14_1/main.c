#include <stdio.h>
#include <stdlib.h>

//���ݣ�
///     (a+b)%m = (a%m + b)%m.
///     (a*b)%m = a%m * b%m.
//Notice:
///     a��M��ȡֵ����һ�����ߺ������127 128 128 127 127 127 128 128������hash���ĵ�ַֻ���ݵ������һ����ĸ�仯��
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
