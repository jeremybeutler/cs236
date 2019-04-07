#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <string>
#include <sstream>
#include <set>
#include <algorithm>
#include <sstream>
#include "Database.h"
#include "../parser/DatalogProgram.h"
#include "../graph/Graph.h"
#include "../graph/Node.h"

class Interpreter
{
private:
    DatalogProgram p;
    Database _db;
    
public:
    Interpreter() {}
    Interpreter(DatalogProgram& p)
			: p(p) 
    {
        createDatabase();
    }

    void createDatabase()
    {
        std::vector<Predicate> schemes = p.schemes();
        std::vector<Predicate> facts = p.facts();

        // loop through each scheme Predicate
        for (unsigned int i = 0; i < schemes.size(); ++i)
        {
            Relation r;
            std::string name = schemes.at(i).id();
            Scheme s;
            std::set<Tuple> tuples;
            // loop through each Parameter in the vector of Parameters in the scheme Predicate 
            for (unsigned int j = 0; j < schemes.at(i).listStr().size(); ++j)
                s.push_back(schemes.at(i).listStr().at(j));

            // loop through each fact Predicate
            for (unsigned int j = 0; j < facts.size(); ++j)
                if (facts.at(j).id() == name)
                {
                    Tuple t;
                    // loop through each Parameter in the vector of Parameters in the fact Predicate 
                    for (unsigned int k = 0; k < facts.at(j).listStr().size(); ++k)
                    {                            
                        t.push_back(facts.at(j).listStr().at(k));
                    }
                    tuples.insert(t);
                }

            r = Relation(name, s, tuples);
            _db[name] = r;
        }
    }

    Database db()
    {
        return _db;
    }

    // Database methods

    Relation selectA(Relation& r, std::string val, int pos)
    {
        std::set<Tuple> tuples_old = r.tuples();
        Relation relation_new = Relation(r.name(), r.scheme(), std::set<Tuple>());        
        for (Tuple tuple : tuples_old) 
            if (tuple.at(pos) == val) 
                relation_new.addTuple(tuple);

        return relation_new;
    }

    Relation selectB(Relation& r, int pos_1, int pos_2)
    {
        std::set<Tuple> tuples_old = r.tuples();
        Relation relation_new = Relation(r.name(), r.scheme(), std::set<Tuple>());
        for (Tuple tuple : tuples_old)
            if (tuple.at(pos_1) == tuple.at(pos_2)) 
                relation_new.addTuple(tuple);
                
        return relation_new;
    }

    Relation project(Relation& r, std::vector<int> indexes, std::vector<int> order = {})
    {
        Scheme scheme_old = r.scheme();
        std::set<Tuple> tuples_old = r.tuples();
        Scheme scheme_new;
        for (unsigned int i = 0; i < indexes.size(); ++i)
            scheme_new.push_back(scheme_old.at(indexes.at(i)));
        
        // if (!(order.empty())) reorder(scheme_new, order);
        Relation relation_new = Relation(r.name(), scheme_new, std::set<Tuple>());
        for (Tuple tuple : tuples_old) 
        {
            Tuple tuple_new;
            for (unsigned int i = 0; i < indexes.size(); ++i)
                tuple_new.push_back(tuple.at(indexes.at(i)));

            relation_new.addTuple(tuple_new);
        }
        return relation_new;
    }

    Relation rename(Relation& r, Scheme scheme_new)
    {
        Relation relation_new = Relation(r.name(), scheme_new, r.tuples());
        return relation_new;
    }

    Relation join(Relation r1, Relation r2)
    {
        std::vector<int> duplicateIndexes;
        Scheme scheme_new = combineSchemes(r1.scheme(), r2.scheme(), duplicateIndexes);
        Relation relation_new = Relation(r1.name(), scheme_new, std::set<Tuple>());
        if (r1.tuples().empty()) 
        {
            relation_new.setTuples(r2.tuples());
            return relation_new;
        }
        for (Tuple t1 : r1.tuples())
            for (Tuple t2 : r2.tuples())
            {
                if (isJoinable(t1, t2, r1.scheme(), r2.scheme()))
                {
                    relation_new.addTuple(combineTuples(t1, t2, duplicateIndexes));
                }
            }

        return relation_new;
    }

