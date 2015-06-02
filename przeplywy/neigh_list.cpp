#include "neigh_list.h"
Path Graph_nl::Dij_alg()
{
	Path path(numV, false);
	std::vector<bool> counted(numV, false);
	std::vector<bool> uncounted(numV, true); // if true - present 
	//std::vector<int> cost(numV, constants::infinit);
	//	std::vector<int> previous(numV, constants::no_v);
	std::priority_queue<std::tuple<int, int>, std::vector<std::tuple<int, int>>, Compare_tuples_cost> cost_q; // index, cost
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


		for (auto iter = neigh_list[closest_ind].begin(), stop = neigh_list[closest_ind].end(); iter != stop; ++iter)
		{
			auto index = std::get<0>(*iter);
			auto cost_next = std::get<1>(*iter);
			if (uncounted[index] == true)
			{
				if (path.cost[index] > path.cost[closest_ind] + cost_next  && path.cost[closest_ind] != constants::infinit)
				{
					path.cost[index] = path.cost[closest_ind] + cost_next;
					cost_q.push(std::make_tuple(index, path.cost[index]));
					path.previous[index] = closest_ind;
				}
			}
		}


	}
	
	
	return path;
}


/************************************************************************************/


Path Graph_nl::Bell_alg()
{
	Path path(numV);
	//std::vector<int> cost(numV, constants::infinit);
	//std::vector<int> previous(numV, constants::no_v);
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
			for (auto iter = neigh_list[i].begin(), stop = neigh_list[i].end(); iter != stop; ++iter)
			{
				auto next_ind = std::get<0>(*iter);
				auto edge_w = std::get<1>(*iter);
				if ((path.cost[next_ind] > path.cost[i] + edge_w) && (path.cost[i] != constants::infinit))
				{
					change = true;
					path.cost[next_ind] = path.cost[i] + edge_w;
					path.previous[next_ind] = i;
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
		for (auto iter = neigh_list[i].begin(), stop = neigh_list[i].end(); iter != stop; ++iter)
		{
			auto next_ind = std::get<0>(*iter);
			auto edge_w = std::get<1>(*iter);
			auto path_cost_i = path.cost[i];
			if (path.cost[next_ind] > path_cost_i + edge_w && path_cost_i != constants::infinit)
			{
				path.change_neg_cyc(true);
			}
		}
	}


	return path;
}

/*************************************************************************************/
void Graph_nl::Prim_alg()
{
	if (directed)
	{
		throw Directed("Graf jest skierowany - nie mozna uruchomic algorytmu.\n");
	}
	mst.clear();

	std::priority_queue< std::tuple<int, int, int>, std::vector< std::tuple<int, int, int> >, Compare_tuples > queue;


	std::vector<bool> visited(numV, false);
	int Vnow = Vstart;
	visited[Vnow] = true;
	for (int i = 1; i < numV; ++i)
	{

		for (auto iter = neigh_list[Vnow].begin(), stop = neigh_list[Vnow].end(); iter != stop; ++iter)
		{

			if (visited[std::get<0>(*iter)] == false)
			{
				queue.push(std::make_tuple(Vnow, std::get<0>(*iter), std::get<1>(*iter)));
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
		visited[std::get<0>(shortest)] = true;
		Vnow = std::get<1>(shortest);
	}

}



void Graph_nl::Kruskal_alg()
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
		for (auto iter = neigh_list[i].begin(), stop = neigh_list[i].end(); iter != stop; ++iter)
		{
			queue.push(std::make_tuple(i, std::get<0>(*iter), std::get<1>(*iter)));
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

int Graph_nl::find_edge(int v1, int v2)
{

	for (auto iter = neigh_list[v1].begin(), stop = neigh_list[v1].end(); iter != stop; ++iter)
	{
		if (std::get<0>(*iter) == v2)
		{
			return std::get<1>(*iter);
		}
	}
	return constants::no_edge;
}

std::ostream& Graph_nl::print(std::ostream& out) const
{
	out << "Neighbourhood list:\n";
	for (int i = 0; i < numV; ++i)
	{
		out << i << " : " << std::setw(2);

		for (auto iter = neigh_list[i].begin(), stop = neigh_list[i].end(); iter != stop; ++iter)
		{
			out << std::get<0>(*iter) << " (" << std::get<1>(*iter) << ")  " << std::setw(3);
		}
		out << "\n";
	}
	return out;
}

/**************************************************/

void Graph_nl::fill_graph_rep()
{
	neigh_list = new std::list<std::tuple<int, int> >[numV];
	for (auto iter = edge_list.begin(), stop = edge_list.end(); iter != stop; ++iter)
	{
		neigh_list[std::get<0>(*iter)].push_back(std::make_tuple(std::get<1>(*iter), std::get<2>(*iter)));
		if (!directed)
		{
			neigh_list[std::get<1>(*iter)].push_back(std::make_tuple(std::get<0>(*iter), std::get<2>(*iter)));
		}
	}
}