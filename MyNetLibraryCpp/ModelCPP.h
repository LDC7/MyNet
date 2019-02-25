#pragma once
#include "ModelSaveLoaderCPP.h"

class ModelCPP
{
public:
	ModelCPP()
	{
		SetMomentumCoefficient(0.1f);
		SetErrorListLength(500);
	}
	
	void Train(int maxN, float eta, float*(*getXFunc)(int, int*), float*(*getYFunc)(int, int*))
	{
		this->eta = eta;
		int n;
		float* inp;
		int* inpCount;
		float* outp;
		int* outpCount;
		float dW;

		if (random)
		{
			for (int i = 0; i < maxN; i++)
			{
				n = rand();
				inp = getXFunc(n, inpCount);
				outp = getYFunc(n, outpCount);
				TrainStep(inp, *inpCount, outp, *outpCount);
				dW = SetNewW();
				if (minDWSetted && dW < minDW)
				{
					return;
				}

				if (targetErrorSetted && targetError > lastError)
				{
					return;
				}
			}
		}
		else
		{
			for (int i = 0; i < maxN; i++)
			{
				n = 0;
				inp = getXFunc(n, inpCount);
				outp = getYFunc(n, outpCount);
				do
				{
					TrainStep(inp, *inpCount, outp, *outpCount);
					if (targetErrorSetted && targetError > lastError)
					{
						SetNewW();
						return;
					}

					n++;
					i++;
					if (batchSizeSetted && i % batchSize == 0)
					{
						dW = SetNewW();
						if (minDWSetted && dW < minDW)
						{
							return;
						}
					}

					inp = getXFunc(n, inpCount);
					outp = getYFunc(n, outpCount);
				} while (i < maxN && inp != NULL && outp != NULL);
				dW = SetNewW();
				if (minDWSetted && dW < minDW)
				{
					return;
				}
			}
		}
	}

	void AddLayer(LayerCPP layer)
	{
		layers.push_back(layer);
		layersCount++;
	}

	float* GetRes(float* input)
	{
		float* temp = input;
		for (list<LayerCPP>::iterator it = layers.begin(); it != layers.end(); ++it)
		{
			it->Next(temp);
			temp = it->GetY();
		}

		return temp;
	}

	void SaveWeights(string path)
	{
		ModelSaveLoaderCPP::SaveWeights(layers, layersCount, path);
	}

	void LoadWeights(string path)
	{
		ModelSaveLoaderCPP::LoadWeights(&layers, path);
	}


	// ��������
	void SetTargetError(float TargetError) { targetErrorSetted = true; targetError = TargetError; }
	float GetTargetError() { return targetErrorSetted ? targetError : -1.0f; }
	void SetMinDW(float MinDW) { minDWSetted = true; minDW = MinDW; }
	float GetMinDW() { return minDWSetted ? minDW : -1.0f; }
	void SetBatchSize(int BatchSize) { batchSizeSetted = true; batchSize = BatchSize; }
	int GetBatchSize() { return batchSizeSetted ? batchSize : -1; }
	void SetRandom(bool Random) { random = Random; }
	bool GetRandom() { return random; }
	void SetMomentumCoefficient(float MomentumCoefficient) { momentumCoefficient = MomentumCoefficient; }
	float GetMomentumCoefficient() { return momentumCoefficient; }
	void SetErrorListLength(int ErrorListLength) { errorListLength = ErrorListLength; }
	int GetErrorListLength() { return errorListLength; }
	void SetLambdaReg(float LambdaReg) { lambdaReg = LambdaReg; }
	float GetLambdaReg() { return lambdaReg; }
	void SetErrorList(list<float> ErrorList) { errorList = ErrorList; }
	list<float> GetErrorList() { return  errorList; }

private:
	list<LayerCPP> layers;
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

	float SetNewW()
	{
		float sum = 0;
		for (list<LayerCPP>::iterator it = layers.begin(); it != layers.end(); ++it)
		{
			sum += it->SetNewW();
		}

		return sum;
	}

	void TrainStep(float* X, int XCount, float* Y, int YCount)
	{
		float sum;
		GetRes(X);
		float* dels;
		float* delsOld = NULL;
		float temp;
		momentum = new float*[layersCount];

		float error = 0;
		for (int i = 0; i < YCount; i++)
		{
			error = powf(layers.back().GetY()[i] - Y[i], 2);
		}

		lastError = error / YCount;
		errorList.push_front(lastError);
		if (errorList.size() > errorListLength)
		{
			list<float>::iterator it = errorList.begin();
			advance(it, errorList.size() - errorListLength);
			errorList.erase(errorList.begin(), it);
		}

		list<LayerCPP>::reverse_iterator itn;
		int ind = layersCount - 1;
		for (list<LayerCPP>::reverse_iterator it = layers.rbegin(); it != layers.rend(); ++it)
		{
			dels = new float[it->GetM()];
			momentum[ind] = new float[it->GetM()];

			for (int j = 0; j < it->GetM(); j++)
			{
				sum = 0;
				if (ind == layersCount - 1)
				{
					dels[j] = (Y[j] - it->GetY()[j]) * it->GetFunction().DerivativeactivationFunction(it->GetYsum()[j]);
				}
				else
				{
					itn = it;
					itn--;
					for (int k = 0; k < itn->GetM(); k++)
					{
						sum += itn->GetW()[k][j] * delsOld[k];
					}

					dels[j] = sum * it->GetFunction().DerivativeactivationFunction(it->GetYsum()[j]);
				}

				for (int k = 0; k < it->GetN(); k++)
				{
					temp = it->GetX()[k] * eta * dels[j];
					it->GetWn()[j][k] += temp - (lambdaReg * it->GetWn()[j][k]) + (momentumCoefficient * momentum[ind][j]);
					momentum[ind][j] = temp;
				}

				it->GetWn0()[j] += eta * dels[j] - (lambdaReg * it->GetWn0()[j]);
			}

			delsOld = dels;
			ind++;
		}
	}
};