    void unite(Relation& r1, std::ostream& out)
    {
        Relation r2 = _db[r1.name()];
        for (Tuple t : r1.tuples())
        {
            if (!(r2.tuples().count(t)))
            {
                r2.addTuple(t);
                out << "  ";
                for (unsigned int i = 0; i < r2.scheme().size(); ++i)
                {
                    out << r2.scheme().at(i) << "=" << t.at(i);
                    out << ((i == r2.scheme().size() - 1) ? "" : ", ");
                }
                out << std::endl;
            }
        }
        _db[r1.name()] = r2;
    }

    // Graph methods

    void buildDependencyGraphs(const std::vector<Rule>& rules, Graph& dependency_graph, Graph& reverse_dependency_graph)
    {
        // for each rule
        for (unsigned int i = 0; i < rules.size(); ++i)
        {
            // add create node and add to dependency graph and reverse dependency graphs
            Node n = Node(i, rules.at(i).predicateHead().id());
            dependency_graph.addNode(n.id(), n);
            reverse_dependency_graph.addNode(n.id(), n);
        }

        // for each rule (r1)
        for (unsigned int i = 0; i < rules.size(); ++i)
            // for each body predicate (p) in r1 
            for (unsigned int j = 0; j < rules.at(i).predicateList().size(); ++j)
                // for each rule (r2)
                for (unsigned int k = 0; k < rules.size(); ++k)
                    // if p.name == r2.head.name, 
                    // add edge from r1 to r2 (dependency graph) and from r2 to r1 (reverse dependency graph)
                    if (rules.at(i).predicateList().at(j).id() == rules.at(j).predicateHead().id())
                    {
                        dependency_graph.node(i).addAdjacentNode(k);
                        reverse_dependency_graph.node(k).addAdjacentNode(i);
                    }
    }

    // DFS methods for generating SCC's from dependancy graph

    void dfs(Node n, Graph& g, std::vector<int>& scc)
    {
        n.visit(true);
        scc.push_back(n.id());
        for (int nid : n.adjacentNodes())
            if (!(g.node(nid).visit()))
                dfs(g.node(nid), g, scc);
    }

    std::vector<std::vector<int>> dfsForest(Graph& g, std::vector<int> order)
    {
        std::vector<std::vector<int>> scc_vect;
        // clear the visit mark for each node in the graph
        for (std::map<int, Node>::iterator iter = g.nodes().begin(); iter != g.nodes().end(); ++iter)
            iter->second.visit(false);

        // run dfs in order
        for (unsigned int i = 0; i < order.size(); ++i)
        {
            std::vector<int> scc;
            dfs(g.node(i), g, scc);
            scc_vect.push_back(scc);
        }
        return scc_vect;
    }

    // DFS methods for generating reverse postorder list from reverse dependancy graph

    void dfs(Node n, Graph& g, int& postorder_counter, std::vector<int> reverse_postorder_vect)
    {
        n.visit(true);
        for (int nid : n.adjacentNodes())
            if (!(g.node(nid).visit()))
                dfs(g.node(nid), g, postorder_counter, reverse_postorder_vect);

        n.postorder(postorder_counter);
        reverse_postorder_vect.push_back(n.id());
        ++postorder_counter;
    }

    std::vector<int> dfsForest(Graph& g)
    {
        int postorder_counter = 1;
        std::vector<int> reverse_postorder_vect;

        // clear the visit mark for each node in the graph
        for (std::map<int, Node>::iterator iter = g.nodes().begin(); iter != g.nodes().end(); ++iter)
            iter->second.visit(false);

        // run dfs on each unmarked node in the graph
        for (std::map<int, Node>::iterator iter = g.nodes().begin(); iter != g.nodes().end(); ++iter)
            if (!(iter->second.visit()))
                dfs(iter->second, g, postorder_counter, reverse_postorder_vect);

        std::reverse(reverse_postorder_vect.begin(), reverse_postorder_vect.end());
        return reverse_postorder_vect;
    }

    // Helper methods
    
    template<class T>
    void reorder(std::vector<T>& in, const std::vector<int>& order)  
    {    
        std::vector<T> copy = in;
        for(unsigned int i = 0; i < order.size(); ++i)  
            in[i] = copy[ order[i] ];  
    }

    bool isJoinable(Tuple t1, Tuple t2, Scheme s1, Scheme s2)
    {
        for (unsigned int i = 0; i < t1.size(); ++i)
        {
            for (unsigned int j = 0; j < t2.size(); ++j)
            {
                if (s1.at(i) == s2.at(j) && t1.at(i) != t2.at(j))
                    return false;
            }
        }
        return true;

    }

