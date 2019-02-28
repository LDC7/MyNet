#pragma once
#include "FunctionWrapperCPP.h"

class LayerCPP
{
public:
	LayerCPP(int nEnters, int nExits, FunctionTypeCPP activationFun);

	~LayerCPP();

	void Next(float* X);

	float SetNewW();

	// Свойства
	void SetN(int N);
	int GetN();
	void SetM(int M);
	int GetM();
	FunctionWrapperCPP GetFunction();
	void SetX(float* X);
	float* GetX();
	void SetY(float* Y);
	float* GetY();
	void SetYsum(float* Ysum);
	float* GetYsum();
	void SetW(float** W);
	float** GetW();
	void SetW0(float* W0);
	float* GetW0();
	void SetWn(float** Wn);
	float** GetWn();
	void SetWn0(float* Wn0);
	float* GetWn0();

private:
	int n;
	int m;
	FunctionWrapperCPP function;
	float* x;
	float* y;
	float* ySum;
	float** w;
	float* w0;
	float** wn;
	float* wn0;

	void InitWeights();
};

