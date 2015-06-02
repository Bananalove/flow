#ifndef FLOW_H
#define FLOW_H

class Flow{
	int numV;
public:
	int** flow_m;
	int fmax;
	Flow(int V, int val = 0) :numV(V), fmax(0)
	{
		flow_m = new int*[numV];
		for (int i = 0; i < numV; ++i)
		{
			flow_m[i] = new int[numV];
		}
				
		for (int i = 0; i < numV; ++i)
		{
			for (int j = 0; j < numV; ++j)
			{
				flow_m[i][j] = val;
			}
		}
	}
	Flow() : flow_m(nullptr), numV(0), fmax(0) {}

	Flow& operator= (const Flow& flow2)
	{
		if (flow_m != nullptr)
		{
			for (int i = 0; i < numV; ++i)
			{
				delete[] flow_m[i];
			}
			delete[] flow_m;
		}
		numV = flow2.numV;
		fmax = flow2.fmax;
		flow_m = new int*[numV];
		for (int i = 0; i < numV; ++i)
		{
			flow_m[i] = new int[numV];
		}

		for (int i = 0; i < numV; ++i)
		{
			for (int j = 0; j < numV; ++j)
			{
				flow_m[i][j] = flow2.flow_m[i][j];
			}
		}
		return *this;
	}
	Flow(const Flow& flow2)
	{
		numV = flow2.numV;
		fmax = flow2.fmax;
		flow_m = new int*[numV];
		for (int i = 0; i < numV; ++i)
		{
			flow_m[i] = new int[numV];
		}

		for (int i = 0; i < numV; ++i)
		{
			for (int j = 0; j < numV; ++j)
			{
				flow_m[i][j] = flow2.flow_m[i][j];
			}
		}

	}

	~Flow()
	{
		if (flow_m != nullptr)
		{
			for (int i = 0; i < numV; ++i)
			{
				delete[] flow_m[i];
			}
			delete[] flow_m;
		}
	}

};




#endif