#pragma once
#include "LayerCPP.h"
#include <functional>
#include <list>

using namespace std;

class ModelCPP
{
public:
	ModelCPP();

	~ModelCPP();
	
	void Train(int maxN, float eta, std::function<float*(int)> getXFunc, int inpCount, std::function<float*(int)> getYFunc, int outpCount);

	void AddLayer(LayerCPP* layer);

	float* GetRes(float* input);

	// Свойства
	void SetTargetError(float TargetError);
	float GetTargetError();
	void SetMinDW(float MinDW);
	float GetMinDW();
	void SetBatchSize(int BatchSize);
	int GetBatchSize();
	void SetRandom(bool Random);
	bool GetRandom();
	void SetMomentumCoefficient(float MomentumCoefficient);
	float GetMomentumCoefficient();
	void SetErrorListLength(int ErrorListLength);
	int GetErrorListLength();
	void SetLambdaReg(float LambdaReg);
	float GetLambdaReg();
	list<float> GetErrorList();
	int GetLayersCount();
	list<LayerCPP*>* GetLayers();

private:
	list<LayerCPP*>* layers;
	int layersCount = 0;
	float eta;
	float** momentum;
	float lastError;

	// public
	bool targetErrorSetted = false;
	float  targetError;
	bool minDWSetted = false;
	float minDW;
	bool batchSizeSetted = false;
	int  batchSize;
	bool random;
	float momentumCoefficient;
	int errorListLength;
	float lambdaReg;
	list<float> errorList;

	float SetNewW();

	void TrainStep(float* X, int XCount, float* Y, int YCount);
};
