// peggame.cpp
// Compile with: g++ peggame.cpp -o peggame

#include "peggame.h"

int coord_to_idx(int r, int c)
{
    return (r * r + r) / 2 + c;
}

typename std::vector<Vertex>::const_iterator Graph::cbegin(Vertex v) const
{
    adjacents.clear();

    for (int r=0; r<5; r++) {
        for (int c=0; c<=r; c++) {
            if (c <= r+2 && c <= 4 && r+2 <= 4 && c >= 0 && r+2 >= 0 && v[coord_to_idx(r,c)] && v[coord_to_idx(r+1,c)] && !v[coord_to_idx(r+2,c)]) {
                Move m = std::make_tuple(r,c,r+2,c);
                adjacents.push_back(doMove(v,m));
            }
            if (c+2 <= r+2 && c+2 <= 4 && r+2 <= 4 && c+2 >= 0 && r+2 >= 0 && v[coord_to_idx(r,c)] && v[coord_to_idx(r+1,c+1)] && !v[coord_to_idx(r+2,c+2)]) {
                Move m = std::make_tuple(r,c,r+2,c+2);
                adjacents.push_back(doMove(v,m));
            }
            if (c+2 <= r && c+2 <= 4 && r <= 4 && c+2 >= 0 && r >= 0 && v[coord_to_idx(r,c)] && v[coord_to_idx(r,c+1)] && !v[coord_to_idx(r,c+2)]) {
                Move m = std::make_tuple(r,c,r,c+2);
                adjacents.push_back(doMove(v,m));
            }
            if (c-2 <= r && c-2 <= 4 && r <= 4 && c-2 >= 0 && r >= 0 && v[coord_to_idx(r,c)] && v[coord_to_idx(r,c-1)] && !v[coord_to_idx(r,c-2)]) {
                Move m = std::make_tuple(r,c,r,c-2);
                adjacents.push_back(doMove(v,m));
            }
            if (c <= r-2 && c <= 4 && r-2 <= 4 && c >= 0 && r-2 >= 0 && v[coord_to_idx(r,c)] && v[coord_to_idx(r-1,c)] && !v[coord_to_idx(r-2,c)]) {
                Move m = std::make_tuple(r,c,r-2,c);
                adjacents.push_back(doMove(v,m));
            }
            if (c-2 <= r-2 && c-2 <= 4 && r-2 <= 4 && c-2 >= 0 && r-2 >= 0 && v[coord_to_idx(r,c)] && v[coord_to_idx(r-1,c-1)] && !v[coord_to_idx(r-2,c-2)]) {
                Move m = std::make_tuple(r,c,r-2,c-2);
                adjacents.push_back(doMove(v,m));
            }
        }
    }

   return adjacents.cbegin();
}

typename std::vector<Vertex>::const_iterator Graph::cend() const
{
    return adjacents.cend();
}

Vertex doMove(const Vertex &v, const Move &m)
{
    Vertex n = v;

    n[coord_to_idx(std::get<0>(m),std::get<1>(m))] = false;
    n[coord_to_idx((std::get<0>(m) + std::get<2>(m))/2,(std::get<1>(m) + std::get<3>(m))/2)] = false;
    n[coord_to_idx(std::get<2>(m),std::get<3>(m))] = true;

    return n;
}

std::ostream &operator<<(std::ostream &os, const Vertex &state)
{
    for (int r=0; r<5; r++) {
        os << std::string(4 - r, ' ');
        for (int c=0; c<=r; c++) {
            os << " " << (state[coord_to_idx(r,c)] ? "1": "0");
        }
        os << std::endl;
    }
    return os;
}

Path dfs(const Graph &graph, const Vertex &start, std::function<bool(const Vertex &vertex)> goalTest)
{
    std::stack<Path> queue;
    std::set<Vertex> visited;
    Path path;
    
    queue.push(path);
    while (!queue.empty()) {
        path = queue.top();
        queue.pop();
        
        Vertex last;
        if (path.size() == 0) {
            last = start;
        } else {
            last = path.back();
        }
        if (goalTest(last)) 
            return path; // path is a vector of Vertices
        
        if (visited.find(last) == visited.end()) {
            visited.insert(last);
            for (auto it = graph.cbegin(last); it != graph.cend(); it++) { // extend path with new Vertex
                Path n = path;
                n.push_back(*it);
                queue.push(n);
            }
        }
    }
    return Path();
}

Path bfs(const Graph &graph, const Vertex &start, std::function<bool(const Vertex &vertex)> goalTest)
{
}

int main() 
{
    Graph graph;

    Vertex start = {false, 
                 true, true, 
              true, true, true, 
           true, true, true, true, 
        true, true, true, true, true};

    Path path = bfs(graph, start, [](Vertex v) { return (std::count(v.begin(), v.end(), true) == 1); });

    std::cout << start << std::endl;
    for (auto it = path.cbegin(); it != path.cend(); it++)
    {
        std::cout << *it << std::endl;
    }

    return 0;
}

