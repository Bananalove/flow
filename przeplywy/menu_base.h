#ifndef MENU_BASE_H
#define MENU_BASE_H

#include "menu_flow.h"
#include "menu_bell.h"
#include "menu_prim.h"


void menu_base(){
	std::cout << "Program korzystajacy z reprezentacji grafow jako macierz wag lub listy sasiadow, obliczajacy minimalne "
		"drzewo rozpinajace algorytmem Kruskala lub Prima, najktrotsza sciezke metoda Dijkstry lub Bellmana-Forda oraz maksymalny przeplyw.\n"
		"Opcje mozliwe do wyboru:\n "
		"1. wyznaczenie MST (graf nieskierowany!) \n "
		"2. wyznaczenie najkrotszej sciezki w grafie (graf skierowany!)\n "
		"3. obliczenie maksymalnego przeplywu (graf skierowany!) \n "
		"4. zakoncz.\n";
	" wybierz numer opcji :\n ";
	char opcja;
	std::cin >> opcja;
	switch (opcja)
	{
	case '1':
	{
		std::cout << "Wyznaczenie MST(graf nieskierowany!) \n ";
		menu();
		menu_base();
		break;
	}
	case '2':
	{
		std::cout << "Wyznaczenie najkrotszej sciezki w grafie (graf skierowany!)\n ";
		
		menu_bell();
		menu_base();
		break;
	}
		/*******************************************************************************************************************/
	case '3':
	{
		std::cout << "Obliczenie maksymalnego przeplywu (graf skierowany!) \n ";

		menu_flow();
		menu_base();
		
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