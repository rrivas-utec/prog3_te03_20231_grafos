#include <iostream>
#include "grafo.h"

int main() {
    grafo<string, int, int> g;
    g.add_vertex({"A", 10});
    g.add_vertex({"A", 10});
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
