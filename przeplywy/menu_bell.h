#ifndef MENU_BELL_H
#define MENU_BELL_H

#include <vector>
#include <iostream>
#include <iomanip>
#include <iomanip>
#include "stoper_bell.h"
#include "pliki.h"
#include "adj_matrix.h"
#include "neigh_list.h"


void menu_bell(){
	std::cout << "Program korzystajacy z reprezentacji grafow jako macierz wag lub listy sasiadow, obliczajacy minimalne "
		"drzewo rozpinajace algorytmem Kruskala lub Prima.\n"
		"Opcje mozliwe do wyboru:\n "
		"1. standardowe testy \n "
		"2. wczytanie danych z pliku i zapis roznych reprezentacji do pliku \n "
		"3. wygenerowanie losowego grafu i wyznacznie minimalnego drzewa rozpinajacego, zapis do pliku.\n "
		"4. zakoncz.\n";
	" wybierz numer opcji :\n ";
	char opcja;
	std::cin >> opcja;
	switch (opcja)
	{
	case '1':
	{
		std::cout << "Standardowe testy \n ";
		std::cout << "Podaj algorytm wyznaczania najkrotszej drogi : wpisz Dijkstra lub Bellman-Ford. \n";
		std::string algor;
		std::cin >> algor;
		while (algor != "Dijkstra" && algor != "Bellman-Ford")
		{
			std::cout << "Podaj algorytm wyznaczania najkrotszej drogi : wpisz Dijkstra lub Bellman-Ford. \n";
			std::cin >> algor;
		}
		std::cout << "Podaj sposob reprezentacji : wpisz matrix lub list. \n";
		std::string rep;
		std::cin >> rep;
		while (rep != "matrix" && rep != "list")
		{
			std::cout << "Podaj sposob reprezentacji : wpisz matrix lub list. \n";
			std::cin >> rep;
		}
		std::cout << "Podaj rozmiar grafu. \n";
		int rozmiar;
		std::cin >> rozmiar;
		while (rozmiar <= 0)
		{
			std::cout << "Podaj rozmiar grafu. \n";
			std::cin >> rozmiar;
		}

		std::cout << "Czas testowania " << rozmiar << " metoda " << algor << " 25% " << std::fixed << std::setprecision(5) << time_calc_bell(rozmiar, 0.25, algor, rep) << " milisekund \n";
		std::cout << "Czas testowania " << rozmiar << " metoda " << algor << " 50% " << std::fixed << std::setprecision(5) << time_calc_bell(rozmiar, 0.50, algor, rep) << " milisekund \n";
		std::cout << "Czas testowania " << rozmiar << " metoda " << algor << " 75% " << std::fixed << std::setprecision(5) << time_calc_bell(rozmiar, 0.75, algor, rep) << " milisekund \n";
	//	std::cout << "Czas testowania " << rozmiar << " metoda " << algor << " 100% " << std::fixed << std::setprecision(4) << time_calc_bell(rozmiar, 1.0, algor, rep) << " milisekund \n";
		std::cout << std::endl;


		menu_bell();
		break;
	}
	case '2':
	{
		std::cout << "Wczytanie danych z pliku i zapis posortowanych do pliku \n ";
		Graph_base graph;
		bool directed;
		std::cout << "Czy graf jest skierowany? Tak - wpisz 1, nie - wpisz 0.\n";
		std::cin >> directed;
		graph.change_directed(directed);


		std::cout << "Podaj nazwe pliku odczytu:\n";
		std::string nazwa;
		std::cin >> nazwa;
		try
		{
			read_file(nazwa.c_str(), graph);
		}
		catch (std::exception& e)
		{
			std::cerr << e.what();
			exit(1);
		}
		std::cout << "Lista krawedzi:\n";
		std::cout << graph;
		Graph_am graph_am(graph);
		graph_am.print(std::cout);

		Graph_nl graph_nl(graph);
		graph_nl.print(std::cout);

		try
		{
			
			std::cout << "Najkrotsza droga - Bellman-Ford lista - to : \n";
			graph_nl.Bell_alg().print_path();
			graph_am.Prim_alg();
			std::cout << "Najkrotsza droga - Bellman-Ford matrix - to : \n";
			graph_am.Bell_alg().print_path();
			std::cout << "Najkrotsza droga - Dijkstra matrix - to : \n";
			graph_am.Dij_alg().print_path();
			
			std::cout << "Najkrotsza droga - Dijkstra lista - to : \n";
			graph_nl.Dij_alg().print_path();
		}
		catch (Directed dir)
		{
			std::cout << dir.what();
		}
		//  write_mst
		std::cout << "Podaj nazwe pliku do zapisu mst:\n";
		std::string nazwa_path;
		std::cin >> nazwa_path;
		try
		{
			write_path(nazwa_path.c_str(), graph_nl.Dij_alg());
		}
		catch (std::exception& e)
		{
			std::cerr << e.what();
		}

		std::cout << "Podaj nazwe pliku do zapisu macierzy:\n";
		std::string nazwa_m;
		std::cin >> nazwa_m;
		try
		{
			write_graph(nazwa_m.c_str(), graph_am);
		}
		catch (std::exception& e)
		{
			std::cerr << e.what();
		}
		std::cout << "Podaj nazwe pliku do zapisu listy sasiadow:\n";
		std::string nazwa_n;
		std::cin >> nazwa_n;
		try
		{
			write_graph(nazwa_n.c_str(), graph_nl);
		}
		catch (std::exception& e)
		{
			std::cerr << e.what();
		}


		menu_bell();
		break;
	}
		/*******************************************************************************************************************/
	case '3':
	{
		std::cout << "3. wygenerowanie losowego grafu i wyznacznie najkrotszej drogi, zapis do pliku.\n ";

		std::cout << "Podaj algorytm wyznaczania najkrotszej drogi : wpisz Dijkstra lub Bellman-Ford. \n";
		std::string algor;
		std::cin >> algor;
		while (algor != "Dijkstra" && algor != "Bellman-Ford")
		{
			std::cout << "Podaj algorytm wyznaczania najkrotszej drogi : wpisz Dijkstra lub Bellman-Ford. \n";
			std::cin >> algor;
		}
		std::cout << "Podaj sposob reprezentacji : wpisz matrix lub list. \n";
		std::string rep;
		std::cin >> rep;
		while (rep != "matrix" && rep != "list")
		{
			std::cout << "Podaj sposob reprezentacji : wpisz matrix lub list. \n";
			std::cin >> rep;
		}
		std::cout << "Podaj rozmiar grafu. \n";
		int rozmiar;
		std::cin >> rozmiar;
		while (rozmiar <= 0)
		{
			std::cout << "Podaj rozmiar grafu. \n";
			std::cin >> rozmiar;
		}
			
		

		Graph_base graph(0, rozmiar);
		graph.fill(0.5);
		std::shared_ptr<Graph_common> p_graph = nullptr;
		if (rep == "matrix")
		{
			p_graph.reset(new Graph_am(graph));
		}
		if (rep == "list")
		{
			p_graph.reset(new Graph_nl(graph));
		}

		if (algor == "Dijkstra")
		{
			std::cout << "Najkrotsza droga to wynosi : \n";
			p_graph->Dij_alg().print_path();
		}
		if (algor == "Bellman-Ford")
		{
			std::cout << "Najkrotsza droga to wynosi : \n";
			p_graph->Bell_alg().print_path();
		}


		std::cout << "Podaj nazwe pliku do zapisu :\n";
		std::string nazwa_n;
		std::cin >> nazwa_n;
		try
		{
			write_path(nazwa_n.c_str(), p_graph->Bell_alg());
		}
		catch (std::exception& e)
		{
			std::cerr << e.what();
		}



		menu_bell();
		break;
	}
	case '4':
	{
		return;
		break;
	}
	default:
	{
		std::cout << "Wybrano niepoprawna opcje, sprobuj ponownie.\n";
		menu_bell();
		break;
	}
	}



}

#endif