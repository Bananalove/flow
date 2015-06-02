/*
Alicja Majewska, algorytm Dijkstry oraz Bellmana-Forda, algorytmy potrzebuja dopracowania
*/

#include <iostream>
#include <string>
#include "menu_base.h"
#include <stdlib.h>
#include <crtdbg.h>




int main() {
	menu_base();
/*	menu_bell();
	Graph_base graf(0,10, 0,0, true);
	graf.fill(0.5);
	Graph_am gam1(graf);
	gam1.print(std::cout);*/
	
/*	Graph_base graf2;
		try
	{
		//read_file(nazwa.c_str(), graph
		//read_file("bell.txt", graph);
			read_file("dij.txt", graf2);
		//read_file("path_1.txt", graf);
	}
	catch (std::exception& e)
	{
		std::cerr << e.what();
		exit(1);
	}

	std::cout << "Lista krawedzi:\n";
	std::cout << graf2;
	Graph_am graf_am = graf2;
	graf_am.print(std::cout);
	Graph_nl graf_nl = graf2;
	graf_nl.print(std::cout);*/

//	menu();
	
/*	std::cout << "Wczytanie danych z pliku i zapis posortowanych do pliku \n ";
	Graph_base graph;
	bool directed;
	std::cout << "Czy graf jest skierowany? Tak - wpisz 1, nie - wpisz 0.\n";
	std::cin >> directed;
	graph.change_directed(directed);


	std::cout << "Podaj nazwe pliku odczytu:\n";
	//std::string nazwa;
	//std::cin >> nazwa;
	
	*/

	
	Graph_base graph;
	graph.change_directed(1);
	try
	{
		//read_file(nazwa.c_str(), graph
		//read_file("bell.txt", graph);
		//read_file("dij.txt", graph);
		read_file("flow_1.txt", graph);
	}
	catch (std::exception& e)
	{
		std::cerr << e.what();
		exit(1);
	}

	//std::cout << "Lista krawedzi:\n";
	//std::cout << graph;
	Graph_am gam(graph);
	gam.print(std::cout);

	//gam.Ford_Fulkerson_BFS();
	//std::cout << "Tutaj doszedlem!\n";
	//gam.Ford_Fulkerson_DFS();
	gam.print_flow(gam.Ford_Fulkerson_BFS());
	gam.print_flow(gam.Ford_Fulkerson_DFS());
	//std::cout << "Fulkerson jest dobrze!!!!!!!\n";
	/*
	Graph_nl gnl(graph);
	gnl.print(std::cout);
	Graph_am* pointer = new Graph_am(graph);
	 pointer = (Graph_am*)malloc(sizeof(Graph_am));
	
	 _CrtMemState state2;
	 _CrtMemCheckpoint(&state2);

	 _CrtMemDumpStatistics(&state1);
	std::cout << "Wypisane!\n";
	std::cout << " Dij_alg_matrix \n";
	gam.Dij_alg().print_path();
	std::cout << " Dij_alg_list \n";
	gnl.Dij_alg().print_path();
	auto path1 = gam.Bell_alg();
	path1.print_path();
	if (path1.is_neg()) { std::cout << "Cykl ujemny matrix!\n"; }

	auto path2 = gnl.Bell_alg();
	path2.print_path();
	if (path2.is_neg()) { std::cout << "Cykl ujemny matrix!\n"; }
	*/	

}
