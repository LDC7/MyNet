#pragma once
#include "FunctionWrapperCPP.h"

class LayerCPP
{
public:
	LayerCPP(int nEnters, int nExits, FunctionTypeCPP activationFun)
	{
		SetN(nEnters);
		SetM(nExits);
		InitWeights();
		function = activationFun;
	}

	~LayerCPP()
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

	void Next(float* X)
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

	float SetNewW()
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

	// Свойства
	void SetN(int N) { n = N; }
	int GetN() { return n; }
	void SetM(int M) { m = M; }
	int GetM() { return m; }
	FunctionWrapperCPP GetFunction() { return function; }
	void SetX(float* X) { x = X; }
	float* GetX() { return x; }
	void SetY(float* Y) { y = Y; }
	float* GetY() { return y; }
	void SetYsum(float* Ysum) { ySum = Ysum; }
	float* GetYsum() { return ySum; }
	void SetW(float** W) { w = W; }
	float** GetW() { return w; }
	void SetW0(float* W0) { w0 = W0; }
	float* GetW0() { return w0; }
	void SetWn(float** Wn) { wn = Wn; }
	float** GetWn() { return wn; }
	void SetWn0(float* Wn0) { wn0 = Wn0; }
	float* GetWn0() { return wn0; }

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

	void InitWeights()
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
};

