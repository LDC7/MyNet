namespace MyNet
{
    public class L1Reg : IRegularizer
    {
        private float lambda;

        public L1Reg(float lambda)
        {
            this.lambda = lambda;
        }

        public float GetReg(Layer layer)
        {
            float sum = 0;
            for (int i = 0; i < layer.M; i++)
            {
                for (int j = 0; j < layer.N; j++)
                {
                    sum += layer.W[i, j] * layer.W[i, j];
                }
            }

            sum = sum / (layer.M * layer.N);
            return lambda * sum;
        }
    }
}
