#ifndef LINKEDLIST_H
#define LINKEDLIST_H

typedef struct Node{
    int value;
    struct Node *next;
}node;

node *create(int num);
void set_next(node *nd1, node *nd2);
node *get_next(node *nd1);
bool has_next(node * nd);

#endif