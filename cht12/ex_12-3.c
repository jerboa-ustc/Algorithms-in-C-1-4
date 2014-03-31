/*************************************************************************
	> File Name: ex_12-3.c
	> Author: jerboa
	> Mail: a.jerboa@gmail.com
	> Created Time: 2013年11月26日 星期二 09时16分40秒
 ************************************************************************/

#include <stdio.h>
#define NULLitem 0
#define bitsword 32
//#define M 1000
//#define SIZE (M/bitsword + 1)
#define key(item) (item)
typedef unsigned long Item;
typedef Item Key;
static Item * st;
static int SIZE;
//static int M = 1000;//= maxKey;

void STinit (int maxN)
{
	int i;
	SIZE = (maxN/bitsword + 1);
//	st = malloc((M+1)*sizeof(Item));
	st = malloc((SIZE)*sizeof(Item));
	for(i=0; i<SIZE; i++)
	{
		st[i] = NULLitem;
	}
}

int STcount ()
{
	int i, j, N=0;
	for(i=0; i<SIZE; i++)
	{
	//	if(st[i] != NULLitem)
		for(j=0; j<bitsword; j++)
		{
			if(st[i] & (1UL<<j))
				N++;
		}
	}
	return N;
}

void STinsert (Item item)
{
	//st[key(item) & (~(1UL<<5 - 1))] | (1UL<<(key(item) & (1UL<<5 - 1)));
	st[key(item) >> 5] |= (1UL<<(key(item) & ((1UL<<5) - 1)));
	/*特别注意：：：<< >>位移操作 优先级低于 + -：：：特别注意*/
}

Item STsearch (Key v)
{
	unsigned long iftest;
	//if(st[v & (~(1UL<<5 - 1))] & (1UL<<(v & (1UL<<5 - 1))))
	iftest=(st[v >> 5] & (1UL<<(v & ((1UL<<5) - 1))));
	if (iftest)
		return v;

	return NULLitem;
}

void STdelete (Item item)
{
	//st[key(item) & (~(1UL<<5 - 1))] & (~(1UL<<(key(item) & (1UL<<5 - 1))));
	st[key(item) >> 5] &= (~(1UL<<(key(item) & ((1UL<<5) - 1))));
}

/********************************main**************************************/
void main(int argc, char *argv[])
{
	//in/output
	freopen("input.txt","r",stdin);
	freopen("out.txt","w",stdout);
	int N, maxN = 950;//atoi(argv[1]);
	Key v;Item item, sitem;
	STinit(maxN);
	for(N=0; N<maxN; N++)
	//while(scanf("%lu",&v) != EOF)
	{
		v = (unsigned long)rand() % (SIZE*bitsword);
		if((sitem=STsearch(v)) != NULLitem)
		{
			printf("%d + item existed, inserting failed.key: %lu\n", N, sitem);
			continue;
		}
		key(item) = v;
		STinsert(item);
		printf("%d + inserting successed.key: %lu\n",N, key(item));
		if (!(N % 10))
		{
			if(STsearch(key(item)))
			{
				STdelete(item);
				printf("%d - item existed, deleting successed.key: %lu\n",N, key(item));
				if(!STsearch(key(item)))
					printf("%d - item gone, search failed.key: %lu\n",N, key(item));
				else
					printf("%d - item existed, deleting failed.key: %lu\n",N, key(item));
			}
		}
	}
	//for test by gdb.
	//STinsert(638);
	//printf("search key: %lu\n",STsearch(638));
}
