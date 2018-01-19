using System;

namespace IEEE754
{
    class MainClass
    {   

        public static void Main(string[] args)
        {
            byte[] b1 = new byte[]{
                    0x01, 0x23, 0x45, 0x67, 
                    0x89, 0xAB, 0xCD, 0xEF};

            byte[] b2 = new byte[]{
                    0xEF, 0xCD, 0xAB, 0x89,
                    0x67, 0x45, 0x23, 0x01};

            Console.Out.WriteLine(BitConverter.ToDouble(b1, 0));
            Console.Out.WriteLine(BitConverter.ToDouble(b2, 0));
        }
    }
}
