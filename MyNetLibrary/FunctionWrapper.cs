namespace MyNet
{
    using System;

    public class FunctionWrapper
    {
        internal Func<float, float> ActivationFunction { get; private set; }
        internal Func<float, float> DerivativeactivationFunction { get; private set; }

        public FunctionWrapper(FunctionType type = FunctionType.Liner)
        {
            ChoseFun(type);
        }

        public enum FunctionType
        {
            Liner,
            BynarySigmoid,
            BipolarSigmoid,
            GyperTan,
            ReLu
        }

        private void ChoseFun(FunctionType activationFun)
        {
            switch (activationFun)
            {
                case FunctionType.Liner:
                    ActivationFunction = new Func<float, float>(x => x);
                    DerivativeactivationFunction = new Func<float, float>(x => 1);
                    break;
                case FunctionType.BynarySigmoid:
                    ActivationFunction = new Func<float, float>(x => (float)(1 / (1 + Math.Pow(Math.E, -x))));
                    DerivativeactivationFunction = new Func<float, float>(x => (1 - ActivationFunction(x)) * ActivationFunction(x));
                    break;
                case FunctionType.BipolarSigmoid:
                    ActivationFunction = new Func<float, float>(x => (float)((2 / (1 + Math.Pow(Math.E, -x))) - 1));
                    DerivativeactivationFunction = new Func<float, float>(x => ((1 + ActivationFunction(x)) * (1 - ActivationFunction(x)) / 2));
                    break;
                case FunctionType.GyperTan:
                    ActivationFunction = new Func<float, float>(x => (float)((Math.Pow(Math.E, 2 * x) - 1) / (Math.Pow(Math.E, 2 * x) + 1)));
                    DerivativeactivationFunction = new Func<float, float>(x => 1 - (float)Math.Pow(ActivationFunction(x), 2));
                    break;
                case FunctionType.ReLu:
                    ActivationFunction = new Func<float, float>(x => (x > 0.0f ? x : 0.0f));
                    DerivativeactivationFunction = new Func<float, float>(x => (float)Math.Log(1 + Math.Exp(x))); // приближение
                    break;
            }
        }
    }
}
