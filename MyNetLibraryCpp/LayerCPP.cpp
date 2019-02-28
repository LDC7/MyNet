#include "stdafx.h"
#include "LayerCPP.h"

LayerCPP::LayerCPP(int nEnters, int nExits, FunctionTypeCPP activationFun)
{
	SetN(nEnters);
	SetM(nExits);
	InitWeights();
	function = activationFun;
}

LayerCPP::~LayerCPP()
{
	delete[] x;
	delete[] y;
	delete[] ySum;
	delete[] w0;
	delete[] wn0;
	for (int i = 0; i < m; i++)
	{
		delete[] w[i];
		delete[] wn[i];
	}
	delete[] w;
	delete[] wn;
}

void LayerCPP::Next(float* X)
{
	float sum;
	SetX(X);
	y = new float[m];
	ySum = new float[m];
	for (int i = 0; i < m; i++)
	{
		sum = w0[i];
		for (int j = 0; j < n; j++)
		{
			sum += w[i][j] * x[j];
		}

		ySum[i] = sum;
		y[i] = function.ActivationFunction(sum);
	}
}

float LayerCPP::SetNewW()
{
	float sum = 0;
	for (int i = 0; i < m; i++)
	{
		sum += abs(w0[i] - wn0[i]);
		w0[i] = wn0[i];
		for (int j = 0; j < n; j++)
		{
			sum += abs(w[i][j] - wn[i][j]);
			w[i][j] = wn[i][j];
		}
	}

	return sum;
}

void LayerCPP::SetN(int N) { n = N; }
int LayerCPP::GetN() { return n; }
void LayerCPP::SetM(int M) { m = M; }
int LayerCPP::GetM() { return m; }
FunctionWrapperCPP LayerCPP::GetFunction() { return function; }
void LayerCPP::SetX(float* X) { x = X; }
float* LayerCPP::GetX() { return x; }
void LayerCPP::SetY(float* Y) { y = Y; }
float* LayerCPP::GetY() { return y; }
void LayerCPP::SetYsum(float* Ysum) { ySum = Ysum; }
float* LayerCPP::GetYsum() { return ySum; }
void LayerCPP::SetW(float** W) { w = W; }
float** LayerCPP::GetW() { return w; }
void LayerCPP::SetW0(float* W0) { w0 = W0; }
float* LayerCPP::GetW0() { return w0; }
void LayerCPP::SetWn(float** Wn) { wn = Wn; }
float** LayerCPP::GetWn() { return wn; }
void LayerCPP::SetWn0(float* Wn0) { wn0 = Wn0; }
float* LayerCPP::GetWn0() { return wn0; }

void LayerCPP::InitWeights()
{
	float limit = sqrtf(6.0f) / sqrtf(n + m);
	w = new float*[m];
	w0 = new float[m];
	wn = new float*[m];
	wn0 = new float[m];
	for (int i = 0; i < m; i++)
	{
		w[i] = new float[n];
		wn[i] = new float[n];
		for (int j = 0; j < n; j++)
		{
			w[i][j] = (float)(((static_cast <float> (rand()) / static_cast <float> (RAND_MAX)) * (2 * limit)) - limit);
			wn[i][j] = w[i][j];
		}
		w0[i] = 0;
		wn0[i] = 0;
	}
}