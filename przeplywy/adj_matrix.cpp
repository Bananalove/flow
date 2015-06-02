#include "adj_matrix.h"
/*
void Graph_am::Ford_Fulkerson_BFS()
{
	//int cp;   // Zmienne proste algorytmu
	bool finished = false;                       // Do wychodzenia z zagnieżdżonych pętli

	int fmax = 0;
	
		
	Graph_base flow(0, numV, 0, 0, true);
	Graph_am flow_m(flow); // macierz przeplywow
	flow_m.fill_number(0);
	std::vector<int> previous(numV, constants::no_v);

	std::vector<int> CFP(numV, 0);
	int cp = 0; // przechowuje wartość przepustowości rezydualnej
	int Ver1 = constants::no_v;
	int Ver2 = constants::no_v;

	std::queue<int> vertex_queue;
	
	

	

	

	// W pętli szukamy ścieżek rozszerzających dotąd,
	// dopóki istnieją w sieci rezydualnej. Każda znaleziona
	// ścieżka zwiększa przepływ wzdłuż zawartych w niej
	// krawędzi grafu sieci przepływowej

	while (true)
	{

		// Na początku pętli zerujemy tablicę poprzedników P

		for (int i = 0; i < numV; i++)
		{
		previous[i] = constants::no_v;
		}
		// źródło nie posiada poprzednika. Wpisujemy tutaj -2,
		// aby BFS nie wybierało źródła

		previous[Vstart] = constants::absolutely_no_v;

		// Do CFP[Vstart] wpiVstartujemy najwiękVstartzą liczbę całkowitą

		CFP[Vstart] = constants::infinit;

		// Zerujemy kolejkę i umieszczamy w niej źródło s

		while (!vertex_queue.empty())
		{
			vertex_queue.pop();
		}
		vertex_queue.push(Vstart);

		// Zmienna finished umożliwia odpowiednie wychodzenie z
		// dwóch zagnieżdżonych pętli - zamiast polecenie goto.

		finished = false;

		// Rozpoczynamy pętlę wyszukującą ścieżki BFS. Pętla kończy
		// się w przypadku braku dalszych wierzchołków w kolejce

		while (!vertex_queue.empty())
		{

			// Z początku kolejki pobieramy element i usuwamy go z kolejki

			Ver1 = vertex_queue.front(); vertex_queue.pop();

			// Sprawdzamy wszystkich sąsiadów wierzchołka x przeglądając
			// wiersz macierzy adj_matrix

			for (Ver2 = 0; Ver2 < numV; Ver2++)
			{

				// Dla sąsiada y wyznaczamy przepustowość rezydualną
				// krawędzi x->y. Jeśli krawędź nie istnieje w sieci,
				// to otrzymamy w cp wynik zero
				if (adj_matrix[Ver1][Ver2] != constants::no_edge && previous[Ver2] == constants::no_v)
				{
					cp = adj_matrix[Ver1][Ver2] - flow_m.adj_matrix[Ver1][Ver2];

					// W previous[Ver2] zapamiętujemy, iż poprzednikiem y jest Ver1

					previous[Ver2] = Ver1;

					// Dla wierzchołka y obliczamy dotychczasową przepustowość
					// rezydualną ścieżki. Jest to mniejsza wartość z przepustowości
					// ścieżki dla poprzednika Ver1 i bieżącej przepustowości
					// rezydualnej krawędzi Ver1->y.

					CFP[Ver2] = CFP[Ver1] > cp ? cp : CFP[Ver1];

					// Jeśli osiągnęliśmy ujście, to ścieżka jest kompletna

					if (Ver2 == Vend)
					{

						// Zwiększamy przepływ maksymalny o przepustowość rezydualną
						// ścieżki - wykorzystujemy tablicę CFP

						fmax += CFP[Vend];

						// Idziemy wstecz po ścieżce zwiększając przepływy
						// wzdłuż jej krawędzi w kierunku zgodnym ze ścieżką
						// oraz zmniejszając przepływy w kierunku przeciwnym

						int i = Ver2;
						while (i != Vstart)
						{
							Ver1 = previous[i];
							flow_m.adj_matrix[Ver1][i] += CFP[Vend];
							flow_m.adj_matrix[i][Ver1] -= CFP[Vend];
							i = Ver1;
						}

						// Ustawiamy finished na true, co spowoduje wyjście z obu pętli

						finished = true; break;
					}

					// Jeśli wierzchołek y nie jest ujściem t, to dopisujemy
					// go na końcu kolejki vertex_queue i kontynuujemy pętlę BFS

					vertex_queue.push(Ver2);
				}
			}

			// Tutaj wychodzimy z pętli while, jeśli
			// została znaleziona ścieżka rozszerzająca

			if (finished) break;
		}

		// Jeśli nie znaleziono ścieżki rozszerzającej, to finished = false
		// i w tym miejscu nastąpi wyjście z głównej pętli while

		if (!finished) break;
	}

	// Prezentujemy wyniki obliczeń. Najpierw wypisujemy
	// wartość maksymalnego przepływu

	std::cout << std::endl << "fmax = " << fmax <<  std::endl << std::endl;

	// Następnie wypisujemy przepływy netto wzdłuż krawędzi

	for (int x = 0; x < numV; x++)
	{
		for (int y = 0; y < numV; y++)
		{
			if (adj_matrix[x][y] != constants::no_edge)
			{
				std::cout << x << " -> " << y << " " << flow_m.adj_matrix[x][y] << ":" << adj_matrix[x][y] << std::endl;
			}
		}
		std::cout << std::endl;
	}
	
}
*/

