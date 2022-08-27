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
        void DFS(int id_nodo, HashTable *table);
    
    private:
        void DFSUtils(int id_vicino);
        int time;
};

DfsGraph::DfsGraph()
{
    time = 0;
}

void DfsGraph::DFS(int id_nodo, HashTable *table){
        tl::expected<node, int> returnedValue = table->searchValue(id_nodo);

        if(!returnedValue.has_value()){
            cout << "Valore non trovato";
            return;
        }

        node value = returnedValue.value();
        value.setTimeVisit(time + 1);
        value.setColor("gray");

        list<int> list_adj = value.getListaAdiacenza();
        list<int>::iterator i;
        for(i = list_adj.begin(); i != list_adj.end(); ++i){
            tl::expected<node, int> adjNode = table->searchValue(*i);
            if(returnedValue.value().getColor()=="white"){
                DFS(*i, table);
            }
        }

        value.setColor("BLACK");
        value.setTimeCompletation(time + 1);
}
#endif