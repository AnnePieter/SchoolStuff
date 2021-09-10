// 8puzzle.h

#ifndef _8PUZZLE_H
#define _8PUZZLE_H

#include <array>
#include <vector>
#include <iostream>
#include <functional>
#include <stack>
#include <set>

enum class Move { l, r, u, d };
using State = std::array<std::array<int,3>,3>;

using Vertex = State;
using Path = std::vector<Vertex>;

class Graph
{
public:
    typename std::vector<Vertex>::const_iterator cbegin(Vertex v) const;
    typename std::vector<Vertex>::const_iterator cend() const;
private:
    mutable std::vector<Vertex> adjacents;
};

std::ostream &operator<<(std::ostream &os, const Vertex &state);

Vertex doMove(const Vertex &v, const Move &m);
Path dfs(const Graph &graph, const Vertex &start, std::function<bool(const Vertex &vertex)> goalTest);
Path bfs(const Graph &graph, const Vertex &start, std::function<bool(const Vertex &vertex)> goalTest);

#endif // _8PUZZLE_H

