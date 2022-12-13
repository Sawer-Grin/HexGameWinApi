#include "graph_math.hpp"


bool cmp_edges(Edge left_edge, Edge right_edge);
bool cmp_edges_with_neighbors(EdgeNeighbor left_edge, EdgeNeighbor right_edge);
inline std::vector<Edge> initialize_char_edges(Graph graph, const int& cost);

std::list<Edge> graph_algorithms::boruvka(Graph graph, const int& start_verticals, const int& max_cost_edge, int& ostov_cost) {

	auto char_edges = initialize_char_edges(graph, max_cost_edge);
    DSU vertices_tree(graph.V());
    ostov_cost = 0;
    int amount_of_vertices = graph.V();
    std::vector<Edge> cheapest_edges(graph.V(), Edge::default_edge());
    std::list<Edge> ostov_tree(0);

    for (int i = 0; i < graph.V(); ++i) {
        vertices_tree.make_set(i);
    }

    while (amount_of_vertices > 1) {

        for (auto edge = char_edges.begin(); edge != char_edges.end(); ++edge) {

            int a_vertex_parents = vertices_tree.find(edge->vertex_a);
            int b_vertex_parents = vertices_tree.find(edge->vertex_b);

            if (a_vertex_parents != b_vertex_parents) {
                
                if (cheapest_edges[a_vertex_parents].is_default() || (cheapest_edges[a_vertex_parents].weight > edge->weight) )
                    cheapest_edges[a_vertex_parents] = *edge;

                if (cheapest_edges[b_vertex_parents].is_default() || (cheapest_edges[b_vertex_parents].weight > edge->weight) )
                    cheapest_edges[b_vertex_parents] = *edge;
            }
        }

        for (auto edge = cheapest_edges.begin(); edge != cheapest_edges.end(); ++edge) {

            if (!edge->is_default()) {
                int parent_vertex_a = vertices_tree.find(edge->vertex_a), 
                    parent_vertex_b = vertices_tree.find(edge->vertex_b); 

                if (parent_vertex_a != parent_vertex_b) {

                    ostov_cost += edge->weight;
                    vertices_tree.unite(parent_vertex_a, parent_vertex_b);
                    amount_of_vertices -= 1;
                    ostov_tree.push_back(*edge);
                }

            }
        }

        cheapest_edges = std::vector<Edge>(graph.V(), Edge::default_edge());
    }

    return ostov_tree;
}

/// It's realisation very slow, but you can implement Fibonacci Heap
/// Complexity O(n^2) --> it's bad
std::list<Edge> graph_algorithms::prim(Graph graph, const int& start_verticals, const int& max_cost_edge, int& ostov_cost) {

    auto char_edges = initialize_char_edges(graph, max_cost_edge);
    std::list<Edge> ostov_tree;
    std::vector<bool> added_edges(char_edges.size(), true);

    added_edges[start_verticals] = false;
    int a = 0, b = 0;
    ostov_cost = 0;
    bool flag_for_not_exit = true, adding_flag = true;

    while (flag_for_not_exit) {
        adding_flag = true;
        for (size_t i = 0; (i < char_edges.size()) && adding_flag; i++) {
            a = char_edges[i].vertex_a, b = char_edges[i].vertex_b;

            if (added_edges[a] ^ added_edges[b]) {
                ostov_tree.push_back(char_edges[i]);
                ostov_cost += char_edges[i].weight;
                added_edges[a] = added_edges[b] = false;
                char_edges.erase(char_edges.begin() + i);
                adding_flag = false;
            }
        }

        if (adding_flag)
            flag_for_not_exit = !adding_flag;
    }

    return ostov_tree;
}

/// Complexity O(E * log(V)) --> more cool =)
/// E --> edges 
/// V --> vertices
std::list<Edge> graph_algorithms::kruscal(Graph graph, const int& max_cost_edge, int& ostov_cost){

    auto char_edges = initialize_char_edges(graph, max_cost_edge);
    DSU vertices_tree(graph.V());
    std::list<Edge> ostov_tree(0);
    ostov_cost = 0;

    for (int i = 0; i < graph.V(); ++i) {
        vertices_tree.make_set(i);
    }

    for (auto item = char_edges.begin(); item != char_edges.end(); ++item) {

        if ( vertices_tree.find(item->vertex_a) != vertices_tree.find(item->vertex_b)) {
            ostov_tree.push_back(*item);
            vertices_tree.unite(item->vertex_a, item->vertex_b);
            ostov_cost += item->weight;
        }
    }
    return ostov_tree;
}

std::list<int> graph_algorithms::dijkstra(Graph graph, const int& start_vertex, const int& finish_vertex, int& cost_of_way) {

    std::priority_queue<EdgeNeighbor, std::vector<EdgeNeighbor>, std::function<bool(EdgeNeighbor, EdgeNeighbor)>> 
        vertices_queue(cmp_edges_with_neighbors);
    std::vector<int> dist(graph.V(), INT_MAX / 3);
    auto edges_with_neighbors = graph.get_adjacent_edges();

    vertices_queue.push(EdgeNeighbor::initialize_edge(start_vertex, 0));
    dist[start_vertex] = 0;

    while (!vertices_queue.empty()) {

        int first_vertex = vertices_queue.top().vertex;
        vertices_queue.pop();

        for (auto edge = edges_with_neighbors[first_vertex].begin(); 
            edge != edges_with_neighbors[first_vertex].end(); ++edge) {

            int second_vertex = edge->vertex;
            if (dist[second_vertex] > dist[first_vertex] + edge->weight) {

                dist[second_vertex] = dist[first_vertex] + edge->weight;
                vertices_queue.push(EdgeNeighbor::initialize_edge(second_vertex, dist[second_vertex]));             
            }
        }
    }

    int temp_cost_of_way = dist[finish_vertex], tmp_vertex = finish_vertex;
    std::list<int> shortest_way(0);
    while (temp_cost_of_way > 0) {

        for (auto edge = edges_with_neighbors[tmp_vertex].begin();
            edge != edges_with_neighbors[tmp_vertex].end(); ++edge) {

            if (dist[tmp_vertex] == dist[edge->vertex] + edge->weight) {

                shortest_way.push_front(tmp_vertex);
                tmp_vertex = edge->vertex;
                temp_cost_of_way -= edge->weight;

                break;
            }
        }
    }
    shortest_way.push_front(start_vertex);

    cost_of_way = dist[finish_vertex];
    return shortest_way;
}

bool cmp_edges(Edge left_edge, Edge right_edge) {
    return left_edge.weight < right_edge.weight;  
}

bool cmp_edges_with_neighbors(EdgeNeighbor left_edge, EdgeNeighbor right_edge) {
    return left_edge.weight < right_edge.weight;
}

inline std::vector<Edge> initialize_char_edges(Graph graph, const int& cost) {

    std::vector<Edge> char_edges(graph.E());
    auto array_of_edges = graph.get_edges();
    auto last_inserted = std::copy_if(
        array_of_edges.begin(), array_of_edges.end(),
        char_edges.begin(),
        [&](Edge& item) { return (item.weight <= cost) && (item.weight > 0); }
    );
    char_edges.erase(last_inserted, char_edges.end());
    std::sort(char_edges.begin(), char_edges.end(), cmp_edges);
    
    return char_edges;
}