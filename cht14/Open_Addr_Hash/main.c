#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "item.h"

static int N, M;
static Item *st;
int conflict = 0;

///判断互质
bool Prime(const int a, const int b)
{
    int div1, div2, div3 = 1;
    if(a <= b)
    {
        div1 = a;
        div2 = b;
    }
    else
    {
        div1 = b;
        div2 = a;
    }
    while(div3 != 0)
    {
        div3 = div2 % div1;
        div2 = div1;
        div1 = div3;
    }
    if(div2 == 1)
        return true;    //互质
    else
        return false;
}

void STinit(int max)
{
    int i;
    N = 0; M = 2*max;
    st = (Item* )malloc(M*sizeof(Item));
    for(i = 0; i < M; i++)
        st[i] = NULLitem;
}

int STcount()
{
    return N;
}

void STinsert(Item item)
{
    int i = hash(item, M);
    while(!null(i))
    //while(st[i] != -1)
    {
        i = (i+1) % M;  conflict++;
    }
    st[i] = item;
    N++;
}

void STinsert_Double(Item item)
{
    int i = hash(item, M);
    int k = hashtwo(item, M);
    ///判断k与M是否互质，k=91,M=26,也算不互质，因为91%26=13,13是26因子，
    ///     这会导致i=(i+k)%M永远在几个固定地址变动，死循环.
    while(!Prime(k, M))
    {
        k++;
    }
    while(!null(i))
        i = (i + k) % M;
    st[i] = item;
    N++;
}

Item STsearch_Double(Item v)
{
    int i = hash(v, M);
    int k = hashtwo(v, M);
    while(!null(i))
    {
        if(eq(v, st[i]))
            return st[i];
        else
            i = (i + k) % M;
    }
    return NULLitem;
}

Item STsearch(Item v)
{
    int i = hash(v, M);
    while(!null(i))
    {
        if(eq(v, st[i]))
            return st[i];
        else
            i = (i+1) % M;
    }
    return NULLitem;
}

void STdelete(Item item)
{
    int j, i = hash(item, M); Item v;
    while(!null(i))
    {
        if(eq(item, st[i]))
            break;
        else
        {
            i = (i+1) % M;
        }
    }
    if(null(i))
        return;
    st[i] = NULLitem; N--;
    for(j = i+1; !null(j); j=(j+1)%M, N--)
    {
        v = st[j]; st[j] = NULLitem;
        STinsert(v);
    }
}

void STdelete_Double(Item item)
{
    int j, i = hash(item, M); Item v;
    int k = hashtwo(item, M);
    ///判断k与M是否互质，k=91,M=26,也算不互质，因为91%26=13,13是26因子，
    ///     这会导致i=(i+k)%M永远在几个固定地址变动，死循环.
    while(!Prime(k, M))
    {
        k++;
    }
    while(!null(i))
    {
        if(eq(item, st[i]))
            break;
        else
        {
            i = (i+k) % M;
        }
    }
    if(null(i))
        return;
    st[i] = NULLitem_Mark; N--;
}

///codeblocks: char = signed
void char_type()
{
   // char c = 0xFF;
    char c = NULLitem_Mark;
   // if(c == -1)
    if(c == -128)
        printf("signed\n");
    //else if(c == 255)
    else if(c == 0)
        printf("unsigned\n");
    else
        printf("error\n");
}

void Display(Item *vex)
{
    int i;
    for(i = 0; i < M; i++)
    {
        if(!null(i))
            printf("%c  ",vex[i]);
    }
    printf("\n");
}

int main()
{
    freopen("in.txt", "r", stdin);
    STinit(13);
    char buff;
    while(scanf("%d", &buff) != EOF)
    {
        //STinsert(buff);
        STinsert_Double(buff);
    }
    Display(st);
   // printf("conflict=%d\n", conflict);
   // printf("search for 85:%c\n", STsearch(85));
    //printf("search for 71:%c\n", STsearch(71));
    //printf("search for 38:%c\n", STsearch(38));
    STdelete_Double(71);
    STdelete_Double(74);
    STdelete_Double(72);
    STdelete_Double(61);
    STdelete_Double(73);
    STdelete_Double(43);
    Display(st);
    //printf("search for -2:%c\n", -128);
    return 0;
}
