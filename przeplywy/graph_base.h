#ifndef GRAPH_BASE_H
#define GRAPH_BASE_H

#include <list>
#include <tuple>// w tym moze byc wiecej niz 4 elementy, ale jest ok :)
#include <utility>
#include <queue>
#include <iostream>
#include <string>
#include <exception>
#include <memory>
#include <vector>
#include <limits>
#include <iomanip>
#include <algorithm> //min_elem
#include "path.h"


/*
* Funktor do sortowania kolejki krotkow - wyznaczenie najmniejszego z elementow
*/
class Compare_tuples
{
public:
	bool operator() (std::tuple<int, int, int>& tp1, std::tuple<int, int, int>& tp2)
	{
		return std::get<2>(tp1) > std::get<2>(tp2);

	}
};

class Compare_tuples_cost
{
public:
	bool operator() (std::tuple<int, int>& tp1, std::tuple<int, int>& tp2)
	{
		return std::get<1>(tp1) > std::get<1>(tp2);

	}
};

/* klasa wyj¹tkowa  */

class Directed {
	std::string error;
public:
	Directed(std::string err = "Wystapil blad\n") : error(err)
	{	}
	std::string  what() const
	{
		return error;
	}
};


class Graph_base {
protected:
	int numE;
	int numV;
	int Vstart;
	int Vend;
	std::vector < std::tuple<int, int, int> > edge_list;
	//int** adj_matrix;
	//	std::list<std::tuple<int, int> >* neigh_list;
	bool directed; // pole decyduje, czy klasa moze wykonywac algorytm Prima lub Kruskala 
	std::list <std::tuple<int, int, int> >  mst; // minimal spinning tree

public:
	Graph_base(int nE = 0, int nV = 0, int  Vs = 0, int Ve = 0, bool dir = false) : numE(nE), numV(nV), Vstart(Vs), Vend(Ve),
		directed(dir)
	{
		edge_list.reserve(numE);
	}

	virtual ~Graph_base()
	{	}

	/********************************** access to basic values ***************************************/
	void change_set(int nE, int nV, int  Vs, int Ve);

	void Graph_base::change_directed(bool dir);

	int show_numE() const
	{
		return numE;
	}
	int show_numV() const
	{
		return numV;
	}
	int show_Vstart() const
	{
		return Vstart;
	}
	int show_Vend() const
	{
		return Vend;
	}
	void add_edge(int vert1, int vert2, int edge_l); // should add numE or add next variable ?


	int find_egde_edge_list(int v1, int v2)
	{
		if (directed)
		{
			for (auto iter = edge_list.begin(), stop = edge_list.end(); iter != stop; ++iter)
			{
				if (std::get<0>(*iter) == v1 && std::get<1>(*iter) == v2)
				{
					return std::get<2>(*iter);
				}
			}
			return constants::no_edge;
		}
		else 
		{
			for (auto iter = edge_list.begin(), stop = edge_list.end(); iter != stop; ++iter)
			{
				auto ver1 = std::get<0>(*iter);
				auto ver2 = std::get<1>(*iter);

				if ((ver1 == v1 && ver2 == v2) || ver2 == v1 && ver1 == v2)
				{
					return std::get<2>(*iter);
				}
			}
			return constants::no_edge;
		}
	}

	/**************************************** Generowanie grafow ********************************************/

	void fill_full();

	void fill(double level);

	void spanning_tree();

	

	/*************************************** Minimum spanning tree **********************************************************/

	int min_span_tree_weight();

	std::ostream& print_mst(std::ostream& out) const;


	
	friend std::ostream& operator<< (std::ostream& out, Graph_base graph);

};
class Graph_common 
{
public:
	virtual Path Dij_alg() = 0;
	virtual Path Bell_alg() = 0;
	virtual void Prim_alg() = 0;
	virtual void Kruskal_alg() = 0;
	virtual int find_edge(int v1, int v2) = 0;
	virtual void fill_graph_rep() = 0;
	virtual std::ostream& print(std::ostream& out) const = 0;
	virtual void Ford_Fulkerson_BFS()=0;
	virtual void Ford_Fulkerson_DFS() = 0;

};



#endif