#ifndef MENU_FLOW_H
#define MENU_FLOW_H
#include "stoper_flow.h"
#include <iomanip>
#include "pliki.h"
void menu_flow()
{
	std::cout << "Program korzystajacy z reprezentacji grafow, obliczajacy maksymalny przeplyw algorytmem Forda-Fulkersona dla "
		"przeszukiwania grafu w glab lub wszerz."
	
		"Opcje mozliwe do wyboru:\n "
		"1. standardowe testy \n "
		"2. wczytanie danych z pliku i zapis grafu przeplywu do pliku \n "
		"3. zakoncz.\n";
	" wybierz numer opcji :\n ";
	char opcja;
	std::cin >> opcja;
	switch (opcja)
	{
	case '1':
	{
		std::cout << "Standardowe testy \n ";
		std::cout << "Podaj algorytm przeszukiwania grafu : wpisz BFS lub DFS. \n";
		std::string algor;
		std::cin >> algor;
		while (algor != "BFS" && algor != "DFS")
		{
			std::cout << "Podaj algorytm przeszukiwania grafu : wpisz BFS lub DFS. \n";
			std::cin >> algor;
		}
		
		std::cout << "Podaj rozmiar grafu. \n";
		int rozmiar;
		std::cin >> rozmiar;
		while (rozmiar <= 0)
		{
			std::cout << "Podaj rozmiar grafu. \n";
			std::cin >> rozmiar;
		}

		std::cout << "Czas testowania " << rozmiar << " metoda " << algor << " 25% " << std::fixed << std::setprecision(5) << time_calc_flow(rozmiar, 0.25, algor) << " milisekund \n";
		std::cout << "Czas testowania " << rozmiar << " metoda " << algor << " 50% " << std::fixed << std::setprecision(5) << time_calc_flow(rozmiar, 0.50, algor) << " milisekund \n";
		std::cout << "Czas testowania " << rozmiar << " metoda " << algor << " 75% " << std::fixed << std::setprecision(5) << time_calc_flow(rozmiar, 0.75, algor) << " milisekund \n";
		std::cout << "Czas testowania " << rozmiar << " metoda " << algor << " 100% " << std::fixed << std::setprecision(4) << time_calc_flow(rozmiar, 1.0, algor) << " milisekund \n";
		std::cout << std::endl;


		menu_flow();
		break;
	}
	case '2':
	{
		std::cout << "Wczytanie danych z pliku i zapis macierzy przeplywu do pliku \n ";
		Graph_base graph;
		bool directed;
		graph.change_directed(true);


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

		

			std::cout << "Maksymalny przeplyw - przeszukiwanie w glab - to : \n";
			Flow flow = graph_am.Ford_Fulkerson_BFS();
			graph_am.print_flow(flow);
			std::cout << "Podaj nazwe pliku do zapisu macierzy przeplywu - BFS:\n";
			std::string nazwa_flow;
			std::cin >> nazwa_flow;
			try
			{
				write_flow(nazwa_flow.c_str(), graph_am, flow);

			}
			catch (std::exception& e)
			{
				std::cerr << e.what();
			}
			//tutaj to jakos wyswietlic
			std::cout << "Maksymalny przeplyw - przeszukiwanie wszerz - to : \n";
			flow = graph_am.Ford_Fulkerson_DFS();
			graph_am.print_flow(flow);
			std::cout << "Podaj nazwe pliku do zapisu macierzy przeplywu - DFS:\n";
			std::cin >> nazwa_flow;
			try
			{
				write_flow(nazwa_flow.c_str(), graph_am, flow);
			}
			catch (std::exception& e)
			{
				std::cerr << e.what();
			}
			
			

		menu_flow();
		break;
	}
		/*******************************************************************************************************************/
	
	case '3':
	{
		return;
		break;
	}
	default:
	{
		std::cout << "Wybrano niepoprawna opcje, sprobuj ponownie.\n";
		menu_flow();
		break;
	}
	}



}
#endif