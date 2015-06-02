#ifndef NEIGH_LIST_H
#define NEIGH_LIST_H
#include "graph_base.h"

class Graph_nl : public Graph_base, public Graph_common { //  Neighbouring list

	std::list<std::tuple<int, int> >* neigh_list;
	Graph_nl() : neigh_list(nullptr)
	{
		fill_graph_rep();
	}
public:
	

	Graph_nl(const Graph_base & base) : Graph_base(base)
	{
		fill_graph_rep();
	}


	Graph_nl& operator= (const Graph_base& base)
	{
		if (&base != this)
		{
			*this = base;
		}
		fill_graph_rep();
		return *this;
	}

	~Graph_nl()
	{
		if (neigh_list != nullptr)
		{
			delete[] neigh_list;
		}
	}


	/************ Algorithms *********************/
	Path Dij_alg();

	Path Bell_alg();

	void Kruskal_alg();

	void Prim_alg();

	/******************************************/

	void fill_graph_rep();

	int find_edge(int v1, int v2);
	
	std::ostream& print(std::ostream& out) const;

	void Ford_Fulkerson_BFS()
	{

	}

	void Ford_Fulkerson_DFS()
	{

	}
};




#endif