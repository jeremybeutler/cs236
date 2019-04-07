#ifndef GRAPH_H
#define GRAPH_H
#include "Node.h"

#include <string>
#include <sstream>
#include <map>

class Graph
{
private:
    std::map<int, Node> _nodes;
public:
	Graph() {}
    Graph(std::map<int, Node> nodes)
		: _nodes(nodes) {}

	Node node(int nid)
	{
		return _nodes[nid];
	}

	std::map<int, Node> nodes()
	{
		return _nodes;
	}

	void addNode(int nid, Node node)
	{
		_nodes[nid] = node;
	}

	std::string toString()
	{
		std::stringstream out;
		for (std::map<int, Node>::iterator iter = _nodes.begin(); iter != _nodes.end(); ++iter)
		{
			out << "R" << iter->first << ":";
			for (int nid : iter->second.adjacentNodes())
			{
				auto last = std::prev(_nodes.end(), 1);
				out << "R" << nid << ((iter == last) ? "" : ",");
			}
			out << std::endl;
		}
		return out.str();
	}
};

#endif // GRAPH_H
