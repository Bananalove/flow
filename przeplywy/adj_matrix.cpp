#include "adj_matrix.h"

Flow Graph_am::Ford_Fulkerson_BFS() // przechodzenie grafow wszerz 
{
	Graph_base flow(0, numV, 0, 0, true);
	Flow flow_m(numV, 0);

	std::vector<int> CFP(numV, 0);
	int cp = 0; // przechowuje wartość przepustowości rezydualnej

	bool go_on = true;
	bool go_on2 = true;
	bool go_on3 = true;

	std::vector<int> previous(numV, constants::no_v);

	int ver1 = constants::no_v;
	int ver2 = constants::no_v;

	std::queue<int> vertex_queue;
	bool finished = false;

	vertex_queue.push(Vstart);
	previous[Vstart] = constants::absolutely_no_v;

	while (go_on)
	{
		finished = false;
		while (!vertex_queue.empty() )
		{
			vertex_queue.pop();
		}
		vertex_queue.push(Vstart);

		CFP[Vstart] = constants::infinit;

		/* zerowanie poprzednikow */
		for (auto iter = previous.begin(), stop = previous.end(); iter != stop; ++iter)
		{
			*iter = constants::no_v;
		}
		previous[Vstart] = constants::absolutely_no_v;

		go_on2 = true;

		while (!vertex_queue.empty() && go_on2)
		{
			ver1 = vertex_queue.front();
			vertex_queue.pop();
			go_on3 = true;

			for (int i = 0; (i < numV) && go_on3; ++i)
			{
				if ((adj_matrix[ver1][i] != constants::no_edge) && (previous[i] == constants::no_v))
				{
					cp = adj_matrix[ver1][i] - flow_m.flow_m[ver1][i];
					if (cp)
					{

						previous[i] = ver1;
						if (CFP[ver1] < cp)
						{
							CFP[i] = CFP[ver1];
						}
						else
						{
							CFP[i] = cp;
						}
						if (i != Vend)
						{
							vertex_queue.push(i);

						}
						else
						{
							ver2 = i;
							flow_m.fmax += CFP[Vend];
							while (ver2 != Vstart)
							{
								
								ver1 = previous[ver2];
								flow_m.flow_m[ver1][ver2] += CFP[Vend];
								flow_m.flow_m[ver2][ver1] -= CFP[Vend];
								ver2 = ver1;
							}
							finished = true;
							go_on3 = false;
							go_on2 = false;

						}

					}
				}
      }

    
    }

   
		if (!finished)
		{
			go_on = false;
		}
  }
	



	return flow_m;
}
	Flow Graph_am::Ford_Fulkerson_DFS() // przechodzenie grafow wszerz 
{
	Graph_base flow(0, numV, 0, 0, true);
	Flow flow_m(numV, 0);

	std::vector<int> CFP(numV, 0);
	int cp = 0; // przechowuje wartość przepustowości rezydualnej

	bool go_on = true;
	bool go_on2 = true;
	bool go_on3 = true;

	std::vector<int> previous(numV, constants::no_v);

	int ver1 = constants::no_v;
	int ver2 = constants::no_v;

	std::stack<int> vertex_stack;
	bool finished = false;

	vertex_stack.push(Vstart);
	previous[Vstart] = constants::absolutely_no_v;

	while (go_on)
	{
		finished = false;
		while (!vertex_stack.empty())
		{
			vertex_stack.pop();
		}
		vertex_stack.push(Vstart);

		CFP[Vstart] = constants::infinit;

		/* zerowanie poprzednikow */
		for (auto iter = previous.begin(), stop = previous.end(); iter != stop; ++iter)
		{
			*iter = constants::no_v;
		}
		previous[Vstart] = constants::absolutely_no_v;

		go_on2 = true;

		while (!vertex_stack.empty() && go_on2)
		{
			ver1 = vertex_stack.top();
			vertex_stack.pop();
			go_on3 = true;

			for (int i = 0; (i < numV) && go_on3; ++i)
			{
				if ((adj_matrix[ver1][i] != constants::no_edge) && (previous[i] == constants::no_v))
				{
					cp = adj_matrix[ver1][i] - flow_m.flow_m[ver1][i];
					if (cp)
					{

						previous[i] = ver1;
						if (CFP[ver1] < cp)
						{
							CFP[i] = CFP[ver1];
						}
						else
						{
							CFP[i] = cp;
						}
						if (i != Vend)
						{
							vertex_stack.push(i);

						}
						else
						{
							ver2 = i;
							flow_m.fmax += CFP[Vend];
							while (ver2 != Vstart)
							{
								ver1 = previous[ver2];
								flow_m.flow_m[ver1][ver2] += CFP[Vend];
								flow_m.flow_m[ver2][ver1] -= CFP[Vend];
								ver2 = ver1;
							}
							finished = true;
							go_on3 = false;
							go_on2 = false;

						}

					}// if(cp)
				} // if (element exist and no previus)
			} // for (adj_marix)


		} // while (stack not empty)


		if (!finished)
		{
			go_on = false;
		}
	} // while ( there are still changes)


	return flow_m;
	
}


	












