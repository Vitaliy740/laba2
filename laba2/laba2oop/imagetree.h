#ifndef IMAGETREE_H
#define IMAGETREE_H
#include <iostream>
#include <fstream>
#include <string.h>
#include <memory>
#include <list.h>
template<typename K,typename V>
class ImageTree
{
    struct node{
    K key;
    V value;
    struct node* right;
    struct node* left;
};

private:
    //struct node* root;
    struct node *m_root;
    size_t m_size;
    void copy_tree(const node* copy){
        if(copy!=NULL){
            copy_tree(copy->left);
            add(copy->key,copy->value);
            copy_tree(copy->right);
        }
    };
    void add(struct node** node,K key, V value){
        if(*node!=NULL){
            struct node* tmp=new struct node;
            tmp->key=key;
            tmp->value=value;
            tmp->left=NULL;
            tmp->right=NULL;
            *node=tmp;
            this->m_size++;
        }
        else{
            if(key> (*node)->key){
                add(&(*node)->right,key,value);
            }
            else if(key < (*node)->key){
                add(&(*node)->left,key,value);
            }
            else{
                struct node* tmp=new struct node;
                tmp->key=key;
                tmp->value=value;
                tmp->left=(*node)->left;
                tmp->right=(*node)->right;
                *node=tmp;
            }
        }
    };
    void delite_tree(struct node* node){
        if(node!=NULL){
            delite_tree(node->left);
            delite_tree(node->right);
            delete node;
        }
    };
    void ordered_list(List<K,V> *list, struct node* node) const{
        if(node!=NULL){
            ordered_list(list,node->left);
            list->Add(node->key,node->value);
            ordered_list(list,node->right);
        }
    };
    void write_in_file(std::ofstream& file, struct node* node) const{
        if(node!=NULL){
            write_in_file(file,node->left);
            file<<node->key<<std::endl;
            file<<node->value<<std::endl;
            write_in_file(file,node->right);
        }
    };
    void delete_node(struct node** root, K key){
        if ((*root)->key>key){
            delete_node(&(*root)->left,key);
        }
        else if ((*root)->key<key){
            delete_node(&(*root)->right,key);
        }
        else{
            if ((*root)->left == NULL){
                     *root = (*root)->right;
                    }
            else if ((*root)->right == NULL) {
                    *root = (*root)->left;
                    }
            else {
                    node* succ_parent = (*root)->right;
                    node *succ = (*root)->right;
                    while (succ->left != NULL) {
                        succ_parent = succ;
                        succ = succ->left;
                        }
                    if (succ_parent != succ) {
                        succ_parent->left = succ->right;
                       }
                    else {
                        (*root)->right = succ->right;
                        }
                    (*root)->key = succ->key;
                    (*root)->value = succ->value;
            }
        }
    };
    bool find_key(struct node* node,K key)const{
        if(node==NULL)
            return false;
        if(key==node->key)
            return true;
        else{
            if(key>node->key)
                return find_key(node->right,key);
            else
                return find_key(node->left,key);
        }

    };
    V& find_value(struct node* node,K key)const{
        if(key==node->key)
            return node->key;
        if(key>node->key)
            return find_value(node->right,key);
        else
            return find_value(node->left,key);
    };
    bool equal_trees(node* node)const{
        if(node==NULL)
            return false;
        if(equal_trees(node->key) && (strcmp(node->value.c_str(),find_value(this->root, node->key).c_str()) == 0) && equal_trees(node->right) && equal_trees(node->left)){
            return true;
        }
        return false;
    };
public:
    ImageTree()
    {
        this->m_root=nullptr;
        this->m_size=0;
    };
    ImageTree(const ImageTree &copy){
        this->m_root=NULL;
        this->m_size=0;
        copy_tree(copy.m_root);
    };
    ~ImageTree(){
        delite_tree(m_root);
    };
    void DeleteTree(){
        delite_tree(this->m_root);
    };
    size_t Size()const{return m_size;}
    void WriteInFile(std::string output) const{
        std::ofstream my_file(output);
        write_in_file(my_file,this->m_root);
        my_file.close();
    };
    void ReadFromFile(std::string input){
        delite_tree(this->m_root);
        std::ifstream infile(input);
        if(!infile.fail()){
            K key;
            V value;
            while(infile>>key>>value)
                this->Add(key,value);
            infile.close();
        }
    };
    bool operator ==(const ImageTree &tree)const{
        if(tree.Size()!=m_size){
            return false;
        }
        return equal_trees(tree.m_root);
    }
;
    void Add(K key,V value){
        add(&(this->m_root),key,value);
    };
    void RemoveAt(K &key){
        if(find_key(m_root,key)){
            delete_node(&this->m_root,key);
            this->m_size--;
        }
        else return;
    };
    V& operator [](const K &key){
        if(find_key(key)){
            return find_value(this->m_root,key);
        }
        else
            throw("No key found");
    };
    bool FindKey(const K &key)const{
        return find_key(this->m_root,key);
    };
    List<K,V>* OrderedList()const{
        List<K,V> *list=new List<K,V>;
        ordered_list(list,this->m_root);
        return list;
    };

};

#endif // IMAGETREE_H
