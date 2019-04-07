#ifndef NODE_H
#define NODE_H

#include <string>
#include <sstream>
#include <set>

class Node
{
private:
    int _id;
    std::string _name;
    std::set<int> _adjacentNodes;
    bool _visit;
    int _postorder;
public:
    Node() {}
    Node(int id, std::string name, std::set<int> adjacentNodes = std::set<int>())
		: _id(id), _name(name), _adjacentNodes(adjacentNodes), _visit(false), _postorder() {}

    int id()
    {
        return _id;
    }

    std::set<int> adjacentNodes()
    {
        return _adjacentNodes;
    }

    bool visit()
    {
        return _visit;
    }

    void visit(bool visit)
    {
        this->_visit = visit;
    }

    int postorder()
    {
        return _postorder;
    }

    void postorder(int postorder)
    {
        this->_postorder = postorder;
    }

    void addAdjacentNode(int nid)
    {
        _adjacentNodes.insert(nid);
    }

	std::string toString()
	{
		std::stringstream out;
        return out.str();
	}
};

#endif // NODE_H
