namespace MyNetProgram
{
    using MNSH = MyNet;
    using System;
    using System.Collections.Generic;
    using MNCPP = MyNetLibraryCppWrapper;

    public class Program
    {
        static void Main(string[] args)
        {
            MNCPP.Layer l = new MNCPP.Layer();
            Console.WriteLine(l.kek());
            Console.ReadKey();

            //Model model = new Model();

            //model.AddLayer(new Layer(2, 2, FunctionWrapper.FunctionType.BynarySigmoid));
            //model.AddLayer(new Layer(2, 1, FunctionWrapper.FunctionType.BynarySigmoid));

            //var l0 = new List<float> { 0.0f, 0.0f };
            //var l1 = new List<float> { 0.0f, 1.0f };
            //var l2 = new List<float> { 1.0f, 0.0f };
            //var l3 = new List<float> { 1.0f, 1.0f };
            //List<List<float>> inp = new List<List<float>>(4)
            //{
            //    l0,
            //    l1,
            //    l2,
            //    l3
            //};
            //List<List<float>> outL = new List<List<float>>(4)
            //{
            //    new List<float> { 0.0f },
            //    new List<float> { 1.0f },
            //    new List<float> { 1.0f },
            //    new List<float> { 0.0f }
            //};

            //model.TargetError = null;
            //model.MinDW = null;
            //model.MomentumCoefficient = 0.01f;

            //model.LambdaReg = 0.0000000001f;            

            ////model.Random = false;
            ////model.BatchSize = 100;
            ////Func<int, IList<float>> fInp = (x => x >= inp.Count ? null : inp[x]);
            ////Func<int, IList<float>> fOut = (x => x >= outL.Count ? null : outL[x]);

            //model.Random = true;
            //Func<int, IList<float>> fInp = (x => inp[x % inp.Count]);
            //Func<int, IList<float>> fOut = (x => outL[x % outL.Count]);

            //model.Train(1000000, 0.01f, fInp, fOut);

            //Console.WriteLine("TRAIN DONE");
            //Console.WriteLine($"0 xor 0 = {model.GetRes(l0)[0]}");
            //Console.WriteLine($"0 xor 1 = {model.GetRes(l1)[0]}");
            //Console.WriteLine($"1 xor 0 = {model.GetRes(l2)[0]}");
            //Console.WriteLine($"1 xor 1 = {model.GetRes(l3)[0]}");
            //Console.WriteLine("DONE");
            //model.SaveWeights("res.txt");
            //Console.ReadKey();
        }
    }
}
