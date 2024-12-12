#include "mygraph.h"

int main() {
    std::cout << "Введите 1:  если хотите задать граф вручную\nВведите 0:  если хотите использовать граф, введенный автоматически\n";
    int choice;
    int endProgramm = 0;
    if(std::cin >> choice){
        if(choice == 1){
            MyGraph g = ReadGraph();
            if(g.GetQ() == 0){std::cout << "Граф пуст, в нем нет смысла искать пути\n\nПрограмма завершена!\n";endProgramm = 1;}
            else{
                std::cout << "\nВведенный граф:\n";
                g.PrintGraph(); // Печать графа
                char input[256];
                int first, last;            // переменные для запуска алгоритма
                while(1){
                    std::cout << "Введите два номера вершин, между которыми нужно посчитать расстояние (для выхода наберите exit)\n"; 
                    std::cin >> input;      // вводим числа, записываем строку в число

                    if(end(input)){std::cout << "\n\nЗадача завершена!\n"; break;}      // проверяем, не ввели ли exit
                    first = charArrayToInt(input);                                      // переводим строку в число
                    std::cin >> input;                 
                    last = charArrayToInt(input);     
                    if(first > 1000 || last > 1000){std::cout << "Некорректный ввод\n"; continue;}      // проверка, что вершины меньше 1000 и это цифры, а не буквы
                    if(g.GetNodes()[first] == nullptr || g.GetNodes()[last] == nullptr){std::cout << "Таких вершин в графе нет, попробуйте еще раз\n\n"; continue;}
                        
                    int way = Dijkstra(g, first, last);
                    if(way == 123123123){std::cout << "Вероятность попадания сюда была крайне мала, но почему-то это случилось, трееееш\n";}
                    else{std::cout << "Кратчайший путь от " << first << " до " << last << " равен " << way << "\n" << std::endl;}
                }
            }
        }
        else if(choice == 0){
            MyGraph g;
            //std::cout <<"Скоро здесь все заработает\n";
            g.Add(0, 1, 4);
            g.Add(0, 4, 2);
            g.Add(1, 2, 1);
            g.Add(1, 3, 3);
            g.Add(1, 4, 2);
            g.Add(2, 3, 7);
            g.Add(3, 4, 1);
            std::cout << "\nНаш граф:\n";
            g.PrintGraph(); // Печать графа
            char input[256];
            int first, last;            // переменные для запуска алгоритма
            while(1){
                std::cout << "Введите два номера вершин, между которыми нужно посчитать расстояние (для выхода наберите exit)\n"; 
                std::cin >> input;      // вводим числа, записываем строку в число

                if(end(input)){std::cout << "\n\nЗадача завершена!\n"; break;}      // проверяем, не ввели ли exit
                first = charArrayToInt(input);                                      // переводим строку в число
                std::cin >> input;                 
                last = charArrayToInt(input);     
                if(first > 1000 || last > 1000){std::cout << "Некорректный ввод\n"; continue;}      // проверка, что вершины меньше 1000 и это цифры, а не буквы
                if(g.GetNodes()[first] == nullptr || g.GetNodes()[last] == nullptr){std::cout << "Таких вершин в графе нет, попробуйте еще раз\n\n"; continue;}
                        
                int way = Dijkstra(g, first, last);
                if(way == 123123123){std::cout << "Вероятность попадания сюда была крайне мала, но почему-то это случилось, трееееш\n";}
                else{std::cout << "Кратчайший путь от " << first << " до " << last << " равен " << way << "\n" << std::endl;}
                }
        }
        else{std::cout << "Перезапустите программу и введите 0 или 1 в первом шаге\n";}
    }
    else{std::cout << "Перезапустите программу и введите 0 или 1 в первом шаге\n";}
    return 0;
}


                    // std::cout <<"\nПроверим, что у нас с данными:\n";
                    // g.PrintGraph();
                    // int v = g.GetV();
                    // int q = g.GetQ();
                    // Node** nodes = g.GetNodes();
                    // int* ways = g.ways;
                    // int* visited = g.visited;
                // std::cout << "v = " << g.GetV() << "; q = " << g.GetQ() << "\nВершины: ";
                // for(int i = 0; i <= g.GetV(); i++){if(g.GetNodes()[i] != nullptr){std::cout << g.GetNodes()[i]->GetValue() << "; ";}}
                    // std::cout << "\nПути: ";
                    // for(int i = 0; i <= v; i++){{std::cout << ways[i] << "; ";}}
                    // std::cout << "\nПосещения: ";
                    // for(int i = 0; i <= v; i++){{std::cout << visited[i] << "; ";}}
                    // std::cout << "\n\n";

                    
                    // g.ways[1] = 0;
                    // std::cout << "\nПроверка до начала цикла:\nПути: ";
                    // for(int i = 0; i <= g.GetV(); i++){{std::cout << g.ways[i] << "; ";}}
            //         // int r = minimum(g);
            //         // std::cout << "\nМинимум: " << r << "\n\n";

            //                     if(choice == 0){
            //     //std::cout <<"Скоро здесь все заработает\n";
            //     g.Add(0, 1, 4);
            //     g.Add(0, 4, 2);
            //     g.Add(1, 2, 1);
            //     g.Add(1, 3, 3);
            //     g.Add(1, 4, 2);
            //     g.Add(2, 3, 7);
            //     g.Add(3, 4, 1);
            //     std::cout << "\nНаш граф:\n";
            //     g.PrintGraph(); // Печать графа
            // }