/*
    Developed by Jacopo Gennaro Esposito 
*/

using namespace std;
#include <iostream>
#include <list>
#include "node.hpp"
#include "hashtable.hpp"
#include "../lib/expected.hpp"

#ifndef dfsGraph_hpp
#define dfsGraph_hpp

class DfsGraph{
    public:
        DfsGraph();
        void DFS(HashTable *table);
    
    private:
        void DFSVisit(int id_nodo, HashTable *table);
        int time;
};

DfsGraph::DfsGraph()
{
    time = 0;
}

void DfsGraph::DFS(HashTable *table){
    for(int i = 1; i < table->size_current; i++){
        cout << "\nCerco il nodo:" << i;
        tl::expected<node *, int> returnedValue = table->searchValue(i);

        if(!returnedValue.has_value()){
            cout << "Valore non trovato";
            return;
        }

        node *value = returnedValue.value();

        DFSVisit(i, table);
    }

}

void DfsGraph::DFSVisit(int id_nodo, HashTable *table){
        tl::expected<node *, int> returnedValue = table->searchValue(id_nodo);

        if(!returnedValue.has_value()){
            cout << "Valore non trovato";
            return;
        }

        node *value = returnedValue.value();
        time+=1;
        value->setTimeVisit(time);
        value->setColor("gray");

        list<int> list_adj = value->getListaAdiacenza();
        list<int>::iterator i;
        for(i = list_adj.begin(); i != list_adj.end(); i++){
            tl::expected<node *, int> adjNode = table->searchValue(*i);
            if(adjNode.value()->getColor()=="white"){
                cout <<"\nEsamino il vicino:"<< *i << endl;
                DFSVisit(*i, table);
            }
        }
        time+=1;
        value->setColor("black");
        value->setTimeCompletation(time);
}
#endif