#ifndef _graph_algorithms
#define _graph_algorithms

#include <iostream>
#include <list>
#include <iostream>
#include <queue>
#include <functional>
#include <climits>

#include "graph.hpp"
#include "edge.hpp"
#include "./special_structures/dsu.hpp"

namespace graph_algorithms {
    std::list<Edge> boruvka(Graph graph, const int& start_verticals, const int& cost, int& ostov_cost);
    std::list<Edge> prim(Graph graph, const int& start_verticals, const int& max_cost_edge, int& ostov_cost);
    std::list<Edge> kruscal(Graph graph, const int& max_cost_edge, int& ostov_cost);
    std::list<int> dijkstra(Graph graph, const int& vertex_a, const int& vertex_b, int& max_cost_edge);
}

#endif