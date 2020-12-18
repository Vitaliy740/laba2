#ifndef IMAGETREE_H
#define IMAGETREE_H
#include <iostream>
#include <fstream>
#include <string.h>
#include <memory>
#include <list.h>
template<class K,class V>
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
    std::unique_ptr<struct node> *m_root;
    size_t m_size;
    void copy_tree(const node* copy);
    void add(std::unique_ptr<struct node>** node,K key, V value);
    void delite_tree(const std::unique_ptr<struct node>* node);
    void ordered_list(List<K,V> *list, std::unique_ptr<struct node>* node) const;
    void write_in_file(std::ofstream& file, std::unique_ptr<struct node>* node) const;
    void delete_node(std::unique_ptr<struct node>** root, K key);
    bool find_key(std::unique_ptr<struct node>* node,K key)const;
    V& find_value(std::unique_ptr<struct node>* node,K key)const;
    bool equal_trees(node* node)const;
public:
    ImageTree();
    ImageTree(const ImageTree &copy);
    ~ImageTree();
    void DeleteTree();
    size_t Size()const{return m_size;}
    void WriteInFile(std::string output) const;
    void ReadFromFile(std::string input);
    bool operator ==(const ImageTree &tree)const;
    void Add(K key,V value);
    void RemoveAt(K &key);
    V& operator [](const K &key);
    bool FindKey(const K &key)const;
    List<K,V>* OrderedList()const;

};

#endif // IMAGETREE_H
