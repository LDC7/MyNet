namespace MyNet
{
    using System;
    using System.Collections.Generic;

    public class Layer
    {
        internal int N { get; private set; }
        internal int M { get; private set; }
        internal FunctionWrapper Function { get; private set; }
        internal IList<float> X { get; set; }
        internal IList<float> Y { get; set; }
        internal IList<float> Ysum { get; set; }
        internal float[,] W { get; set; }
        internal float[] W0 { get; set; }
        internal float[,] Wn { get; set; }
        internal float[] Wn0 { get; set; }

        public Layer(int nEnters, int nExits, FunctionWrapper.FunctionType activationFun)
        {
            N = nEnters;
            M = nExits;
            InitWeights();
            Function = new FunctionWrapper(activationFun);
        }

        public void Next(IList<float> X)
        {
            float sum;
            this.X = X;
            Y = new List<float>(M);
            Ysum = new List<float>(M);
            for (int i = 0; i < M; i++)
            {
                sum = W0[i];
                for (int j = 0; j < N; j++)
                {
                    sum += W[i, j] * this.X[j];
                }

                Ysum.Add(sum);
                Y.Add(Function.ActivationFunction(sum));
            }
        }

        public float SetNewW()
        {
            float sum = 0;
            for (int i = 0; i < M; i++)
            {
                sum += Math.Abs(W0[i] - Wn0[i]);
                W0[i] = Wn0[i];
                for (int j = 0; j < N; j++)
                {
                    sum += Math.Abs(W[i, j] - Wn[i, j]);
                    W[i, j] = Wn[i, j];
                }
            }

            return sum;
        }

        private void InitWeights()
        {
            Random rand = new Random();
            double limit = Math.Sqrt(6) / Math.Sqrt(N + M);
            W = new float[M, N];
            W0 = new float[M];
            Wn = new float[M, N];
            Wn0 = new float[M];
            for (int i = 0; i < M; i++)
            {
                for (int j = 0; j < N; j++)
                {
                    W[i, j] = (float)((rand.NextDouble() * (2 * limit)) - limit);
                    Wn[i, j] = W[i, j];
                }
            }
        }
    }
}
