#ifndef MENU_H
#define MENU_H

#include <vector>
#include <iostream>
#include <iomanip>
#include <iomanip>
#include "stoper.h"
#include "pliki.h"
#include "adj_matrix.h"
#include "neigh_list.h"

void menu(){
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
		std::cout << "Podaj algorytm wyznaczania MST : wpisz Prim lub Kruskal. \n";
		std::string algor;
		std::cin >> algor;
		while (algor != "Prim" && algor != "Kruskal")
		{
			std::cout << "Podaj repytm wyznaczania MST : wpisz Prim lub Kruskal. \n";
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

		std::cout << "Czas testowania " << rozmiar << " metoda " << algor << " 25% " << std::fixed<< std::setprecision(5) <<  time_calc(rozmiar, 0.25, algor, rep )  << " milisekund \n";
		std::cout << "Czas testowania " << rozmiar << " metoda " << algor << " 50% " << std::fixed<< std::setprecision(5) <<  time_calc(rozmiar, 0.50, algor, rep)  << " milisekund \n";
		std::cout << "Czas testowania " << rozmiar << " metoda " << algor << " 75% " << std::fixed<< std::setprecision(5) << time_calc(rozmiar, 0.75, algor, rep)  << " milisekund \n";
		std::cout << "Czas testowania " << rozmiar << " metoda " << algor << " 100% " << std::fixed << std::setprecision(4) << time_calc(rozmiar, 1.0, algor, rep)  << " milisekund \n";
		std::cout << std::endl;

		menu();
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
			graph_nl.Prim_alg();
			std::cout << "Najkrotsza droga - Prim lista - to : " << graph.min_span_tree_weight() << "\n";
			graph.print_mst(std::cout);
			graph_am.Prim_alg();
			std::cout << "Najkrotsza droga - Prim matrix - to : " << graph.min_span_tree_weight() << "\n";
					graph.print_mst(std::cout);
			graph_am.Kruskal_alg();
			std::cout << "Najkrotsza droga - Kruskal matrix - to : " << graph.min_span_tree_weight() << "\n";
					graph.print_mst(std::cout);
			graph_nl.Kruskal_alg();
			std::cout << "Najkrotsza droga - Kruskal lista - to : " << graph.min_span_tree_weight() << "\n";
					graph.print_mst(std::cout);
		}
		catch (Directed dir)
		{
			std::cout << dir.what();
		}
		//  write_mst
		std::cout << "Podaj nazwe pliku do zapisu mst:\n";
		std::string nazwa_mst;
		std::cin >> nazwa_mst;
		try
		{
			write_mst(nazwa_mst.c_str(), graph);
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


		menu();
		break;
	}
		/*******************************************************************************************************************/
	case '3':
	{
		std::cout << "3. wygenerowanie losowego grafu i wyznacznie minimalnego drzewa rozpinajacego, jego zapis do pliku.\n ";
			
		std::cout << "Podaj algorytm wyznaczania MST : wpisz Prim lub Kruskal. \n";
		std::string alg;
		std::cin >> alg;
		while (alg != "Prim" && alg != "Kruskal")
		{
			std::cout << "Podaj repytm wyznaczania MST : wpisz Prim lub Kruskal. \n";
			std::cin >> alg;
		}
		std::cout << "Podaj sposob reprezentacji : wpisz matrix lub list. \n";
		std::string rep;
		std::cin >> rep;
		while (rep != "Prim" && rep != "Kruskal")
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
			p_graph.reset( new Graph_am(graph));
		}
		if (rep == "list")
		{
			p_graph.reset(new Graph_nl(graph));
		}
			
			if (alg == "Kruskal")
			{
				p_graph->Kruskal_alg();
				std::cout << "MST wynosi: " <<  graph.min_span_tree_weight() << "\n";
			}
			if (alg == "Prim")
			{
				p_graph->Prim_alg();
				std::cout << "MST wynosi: " <<  graph.min_span_tree_weight() << "\n";
			}
		
		
		std::cout << "Podaj nazwe pliku do zapisu mst:\n";
		std::string nazwa_n;
		std::cin >> nazwa_n;
		try
		{
			write_graph(nazwa_n.c_str(), *p_graph);
		}
		catch (std::exception& e)
		{
			std::cerr << e.what();
		}


		
		menu();
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
		menu();
		break;
	}
	}



}

#endif