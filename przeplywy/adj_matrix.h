#ifndef ADJ_MATRIX_H
#define ADJ_MATRIX_H
#include "graph_base.h"

class Graph_am : public Graph_base, public Graph_common{  //  Adjacency matrix

	int** adj_matrix;
	Graph_am() : adj_matrix(nullptr)
	{
		fill_graph_rep();
	}
public:
	
	//MyInt(const Number<int> &x) : Number<int>(x) {}
	Graph_am (const Graph_base & base) : Graph_base(base) 	
	{	
		fill_graph_rep();
	}
	
	Graph_am* operator= ( Graph_common* base)
	{
		
		*this = base;
		
		fill_graph_rep();
		return this;
	}

	Graph_am& operator= (const Graph_base& base)
	{
		if (&base != this)
		{
			*this = base;
		}
		fill_graph_rep();
		return *this;
	}
	Graph_am(const Graph_am& gram) = delete;
	Graph_am& operator=(const Graph_am& gram) = delete;


/*	Graph_am& (const Graph_am & base)
	{
		*this = base;
		fill_graph_rep();
		return *this;

	}*/

	~Graph_am()
	{
		if (adj_matrix != nullptr)
		{
			for (int i = 0; i < numV; ++i)
			{
				delete[]adj_matrix[i];
			}
			delete[] adj_matrix;
		}
	}

	
	/************ Algorithms *********************/
	Path Dij_alg();

	Path Bell_alg();

	void Kruskal_alg();

	void Prim_alg();
	/*************************************************/

	void fill_graph_rep();

	
	int find_edge(int v1, int v2)
	{
		return adj_matrix[v1][v2];
	}

	std::ostream& print(std::ostream& out) const;

	Flow Ford_Fulkerson_BFS();
	Flow Ford_Fulkerson_DFS();
	
	void print_flow(const Flow& flow) const;
	
	void print_flow(const Flow& flow, std::ostream& out) const;
	
};


#endif