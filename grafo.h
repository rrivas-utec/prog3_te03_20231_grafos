//
// Created by rrivas on 4/07/2023.
//

#ifndef PROG3_TE03_20231_GRAFOS_GRAFO_H
#define PROG3_TE03_20231_GRAFOS_GRAFO_H

#include <utility>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <forward_list>
#include <queue>
#include <stack>

using namespace std;

template<
        typename KeyType,
        typename ValueType,
        typename WeightType>
class grafo {
    using VertexType = size_t;
    using AdjacentType = pair<VertexType, WeightType>;
    using ItemType = pair<VertexType, ValueType>;
    using EdgeType = tuple<VertexType, VertexType, WeightType>;
    // Lista de Vertices
    unordered_map<KeyType, ItemType> vertices;
    // Lista de Adyacentes
    vector<forward_list<AdjacentType>> adjacent_vertices;
    KeyType get_key(VertexType vertex) {
        auto it = find_if(begin(vertices), end(vertices), [vertex](const auto& item){
           return item.second.first == vertex;
        });
        // Validar si no lo encontro
        if (it == end(vertices)) {
            throw runtime_error("clave no encontrada");
        }
        return it->first;
    }
public:
    grafo() = default;
    // Adicionar Vertices
    bool add_vertex(pair<KeyType, ValueType> node) {
        // Si no lo encuentra lo adicional
        auto [key, value] = node;
        if (vertices.find(key) == end(vertices)) { // Sino existe
            auto item = pair{size(adjacent_vertices), value};
            vertices.emplace(key, item);
            adjacent_vertices.emplace_back();
            return true;
        }
        return false;
    }
    // Adicionar Aristas
    void add_edge(KeyType kv1, KeyType kv2, WeightType weight) {
        auto vx1 = vertices[kv1].first;
        auto vx2 = vertices[kv2].first;
        adjacent_vertices[vx1].emplace_front(vx2, weight);
        adjacent_vertices[vx2].emplace_front(vx1, weight);
    }
    template <typename UnaryFunction>
    void bfs(KeyType key, UnaryFunction fun) {
        // Definir variables
        queue<VertexType> q;
        unordered_set<VertexType> visited;
        auto is_visited = [&visited](auto vertex) { return visited.find(vertex) != end(visited); };
        // Agregar el primer valor
        auto fv = vertices[key].first;
        q.push(fv);
        visited.insert(fv);
        // El Bucle
        while (!q.empty()) {
            // obtener el primer valor del queue
            auto v = q.front();
            fun(get_key(v));
            q.pop();
            // agregar los adyacentes al queue
            for (auto [a, w]: adjacent_vertices[v]) {
                if (!is_visited(a)) {
                    q.push(a);
                    visited.insert(a);
                }
            }
        }
    }
    template <typename UnaryFunction>
    void dfs(KeyType key, UnaryFunction fun) {
        // Definir variables
        stack<VertexType> s;
        unordered_set<VertexType> visited;
        // Tomar el primer valor
        auto fv = vertices[key].first;
        // Agregar al stack y set
        s.push(fv);
        visited.insert(fv);
        // bucle
        while(!s.empty()) {
            auto v = s.top(); // Paso #3

            // Buscar si hay algun adyacente no visita
            auto av = adjacent_vertices[v];
            auto it = find_if(begin(av), end(av), [&visited](auto adjacent) {
                return visited.find(adjacent.first) == end(visited);
            });

            if (it != end(av)) {    // Paso #4
                s.push(it->first);
                visited.insert(it->first);
            }
            else {                  // Paso #5
                s.pop();
                fun(get_key(v));
            }
        }
    }
    template<typename UnaryFunction>
    void prim(KeyType key, UnaryFunction fun) {
        auto edge_compare = [](auto e1, auto e2) {
            return get<2>(e1) > get<2>(e2);
        };
        priority_queue<EdgeType, vector<EdgeType>, decltype(edge_compare)> pq;
        unordered_set<VertexType> visited;
        auto is_visited = [&visited](auto vertex) { return visited.find(vertex) != end(visited); };

        auto fvx = vertices[key].first;
        for (auto [fva, fw]: adjacent_vertices[fvx]) {
            pq.push({fvx, fva, fw});
        }
        visited.insert(fvx);
        while (!pq.empty()) {
            // Obtenemos el top
            auto [vx, va, w] = pq.top();
            pq.pop();
            if (!is_visited(va)) {
                visited.insert(va);
                fun(get_key(vx), get_key(va), w);
                for(auto [vaa, waa]: adjacent_vertices[va]) {
                    pq.push({va, vaa, w})
                }
            }
        }
    }
};

#endif //PROG3_TE03_20231_GRAFOS_GRAFO_H
