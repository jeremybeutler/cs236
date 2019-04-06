#ifndef GRAPH_H
#define GRAPH_H
#include "node.h"

#include <string>
#include <sstream>
#include <map>

class Graph
{
private:
    std::map<int, Node> nodes;
public:
    Graph() {}
    Graph(std::map<int, Node> nodes)
		: nodes(nodes) {}

	std::string toString()
	{
		std::stringstream out;
		return out.str();
	}
};

#endif // GRAPH_H
