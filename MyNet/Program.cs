namespace MyNetProgram
{
    using MyNet;
    using System;
    using System.Collections.Generic;

    public class Program
    {
        static void Main(string[] args)
        {
            Model model = new Model();

            model.AddLayer(new Layer(2, 2, FunctionWrapper.FunctionType.BynarySigmoid));
            model.AddLayer(new Layer(2, 1, FunctionWrapper.FunctionType.BynarySigmoid));

            var l0 = new List<float> { 0.0f, 0.0f };
            var l1 = new List<float> { 0.0f, 1.0f };
            var l2 = new List<float> { 1.0f, 0.0f };
            var l3 = new List<float> { 1.0f, 1.0f };
            List<List<float>> inp = new List<List<float>>(4)
            {
                l0,
                l1,
                l2,
                l3
            };
            List<List<float>> outL = new List<List<float>>(4)
            {
                new List<float> { 0.0f },
                new List<float> { 1.0f },
                new List<float> { 1.0f },
                new List<float> { 0.0f }
            };

            model.TargetError = null;
            model.MinDW = null;
            model.MomentumCoefficient = 0.0f;
            Console.WriteLine(model.MomentumCoefficient);

            //model.Regularizer = null;
            model.Regularizer = new LenReg(0.5f, 0.0006f); //работает? да ну бред

            //model.AddLayer(new Layer(1, 1, Layer.FunctionType.BynarySigmoid));
            //List<List<float>> outL = new List<List<float>>(10);
            //List<List<float>> inp = new List<List<float>>(10);
            //var l0 = new List<float> { 0.0f }; outL.Add(new List<float> { 0.0f });
            //var l1 = new List<float> { 0.6f }; outL.Add(new List<float> { 1.0f });
            //var l2 = new List<float> { 0.4f }; outL.Add(new List<float> { 0.0f });
            //var l3 = new List<float> { 0.5f }; outL.Add(new List<float> { 1.0f });
            //var l4 = new List<float> { 0.49f }; outL.Add(new List<float> { 0.0f });
            //var l5 = new List<float> { 0.1f }; outL.Add(new List<float> { 0.0f });
            //var l6 = new List<float> { 0.7f }; outL.Add(new List<float> { 1.0f });
            //var l7 = new List<float> { 0.8f }; outL.Add(new List<float> { 1.0f });
            //var l8 = new List<float> { 0.9f }; outL.Add(new List<float> { 1.0f });
            //var l9 = new List<float> { 0.3f }; outL.Add(new List<float> { 0.0f });
            //inp.Add(l0);
            //inp.Add(l1);
            //inp.Add(l2);
            //inp.Add(l3);
            //inp.Add(l4);
            //inp.Add(l5);
            //inp.Add(l6);
            //inp.Add(l7);
            //inp.Add(l8);
            //inp.Add(l9);
            //Func<int, IList<float>> fInp = (x => x >= inp.Count ? null : inp[x]);
            //Func<int, IList<float>> fOut = (x => x >= outL.Count ? null : outL[x]);

            //model.Random = false;
            //model.BatchSize = 100;
            //Func<int, IList<float>> fInp = (x => x >= inp.Count ? null : inp[x]);
            //Func<int, IList<float>> fOut = (x => x >= outL.Count ? null : outL[x]);

            model.Random = true;
            Func<int, IList<float>> fInp = (x => inp[x % inp.Count]);
            Func<int, IList<float>> fOut = (x => outL[x % outL.Count]);

            model.Train(1000000, 0.01f, fInp, fOut);
            //model.Load("res.txt");

            Console.WriteLine("TRAIN DONE");
            Console.WriteLine($"0 xor 0 = {model.GetRes(l0)[0]}");
            Console.WriteLine($"0 xor 1 = {model.GetRes(l1)[0]}");
            Console.WriteLine($"1 xor 0 = {model.GetRes(l2)[0]}");
            Console.WriteLine($"1 xor 1 = {model.GetRes(l3)[0]}");
            Console.WriteLine("DONE");
            model.SaveWeights("res.txt");
            Console.ReadKey();
        }
    }
}
