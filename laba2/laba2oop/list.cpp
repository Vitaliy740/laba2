#include "list.h"

template<typename K,typename V>
void List<K,V>::Add(K key,V value){
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
}
template<typename K,typename V>
List<K,V>::~List(){
    while(Head){
        Tail=Head->next;
        delete Head;
        Head=Tail;
    }
}
