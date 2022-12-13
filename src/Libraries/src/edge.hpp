#ifndef edge_struct
#define edge_struct

struct Edge {
    int vertex_a;
    int vertex_b;
    int weight;

    static Edge default_edge() {
        return Edge {
            .vertex_a = 0,
            .vertex_b = 0,
            .weight = 0,
        };
    }
    
    static Edge initialize_edge(int vert_a, int vert_b, int weight){
        return Edge {
            .vertex_a = vert_a,
            .vertex_b = vert_b,
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
        return (weight == 0) && (vertex_a == 0) && (vertex_b == 0);  
    }

    bool operator==(const Edge& edge) {
        return (vertex_a == edge.vertex_a) && (vertex_b == edge.vertex_b) && (weight == edge.weight);
    }

};

#endif