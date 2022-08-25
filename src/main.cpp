using namespace std;
#include "iostream"
#include <iomanip>
#include <limits>
#include "hashtable.hpp"
#include "node.hpp"
#include "../lib/expected.hpp"


void displaymenu(){
    cout << "\n******************************************";
    cout << "\n**         HashGraph V0.0.1             **";
    cout << "\n** Developed by Jacopo Gennaro Esposito **";
    cout << "\n** ------------------------------------ **";
    cout << "\n**                Menu                  **";
    cout << "\n**         1) Aggiungi nodo su HT       **";
    cout << "\n**         2) Rimuovi nodo da HT        **";
    cout << "\n**         3) Trova nodo in HT          **";
    cout << "\n**         4) Esegui DFS                **";
    cout << "\n**         5) Esci                      **";
    cout << "\n******************************************";
}

int main(){
    const char * welcomeMessage = "\n\n Benvenuti in HashGraph, memorizza e gestisci un grafo orientato grazie ad una hash table";
    bool exec = true;
    int scelta;
    cout << welcomeMessage;

    int nodeValue, nodeDestination, key;
    HashTable *table = new HashTable();
    node *value;
    tl::expected<node, int> returnedValue;
    node rvalue;
    
    displaymenu();
    
    do{
        cout << "\n Scelta -> ";
        cin >> scelta;
        switch(scelta){
            case 1:
            {
                cout << "Aggiungi nodo su HT" << endl;
                cout << "Composizione nodo: " << endl;
                cout << "Inserisci identificativo nodo-> ";
                cin >> nodeValue;
                cout << "\nInserisci identicativo nodo destinazione-> ";
                cin >> nodeDestination;
                value = new node(nodeValue, nodeDestination, false, -1, -1, "white");
                
                cout << "\nInserisci chiave per HT-> ";
                cin >> key;
                table->put(key, value);
                returnedValue = table->searchValue(key);
                rvalue = returnedValue.value();
                cout << rvalue.getColor();
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
                
                cout << left << setw(20) << rvalue.getValue() << left << setw(20) << rvalue.getDestination() << left << setw(20) << rvalue.getVisited() 
                 << left << setw(20) << rvalue.getTimeVisit()  << left << setw(20) << rvalue.getTimeCompletation() << left << setw(20) << rvalue.getColor() << endl; 
            break;
            }
            case 4:
                cout << "Eseguo DFS";
                break;
            case 5:
                exec = false;
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