Path Graph_am::Dij_alg()

{
	std::vector<bool> counted(numV, false);
	std::vector<bool> uncounted(numV, true); // if true - present 
	Path path(numV, false);
	//std::vector<int> path(numV, constants::infinit);
	//std::vector<int> previous(numV, constants::no_v);
	std::priority_queue<std::tuple<int, int>, std::vector<std::tuple<int, int>>, Compare_tuples_cost> cost_q; // index, path
	path.cost[Vstart] = 0;
	cost_q.push(std::make_tuple(Vstart, path.cost[Vstart]));


	for (int k = 0; k < numV; ++k)
	{
		auto closest = cost_q.top();
		cost_q.pop();
		auto closest_ind = std::get<0>(closest);
		auto closest_cost = std::get<1>(closest);
		counted[closest_ind] = true;
		uncounted[closest_ind] = false;

		for (int i = 0; i < numV; ++i)
		{
			if (adj_matrix[closest_ind][i] != constants::no_edge)
			{
				if (uncounted[i] == true) // if present in uncounted
				{
					if (path.cost[i] > path.cost[closest_ind] + adj_matrix[closest_ind][i] && path.cost[closest_ind] != constants::infinit)
					{
						path.cost[i] = path.cost[closest_ind] + adj_matrix[closest_ind][i];
						cost_q.push(std::make_tuple(i, path.cost[i]));
						path.previous[i] = closest_ind;
					}
				}
			}
		}
	}

	
	return path;
}




Path Graph_am::Bell_alg()
{
	Path path(numV);
	path.cost[Vstart] = 0;
	bool change = true;
	std::vector<bool> visited(numV, false);
	visited[Vstart] = true;
	for (int bell = 1; bell < numV; ++bell) // dla n-1 wierzcholkow, 0 juz zalatwione
	{
		change = false;
		// dla kazdego wierzcholka i wykonuj 
		for (int i = 0; i < numV; ++i)
		{
			for (int j = 0; j < numV; ++j)
			{
				if (adj_matrix[i][j] != constants::no_edge)
				{
					if (path.cost[j] > path.cost[i] + adj_matrix[i][j] && path.cost[i] != constants::infinit) 
					{
						change = true;
						path.cost[j] = path.cost[i] + adj_matrix[i][j];
						path.previous[j] = i;
					}
				}
			}
		}
		if (!change)
		{
			break;
		}
	}
	

	// sprawdzanie ujemnej petli
	for (int i = 0; i < numV; ++i)
	{

		for (int j = 0; j < numV && change; ++j)
		{
			if (adj_matrix[i][j] != constants::no_edge)
			{
				if ((path.cost[j] > path.cost[i] + adj_matrix[i][j]) && (path.cost[i] =! constants::infinit))
				{
					path.change_neg_cyc(true);
				}
			}
		}
	}

	return path;
}

/************************************* Algorytm Prima ********************************************************************/





void Graph_am::Prim_alg()
{

	if (directed)
	{
		throw Directed("Graf jest skierowany - nie mozna uruchomic algorytmu.\n");
	}
	mst.clear();
	std::priority_queue< std::tuple<int, int, int>, std::vector< std::tuple<int, int, int> >, Compare_tuples > queue;


	std::vector<bool> visited(numV, false);
	int Vnow = 0;
	visited[Vnow] = true;

	for (int i = 1; i < numV; ++i)
	{

		for (int u = 0; u < numV; ++u) // dla wszystkich sasiadow danego wierzcholka
		{
			if (adj_matrix[Vnow][u] != constants::no_edge)
			{
				if (visited[u] == false)
				{
					queue.push(std::make_tuple(Vnow, u, adj_matrix[Vnow][u]));
				}
			}
		}
		auto shortest = queue.top();
		queue.pop();
		while (visited[std::get<1>(shortest)] == true && !queue.empty())
		{
			shortest = queue.top();
			queue.pop();
		}
		mst.push_back(shortest);
		visited[std::get<1>(shortest)] = true;

		//	std::cout << "Krawedz :" << std::get<0>(shortest) << " " << std::get<1>(shortest) << " " << std::get<2>(shortest) << " \n";

		visited[std::get<0>(shortest)] = true;
		Vnow = std::get<1>(shortest);
	}

}

