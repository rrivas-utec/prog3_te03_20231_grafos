//
// Created by rrivas on 4/07/2023.
//

#ifndef PROG3_TE03_20231_GRAFOS_GRAFO_H
#define PROG3_TE03_20231_GRAFOS_GRAFO_H

#include <utility>
#include <vector>
#include <unordered_map>
#include <forward_list>
using namespace std;

template<
        typename KeyType,
        typename ValueType,
        typename WeightType>
class grafo {
    using VertexType = size_t;
    using AdjacentType = pair<VertexType, WeightType>;
    using ItemType = pair<VertexType, ValueType>;
    // Lista de Vertices
    unordered_map<KeyType, ItemType> vertices;
    // Lista de Adyacentes
    vector<forward_list<AdjacentType>> adjacent_vertices;
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
};

#endif //PROG3_TE03_20231_GRAFOS_GRAFO_H
