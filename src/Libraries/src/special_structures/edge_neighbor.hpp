#ifndef edge_neighbor_struct
#define edge_neighbor_struct

struct EdgeNeighbor {
    int vertex;
    int weight;

    static EdgeNeighbor default_edge() {
        return EdgeNeighbor {
            .vertex = 0,
            .weight = 0,
        };
    }

    static EdgeNeighbor initialize_edge(int vertex, int weight){
        return EdgeNeighbor {
            .vertex = vertex,
            .weight = weight,
        };
    }

    void set_weight(int new_weight) {
        this->weight = new_weight;
    }

    bool compare_by_price(Edge& edge){
        return this->weight > edge.weight;
    }

    bool is_default() {
        return (weight == 0) && (vertex == 0);  
    }

    bool operator==(const EdgeNeighbor& edge) {
        return (vertex == edge.vertex) && (weight == edge.weight);
    }
};

#endif