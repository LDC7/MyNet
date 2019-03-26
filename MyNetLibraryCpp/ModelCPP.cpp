#include "stdafx.h"
#include "ModelCPP.h"

ModelCPP::ModelCPP()
{
	SetMomentumCoefficient(0.1f);
	SetErrorListLength(500);
	layers = new list<LayerCPP*>();
}

ModelCPP::~ModelCPP()
{
	for (list<LayerCPP*>::iterator it = layers->begin(); it != layers->end(); it++)
	{
		delete (*it);
	}
	delete layers;
}

void ModelCPP::Train(int maxN, float eta, std::function<float*(int)> getXFunc, int inpCount, std::function<float*(int)> getYFunc, int outpCount)
{
	this->eta = eta;
	int n;
	float* inp;
	float* outp;
	float dW;

	momentum = new float*[layersCount];
	int ind = layersCount - 1;
	for (list<LayerCPP*>::reverse_iterator it = layers->rbegin(); it != layers->rend(); it++)
	{
		momentum[ind] = new float[(*it)->GetM()]();
		ind--;
	}

	if (random)
	{
		for (int i = 0; i < maxN; i++)
		{
			n = rand();
			inp = getXFunc(n);
			outp = getYFunc(n);
			TrainStep(inp, inpCount, outp, outpCount);
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
		for (int i = 0; i < maxN;)
		{
			n = 0;
			inp = getXFunc(n);
			outp = getYFunc(n);
			do
			{
				TrainStep(inp, inpCount, outp, outpCount);
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

				inp = getXFunc(n);
				outp = getYFunc(n);
			} while (i < maxN && inp != NULL && outp != NULL);
			dW = SetNewW();
			if (minDWSetted && dW < minDW)
			{
				return;
			}
		}
	}

	for (int i = 0; i < layersCount; i++)
	{
		delete[] momentum[i];
	}
	delete[] momentum;
}

void ModelCPP::AddLayer(LayerCPP* layer)
{
	layers->push_back(layer);
	layersCount++;
}

float* ModelCPP::GetRes(float* input)
{
	float* temp = input;
	for (list<LayerCPP*>::iterator it = layers->begin(); it != layers->end(); it++)
	{
		(*it)->Next(temp);
		temp = (*it)->GetY();
	}

	return temp;
}

// Свойства
void ModelCPP::SetTargetError(float TargetError) { targetErrorSetted = true; targetError = TargetError; }
float ModelCPP::GetTargetError() { return targetErrorSetted ? targetError : -1.0f; }
void ModelCPP::SetMinDW(float MinDW) { minDWSetted = true; minDW = MinDW; }
float ModelCPP::GetMinDW() { return minDWSetted ? minDW : -1.0f; }
void ModelCPP::SetBatchSize(int BatchSize) { batchSizeSetted = true; batchSize = BatchSize; }
int ModelCPP::GetBatchSize() { return batchSizeSetted ? batchSize : -1; }
void ModelCPP::SetRandom(bool Random) { random = Random; }
bool ModelCPP::GetRandom() { return random; }
void ModelCPP::SetMomentumCoefficient(float MomentumCoefficient) { momentumCoefficient = MomentumCoefficient; }
float ModelCPP::GetMomentumCoefficient() { return momentumCoefficient; }
void ModelCPP::SetErrorListLength(int ErrorListLength) { errorListLength = ErrorListLength; }
int ModelCPP::GetErrorListLength() { return errorListLength; }
void ModelCPP::SetLambdaReg(float LambdaReg) { lambdaReg = LambdaReg; }
float ModelCPP::GetLambdaReg() { return lambdaReg; }
list<float> ModelCPP::GetErrorList() { return  errorList; }
int ModelCPP::GetLayersCount() { return layersCount; }
list<LayerCPP*>* ModelCPP::GetLayers() { return layers; }

float ModelCPP::SetNewW()
{
	float sum = 0;
	for (list<LayerCPP*>::iterator it = layers->begin(); it != layers->end(); it++)
	{
		sum += (*it)->SetNewW();
	}

	return sum;
}

void ModelCPP::TrainStep(float* X, int XCount, float* Y, int YCount)
{
	float sum;
	GetRes(X);
	float* dels = NULL;
	float* delsOld = NULL;
	float temp;	

	float error = 0;
	for (int i = 0; i < YCount; i++)
	{
		error += powf(layers->back()->GetY()[i] - Y[i], 2);
	}

	lastError = error / YCount;
	errorList.push_front(lastError);
	if (errorList.size() > errorListLength)
	{
		list<float>::iterator it = errorList.begin();
		advance(it, errorList.size() - errorListLength);
		errorList.erase(errorList.begin(), it);
	}

	list<LayerCPP*>::reverse_iterator itn;
	int ind = layersCount - 1;
	for (list<LayerCPP*>::reverse_iterator it = layers->rbegin(); it != layers->rend(); it++)
	{
		dels = new float[(*it)->GetM()];

		for (int j = 0; j < (*it)->GetM(); j++)
		{
			sum = 0;
			if (ind == layersCount - 1)
			{
				dels[j] = (Y[j] - (*it)->GetY()[j]) * (*it)->GetFunction()->DerivativeactivationFunction((*it)->GetYsum()[j]);
			}
			else
			{
				itn = it;
				itn--;
				for (int k = 0; k < (*itn)->GetM(); k++)
				{
					sum += (*itn)->GetW()[k][j] * delsOld[k];
				}

				dels[j] = sum * (*it)->GetFunction()->DerivativeactivationFunction((*it)->GetYsum()[j]);
			}

			for (int k = 0; k < (*it)->GetN(); k++)
			{
				temp = (*it)->GetX()[k] * eta * dels[j];
				(*it)->GetWn()[j][k] += temp - (lambdaReg * (*it)->GetWn()[j][k]) + (momentumCoefficient * momentum[ind][j]);
				momentum[ind][j] = temp;
			}

			(*it)->GetWn0()[j] += eta * dels[j] - (lambdaReg * (*it)->GetWn0()[j]);
		}

		delete[] delsOld;
		delsOld = dels;
		ind--;
	}

	delete[] dels;
}