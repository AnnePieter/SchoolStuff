// 8puzzle.cpp
// Compile with: g++ 8puzzle.cpp -o 8puzzle

#include "8puzzle.h"

typename std::vector<Vertex>::const_iterator Graph::cbegin(Vertex v) const
{
    adjacents.clear();

    for (int r=0; r<3; r++) {
        for (int c=0; c<3; c++) {
            if (v[r][c] == 0) {
                if (c<2) adjacents.push_back(doMove(v,Move::l)); 
                if (c>0) adjacents.push_back(doMove(v,Move::r));
                if (r<2) adjacents.push_back(doMove(v,Move::u));
                if (r>0) adjacents.push_back(doMove(v,Move::d));
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
    bool done=false;
    Vertex n = v;

    for (int r=0; r<3 && !done; r++) {
        for (int c=0; c<3 && !done; c++) {
            if (v[r][c] == 0) {
                switch(m) {
                    case Move::l: std::swap(n[r][c], n[r][c+1]); done = true; break;
                    case Move::r: std::swap(n[r][c], n[r][c-1]); done = true; break;
                    case Move::u: std::swap(n[r+1][c], n[r][c]); done = true; break;
                    case Move::d: std::swap(n[r-1][c], n[r][c]); done = true; break;
                }
            }
        }
    }
    return n;
}

std::ostream &operator<<(std::ostream &os, const Vertex &state)
{
    for (int r=0; r<3; r++) {
        for (int c=0; c<3; c++) {
            if (state[r][c] != 0) {
		os << state[r][c];
            } else {
                os << " ";
            }
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
	// Here goes the solution to exercise #2
}

int main() 
{
    Graph graph;

    Vertex start = {{
        {{1,2,3}},
        {{7,0,4}},
        {{8,6,5}}
    }};

    Vertex goal = {{
        {{1,2,3}},
        {{4,5,6}},
        {{7,8,0}}
    }};

    Path path = bfs(graph, start, [&](Vertex v) { return (v == goal); });

    std::cout << start << std::endl;
    for (auto it = path.cbegin(); it != path.cend(); it++)
    {
        std::cout << *it << std::endl;
    }

    return 0;
}

