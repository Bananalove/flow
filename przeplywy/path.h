#ifndef PATH_H
#define PATH_H
#include <vector>
#include <iomanip>
#include <iostream>
#include <algorithm>

namespace constants {
	const int no_edge = -100;
	const char no_elem = '.';
	const int no_v = -100;
	const int infinit = std::numeric_limits<int>::max();
	const int absolutely_no_v = -1000;
	//const double infinit = std::numeric_limits<double>::infinity();
	
}
class Path {
	bool negativ_cycle;
	int V;
public:
	std::vector<int> cost;
	std::vector<int> previous;
	Path(int  Vnum = 0,bool is_neg = false) : V(Vnum), negativ_cycle(is_neg),  cost(V, constants::infinit), previous(V, constants::no_v)
	{
	
	}

	void change_neg_cyc(bool is_neg)
	{
		negativ_cycle = is_neg;
	}
	bool is_neg() const
	{
		return negativ_cycle;
	}

	

	void print_path() const
	{
		for (int i = 0; i < V; ++i)
		{
			std::vector<int> prev;
			prev.reserve(V);
			std::cout << std::fixed << std::setw(3) << i << " | " << std::setw(3) << cost[i] << " | ";
			
			for (int j = i; previous[j] != constants::no_v; j = previous[j])
			{
				prev.push_back(previous[j]);
			}
			std::reverse(prev.begin(), prev.end());
			for (auto iter = prev.begin(), stop = prev.end(); iter != stop; ++iter)
			{
				std::cout << std::fixed << std::setw(3) << *iter << "  ";
			}
			std::cout << std::fixed << std::setw(3) << i << "  ";
			std::cout << "\n";
		}
	}
	void print_path(std::ostream& out) const
	{
		for (int i = 0; i < V; ++i)
		{
			std::vector<int> prev;
			prev.reserve(V);
			out << std::fixed << std::setw(3) << i << " | " << std::setw(3) << cost[i] << " | ";

			for (int j = i; previous[j] != constants::no_v; j = previous[j])
			{
				prev.push_back(previous[j]);
			}
			std::reverse(prev.begin(), prev.end());
			for (auto iter = prev.begin(), stop = prev.end(); iter != stop; ++iter)
			{
				out << std::fixed << std::setw(3) << *iter << "  ";
			}
			out << std::fixed << std::setw(3) << i << "  \n";
		}
	}
	

};







#endif