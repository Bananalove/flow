#ifndef STOPER_H
#define STOPER_H
#include <ctime>
#include <cstdlib>
#include <numeric>
#include <string>
#include <vector>
#include <cassert>
#include "graph_base.h"
#include "adj_matrix.h"
#include "neigh_list.h"

float time_calc(int size, double level, std::string alg, std::string rep)
{
	const int loops_num = 100;
	// generowanie 
	srand(time(NULL));
	std::vector<float> time_vec(loops_num, 0);
	for (int tm = 0; tm < loops_num; ++tm)
	{
		
		auto start = std::clock(), end = std::clock();
		Graph_base graph(0, size);
		std::shared_ptr<Graph_common> p_graph = nullptr;
		//Graph_common* p_graph = nullptr;
		assert(level > 0);
		graph.fill(level);
		if (rep == "matrix")
		{
			p_graph.reset(new Graph_am(graph));
		}
		if (rep == "list")
		{
			p_graph.reset(new Graph_nl(graph));
		}

			if (alg == "Kruskal")
			{
				start = std::clock();
			    p_graph->Kruskal_alg();
				end = std::clock();
			}
			if (alg == "Prim")
			{
				start = std::clock();
				p_graph->Prim_alg();
				end = std::clock();
			}
		time_vec[tm] = (((float)(end - start)) / CLOCKS_PER_SEC);

	}

	float init(0);
	return std::accumulate(time_vec.begin(), time_vec.end(), init) * 10;
	
}










#endif