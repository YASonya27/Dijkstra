#ifndef MYGRAPH_H
#define MYGRAPH_H

#include<iostream>

class Node{
    friend class MyGraph;
    private:
        int value;                      // Номер вершины
        Node** neighbors;               // список соседей
        int* edges;                      // список ребер
    public:
        Node(int val = 0){
            value = val;
            neighbors = new Node*[100];  // считаем, что соседей не может быть больше 100
            edges = new int[100];
            for(int i = 0; i < 100; i++){
                neighbors[i] = nullptr;      // по умолчанию соседей нет
                edges[i] = 100000000;         // по умолчанию все ребра бесконечно большие
            }
        }
        ~Node(){
            delete[] neighbors;
            delete[] edges;
        }

        Node(const Node& other) : value(other.value) {
        neighbors = new Node*[100];  // создать новый массив соседей
        edges = new int[100];         // создать новый массив рёбер
        for (int i = 0; i < 100; i++) {
            neighbors[i] = other.neighbors[i]; // копировать указатели на соседей
            edges[i] = other.edges[i]; // копировать веса рёбер
            }
        }

        int GetValue(){return value;}
        Node** GetNeighbors(){return neighbors;}
        int* GetEdges(){return edges;}

        void deleted(){
            delete[] neighbors;
            delete[] edges;
        }
};


class MyGraph{
    private:
        Node** nodes;       // список с указателями на узлы
        int v;              // самый большой номер узла
        int quontity;       // количество ненулевых узлов;
    public:
        int* ways;          // пути для алгоритма Дейкстры
        int* visited;       // проверка посетили ли мы вершину
        int GetQ(){return quontity;}
        int GetV(){return v;}
        Node** GetNodes(){return nodes;}
        MyGraph(){
            v = 0;
            quontity = 0;
            nodes = new Node*[1000];        // считаем, что вершин будет не больше 1000
            ways = new int[1000];
            visited = new int[1000];
            for(int i = 0 ; i < 1000; i++){nodes[i] = nullptr; ways[i] = 100000000;visited[i] = 0;}

        }   
        ~MyGraph(){
            if(v > 0){
                for(int i = 0; i < v; i++){if(nodes[i] != nullptr) delete nodes[i];}
            }
            delete[] nodes; 
        }

        MyGraph(const MyGraph& other){
            v = other.v, quontity = other.quontity;
            nodes = new Node*[1000];  // выделение памяти для нового массива
            ways = new int[1000];
            visited = new int[1000];
            for (int i = 0; i < 1000; i++) {
                if (other.nodes[i] != nullptr) {
                    nodes[i] = new Node(*(other.nodes[i])); // Копируем узел
                } 
                else {
                    nodes[i] = nullptr; // Соседей нет
                }
                ways[i] = other.ways[i]; // Копируем веса рёбер
                visited[i] = other.visited[i]; // Копируем статус посещения
                }
        }
        void Add(int first, int second, int edge);
        void PrintGraph();
};

MyGraph ReadGraph();                        // Чтение графа
int charArrayToInt(const char* str);        //  Перевод строки в число
bool end(char* input);                      //  Сравнение строки с "exit"
int Dijkstra(MyGraph& graph, int i, int j); //  Сам алгоритм Дейкстры
int minimum(MyGraph& graph);                //  Поиск вершины с наименьшим путем, но не посещенной

#endif