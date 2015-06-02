#include "Graph_base.h"
#include <iomanip>
#define _CRTDBG_MAP_ALLOC 


/* Plik definuje operacje dla wspolnej wersji grafow */

/********************************************** Podstawowe operacje *****************************************************/
void Graph_base::change_set(int nE, int nV, int  Vs, int Ve)
{
	numE = nE;
	numV = nV;
	Vstart = Vs;
	Vend = Ve;
}
void Graph_base::change_directed(bool dir)
{
	directed = dir;
}
/*************************************************************************************************************************/
void Graph_base::add_edge(int vert1, int vert2, int edge_l)
{
	if (numE == static_cast<int>(edge_list.size()))
	{
		++numE;
	}
	auto edge = std::make_tuple(vert1, vert2, edge_l);
	edge_list.push_back(edge);
}




std::ostream& Graph_base::print_mst(std::ostream& out) const
{
	out << "Minimal spanning tree:\n";

	for (auto iter = mst.begin(), stop = mst.end(); iter != stop; ++iter)
	{
		out << std::get<0>(*iter) << "  " << std::get<1>(*iter) << "   " << std::get<2>(*iter) << "\n";
	}


	return out;
}

int Graph_base::min_span_tree_weight()
{
	if (mst.empty())
	{
		return 0;
	}
	int mstw = 0;
	for (auto iter = mst.begin(), stop = mst.end(); iter != stop; ++iter)
	{
		mstw += std::get<2>(*iter);
	}

	return mstw;
}


