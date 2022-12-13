#include <iostream>
#include <vector>
#include <gtest/gtest.h>


#include "./../src/graph.hpp"
#include "./../src/edge.hpp"
#include "./../src/graph_math.hpp"
#include "./../src/special_structures/edge_neighbor.hpp"

Graph generate_graph_for_test() {
  Graph graph(6);
  graph.set_edge_value(0, 1, 1);
  graph.set_edge_value(1, 4, 1);
  graph.set_edge_value(0, 2, 2);
  graph.set_edge_value(2, 3, 1);
  graph.set_edge_value(3, 4, 3);

  return graph;
}

Graph generate_first_graph_for_testing_math() {
  Graph graph(7);
  graph.set_edge_value(0, 1, 28);
  graph.set_edge_value(1, 2, 16);
  graph.set_edge_value(2, 3, 12);
  graph.set_edge_value(3, 6, 18);
  graph.set_edge_value(3, 4, 22);
  graph.set_edge_value(1, 6, 14);
  graph.set_edge_value(4, 6, 24);
  graph.set_edge_value(4, 5, 25);
  graph.set_edge_value(0, 5, 10);

  return graph;
}

Graph generate_second_graph_for_testing_math() {
  Graph graph(7);
  graph.set_edge_value(2, 0, 1);
  graph.set_edge_value(2, 5, 5);
  graph.set_edge_value(0, 5, 4);
  graph.set_edge_value(0, 1, 7);
  graph.set_edge_value(0, 3, 8);
  graph.set_edge_value(5, 3, 6);
  graph.set_edge_value(5, 6, 2);
  graph.set_edge_value(1, 3, 11);
  graph.set_edge_value(3, 6, 9);
  graph.set_edge_value(1, 6, 3);
  graph.set_edge_value(1, 4, 10);
  graph.set_edge_value(4, 6, 12);

  return graph;
}

Graph generate_graph_for_testing_short_path() {
  Graph graph(9);
  graph.set_edge_value(0, 1, 4);
  graph.set_edge_value(0, 7, 8);
  graph.set_edge_value(1, 2, 8);
  graph.set_edge_value(1, 7, 11);
  graph.set_edge_value(2, 3, 7);
  graph.set_edge_value(2, 8, 2);
  graph.set_edge_value(2, 5, 4);
  graph.set_edge_value(3, 4, 9);
  graph.set_edge_value(3, 5, 14);
  graph.set_edge_value(4, 5, 10);
  graph.set_edge_value(5, 6, 2);
  graph.set_edge_value(6, 7, 1);
  graph.set_edge_value(6, 8, 6);
  graph.set_edge_value(7, 8, 7);

  return graph;
}

TEST(GraphTests, CheckConnectionsBetweenVerticals) {
  auto graph = generate_graph_for_test();

  EXPECT_EQ(true, graph.is_connected_with(1, 4, 1));
  EXPECT_EQ(true, graph.is_connected_with(4, 0, 2));
  EXPECT_EQ(true, graph.is_connected_with(1, 3, 4));
  EXPECT_EQ(true, graph.is_connected_with(1, 0, 1));
  EXPECT_EQ(true, graph.is_connected_with(0, 2, 2));
  EXPECT_EQ(true, graph.is_connected_with(2, 3, 1));

  ASSERT_NE(true, graph.is_connected_with(1, 3, 0));
  ASSERT_NE(true, graph.is_connected_with(0, 5, 10));
}

TEST(GraphTests, ChechEdgeValue) {
  auto graph = generate_graph_for_test();

  EXPECT_EQ(1, graph.get_edge_value(0, 1));
  EXPECT_EQ(1, graph.get_edge_value(1, 4));
  EXPECT_EQ(3, graph.get_edge_value(4, 3));
  EXPECT_EQ(1, graph.get_edge_value(3, 2));
  EXPECT_EQ(2, graph.get_edge_value(2, 0));
  EXPECT_EQ(0, graph.get_edge_value(0, 5));
}

