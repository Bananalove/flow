#ifndef STOPER_FLOW_H
#define STOPER_FLOW_H
#include <ctime>
#include <cstdlib>
#include <numeric>
#include <string>
#include <vector>
#include <cassert>
#include "graph_base.h"
#include "adj_matrix.h"

float time_calc_flow(int size, double level, std::string alg)
{
	const int loops_num = 100;
	// generowanie 
	srand(time(NULL));
	std::vector<float> time_vec(loops_num, 0);
	for (int tm = 0; tm < loops_num; ++tm)
	{

		auto start = std::clock(), end = std::clock();
		Graph_base graph(0, size, 0, rand() % size, true);
		assert(level > 0);
		graph.fill(level);
		Graph_am gam(graph);

		
		if (alg == "BFS")
		{
			start = std::clock();
			gam.Ford_Fulkerson_BFS();
			end = std::clock();
		}
		if (alg == "DFS")
		{
			start = std::clock();
			gam.Ford_Fulkerson_DFS();
			end = std::clock();
		}
		time_vec[tm] = (((float)(end - start)) / CLOCKS_PER_SEC);

	}

	float init(0);
	return std::accumulate(time_vec.begin(), time_vec.end(), init) * 1000 / loops_num;

}










#endif