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
            MNCPP.Model model = new MNCPP.Model();

            model.AddLayer(new MNCPP.Layer(2, 2, MNCPP.FunctionType.BynarySigmoid));
            model.AddLayer(new MNCPP.Layer(2, 1, MNCPP.FunctionType.BynarySigmoid));

            
            var l0 = new MNCPP.FloatArrayPointer(2); l0.SetValue(0, 0.0f); l0.SetValue(1, 0.0f);
            var l1 = new MNCPP.FloatArrayPointer(2); l1.SetValue(0, 0.0f); l1.SetValue(1, 1.0f);
            var l2 = new MNCPP.FloatArrayPointer(2); l2.SetValue(0, 1.0f); l2.SetValue(1, 0.0f);
            var l3 = new MNCPP.FloatArrayPointer(2); l3.SetValue(0, 1.0f); l3.SetValue(1, 1.0f);
            List<MNCPP.FloatArrayPointer> inp = new List<MNCPP.FloatArrayPointer>(4)
            {
                l0,
                l1,
                l2,
                l3
            };
            var o0 = new MNCPP.FloatArrayPointer(1); o0.SetValue(0, 0.0f);
            var o1 = new MNCPP.FloatArrayPointer(1); o1.SetValue(0, 1.0f);
            var o2 = new MNCPP.FloatArrayPointer(1); o2.SetValue(0, 1.0f);
            var o3 = new MNCPP.FloatArrayPointer(1); o3.SetValue(0, 0.0f);
            List<MNCPP.FloatArrayPointer> outL = new List<MNCPP.FloatArrayPointer>(4)
            {
                o0,
                o1,
                o2,
                o3
            };

            
            model.SetRandom(false);
            Func<int, MNCPP.FloatArrayPointer> fInp = (x => x < inp.Count ? inp[x] : null);
            Func<int, MNCPP.FloatArrayPointer> fOut = (x => x < outL.Count ? outL[x] : null);
            
            /*
            model.SetRandom(true);
            Func<int, MNCPP.FloatArrayPointer> fInp = (x => inp[x % inp.Count]);
            Func<int, MNCPP.FloatArrayPointer> fOut = (x => outL[x % outL.Count]);
            */

            model.SetLambdaReg(0.0f);
            model.SetMomentumCoefficient(0.0f);
            model.SetBatchSize(1000);

            model.Train(1000000, 0.1f, fInp, 2, fOut, 1);

            Console.WriteLine("TRAIN DONE");
            Console.WriteLine($"0 xor 0 = {model.GetRes(l0).GetValue(0)}");
            Console.WriteLine($"0 xor 1 = {model.GetRes(l1).GetValue(0)}");
            Console.WriteLine($"1 xor 0 = {model.GetRes(l2).GetValue(0)}");
            Console.WriteLine($"1 xor 1 = {model.GetRes(l3).GetValue(0)}");
            Console.WriteLine("DONE");

            model.SaveWeights("res.txt");
            

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