void Graph_am::Ford_Fulkerson_BFS() // przechodzenie grafow wszerz 
{
	int fmax = 0;
	Graph_base flow(0, numV, 0, 0, true);
	Graph_am flow_m(flow); // macierz przeplywow
	flow_m.fill_number(0);

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
		std::cout << "JEstem w petli glownej!-----------------------------------\n";
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
			std::cout << "JEstem w petli mnijeszej!************************\n";
			ver1 = vertex_queue.front();
			vertex_queue.pop();
			go_on3 = true;

			for (int i = 0; (i < numV) && go_on3; ++i)
			{
				if ((adj_matrix[ver1][i] != constants::no_edge) && (previous[i] == constants::no_v))
				{
					//std::cout << "ver1 " << ver1 << "\n";
					cp = adj_matrix[ver1][i] - flow_m.adj_matrix[ver1][i];
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
							fmax += CFP[Vend];
							std::cout << "Ide wstecz!\n";
							ver2 = i;
							while (ver2 != Vstart)
							{
								ver1 = previous[ver2];
								flow_m.adj_matrix[ver1][ver2] += CFP[Vend];
								flow_m.adj_matrix[ver2][ver1] -= CFP[Vend];
								ver2 = ver1;
							}
							finished = true;
							//go_on2 = false;
							std::cout << "Finished!\n";
							go_on3 = false;
							go_on2 = false;

						}

					}
				}
      }

      // Tutaj wychodzimy z pętli while, jeśli
      // została znaleziona ścieżka rozszerzająca

		/*	if (finished)
			{
				go_on2 = false;
			}*/
    }

    // Jeśli nie znaleziono ścieżki rozszerzającej, to esc = false
    // i w tym miejscu nastąpi wyjście z głównej pętli while

		if (!finished)
		{
			go_on = false;
		}
  }
	

	std::cout << "Fmax ostatecznie  wynosi " << fmax << "\n";

	// Następnie wypisujemy przepływy netto wzdłuż krawędzi
	for (int i = 0; i < numV; ++i)
	{
		for (int j = 0; j < numV; ++j)
		{
			if (adj_matrix[i][j] != constants::no_v)
			{
				std::cout << i << " -> " << j << "  " << flow_m.adj_matrix[i][j] << " : " << adj_matrix[i][j] << "\n";
			}
		}
	}
	std::cout << std::endl;
}
	


		/*
void Graph_am::Ford_Fulkerson_BFS() // przechodzenie grafow wszerz 
{
	int fmax = 0;
	Graph_base flow(0, numV, 0, 0, true);
	Graph_am flow_m(flow); // macierz przeplywow
	flow_m.fill_number(0);
	std::vector<int> previous(numV, constants::no_v);

	std::vector<int> CFP(numV, 0);
	int cp = 0; // przechowuje wartość przepustowości rezydualnej
	int ver1 = constants::no_v;
	int ver2 = constants::no_v;

	

	std::queue<int> vertex_queue;
	bool finished = false;
	bool go_on = true;
	bool go_on2 = true;

	int ver;
	while (go_on)
	{
		while (!vertex_queue.empty())
		{
			vertex_queue.pop();
		}
		vertex_queue.push(Vstart);

		CFP[Vstart] = constants::infinit;

		for (auto iter = previous.begin(), stop = previous.end(); iter != stop; ++iter)
		{
			*iter = constants::no_v;
		}
		previous[Vstart] = constants::absolutely_no_v;

		finished = false;

		
		while (!vertex_queue.empty() && go_on2 )
		{
			ver = vertex_queue.front();
			vertex_queue.pop();
			// tutaj wykonujemy operacje na wierzcholku v ??
			std::cout << "nowa kolejka *********************\n";
			for (int i = 0;(( i < numV) ); ++i)
			{
				if ((adj_matrix[ver][i] != constants::no_edge)  && (previous[i] == constants::no_v)) 
				{
					
					cp = adj_matrix[ver][i] - flow_m.adj_matrix[ver][i];
					//CFP[y] = CFP[x] > cp ? cp : CFP[x];
					previous[i] = ver;
					CFP[i] =  CFP[ver] > cp ? cp : CFP[ver]; // wybierz minimum
					std::cout << "CFP[i] " << CFP[i] << " CFP[ver] " << CFP[ver] << " cp " << cp << "\n";
					std::cout << ver << " -> " << i << "  " << CFP[i] << " : " << adj_matrix[ver][i] << "\n";
					if (i == Vend)
					{
						for (int j = 0; j < numV; ++j)
						{
							std::cout << CFP[j] << " ";
						}
						std::cout << "\n";
						fmax += CFP[Vend];
						//break;
						std::cout << "Fmax wynosi " << fmax << "\n";
						ver2 = Vend;
						std::cout << "i == Vend\n";
						while (ver2 != Vstart)
						{
							ver1 = previous[ver2];
							flow_m.adj_matrix[ver1][ver2] += CFP[Vend];
							flow_m.adj_matrix[ver2][ver2] -= CFP[Vend];
							ver2 = ver1;
							std::cout << "ide do tylu!\n";
						}

						finished = true;
						std::cout << "koniec vedn\n";
						break;
					}
					else 
					{
						vertex_queue.push(i);
					}
				}
			}
			if (finished)
			{
			//	break;
				go_on2 = false;
			}
		}
		if (!finished)
		{
			//break;
			go_on = false;
		}

		
	}

	std::cout << "Fmax ostatecznie  wynosi " << fmax << "\n";

	// Następnie wypisujemy przepływy netto wzdłuż krawędzi
	for (int i = 0; i < numV; ++i)
	{
		for (int j = 0; j < numV; ++j)
		{
			if (adj_matrix[i][j] != constants::no_v)
			{
				std::cout << i << " -> " << j << "  " << flow_m.adj_matrix[i][j] << " : " << adj_matrix[i][j] << "\n";
			}
		}
	}
		std::cout << std::endl;


	

	


}

*/
	












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