/*
    Developed by Jacopo Gennaro Esposito 
*/
using namespace std;
#include "iostream"
#include <iomanip>
#include <limits>
#include <fstream>
#include <filesystem>
#include <list>
#include "dfsGraph.hpp"
#include "hashtable.hpp"
#include "node.hpp"
#include "../lib/expected.hpp"


void displaymenu(){
    cout << "\n******************************************";
    cout << "\n**         HashGraph V0.0.2             **";
    cout << "\n** Developed by Jacopo Gennaro Esposito **";
    cout << "\n** ------------------------------------ **";
    cout << "\n**                Menu                  **";
    cout << "\n**         1) Aggiungi nodo su HT       **";
    cout << "\n**         2) Rimuovi nodo da HT        **";
    cout << "\n**         3) Trova nodo in HT          **";
    cout << "\n**         4) Aggiungi arco             **";
    cout << "\n**         5) Rimuovi arco              **";
    cout << "\n**         6) Trova arco                **";
    cout << "\n**         7) Esegui DFS                **";
    cout << "\n**         8) Mostra menu               **";
    cout << "\n**         9) Esci                      **";
    cout << "\n******************************************";
}

int main(){
    const char * welcomeMessage = "\n\n Benvenuti in HashGraph, memorizza e gestisci un grafo orientato grazie ad una hash table";
    bool exec = true;
    string inputFile, input1;
    char buffer[256];

    int nodeValue, nodeDestination, key, scelta, userInputDimensionTable, fileDimensionTable;
    node *value;
    tl::expected<node *, int> returnedValue;
    node *rvalue;

    cout << welcomeMessage;

    cout << "\n\nScegli il file di input-> ";
    cin >> inputFile;

    ifstream file;
    file.open(inputFile);

    if(!file.is_open()){
        cout << "File doesn't exist";
        return -1;
    }

    
    cout << "\n\nInserisci dimensione HashTable-> ";
    cin >> userInputDimensionTable;
    file  >> input1;
    fileDimensionTable = stoi(input1);
    cout << "Numero nodi presenti nel file di input->" << fileDimensionTable << endl;

    if(userInputDimensionTable < fileDimensionTable){
        cout << "\n Errore tabella di Hashing troppo piccola per contenere i dati di input!" << endl;
        return -3;
    }

    HashTable *table = new HashTable(userInputDimensionTable);

    file.getline(buffer, 256);
    int i = 1;
    string idNode, destinationNode;
    
    while(file >> idNode >> destinationNode){
        list<int> lista_adiacenza;
        list<int> lista_adj_destNode;
        tl::expected<node *, int> secondReturnedValue;

        lista_adiacenza.push_back(stoi(destinationNode));
        lista_adj_destNode.push_back(stoi(idNode));

        returnedValue = table->searchValue(stoi(idNode));
        secondReturnedValue = table->searchValue(stoi(destinationNode));

        if(!returnedValue.has_value()){
            table->put(stoi(idNode), new node(stoi(idNode), stoi(destinationNode), false, -1, -1, "white", lista_adiacenza));
        }
        else{
            rvalue = returnedValue.value();
            rvalue->setListaAdiacenza(stoi(destinationNode));
        }
        if(!secondReturnedValue.has_value()){
            table->put(stoi(destinationNode), new node(stoi(destinationNode), 0, false, -1, -1, "white", lista_adj_destNode));
        }
        else{
            rvalue = secondReturnedValue.value();
            rvalue->setListaAdiacenza(stoi(idNode));
        }
    }

    displaymenu();
    
    do{
        cout << "\n Scelta -> ";
        cin >> scelta;
        switch(scelta){
            case 1:
            {
                cout << "Aggiungi nodo su HT" << endl;
                cout << "Composizione nodo: " << endl;
                cout << "\nInserisci identificativo nodo-> ";
                cin >> nodeValue;
                cout << "\nInserisci identicativo nodo destinazione-> ";
                cin >> nodeDestination;
                list<int> lista_adiacenza;
                lista_adiacenza.push_back(nodeDestination);
                value = new node(nodeValue, nodeDestination, false, -1, -1, "white", lista_adiacenza);
                
                cout << "\nInserisci chiave per HT-> ";
                cin >> key;
                table->put(key, value);
                returnedValue = table->searchValue(key);
                rvalue = returnedValue.value();
                cout << "Nodo aggiunto con successo ad HT" << endl;
            break;
            }
            case 2:
            {
                cout << "Rimuovi nodo da HT";
                int searchKey = 0;
                cout << "\nInserisci numero chiave del nodo che vuoi rimuovere-> ";

                cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                cin >> searchKey;
                table->deleteNode(searchKey);

            break;
            }
            case 3:
            {
                int searchKey;
                cout << "Trova nodo in HT";
                cout << "\nInserisci numero chiave del nodo che vuoi cercare-> ";

                cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 

                cin >> searchKey;
                cout << "Ricerco chive-> " << searchKey << endl;

                returnedValue = table->searchValue(searchKey);
                
                if(!returnedValue.has_value()){
                    cout << "Valore non trovato";
                    break;
                }

                rvalue = returnedValue.value();
                
                cout << left << setw(20) << "\n\nID Nodo" << left << setw(20) << "ID Destinazione" << left << setw(20) << "Visitato" 
                << left << setw(20) << "Tem Inizio Visita"  << left << setw(20) << "Tem Fine Visita"  << left << setw(20) << "Colore" << endl;
                
                cout << left << setw(20) << rvalue->getValue() << left << setw(20) << rvalue->getDestination() << left << setw(20) << rvalue->getVisited() 
                << left << setw(20) << rvalue->getTimeVisit()  << left << setw(20) << rvalue->getTimeCompletation() << left << setw(20) << rvalue->getColor() << endl;

            break;
            }
            case 4:
            {
                cout << "Aggiungi arco";
                int idPrimoNodo, idSecondoNodo;
                tl::expected<node *, int> secondReturnedValue; 
                cout << "\nInserisci id primo nodo->";
                cin >> idPrimoNodo;
                cout << "\nInserisci id secondo nodo->";
                cin >> idSecondoNodo;

                returnedValue = table->searchValue(idPrimoNodo);
                secondReturnedValue = table->searchValue(idSecondoNodo);
                
                if(!returnedValue.has_value() && !secondReturnedValue.has_value()){
                    cout << "Valore non trovato";
                    break;
                }

                rvalue = returnedValue.value();
                rvalue->setListaAdiacenza(idSecondoNodo);
                rvalue = secondReturnedValue.value();
                rvalue->setListaAdiacenza(idPrimoNodo);

                cout << "\nArco aggiunto con successo";

                break;
            }
            case 5:
            {
                cout << "\nRimuovi arco";
                int idPrimoNodo, idSecondoNodo;
                tl::expected<node *, int> secondReturnedValue; 
                cout << "\nInserisci id primo nodo->";
                cin >> idPrimoNodo;
                cout << "\nInserisci id secondo nodo->";
                cin >> idSecondoNodo;

                returnedValue = table->searchValue(idPrimoNodo);
                secondReturnedValue = table->searchValue(idSecondoNodo);
                
                if(!returnedValue.has_value() && !secondReturnedValue.has_value()){
                    cout << "\nValore non trovato";
                    break;
                }

                rvalue = returnedValue.value();
                rvalue->removeValueFromList(idSecondoNodo);
                rvalue = secondReturnedValue.value();
                rvalue->removeValueFromList(idPrimoNodo);

                cout << "\nArco eliminato con successo";

                break;
            }
            case 6:
            {
                cout << "\nTrova arco";
                int idPrimoNodo, idSecondoNodo;
                tl::expected<node *, int> secondReturnedValue;
                node *rSecondValue; 
                cout << "\nInserisci id primo nodo->";
                cin >> idPrimoNodo;
                cout << "\nInserisci id secondo nodo->";
                cin >> idSecondoNodo;

                returnedValue = table->searchValue(idPrimoNodo);
                secondReturnedValue = table->searchValue(idSecondoNodo);
                
                if(!returnedValue.has_value() && !secondReturnedValue.has_value()){
                    cout << "\nValore non trovato";
                    break;
                }

                rvalue = returnedValue.value();
                rSecondValue = secondReturnedValue.value();
                int valueEdge1 = rvalue->findNodeInAdjList(idSecondoNodo);
                int valueEdge2 = rSecondValue->findNodeInAdjList(idPrimoNodo);

                if((valueEdge1 == -1) || (valueEdge2 == -1)){
                    cout << "\nArco non trovato";
                    break;
                }                

                cout << "\nArco: " << valueEdge2 << "-" << valueEdge1;

                break;
            }
            case 7:
            {
                cout << "Eseguo DFS";
                DfsGraph *dfs = new DfsGraph();
                dfs->DFS(table);
                break;
            }
            case 8:
                displaymenu();
                break;
            case 9:
                exec = false;
                table->~HashTable();
                cout << "Esco...";
            break;
            default:
                cout << "Errore input";
                cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');        
        }

    }
    while(exec);

    return 0;
}