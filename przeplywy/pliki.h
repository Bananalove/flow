#ifndef PLIKI_H
#define PLIKI_H
#include <exception>
#include <fstream>
#include <list>
#include "graph_base.h"
#include "path.h"


/*
definiowane operacje zapisu do plikow

*/

std::ostream& operator<< (std::ostream& out, Graph_base graph)
{
	for (auto iter = graph.edge_list.begin(), stop = graph.edge_list.end(); iter != stop; ++iter)
	{
		out << std::get<0>(*iter) << " " << std::get<1>(*iter) << " " << std::get<2>(*iter) << "\n";
	}
	return out;
}



std::istream& operator>> (std::istream& in, Graph_base& graph)
{
	int numE;
	int numV;
	int Vstart;
	int Vend;
	in >> numE >> numV >> Vstart >> Vend;
	graph.change_set(numE, numV, Vstart, Vend);
	int vert1, vert2, edge_l;
	for (int i = 0; i < numE; ++i)
	{
		in >> vert1 >> vert2 >> edge_l;
		graph.add_edge(vert1, vert2, edge_l);
	}
	return in;
}

void read_file(const char* name, Graph_base& graph)
{

	std::ifstream ifs;
	ifs.open(name, std::ifstream::in);
	if (ifs.is_open())
	{
		ifs >> graph;
		ifs.close();
	}
	else
	{
		throw std::runtime_error("Plik odczytu nie zostal otwarty!\n");
	}
}
void write_file(const char* name, const Graph_base& graph)
{

	std::ofstream ofs;
	ofs.open(name, std::ofstream::out);
	if (ofs.is_open())
	{
		ofs << graph;
		ofs.close();
	}
	else
	{
		throw std::runtime_error("Plik zapisu nie zostal otwarty!\n");
	}
}


void write_graph(const char* name, const Graph_common& graph)
	{

	std::ofstream ofs;
	ofs.open(name, std::ofstream::out);
	if (ofs.is_open())
	{
		graph.print(ofs);
		ofs.close();
	}
	else
	{
		throw std::runtime_error("Plik zapisu nie zostal otwarty!\n");
	}
}

void write_path(const char* name, const Path& path)
{

	std::ofstream ofs;
	ofs.open(name, std::ofstream::out);
	if (ofs.is_open())
	{
		path.print_path(ofs);
		ofs.close();
	}
	else
	{
		throw std::runtime_error("Plik zapisu nie zostal otwarty!\n");
	}
}
void write_mst(const char* name, const Graph_base& graph)
{

	std::ofstream ofs;
	ofs.open(name, std::ofstream::out);
	if (ofs.is_open())
	{
		graph.print_mst(ofs);
		ofs.close();
	}
	else
	{
		throw std::runtime_error("Plik zapisu nie zostal otwarty!\n");
	}
}

#endif
