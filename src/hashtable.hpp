using namespace std;
#include "node.hpp"
#include "../lib/expected.hpp"
#include <stdexcept>

#ifndef hashtable_hpp
#define hashtable_hpp


class HashNode{
    public:
        HashNode(int key, node *value){
            this->value=value;
            this->key=key;
        }
        int getKey(){
            return key;
        }
        void setKey(int key){
            this->key = key;
        }
        node getValue(){
            return *value;
        }
    private:
        node *value;
        int key;
};

const int TABLE_SIZE = 128;

class HashTable{
    private:
        HashNode **table;
        bool isFull();
        int hashFunc1(int key);
        int hashFunc2(int key);
    public:
        int size_current;
        HashTable();
        tl::expected<node, int> searchValue(int key);
        void put(int key, node *value);
        void deleteNode(int key);
        void displayHashTable();
};

HashTable::HashTable(){
    table = new HashNode*[TABLE_SIZE];
    for (int i = 0; i < TABLE_SIZE; i++)
        table[i] = NULL;
}

void HashTable::put(int key, node *value){
    if(isFull()){
        return;
    }
    int hash = hashFunc1(key);
    
    if(table[hash]!=NULL){
        int offset = hashFunc2(key);
        if(table[hash]->getKey() == -2){
            table[hash] = new HashNode(key, value);
            size_current++;
            return;
        }
        for(int i = 1; i < TABLE_SIZE; i++){
            int newHash = (hash + i * offset) % TABLE_SIZE;
            if(table[newHash]==NULL){
                table[newHash] = new HashNode(key, value);
                break;
            }
        }
    }
    else{
        table[hash] = new HashNode(key, value);
    }
    size_current++;

}

tl::expected<node, int> HashTable::searchValue(int key){
    int hash1 = hashFunc1(key);
    int hash2 = hashFunc2(key);
    if(table[(hash1 + 0*hash2)%TABLE_SIZE] == NULL){
        return tl::unexpected(-1);
    }

    if(table[(hash1 + 0*hash2)%TABLE_SIZE]->getKey() == -2)
        return tl::unexpected(-2);

    int i = 0;
    while(table[(hash1 + i*hash2)%TABLE_SIZE]->getKey() != key){
        if(table[(hash1 + i*hash2)%TABLE_SIZE] == NULL){
            cout << "Sono nella ricerca";
            return tl::unexpected(-1);
        }
        i++;
    }
    return table[(hash1 + i*hash2)%TABLE_SIZE]->getValue();
}

void HashTable::deleteNode(int key){
    int hash1 = hashFunc1(key);
    int hash2 = hashFunc2(key);
    
    if(table[(hash1 + 0*hash2)%TABLE_SIZE] == NULL){
        return;
    }


    int i = 0;
    while(table[(hash1 + i*hash2)%TABLE_SIZE]->getKey() != key){
        if(table[(hash1 + i*hash2)%TABLE_SIZE] == NULL){
            return;
        }
        i++;
    }
    table[(hash1 + i*hash2)%TABLE_SIZE] = new HashNode(-2, new node(-1, -1, false, -1, -1, "boh"));
}

// void HashTable::displayHashTable(){
//     for(int i = 0; i < TABLE_SIZE; i++){
//         //node value = table[i]->getValue();
//         cout << "* Row" << i << " Key-->" << table[i]->getKey() << "Value-->" << table[i]->getValue().getValue() << "*" << endl;
//     }
// }

bool HashTable::isFull(){
    if(size_current == TABLE_SIZE){
        return true;
    }
    else{
        return false;
    }
}

int HashTable::hashFunc1(int key){
    return (key % TABLE_SIZE);
}

int HashTable::hashFunc2(int key){
    return (127 - (key % TABLE_SIZE));
}

#endif