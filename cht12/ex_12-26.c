/*
 * SOSearch.c
 *
 *  Created on: 2013年12月7日
 *      Author: Administrator
 */

#include <stdio.h>
#include <stdlib.h>
#define NULLitem 0
#define bitsword 32
#define key(item) (item)
#define less(a,b) ((a<b)?1:0)
#define eq(a,b) (a==b)
typedef unsigned long Item;
typedef Item Key;
//static Item * st;
int nr;
typedef struct STnode * link;
struct STnode {
	Item item;
	link l,r;
	int N;
};
static link head,z;

//新建
link NEW(Item item,link l,link r,int N){
	link x = malloc(sizeof(*x));
	x->item = item; x->l = l; x->r = r; x->N = N;
	return x;
}

void STinit(){
	head = (z = NEW(NULLitem,0,0,0));
}

//旋转
link rotR(link h){
	link x = h->l; h->l = x->r; x->r = h;
	return x;
}

link rotL(link h){
	link x = h->r; h->r = x->l; x->l = h;
	return x;
}
//旋转定义结束

// BST根插入
link insertT(link h, Item item){
	Key v = key(item);
	if(h == z)
		return NEW(item,z,z,1);
	if(less(v,key(h->item))) {
		h->l = insertT(h->l, item);
		h = rotR(h);
	}
	else {
		h->r = insertT(h->r, item);
		h = rotL(h);
	}
	return h;
}

void STinsert(Item item){
	head = insertT(head, item);
}

//查找
link searchR(link h, Key v){
	//Key t = key(h->item);
	Key t = h->item;
	link tmp = NULL;
	nr++;
	if (h == z)
		return NULL;
	if eq(v, t)
		return h;
	if less(v, t){
		if ((tmp = searchR(h->l, v)) != NULL){
			h->l = tmp;	h = rotR(h);
		}
		else
			return NULL;
	}
	else{
		if ((tmp = searchR(h->r, v)) != NULL){
			h->r = tmp; h = rotL(h);
		}
		else
			return NULL;
	}

	return h;
}

Item STsearch(Key v){
	//link tmp = NULL;
	head = searchR(head, v);
	if ((head != NULL) && (head != z))
		return (head->item);
	else
		return 0;
}

//中序
void Inorder(link h){
	if(h != z){
		Inorder(h->l);
		printf(" 中序 %lu ",h->item);
		Inorder(h->r);
	}
}
//后序
void Postorder(link h){
	if(h != z){
		Postorder(h->l);Postorder(h->r);
		printf(" 后序 %lu ",h->item);
		
	}
}
/********************************main********************************/
void main(){
	Key v; Item item;int ret;
	freopen("input.txt","r",stdin);
	//freopen("output.txt","w",stdout);
	STinit();
	while(scanf("%lu",&v) != EOF){
		key(item) = v;
		STinsert(item);
	}
	//printf("head->r->item = %d\n",head->r->item);

	//Inorder(head);
	//printf(" =表达式 %d\n",(nr=(3+6)));
	ret=STsearch(69);
	printf("nr=%d,	ret=%d\n",nr,ret);
	nr=0;
	printf("head->r->r->r->r->item = %d\n",head->r->r->r->r->item);
	//Inorder(head);
	/*ret=STsearch(72);
	printf("nr=%d,	ret=%d\n",nr,ret);
	nr=0;
	ret=STsearch(72);
	printf("nr=%d,	ret=%d\n",nr,ret);
	nr=0;
	ret=STsearch(65);
	printf("nr=%d,	ret=%d\n",nr,ret);
	nr=0;*/
	Inorder(head);
	puts("");
	Postorder(head);
}
