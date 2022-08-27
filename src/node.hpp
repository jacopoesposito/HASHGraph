using namespace std;
#include <string>
#include <algorithm>
#include <list>

#ifndef node_hpp
#define node_hpp

class node
{
private:
    int value;
    int destination;
    bool visited;
    int time_visit;
    int time_completation;
    string color;
    list<int> lista_adiacenza;

public:
    node(int value, int destination, bool visited, int time_visit, int time_completation, string color, list<int> lista_adiacenza);
    node(int value, int destination, bool visited, int time_visit, int time_completation, string color);
    node();
    ~node();

    //Getter
    int getValue();
    int getDestination();
    bool getVisited();
    int  getTimeVisit();
    int getTimeCompletation();
    string getColor();
    list<int> getListaAdiacenza();

    //Setter
    void setValue(int value);
    void setDestination(int destination);
    void setVisited(bool visited);
    void  setTimeVisit(int time_visit);
    void setTimeCompletation(int time_completation);
    void setColor(string color);
};

int node::getValue(){
    return this->value;
}

int node::getDestination(){
    return this->destination;
}

bool node::getVisited(){
    return this->visited;
}

int node::getTimeVisit(){
    return this->time_visit;
}

int node::getTimeCompletation(){
    return this->time_completation;
}

string node::getColor(){
    return this->color;
}

list<int> node::getListaAdiacenza(){
    return this->lista_adiacenza;
}

void node::setValue(int value){
    this->value = value;
}

void node::setDestination(int destination){
    this->destination = destination;
}

void node::setVisited(bool visited){
    this->visited = visited;
}

void node::setTimeVisit(int time_visit){
    this->time_visit = time_visit;
}

void node::setTimeCompletation(int time_completation){
    this->time_completation = time_completation;
}

void node::setColor(string color){
    this->color = color;
}

node::node()
{

}

node::node(int value, int destination, bool visited, int time_visit, int time_completation, string color)
{
    this->value = value;
    this->destination = destination;
    this->visited = visited;
    this->time_visit = time_visit;
    this->time_completation = time_completation;
    this->color = color;
}

node::node(int value, int destination, bool visited, int time_visit, int time_completation, string color, list<int> lista_adiacenza)
{
    this->value = value;
    this->destination = destination;
    this->visited = visited;
    this->time_visit = time_visit;
    this->time_completation = time_completation;
    this->color = color;
    this->lista_adiacenza = lista_adiacenza;
}

node::~node()
{
}


#endif