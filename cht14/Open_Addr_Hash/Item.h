#ifndef ITEM_H_INCLUDED
#define ITEM_H_INCLUDED

typedef char Item;
#define NULLitem -1   ///0xFF,%c输出DEL
#define null(a) (st[a] == NULLitem)
#define NULLitem_Mark -224  /// -224=1,0010,0000补码=1,1110,0000原码。%c输出时，取补码后7位为010,0000=32=字符SPACE.
#define hash(v, M) ((int)(0.616161 * (float)v) % M)
#define hashtwo(v, M) ((v % 97) + 1)
#define eq(a, b) (a == b)

#endif // ITEM_H_INCLUDED
