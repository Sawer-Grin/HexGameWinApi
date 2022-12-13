#ifndef _DSU_struct_
#define _DSU_struct_

#include <iostream>
#include <vector>
#include <algorithm>

class DSU {
public:
	DSU() : vertices_tree(0), rank(0) {};
	DSU(int amount_of_vertices): vertices_tree(amount_of_vertices), rank(amount_of_vertices) {};
	~DSU() {};
	int find(int virtex);
	void unite(int first_vertex, int second_vertex);
	void make_set(int vertex);

private:
	std::vector<int> vertices_tree;
	std::vector<int> rank;
};

#endif