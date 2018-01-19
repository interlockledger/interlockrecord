using System;
using NUnit.Framework;

namespace IEEE754
{
    [TestFixture]
    public class IEEE754UtilsTest
    {

        public static void ArrayEquals(byte [] expected, byte [] actual)
        {
            Assert.AreEqual(expected.Length, actual.Length);
            for (int i = 0; i < expected.Length; i++)
            {
                Assert.AreEqual(expected[i], actual[i]);
            }
        }

        [Test]
        public void TestBigEndian()
        {
            Assert.AreNotEqual(BitConverter.IsLittleEndian, IEEE754Utils.BigEndian);
        }

        [Test]
        public void TestLittleEndian()
        {
            Assert.AreEqual(BitConverter.IsLittleEndian, IEEE754Utils.LittleEndian);
        }

        [Test]
        public void TestIEEE754()
        {
            Assert.AreEqual(IEEE754Utils.BigEndian != IEEE754Utils.LittleEndian,
                            IEEE754Utils.IEEE754);
        }

        [Test]
        public void TestMustRevert()
        {
            Assert.AreEqual(IEEE754Utils.BigEndian, IEEE754Utils.MustRevert(false));
            Assert.AreEqual(IEEE754Utils.LittleEndian, IEEE754Utils.MustRevert(true));
        }

        [Test]
        public void TestRevert()
        {

            for (int size = 0; size <= 16; size++)
            {
                byte[] src = new byte[size];
                byte[] exp = new byte[size];
                for (int i = 0; i < size; i++) 
                {
                    src[i] = (byte)i;
                    exp[i] = (byte)(size - i - 1);
                }
                IEEE754Utils.Revert(src);
                ArrayEquals(exp, src);
            }
        }

        [Test]
        public void TestReverseCopy()
        {
            byte[] src = new byte[]{ 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06 };

            byte[] exp = new byte[]{};
            byte[] actual = IEEE754Utils.ReverseCopy(src, 0, 0);
            Assert.AreEqual(0, actual.Length);

            exp = new byte[] { 0x00 };
            actual = IEEE754Utils.ReverseCopy(src, 0, 1);
            ArrayEquals(exp, actual);

            exp = new byte[] { 0x01 };
            actual = IEEE754Utils.ReverseCopy(src, 1, 1);
            ArrayEquals(exp, actual);

            exp = new byte[] { 0x02, 0x01 };
            actual = IEEE754Utils.ReverseCopy(src, 1, 2);
            ArrayEquals(exp, actual);

            exp = new byte[] { 0x03, 0x02, 0x01 };
            actual = IEEE754Utils.ReverseCopy(src, 1, 3);
            ArrayEquals(exp, actual);

            exp = new byte[] { 0x04, 0x03, 0x02, 0x01 };
            actual = IEEE754Utils.ReverseCopy(src, 1, 4);
            ArrayEquals(exp, actual);
        }

        [Test]
        public void TestSerializeFloat()
        {
            ArrayEquals(new byte[] { 0x00, 0x00, 0x00, 0x00 },
                        IEEE754Utils.Serialize(0f, true));
            ArrayEquals(new byte[] { 0x80, 0x00, 0x00, 0x00 },
                        IEEE754Utils.Serialize(-0f, true));
            ArrayEquals(new byte[] { 0x3f, 0x80, 0x00, 0x00 },
                        IEEE754Utils.Serialize(1f, true));
            ArrayEquals(new byte[] { 0xc0, 0x00, 0x00, 0x00 },
                        IEEE754Utils.Serialize(-2f, true));
            ArrayEquals(new byte[] { 0x40, 0x49, 0x0f, 0xdb },
                        IEEE754Utils.Serialize(3.1415927410f, true));

            ArrayEquals(new byte[] { 0x00, 0x00, 0x00, 0x00 },
                        IEEE754Utils.Serialize(0f, false));
            ArrayEquals(new byte[] { 0x00, 0x00, 0x00, 0x80 },
                        IEEE754Utils.Serialize(-0f, false));
            ArrayEquals(new byte[] { 0x00, 0x00, 0x80, 0x3f },
                        IEEE754Utils.Serialize(1f, false));
            ArrayEquals(new byte[] { 0x00, 0x00, 0x00, 0xc0 },
                        IEEE754Utils.Serialize(-2f, false));
            ArrayEquals(new byte[] { 0xdb, 0x0f, 0x49, 0x40 },
                        IEEE754Utils.Serialize(3.1415927410f, false));
        }

