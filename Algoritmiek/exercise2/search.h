// search.h

#ifndef SEARCH_H
#define SEARCH_H

#include <array>
#include <vector>
#include <iostream>
#include <functional>
#include <stack>
#include <set>
#include <map>
#include <queue>

using Vertex = char;
using Path = std::vector<Vertex>;

class Graph
{
public:
    typename std::vector<Vertex>::const_iterator cbegin(Vertex v) const;
    typename std::vector<Vertex>::const_iterator cend() const;
private:
    mutable Vertex currentVertex;
    typedef std::map<Vertex,std::vector<Vertex>> GraphMap;
    static GraphMap adjacents;
};

Path dfs(const Graph &graph, const Vertex &start, std::function<bool(const Vertex &vertex)> goalTest);
Path bfs(const Graph &graph, const Vertex &start, std::function<bool(const Vertex &vertex)> goalTest);

#endif // SEARCH_H