/**************************************** Algorytm Kruskala **************************************************************/



void Graph_am::Kruskal_alg()
{

	if (directed)
	{
		throw Directed("Graf jest skierowany - nie mozna uruchomic algorytmu.\n");
	}
	mst.clear();
	// wektor bazy zbiorow rozlacznch
	std::vector<int> zbior(numV);
	// kolejka krawedzi
	std::priority_queue< std::tuple<int, int, int>, std::vector< std::tuple<int, int, int> >, Compare_tuples > queue;
	for (int i = 0; i < numV; ++i) /* umieszczenie krawedzi w kolejce */
	{
		zbior[i] = i;
		for (int u = 0; u < numV; ++u)
		{
			if (adj_matrix[i][u] != constants::no_edge)
			{
				queue.push(std::make_tuple(i, u, adj_matrix[i][u]));

			}
		}
	}



	for (int i = 1; i < numV; ++i) // przegladanie kolejnych wierzcholkow
	{
		auto edge = queue.top();
		queue.pop();
		while (zbior[std::get<0>(edge)] == zbior[std::get<1>(edge)] && !queue.empty()) // czy zbiory sa rozlaczne?
		{
			edge = queue.top();
			queue.pop();
		}
		mst.push_back(edge);
		int zmien = zbior[std::get<0>(edge)];  // numer podzbioru, ktory bedzie zmieniany
		for (int i = 0; i < numV; ++i) // laczenie zbiorow rozlacznych
		{
			if (zbior[i] == zmien)
			{
				zbior[i] = zbior[std::get<1>(edge)];
			}
		}
	}
}


void Graph_am::fill_graph_rep()
{
	adj_matrix = new int*[numV];
	for (int i = 0; i < numV; ++i)
	{
		adj_matrix[i] = new int[numV];
	}
	for (int i = 0; i < numV; ++i)
	{
		for (int j = 0; j < numV; ++j)
		{
			adj_matrix[i][j] = constants::no_edge;
		}
	}
	for (auto iter = edge_list.begin(), stop = edge_list.end(); iter != stop; ++iter)
	{
		adj_matrix[std::get<0>(*iter)][std::get<1>(*iter)] = std::get<2>(*iter);
		if (!directed)
		{
			adj_matrix[std::get<1>(*iter)][std::get<0>(*iter)] = std::get<2>(*iter);
		}
	}
}


/********************************************************************************/
std::ostream& Graph_am::print(std::ostream& out) const
{
	out << "Adjacency matrix \n";
	out << ' ' << std::setw(8);
	for (int i = 0; i < numV; ++i)
	{
		out << i << std::setw(8);
	}
	out << "\n";
	for (int i = 0; i < numV; ++i)
	{
		out << i << std::setw(8);
		for (int j = 0; j < numV; ++j)
		{

			if (adj_matrix[i][j] != constants::no_edge)
			{
				out << adj_matrix[i][j];
				out << std::setw(8);
			}
			else
			{
				out << constants::no_elem;
				out << std::setw(8);
			}

		}
		out << "\n";
	}
	return out;
}




void Graph_am :: print_flow(const Flow& flow) const
{

	std::cout << "Fmax   wynosi " << flow.fmax << "\n";
	std::cout << std::endl;
	for (int i = 0; i < numV; ++i)
	{
		for (int j = 0; j < numV; ++j)
		{
			if (adj_matrix[i][j] != constants::no_v)
			{
				std::cout << i << " -> " << j << "  " << adj_matrix[i][j] << " / " << flow.flow_m[i][j] << "\n";
			}
		}
	}


}
void Graph_am::print_flow(const Flow& flow, std::ostream& out) const
{

	out << "Fmax   wynosi " << flow.fmax << "\n";
	out << std::endl;
	for (int i = 0; i < numV; ++i)
	{
		for (int j = 0; j < numV; ++j)
		{
			if (adj_matrix[i][j] != constants::no_v)
			{
				out << i << " -> " << j << "  " << adj_matrix[i][j] << " / " << flow.flow_m[i][j] << "\n";
			}
		}
	}



}