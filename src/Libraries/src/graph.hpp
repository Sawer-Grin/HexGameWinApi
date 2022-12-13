#if !defined(_graph)
#define _graph

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <iterator>
#include <ctime>
#include <vector>
#include <algorithm>
#include <string>
#include <list>
#include <string>
#include <math.h>
#include <set>

#include "edge.hpp"
#include "./special_structures/edge_neighbor.hpp"

class Graph {
public:
	Graph() : matrix(0), edges(0) {}
	Graph(const int& vertices);
	Graph(const Graph& graph);
	Graph& operator= (const Graph& graph);
	friend std::ostream& operator<<(std::ostream& os, const Graph& graph);
	~Graph();
	int E() const { return edges.size(); }														// Method for getting the number of edges in a graph
	int V() const { return matrix.size(); }														// Method for getting the number of vertices in a graph
	bool adjacent(const int& x, const int& y, const int& value);                                // Method for getting information about an edge between vertices
	std::vector<std::list<EdgeNeighbor>> get_adjacent_edges();									// Method for getting list of verticals with all adges connected with this vertex
	std::list<int> get_neighbors(const int& x, const int& value) const;							// Method for getting a list of get_neighbors
	int get_vertex_degree(const int& x) const;
	int get_node_value(const int& x) const;														// Method for obtaining information about the number of edges at a edge
	int get_edge_value(const int& x, const int& y) const { return matrix[x][y]; }				// Method for getting edge value
	void set_edge_value(const int& x, const int& y, const int& value);							// Method for setting the desired edge value
	bool is_connected_with(const int& u, const int& v, const int& value) const;
	std::vector<std::vector<int>> get_matrix() { return this->matrix; }
	std::vector<Edge> get_edges() { return this->edges; }

protected:
	std::vector<std::vector<int>> matrix;                                                 		// 	Submission of graph as matrix
	std::vector<Edge> edges;																	//	Submission of graph as vector(array) of edges
};

#endif