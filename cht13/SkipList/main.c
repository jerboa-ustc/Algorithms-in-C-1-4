#include <stdio.h>
#include <stdlib.h>
#include "SkipList.h"

//define static var.
static link head, z;  ///z:watch node.
static int N, lgN;
//not static var.
/*link head, z;  ///z:watch node.
int N, lgN;*/
int randX();

//New Node
link NEW(Item item, int k)
{
    int i;  link x = (link)malloc(sizeof *x);
    x->next = (link)malloc(k*sizeof(link));
    x->item = item;
    x->sz = k;
    LIST_FOR_EACH(i, k)
        x->next[i] = z;
    return x;
}

//Node Init
void STinit()
{
    N = 0; lgN = 0;
    z = NEW(NULLitem, 0);   ///watch node : '~'
    head = NEW((char)35, lgNmax+1);
    randX();
}

//random
int randX()
{
    int i,j,t=rand();
    for(i = 1,j = 2; i < lgNmax; i++, j += j)
        if(t > RAND_MAX/j)  break;
    if(i > lgN) lgN = i;
    return i;///5
}

///recursion insert
void insertR(link t, link x, int k)
{
    //int level = k-1;
    Item v = x->item;
    if(LESS(v, t->next[k]->item))
    {
        if(k < x->sz)
        {
            x->next[k] = t->next[k];
            t->next[k] = x;
        }
        if(k == 0)
        {
            return;
        }
        insertR(t, x, k-1);
        return;
    }
    insertR(t->next[k], x, k);
}

//insert Node
void STinsert(Item item)
{
    insertR(head, NEW(item, randX()), lgN);
    N++;
}

///recursiion search
Item searchR(link t, Item v, int k)
{
    if(t == z)
        return NULLitem;
    if(EQ(v, t->item))
        return t->item;
    if(LESS(v, t->next[k]->item))
    {
        if(k == 0)
            return NULLitem;
        return searchR(t, v, k-1);
    }
    return searchR(t->next[k], v, k);
}

//STnode search
Item STsearch(Item v)
{
    return searchR(head, v, lgN);
}

//打印整个跳跃表包括表头和观察哨节点。#:表头，~:观察哨。
void STdisplay()
{
    int i;  link pos;
    printf("Num of Nodes:N=%d\tLevels used:lgN=%d\tLevels designed:lgNmax=%d\n", N, lgN, lgNmax);
    for(i = lgNmax; i > -1; i--)
    {
        pos = head;
        while(pos != z)
        {
            printf("%c  ",pos->item);
            pos = pos->next[i];
        }
        printf("%c\n",z->item);
    }
}

///recursiion STnode delete
void deleteR(link t, Item v, int k)
{
    link x = t->next[k];
    if(!LESS(x->item, v))
    {
        if(EQ(v, x->item))
        {
            t->next[k] = x->next[k];
        }
        if(k == 0)
        {
            free(x);
            return;
        }
        deleteR(t, v, k-1);
        return;
    }
    deleteR(t->next[k], v, k);
}

//STdelete
void STdelete(Item v)
{
    deleteR(head, v, lgN);
    N--;
}

int main()
{
    freopen("in.txt", "r", stdin);

    int buff;
    ///随机插入
    STinit();
    printf("insert random\n");
    while(scanf("%d", &buff) != EOF)
    {
        STinsert((char)buff);
    }
    //printf("Num of Nodes:N=%d\tLevels used:lgN=%d\tLevels designed:lgNmax=%d\n", N, lgN, lgNmax);
    STdisplay();
    printf("search for 36: %c\n",STsearch(36));
    printf("delete J U G\n");
    STdelete('J');
    STdelete('U');
    STdelete('G');
    STdisplay();
    printf("insert O Q $\n");
    STinsert('O');
    STinsert('Q');
    STinsert('$');
    STinsert('@');
    STdisplay();
    return 0;
}
