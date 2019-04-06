#ifndef NODE_H
#define NODE_H

#include <string>
#include <sstream>
#include <set>

class Node
{
private:
    std::string name;
    std::set<int> adjacentNodes;
    bool visit;
    // postorder
public:
    Node(std::string name, std::set<int> adjacentNodes = std::set<int>())
		: name(name), adjacentNodes(adjacentNodes), visit(false) {}

    void addAdjacentNode(int nid)
    {
        adjacentNodes.insert(nid);
    }

	std::string toString()
	{
		std::stringstream out;
        return out.str();
	}
};

#endif // NODE_H
