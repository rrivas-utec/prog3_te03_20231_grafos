#include <iostream>
#include "grafo.h"

int main() {
    grafo<string, int, int> g;
    // Vertices
    g.add_vertex({"A", 1});
    g.add_vertex({"E", 2});
    g.add_vertex({"I", 3});
    g.add_vertex({"O", 4});
    g.add_vertex({"U", 5});
    // Aristas
    g.add_edge("A", "I", 20);
    g.add_edge("A", "E", 10);
    g.add_edge("E", "I", 15);
    g.add_edge("E", "O", 7);
    g.add_edge("O", "U", 12);

    g.bfs("A", [](auto key) {
        cout << key << " ";
    });
    cout << endl;
    g.dfs("A", [](auto key) {
        cout << key << " ";
    });
    cout << endl;

    return 0;
}