TEST(GraphTests, CheckEdjacentEdges) {

  auto graph = generate_graph_for_test();
  auto edges = graph.get_edges();
  auto edges_with_neighbors = graph.get_adjacent_edges();

  for (auto edge = edges.begin(); edge != edges.end(); ++edge){

    auto result_of_search = std::find(
      edges_with_neighbors[edge->vertex_b].begin(), 
      edges_with_neighbors[edge->vertex_b].end(), 
      EdgeNeighbor::initialize_edge(edge->vertex_a, edge->weight)
    );
    ASSERT_TRUE(result_of_search != edges_with_neighbors[edge->vertex_b].end());

    result_of_search = std::find(
      edges_with_neighbors[edge->vertex_a].begin(),
      edges_with_neighbors[edge->vertex_a].end(),
      EdgeNeighbor::initialize_edge(edge->vertex_b, edge->weight)
    );
    ASSERT_TRUE(result_of_search != edges_with_neighbors[edge->vertex_a].end());
  }
}

TEST(GraphMath, BoruvkaAlgorithm) {
  auto first_graph = generate_first_graph_for_testing_math(),
    second_graph = generate_second_graph_for_testing_math();
  int ostov_cost_for_first_graph = 0, ostov_cost_for_second_graph = 0;
  auto solution_for_first_graph = graph_algorithms::boruvka(first_graph, 0, 28, ostov_cost_for_first_graph),
    solution_for_second_graph = graph_algorithms::boruvka(second_graph, 0, 28, ostov_cost_for_second_graph);

  int expected_ostov_cost_for_first_graph = 99, expected_ostov_cost_for_second_graph = 26;
  
  ASSERT_EQ(ostov_cost_for_first_graph, expected_ostov_cost_for_first_graph);
  ASSERT_EQ(expected_ostov_cost_for_second_graph, ostov_cost_for_second_graph);
}

TEST(GraphMath, PrimAlgorithm) {
  auto first_graph = generate_first_graph_for_testing_math(),
    second_graph = generate_second_graph_for_testing_math();
  int ostov_cost_for_first_graph = 0, ostov_cost_for_second_graph = 0;
  
  auto solution_for_first_graph = graph_algorithms::prim(first_graph, 0, 28, ostov_cost_for_first_graph),
    solution_for_second_graph = graph_algorithms::prim(second_graph, 0, 28, ostov_cost_for_second_graph);
  
  int expected_ostov_cost_for_first_graph = 99, expected_ostov_cost_for_second_graph = 26;
  ASSERT_EQ(expected_ostov_cost_for_first_graph, ostov_cost_for_first_graph);
  ASSERT_EQ(expected_ostov_cost_for_second_graph, ostov_cost_for_second_graph); 
}

TEST(GraphMath, KruscalAlgorithm) {
  auto first_graph = generate_first_graph_for_testing_math(),
    second_graph = generate_second_graph_for_testing_math();
  int ostov_cost_for_first_graph = 0, ostov_cost_for_second_graph = 0;

  auto solution_for_first_graph = graph_algorithms::kruscal(first_graph, 28, ostov_cost_for_first_graph),
    solution_for_second_graph = graph_algorithms::kruscal(second_graph, 28, ostov_cost_for_second_graph);

  int expected_ostov_cost_for_first_graph = 99, expected_ostov_cost_for_second_graph = 26;
  ASSERT_EQ(expected_ostov_cost_for_first_graph, ostov_cost_for_first_graph);
  ASSERT_EQ(expected_ostov_cost_for_second_graph, ostov_cost_for_second_graph);
}

TEST(GraphMath, DijkstraAlgorithm) {
  auto graph = generate_graph_for_testing_short_path();
  int cost_of_way = 0;
  auto solution = graph_algorithms::dijkstra(graph, 0, 4, cost_of_way);
  
  std::list<int> expected_output;
  expected_output.push_back(0);
  expected_output.push_back(7);
  expected_output.push_back(6);
  expected_output.push_back(5);
  expected_output.push_back(4);
  
  ASSERT_EQ(solution, expected_output);
  ASSERT_EQ(cost_of_way, 21);
}