#include "graph_base.h"
#include <ctime>
#include <cstdlib>
#include <numeric>
#define _CRTDBG_MAP_ALLOC 
/* 
* File defines funtions to generating graphs
*
*/
void Graph_base::fill_full()
{
	edge_list.reserve(numV*(numV - 1) / 2);
	srand(time(NULL));
	if (!directed)
	{
		for (int i = 0; i < numV; ++i)
		{
			for (int j = 0; j < numV; ++j)
			{
				if (i != j)
				{
					add_edge(i, j, rand());
				}
			}
		}
	}
	else
	{
		for (int i = 0; i < numV; ++i)
		{
			for (int j = 0; j < numV; ++j)
			{
				
				add_edge(i, j, rand());
				
			}
		}
	}
}
void  Graph_base::fill(double level)
{
	int maxE = numV*(numV - 1) / 2;
	if (directed)
	{
		maxE = numV*(numV - 1);
	}
	spanning_tree(); // adds n-1 edges
	srand(time(NULL));
	
	
		if (level == 1.0)
		{
			fill_full();
		}
		else
		{
			int E_to_add = static_cast<int> (level * maxE);
			edge_list.reserve(E_to_add);
			for (int i = numV - 1; i < E_to_add; ++i)
			{
				int v1 = rand() % numV;
				int v2 = rand() % numV;
				while (v1 == v2)
				{
					v2 = rand() % numV;
				}
				while (find_egde_edge_list(v1, v2) != constants::no_edge || v1 == v2)
				{
					v1 = rand() % numV;
					v2 = rand() % numV;
				}
				add_edge(v1, v2, rand());
			}
		}
	

}


void Graph_base::spanning_tree()
{
	srand(time(NULL));
	//std::vector<bool> included(numV, false);
	std::vector<int> connected(1,0);
	std::vector<int> unconnected;
	for (int i = 1; i < numV; ++i)
	{
		unconnected.push_back(i);
	}
	// creating spanning tree
	int v1 = 0; // connected
	
	
	for (int i = 1; i < numV; ++i)
	{

	
		int ind_v2 = rand() % unconnected.size();
		int v2 = unconnected[ind_v2]; // losowanie z niepolaczonych wierzcholkow
		connected.push_back(unconnected.at(ind_v2));
		std::swap(unconnected.back(), unconnected.at(ind_v2));
		unconnected.pop_back();

		add_edge(v1, v2, rand());
		//std::cout << "V1  " << v1 << " v2 " << v2 << "\n";
		v1  = connected[rand() % connected.size()]; // losowanie z polaczonych wierzcholkow
	
	}


}