        [Test]
        public void TestSerializeDouble()
        {
            ArrayEquals(new byte[] { 
                            0x00, 0x00, 0x00, 0x00,
                            0x00, 0x00, 0x00, 0x00 },
                        IEEE754Utils.Serialize(0d, true));
            ArrayEquals(new byte[] { 
                            0x80, 0x00, 0x00, 0x00,
                            0x00, 0x00, 0x00, 0x00},
                        IEEE754Utils.Serialize(-0d, true));
            ArrayEquals(new byte[] {
                            0x01, 0x23, 0x45, 0x67,
                            0x89, 0xAB, 0xCD, 0xEF},
                        IEEE754Utils.Serialize(
                            BitConverter.Int64BitsToDouble(0x0123456789ABCDEFL), true));

            ArrayEquals(new byte[] {
                            0x00, 0x00, 0x00, 0x00,
                            0x00, 0x00, 0x00, 0x00 },
                        IEEE754Utils.Serialize(0d, false));
            ArrayEquals(new byte[] {
                            0x00, 0x00, 0x00, 0x00,
                            0x00, 0x00, 0x00, 0x80},
                        IEEE754Utils.Serialize(-0d, false));
            ArrayEquals(new byte[] {
                            0xEF, 0xCD, 0xAB, 0x89,
                            0x67, 0x45, 0x23, 0x01},
                        IEEE754Utils.Serialize(BitConverter.Int64BitsToDouble(0x0123456789ABCDEFL), false));
        }

        [Test]
        public void TestUnserializeSingle()
        {
            Assert.AreEqual(3.1415927410f,
                        IEEE754Utils.UnserializeSingle(new byte[] {
                            0x40, 0x49, 0x0f, 0xdb }, 0, true));

            Assert.AreEqual(3.1415927410f,
                        IEEE754Utils.UnserializeSingle(new byte[] {
                            0x00, 0x40, 0x49, 0x0f, 0xdb, 0x00 }, 1, true));

            Assert.AreEqual(3.1415927410f,
                        IEEE754Utils.UnserializeSingle(new byte[] {
                            0xdb, 0x0f, 0x49, 0x40 }, 0, false));

            Assert.AreEqual(3.1415927410f,
                        IEEE754Utils.UnserializeSingle(new byte[] {
                            0x00, 0xdb, 0x0f, 0x49, 0x40, 0x00 }, 1, false));
        }


        [Test]
        public void TestUnserializeDouble()
        {
            Assert.AreEqual(BitConverter.Int64BitsToDouble(0x0123456789ABCDEFL),
                        IEEE754Utils.UnserializeDouble(new byte[] {
                            0x01, 0x23, 0x45, 0x67,
                            0x89, 0xAB, 0xCD, 0xEF }, 0, true));

            Assert.AreEqual(BitConverter.Int64BitsToDouble(0x0123456789ABCDEFL),
                        IEEE754Utils.UnserializeDouble(new byte[] {
                            0x00, 0x01, 0x23, 0x45, 0x67,
                            0x89, 0xAB, 0xCD, 0xEF, 0x00 }, 1, true));

            Assert.AreEqual(BitConverter.Int64BitsToDouble(0x0123456789ABCDEFL),
                        IEEE754Utils.UnserializeDouble(new byte[] {
                            0xEF, 0xCD, 0xAB, 0x89,
                            0x67, 0x45, 0x23, 0x01 }, 0, false));

            Assert.AreEqual(BitConverter.Int64BitsToDouble(0x0123456789ABCDEFL),
                        IEEE754Utils.UnserializeDouble(new byte[] {
                            0x00, 0xEF, 0xCD, 0xAB, 0x89,
                            0x67, 0x45, 0x23, 0x01, 0x00 }, 1, false));
        }
    }
}
