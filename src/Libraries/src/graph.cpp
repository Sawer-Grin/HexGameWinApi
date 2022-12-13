#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <list>
#include <bits/stdc++.h>

#include "graph.hpp"

Graph::Graph(const int& vertices) {
	this->edges = std::vector<Edge>(0);
	matrix.reserve(vertices);
	matrix.resize(vertices);
	for (int i = 0; i < vertices; ++i) {
		matrix[i].reserve(vertices);
		matrix[i].resize(vertices);
		for (int j = 0; j < vertices; ++j) {
			matrix[i][j] = 0;
		}
	}
}

Graph::Graph(const Graph& graph) {
	this->edges = std::vector<Edge>(graph.edges);
	matrix.resize(graph.V());
	int vertices = graph.V();
	for (int i = 0; i < vertices; ++i) {
		matrix[i].resize(vertices);
		for (int j = 0; j < vertices; ++j) {
			matrix[i][j] = graph.matrix[i][j];
		}
	}
}

Graph& Graph::operator=(const Graph& graph) {
	int vertices = graph.V();
	
	this->matrix.resize(vertices);
	for (int i = 0; i < vertices; ++i) {
		this->matrix[i] = std::vector<int>(graph.matrix[i]);
	}
	this->edges = std::vector<Edge>(graph.edges);
	
	return *this;
}

std::ostream& operator<<(std::ostream& os, const Graph& graph) {
    for (int i = 0; i < graph.matrix.size(); ++i){
    	os << "|";
    	for (int j = 0; j < graph.matrix[i].size(); ++j) {
    		os << graph.matrix[i][j] << "|";
    	}
    	os << "\n";
    }
    return os;
}

Graph::~Graph() {
	if (this->matrix.size() > 0) {
		for (int i = 0; i < this->V(); ++i)
			this->matrix[i].clear();
		this->matrix.clear();
	}

	if (this->edges.size() > 0) {
		this->edges.clear();
	}
}

// Method for setting the desired edge value
void Graph::set_edge_value(const int& first, const int& second, const int& value) {
	bool empty = matrix[first][second] == 0;
	matrix[first][second] = matrix[second][first] = value;
	if ((value != 0) && (empty))
		edges.push_back({ first, second, value });
}

bool Graph::adjacent(const int& x, const int& y, const int& value) {
	if (matrix[x][y] == matrix[y][x]) {
		if (matrix[x][y] == value)
			return true;
		else
			return false;
	}
	return false;
}

std::vector<std::list<EdgeNeighbor>> Graph::get_adjacent_edges() {
	std::vector<std::list<EdgeNeighbor>> output(this->V());

	for (auto edge = edges.begin(); edge != edges.end(); ++edge) {
		output[edge->vertex_a].push_back(
			EdgeNeighbor::initialize_edge(edge->vertex_b, edge->weight)
		);
		output[edge->vertex_b].push_back(
			EdgeNeighbor::initialize_edge(edge->vertex_a, edge->weight)
		);
	}
	
	return output;
}

int Graph::get_node_value(const int& x) const {
	int p = 0;
	for (int i = 0; i < this->V(); ++i) {
		if (matrix[x][i] > 0) {
			++p;
		}
	}
	return p;
}

// Algorithm for searching in the graph of neighbors with the considered vertex
/// Needs to refactor
std::list<int> Graph::get_neighbors(const int& x, const int& value) const {
	std::list<int> output;
	for (int i = 0; i < this->V(); ++i) {
		if ((matrix[x][i] > 0) && (matrix[x][i] <= value) && (x != i)) {
			output.push_front(i);
		}
	}
	return output;
}

int Graph::get_vertex_degree(const int& x) const {
	int p = 0;
	for (int i = 0; i < this->V(); ++i) {
		if (matrix[x][i] > 0) {
			++p;
		}
	}
	return p;
}

/// depth-first search algorithm
/// needs to refactor 
bool Graph::is_connected_with(const int& u, const int& v, const int& value) const {
	std::vector<bool> connect(this->V(), false);
	std::vector<int> stack;
	std::list<int> list_of_get_neighbords;
	int f_ver = 0, s_ver = 0;
	
	stack.push_back(u);
	connect[u] = true;
	while (stack.size() > 0) {

		f_ver = stack.back(); 
		stack.pop_back();
		list_of_get_neighbords = this->get_neighbors(f_ver, value);

		while (!list_of_get_neighbords.empty()) {
			s_ver = list_of_get_neighbords.front();
			list_of_get_neighbords.pop_front();
			if (!connect[s_ver]) {
				stack.push_back(s_ver);
				connect[s_ver] = true;
			}
		}
	}
	return connect[v];
}