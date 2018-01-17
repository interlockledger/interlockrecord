using System;

namespace IEEE754
{
    class MainClass
    {   
        public static void Main(string[] args)
        {
            

            byte[] b = BitConverter.GetBytes(3.1415927410f);

            Console.Out.WriteLine(BitConverter.IsLittleEndian);
            Console.Out.WriteLine(b[0]);
            Console.Out.WriteLine(b[1]);
            Console.Out.WriteLine(b[2]);
            Console.Out.WriteLine(b[3]);
        }
    }
}
