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
	static void SaveWeights(list<LayerCPP*>* layers, int layersCount, string path);

	static void LoadWeights(list<LayerCPP*>* layers, string path);
};