    Tuple combineTuples(Tuple t1, Tuple t2, std::vector<int> duplicateIndexes)
    {
        Tuple tuple_new;
        for (unsigned int i = 0; i < t1.size(); ++i)
            tuple_new.push_back(t1.at(i));
        
        for (unsigned int i = 0; i < t2.size(); ++i)
            if (!(std::find(duplicateIndexes.begin(), duplicateIndexes.end(), i) != duplicateIndexes.end()))
                tuple_new.push_back(t2.at(i));
        
        return tuple_new;
    }

    Scheme combineSchemes(Scheme s1, Scheme s2, std::vector<int>& duplicateIndexes)
    {
        Scheme scheme_new;
        for (unsigned int i = 0; i < s1.size(); ++i)
            scheme_new.push_back(s1.at(i));

        for (unsigned int i = 0; i < s2.size(); ++i)
            if (!(count(scheme_new.begin(), scheme_new.end(), s2.at(i)))) 
                scheme_new.push_back(s2.at(i));
            else
                duplicateIndexes.push_back(i);

        return scheme_new;
    }

    int countTuples()
    {
        int count = 0;
        for (const auto& pair : _db) {
            Relation r = pair.second;
            for (Tuple t : r.tuples())
                ++count;
        }
        return count;
    }
    
    // Datalog Language methods

    Relation query(Predicate p)
    {
        std::string name = p.id();
        Relation r = _db[name];
        std::vector<Parameter> param_list = p.list();
        std::vector<std::string> query_vars;
        Scheme scheme_new;
        std::vector<int> indexes;
        for (unsigned int i = 0; i < param_list.size(); ++i)
        {
            std::string param_val = param_list.at(i).value();
            if (param_list.at(i).isConstant())
                r = selectA(r, param_val, i);
            else if (count(query_vars.begin(), query_vars.end(), param_val))
            {
                auto it = std::find(query_vars.begin(), query_vars.end(), param_val);
                r = selectB(r, std::distance(query_vars.begin(), it), i);
            }
            else
            {
                query_vars.push_back(param_val);
                scheme_new.push_back(param_val);
                indexes.push_back(i);
            }
        }
        r = project(r, indexes);
        r = rename(r, scheme_new);
        return r;
    }

    std::string evaluateQueries()
    {
        std::stringstream out;
        out << "Query Evaluation" << std::endl;
        std::vector<Predicate> queries = p.queries();
        for (unsigned int i = 0; i < queries.size(); ++i)
        {
            out << queries.at(i).toString() << "? " << query(queries.at(i)).toString();
        }
        return out.str();
    }

    std::string evaluateRule(Rule r)
    {
        std::stringstream out;
        Relation r_new = Relation(r.predicateHead().id(), Scheme(), std::set<Tuple>());
        Relation r_temp;
        std::vector<std::string> param_list_str = r.predicateHead().listStr();
        std::vector<int> indexes;
        int count = 0;

        for (unsigned int i = 0; i < r.predicateList().size(); ++i)
        {
            r_temp = query(r.predicateList().at(i));
            r_new = join(r_new, r_temp);
        }

        std::vector<std::string> r_new_vect = r_new.scheme();
        if (!(r_new_vect.empty()))
            for (unsigned int i = 0; i < param_list_str.size(); ++i)
            {
                auto it = std::find(r_new_vect.begin(), r_new_vect.end(), param_list_str.at(i));
                indexes.push_back(std::distance(r_new_vect.begin(), it));
                ++count;
            }

        r_new = project(r_new, indexes);
        unite(r_new, out);
        return out.str();
    }

    std::string evaluateRules()
    {
        std::stringstream out;
        std::vector<Rule> rules = p.rules();
        int pre_count, post_count;
        int loop_count = 0;
        Graph dependency_graph, reverse_dependency_graph;

        buildDependencyGraphs(rules, dependency_graph, reverse_dependency_graph);
        out << "Dependency Graph" << std::endl << dependency_graph.toString() << std::endl;
        std::vector<int> order = dfsForest(reverse_dependency_graph);
        std::vector<std::vector<int>> scc_vect = dfsForest(dependency_graph, order);

        out << "Rule Evaluation" << std::endl;

        do 
        {
            loop_count++;
            pre_count = countTuples();
            for (unsigned int i = 0; i < rules.size(); ++i)
            {
                out << rules.at(i).toString() << std::endl;
                out << evaluateRule(rules.at(i));
            }
            post_count = countTuples();
        }
        while (pre_count != post_count);
        
        out << std::endl << "Schemes populated after " << loop_count << " passes through the Rules." << std::endl;
        return out.str();
    }

};

#endif // INTERPRETER_H
