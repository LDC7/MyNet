#include "stdafx.h"
#include "ModelCPP.h"

ModelCPP::ModelCPP()
{
	SetMomentumCoefficient(0.1f);
	SetErrorListLength(500);
}

ModelCPP::~ModelCPP()
{
	for (list<LayerCPP*>::iterator it = layers.begin(); it != layers.end(); ++it)
	{
		delete (*it);
	}
}

void ModelCPP::Train(int maxN, float eta, float*(*getXFunc)(int), float*(*getYFunc)(int))
{
	this->eta = eta;
	int n;
	float* inp;
	int inpCount;
	float* outp;
	int outpCount;
	float dW;

	if (random)
	{
		for (int i = 0; i < maxN; i++)
		{
			n = rand();
			inp = getXFunc(n);
			inpCount = sizeof(inp) / sizeof(float);
			outp = getYFunc(n);
			outpCount = sizeof(outp) / sizeof(float);
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
		for (int i = 0; i < maxN; i++)
		{
			n = 0;
			inp = getXFunc(n);
			inpCount = sizeof(inp) / sizeof(float);
			outp = getYFunc(n);
			outpCount = sizeof(outp) / sizeof(float);
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
				inpCount = sizeof(inp) / sizeof(float);
				outp = getYFunc(n);
				outpCount = sizeof(outp) / sizeof(float);
			} while (i < maxN && inp != NULL && outp != NULL);
			dW = SetNewW();
			if (minDWSetted && dW < minDW)
			{
				return;
			}
		}
	}
}

void ModelCPP::AddLayer(LayerCPP* layer)
{
	layers.push_back(layer);
	layersCount++;
}

float* ModelCPP::GetRes(float* input)
{
	float* temp = input;
	for (list<LayerCPP*>::iterator it = layers.begin(); it != layers.end(); ++it)
	{
		(*it)->Next(temp);
		temp = (*it)->GetY();
	}

	return temp;
}

void ModelCPP::SaveWeights(string path)
{
	ModelSaveLoaderCPP::SaveWeights(&layers, layersCount, path);
}

void ModelCPP::LoadWeights(string path)
{
	ModelSaveLoaderCPP::LoadWeights(&layers, path);
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
void ModelCPP::SetErrorList(list<float> ErrorList) { errorList = ErrorList; }
list<float> ModelCPP::GetErrorList() { return  errorList; }

float ModelCPP::SetNewW()
{
	float sum = 0;
	for (list<LayerCPP*>::iterator it = layers.begin(); it != layers.end(); ++it)
	{
		sum += (*it)->SetNewW();
	}

	return sum;
}

void ModelCPP::TrainStep(float* X, int XCount, float* Y, int YCount)
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
		error = powf(layers.back()->GetY()[i] - Y[i], 2);
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
				dels[j] = (Y[j] - it->GetY()[j]) * it->GetFunction()->DerivativeactivationFunction(it->GetYsum()[j]);
			}
			else
			{
				itn = it;
				itn--;
				for (int k = 0; k < itn->GetM(); k++)
				{
					sum += itn->GetW()[k][j] * delsOld[k];
				}

				dels[j] = sum * it->GetFunction()->DerivativeactivationFunction(it->GetYsum()[j]);
			}

			for (int k = 0; k < it->GetN(); k++)
			{
				temp = it->GetX()[k] * eta * dels[j];
				it->GetWn()[j][k] += temp - (lambdaReg * it->GetWn()[j][k]) + (momentumCoefficient * momentum[ind][j]);
				momentum[ind][j] = temp;
			}

			it->GetWn0()[j] += eta * dels[j] - (lambdaReg * it->GetWn0()[j]);
		}

		delete[] delsOld;
		delsOld = dels;
		ind++;
	}

	for (int i = 0; i < layersCount; i++)
	{
		delete[] momentum[i];
	}
	delete[] delsOld;
	delete[] momentum;
}