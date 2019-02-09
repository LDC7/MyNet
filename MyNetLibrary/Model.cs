namespace MyNet
{
    using System;
    using System.Collections.Generic;

    public class Model
    {
        private IList<Layer> layers;
        private float eta;
        private float lastError;
        private float[][] momentum;
        public float? TargetError { get; set; }
        public float? MinDW { get; set; }
        public bool Random { get; set; }
        public int? BatchSize { get; set; }
        public IRegularizer Regularizer { get; set; }
        public float MomentumCoefficient { get; set; }

        public Model()
        {
            layers = new List<Layer>();
            MomentumCoefficient = 0.1f;
        }

        public void Train(int maxN, float eta, Func<int, IList<float>> getXFunc, Func<int, IList<float>> getYFunc)
        {
            this.eta = eta;
            int n;
            IList<float> inp = null;
            IList<float> outp = null;
            float dW;

            if (Random)
            {
                Random rand = new Random();
                for (int i = 0; i < maxN; i++)
                {
                    n = rand.Next();
                    TrainStep(getXFunc(n), getYFunc(n));
                    dW = SetNewW();
                    if (MinDW != null && dW < MinDW)
                    {
                        return;
                    }

                    if (TargetError != null && TargetError > lastError)
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
                    outp = getYFunc(n);
                    do
                    {
                        TrainStep(inp, outp);
                        if (TargetError != null && TargetError > lastError)
                        {
                            SetNewW();
                            return;
                        }

                        n++;
                        i++;
                        if (BatchSize != null && i % BatchSize == 0)
                        {
                            dW = SetNewW();
                            if (MinDW != null && dW < MinDW)
                            {
                                return;
                            }
                        }

                        inp = getXFunc(n);
                        outp = getYFunc(n);
                    }
                    while (i < maxN && inp != null && outp != null);
                    dW = SetNewW();
                    if (MinDW != null && dW < MinDW)
                    {
                        return;
                    }
                }
            }
        }

        public void AddLayer(Layer layer)
        {
            layers.Add(layer);
        }

        public IList<float> GetRes(IList<float> input)
        {
            IList<float> temp = input;
            foreach (var l in layers)
            {
                l.Next(temp);
                temp = l.Y;
            }

            return temp;
        }

        public void SaveWeights(string path)
        {
            ModelSaveLoader.SaveWeights(layers, path);
        }

        public void LoadWeights(string path)
        {
            ModelSaveLoader.LoadWeights(layers, path);
        }

        private float SetNewW()
        {
            float sum = 0;
            for (int j = 0; j < layers.Count; j++)
            {
                sum += layers[j].SetNewW();
            }

            return sum;
        }

        private void TrainStep(IList<float> X, IList<float> Y)
        {
            float sum;
            GetRes(X);
            float[] dels;
            float[] delsOld = null;
            float regulation;
            float temp;
            momentum = new float[layers.Count][];

            double error = 0;
            for (int i = 0; i < Y.Count; i++)
            {
                error = Math.Pow(layers[layers.Count - 1].Y[i] - Y[i], 2);
            }

            lastError = (float)error / Y.Count;
            for (int i = layers.Count - 1; i >= 0; i--)
            {
                dels = new float[layers[i].M];
                momentum[i] = new float[dels.Length];
                regulation = (Regularizer == null) ? 0.0f : Regularizer.GetReg(layers[i]);

                for (int j = 0; j < dels.Length; j++)
                {
                    sum = 0;
                    if (i == layers.Count - 1)
                    {
                        dels[j] = (Y[j] - layers[i].Y[j] + regulation) * layers[i].Function.DerivativeactivationFunction(layers[i].Ysum[j]);
                    }
                    else
                    {
                        for (int k = 0; k < layers[i + 1].M; k++)
                        {
                            sum += layers[i + 1].W[k, j] * delsOld[k];
                        }

                        dels[j] = (sum + regulation) * layers[i].Function.DerivativeactivationFunction(layers[i].Ysum[j]);
                    }

                    for (int k = 0; k < layers[i].N; k++)
                    {
                        temp = layers[i].X[k] * eta * dels[j];
                        layers[i].Wn[j, k] += temp + (MomentumCoefficient * momentum[i][j]);
                        momentum[i][j] = temp;
                    }

                    layers[i].Wn0[j] += eta * dels[j];
                }

                delsOld = dels;
            }
        }
    }
}
