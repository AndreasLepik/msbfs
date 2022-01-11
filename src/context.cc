#include "context.h"
#include "graph.h"

using namespace std;

Context::Context(string path, BFS *algorithm) : path(path), bfs(algorithm){};

void Context::run(vector<int> sources)
{
  Graph graph{5};
  graph.loadGraphFromFile("../data_sets/test/out.test");

  bfs->run(graph, sources);
}

void Context::setData(string path)
{
  this->path = path;
}

void Context::setAlgorithm(BFS *algorithm)
{
  this->bfs = algorithm;
}
