namespace MyNet
{
    using System.Collections.Generic;
    using System.IO;
    using System.Text;

    internal abstract class ModelSaveLoader
    {
        internal static void SaveWeights(IList<Layer> layers, string path)
        {
            byte[] buf;
            StringBuilder sb;
            using (FileStream fs = new FileStream(path, FileMode.Create))
            {
                buf = Encoding.Default.GetBytes($"{layers.Count}\n");
                fs.Write(buf, 0, buf.Length);

                foreach (var l in layers)
                {
                    buf = Encoding.Default.GetBytes($"{l.N} {l.M}\n");
                    fs.Write(buf, 0, buf.Length);
                    for (int i = 0; i < l.M; i++)
                    {
                        sb = new StringBuilder($"{l.W0[i]} ");
                        for (int j = 0; j < l.N; j++)
                        {
                            sb.Append($"{l.W[i, j]} ");
                        }

                        buf = Encoding.Default.GetBytes($"{sb.ToString()}\n");
                        fs.Write(buf, 0, buf.Length);
                    }
                }
            }
        }

        internal static void LoadWeights(IList<Layer> layers, string path)
        {
            byte[] buf;
            string str;
            string[] lines;
            using (FileStream fs = new FileStream(path, FileMode.Open))
            {
                buf = new byte[fs.Length];
                fs.Read(buf, 0, (int)fs.Length);
                str = Encoding.Default.GetString(buf);
            }

            lines = str.Split('\n');
            int layersN = int.Parse(lines[0]);
            if (layers.Count != layersN)
            {
                return;
            }

            int l = 1;
            string[] temp;
            for (int i = 0; i < layersN; i++)
            {
                temp = lines[l].Split(' ');
                if (int.Parse(temp[0]) != layers[i].N || int.Parse(temp[1]) != layers[i].M)
                {
                    return;
                }

                l++;
                for (int j = 0; j < layers[i].M; l++, j++)
                {
                    temp = lines[l].Split(' ');
                    layers[i].W0[j] = float.Parse(temp[0]);
                    layers[i].Wn0[j] = layers[i].W0[j];
                    for (int k = 0; k < layers[i].N; k++)
                    {
                        layers[i].W[j, k] = float.Parse(temp[k + 1]);
                        layers[i].Wn[j, k] = layers[i].W[j, k];
                    }
                }
            }
        }
    }
}
