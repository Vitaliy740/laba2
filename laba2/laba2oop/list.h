#ifndef LIST_H
#define LIST_H
#include <iostream>
template <typename K,typename V>
struct ListNode{
    K key;
    V value;
    struct ListNode *next;
    struct ListNode *prev;
};
template <typename K,typename V>
class List
{
public:
    ListNode<K,V> *Head, *Tail;
    List():Head(NULL),Tail(NULL){}
    ~List();
    void Add(K key, V value);

};

#endif // LIST_H
