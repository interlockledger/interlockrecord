using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using NUnit.Framework;
using InterlockRecord;

namespace InterlockRecord.Tests
{
    
    public class IRecordUtilTest
    {
        private static readonly string[] SAMPLES =
        {
            "abcdefg",
            "cabeça",
            "euro \u20AC",
        };

        private static void FillRandomNonZero(byte [] b)
        {
            Random rand = new Random();

            for (int i = 0; i < b.Length; i++)
            {
                b[i] = (byte)(rand.Next(255) + 1);
            }
        }

        [Test]
        public void ToUTF8Test()
        {
            foreach(string s in SAMPLES)
            {
                byte[] ret = IRecordUtil.ToUTF8(s);
                byte[] tmp = Encoding.UTF8.GetBytes(s);
                byte[] exp = new byte[tmp.Length + 1];
                Assert.AreEqual(exp.Length, ret.Length);
                tmp.CopyTo(exp, 0);
                Assert.True(exp.SequenceEqual(ret));
            }
        }

        [Test]
        public void CStringLengthByteArrayTest()
        {
            Random rand = new Random();

            for (int i = 0; i < 16; i++)
            {
                // The null terminated string
                byte[] s = new byte[i+1];
                for (int j = 0; j < i; j++)
                {
                    s[j] = (byte)(rand.Next(255) + 1);
                }
                Assert.AreEqual(i, IRecordUtil.CStringLength(s));
            }
        }

        [Test]
        public void CStringLengthByteArrayIntTest()
        {
            for (int i = 2; i < 16; i++)
            {
                // The null terminated string
                byte[] s = new byte[i + 1];
                FillRandomNonZero(s);
                s[i] = 0;
                Assert.AreEqual(i - 1, IRecordUtil.CStringLength(s, 1));
            }
        }

        [Test]
        public void FromUTF8ByteArrayTest()
        {
            foreach (string s in SAMPLES)
            {
                byte[] utf8 = IRecordUtil.ToUTF8(s);
                string ret = IRecordUtil.FromUTF8(utf8);
                Assert.AreEqual(s, ret);
            }
        }

        [Test]
        public void FromUTF8ByteArrayIntIntTest()
        {
            foreach (string s in SAMPLES)
            {
                byte[] tmp = IRecordUtil.ToUTF8(s);
                byte[] utf8 = new byte[tmp.Length + 2];
                tmp.CopyTo(utf8, 1);

                string ret = IRecordUtil.FromUTF8(utf8, 1, tmp.Length - 1);
                Assert.AreEqual(s, ret);
            }
        }
    }
}
