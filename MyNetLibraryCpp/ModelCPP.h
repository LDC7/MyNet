#pragma once
#include "ModelSaveLoaderCPP.h"

class ModelCPP
{
public:
	ModelCPP();

	~ModelCPP();
	
	void Train(int maxN, float eta, float*(*getXFunc)(int), float*(*getYFunc)(int));

	void AddLayer(LayerCPP* layer);

	float* GetRes(float* input);

	void SaveWeights(string path);

	void LoadWeights(string path);

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
	void SetErrorList(list<float> ErrorList);
	list<float> GetErrorList();

private:
	list<LayerCPP*> layers;
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
