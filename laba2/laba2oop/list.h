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
    ~List(){
        while(Head){
            Tail=Head->next;
            delete Head;
            Head=Tail;
        }
    };
    void Add(K key, V value){
        ListNode<K,V> *temp=new ListNode<K,V>;
        temp->next=NULL;
        temp->key=key;
        temp->value=value;
        if(Head!=NULL){
            temp->prev=Tail;
            Tail->next=temp;
            Tail=temp;
        }
        else{
            temp->prev=NULL;
            Head=Tail=temp;
        }
    };

};

#endif // LIST_H
