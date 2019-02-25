#pragma once
#include <iostream>
#include <fstream>
#include <list>
#include "LayerCPP.h"
using namespace std;

static class ModelSaveLoaderCPP
{
private:
	static const char Separator = ' ';

public:
	static void SaveWeights(list<LayerCPP> layers, int layersCount, string path)
	{
		ofstream fout(path);

		fout << layersCount << endl;

		for (list< LayerCPP>::iterator it = layers.begin(); it != layers.end(); ++it)
		{
			fout << it->GetN() << Separator << it->GetM() << endl;

			for (int i = 0; i < it->GetM(); i++)
			{
				fout << it->GetW0()[i] << Separator;
				for (int j = 0; j < it->GetN(); j++)
				{
					fout << it->GetW()[i][j] << Separator;
				}
				fout << endl;
			}

			fout.close();
		}
	}

	static void LoadWeights(list<LayerCPP>* layers, string path)
	{
		int layersCount;
		int n, m;
		ifstream fin(path);

		fin >> layersCount;

		int l = 0;
		for (list<LayerCPP>::iterator it = layers->begin(); l < layersCount; ++it)
		{
			fin >> n >> m;
			for (int i = 0; i < m; i++)
			{
				fin >> it->GetW0()[i];
				for (int j = 0; j < n; j++)
				{
					fin >> it->GetWn()[i][j];
				}
			}			
			l++;
		}

		fin.close();
	}
};
