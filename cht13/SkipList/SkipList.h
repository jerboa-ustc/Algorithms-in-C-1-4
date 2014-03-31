#ifndef SKIPLIST_H_INCLUDED
#define SKIPLIST_H_INCLUDED

typedef struct STnode* link;
typedef char Item;
struct STnode {
    Item item;
    link* next;
    int sz;
};

#define LIST_FOR_EACH(i, k) \
    for(i = 0; i < k; i++)


#define NULLitem ((char)126)

///小跳跃表最大层数5
#define lgNmax 5

//比较
#define LESS(a, b) (a < b)
#define EQ(a, b) (a == b)
/*extern link head, z;  //z:watch node.
extern int N, lgN;*/

#endif // SKIPLIST_H_INCLUDED
