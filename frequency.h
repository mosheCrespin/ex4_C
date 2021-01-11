#ifndef MYMATH_H
#define MYMATH_H
#define ALPHABET 26
#define LOWERCASE 32
#define NODE struct node
typedef enum {FALSE=0, TRUE=1} boolean;
#define CHARTOINDEX(c) ((int)c- (int)'a')

NODE* make_node();
NODE* insert_char(NODE*, char);
void insert_word(NODE*, char*);
void proper_word(NODE*,char*);
void proccesing(NODE*,char*);
void lexicographical_order_r_help(NODE*,char*,int);
void lexicographical_order_r(NODE*);
void lexicographical_order_help(NODE*,char*,int);
void lexicographical_order(NODE*);
void free_tree(NODE*);
NODE* input();

#endif