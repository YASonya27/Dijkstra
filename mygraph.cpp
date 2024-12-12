#include "mygraph.h"
#include<iostream>
#include <stdio.h>

// class Node{
//     private:
//         int value;                      // Номер вершины
//         Node** neighbors;               // список соседей
//         int* edges;                      // список ребер

// public:
//         Node(int val = 0){
//             value = val;
//             neighbors = new Node*[100];  // считаем, что соседей не может быть больше 100
//             edges = new int[100];
//             for(int i = 0; i < 100; i++){
//                 neighbors[i] = nullptr;      // по умолчанию соседей нет
//                 edges[i] = 100000000;         // по умолчанию все ребра бесконечно большие
//             }
//         }
//         ~Node()){}
//         void deleted(){}
// };

// class Graph{
//     private:
//         Node** nodes;
//         int v;

int minimum(MyGraph& graph);      // декларация функций
void traversal(int n, MyGraph& graph);

void PrintNode(Node* node){
    int value = node->GetValue();
    Node** neighbors = node->GetNeighbors();
    int* edges = node->GetEdges();

    std::cout << "Вершина " << value << std::endl;
    int i = 0;
    while(neighbors[i] != nullptr){
        std::cout << "Сосед " << neighbors[i]->GetValue() << "; расстояние " << edges[i] << std::endl;\
        i += 1;
    }
    std::cout << "\n\n";
}

void MyGraph::Add(int first, int second, int edge){
    // проверяем, если ли узлы, если нет, создаем их (увеличиваем количество ненулевых узлов, меняем значение наибольшего элемента)
    if(nodes[first] == nullptr){
        nodes[first] = new Node(first);
        quontity += 1;
        if(first > v){v = first;}
    }
    if(nodes[second] == nullptr){
        nodes[second] = new Node(second);
        quontity += 1;
        if(second > v){v = second;}
    }

    // добавляем в соседей first узел со значением second, в соседей second узел со значением first, и записываем ребро между ними
    int i = 0;
    while(nodes[first]->neighbors[i] != nullptr){i += 1;}       // пока можем идти по соседям, идем по соседям
    nodes[first]->neighbors[i] = nodes[second];                 // следующий сосед после всех пройденный, теперь second
    nodes[first]->edges[i] = edge;                              // добавляем путь

    // аналогично с second, нужно добавить first в его соседи
    i = 0;
    while(nodes[second]->neighbors[i] != nullptr){i += 1;}       // пока можем идти по соседям, идем по соседям
    nodes[second]->neighbors[i] = nodes[first];                 // следующий сосед после всех пройденный, теперь second
    nodes[second]->edges[i] = edge;                              // добавляем путь
}


void MyGraph::PrintGraph(){
    std::cout << "\n";
    for(int i = 0; i <= v; i++){
        if(nodes[i] != nullptr){PrintNode(nodes[i]);}
    }
}


int charArrayToInt(const char* str) {
    int result = 0; // Переменная для хранения результата

    for (int i = 0; str[i] != '\0'; ++i) {
        if (str[i] < '0' || str[i] > '9'){result = 987654109; break;}      // проверка, что у нас не буквы (если буквы или другие символы делаем значение невозможным)
        result = result * 10 + (str[i] - '0'); // Преобразование символа в число и добавление к результату
    }
    
    return result; // Возвращаем результат с учетом знака
}

bool end(char* input){
    // Проверка на выход
    int isExit = 1; // флаг для проверки, что нужно выйти из цикла while(1)
    const char *exitStr = "exit"; // Строка для сравнения
    for (int i = 0; exitStr[i] != '\0' || input[i] != '\0'; i++) {      // идем, пока одна из строк не закончится
        if (input[i] != exitStr[i]) {// Если строки не равны
            isExit = 0; 
            break; // Выходим из цикла
        }
    }
    return isExit;
}

MyGraph ReadGraph() {
    MyGraph g; 
    char input[256]; // выделяем память для строки
    int first, second, edge; // Переменные для хранения узлов и веса ребра

    std::cout << "\nВведите тройки чисел (пара узлов и вес ребра), или 'exit' для выхода\nВажно! Узлы должны быть меньше 1000!\n";

    while (true) {
        std::cout << "Введите: "; 
        std::cin >> input; // Считываем строку до пробела

        if (end(input)) {
            break; // Выходим из цикла
        }

        first = charArrayToInt(input);      // превращаем строку в число
        std::cin >> input;                  // считываем новую строку
        second = charArrayToInt(input);     // превращаем строку в число
        std::cin >> input;                  // считываем новую строку
        edge = charArrayToInt(input);       // превращаем строку в число



        // Проверка, что вершины меньше 1000 и не были введены буквы
        if (first >= 1000 || second >= 1000) {
            std::cout << "Ошибка: нужно ввести числа, меньше 1000 (именно числа, не буквы)\n"; 
            continue;
        }
        if(edge == 987654109){std::cout << "Ошибка: ребро не может быть не числом\n"; continue;}

        // std::cout << "Добавляем ребро: " << first<< " " << second << " " << edge << "\n";
        // Добавляем ребро в граф
        g.Add(first, second, edge);
    }
    return g;
}

int Dijkstra(MyGraph& graph, int first, int last){
    for(int i = 0 ; i < 1000; i++){graph.ways[i] = 100000000; graph.visited[i] = 0;} // делаем все пути бесконечно большими, а вершины непосещенными
    graph.ways[first] = 0;  // расстояние до первой вершины считаем равным 0
    int numSmallest = first;        // номер вершины, до которой расстояние минимально 
    // std::cout << "\nНАЧИНАЕМ ОБХОД!\n";
    for(int i = 0; i < graph.GetQ(); i++){              // в значении q, которое мы получаем лежит количество вершин в графе
        traversal(numSmallest, graph);
        graph.visited[numSmallest] = 1;
        // std::cout << "Вершина " << numSmallest <<  " посещена!\n";
        if(i != graph.GetQ()-1){
            numSmallest = minimum(graph);
            if(numSmallest == 10000010){std::cout << "Что-то пошло не так((\n"; return 123123123;}
        }

    }
    return graph.ways[last];
}

int minimum(MyGraph& graph){
    int minimumVal = 100000000;
    int minimumNum = 10000010;
    int q = graph.GetQ();
    for(int i = 0; i <= q; i++){     // Идем по всем вершинам 
        if(graph.visited[i] == 0){     // Если вершина еще не посещена
            if(graph.ways[i] < minimumVal){
                minimumVal = graph.ways[i]; minimumNum = i;}
        }
    }
    return minimumNum;
}

void traversal(int n, MyGraph& graph){
    Node* node = graph.GetNodes()[n];   // теперь в node лежит указатель на вершину, чьих соседей мы будет рассматривать
    Node** neighbors = node->GetNeighbors();    // а это соседи
    int s = graph.ways[n];              // минимальный путь до вершины n
    int i = 0;
    int vertex;                         // здесь будет значение очередного соседа
    while(neighbors[i] != nullptr){     // пойдем по соседям
        vertex = neighbors[i]->GetValue();
        if(graph.visited[vertex] == 0){     // Если вершина еще не посещена
            if(graph.ways[vertex] > s + node->GetEdges()[i]){   // и путь до вершины больше, чем если мы пойдем через вершину n
                graph.ways[vertex] = s + node->GetEdges()[i];   // обновляем путь
            }
        }
        i += 1;
    }
}