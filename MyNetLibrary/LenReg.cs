namespace MyNet
{
    public class LenReg : IRegularizer
    {
        private float alpha;
        private IRegularizer L1;
        private IRegularizer L2;

        public LenReg(float trust, float lambda)
        {
            alpha = trust;
            L1 = new L1Reg(lambda);
            L2 = new L2Reg(lambda);
        }

        public float GetReg(Layer layer)
        {
            return (alpha * L1.GetReg(layer)) + ((1 - alpha) * L2.GetReg(layer));
        }
    }
}
