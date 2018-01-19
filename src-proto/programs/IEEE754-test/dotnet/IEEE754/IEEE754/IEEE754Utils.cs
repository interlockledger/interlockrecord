using System;
namespace IEEE754
{
    /// <summary>
    /// This class implements IEEE754 utility functions.
    /// </summary>
    public class IEEE754Utils
    {
        /// <summary>
        /// Ve value of PI as a single precision value (binary32).
        /// </summary>
        internal const float PI = 3.1415927410f;

        /// <summary>
        /// The expected serialization of PI in big endian format.
        /// </summary>
        internal static readonly byte[] PI_BE = new byte[] { 0x40, 0x49, 0x0f, 0xdb };

        /// <summary>
        /// The expected serialization of PI in little endian format.
        /// </summary>
        internal static readonly byte[] PI_LE = new byte[] { 0xdb, 0x0f, 0x49, 0x40 };

        /// <summary>
        /// Gets a value indicating whether this machine implements IEEE754 Big Endian.
        /// </summary>
        /// <value><c>true</c> if big endian; otherwise, <c>false</c>.</value>
        public static bool BigEndian 
        {
            private set;
            get;
        }

        /// <summary>
        /// Gets a value indicating whether this machine implements IEEE754 Little Endian.
        /// </summary>
        /// <value><c>true</c> if little endian; otherwise, <c>false</c>.</value>
        public static bool LittleEndian
        {
            private set;
            get;
        }

        /// <summary>
        /// Returns true if the floating point format of this machine is indeed IEEE754.
        /// </summary>
        /// <remarks>
        /// This property returns false if the machine is neither big endian nor
        /// little endian.
        /// </remarks>
        /// <value><c>true</c> if the FPU is IEEE754; otherwise, <c>false</c>.</value>
        public static bool IEEE754
        {
            get 
            {
                return LittleEndian != BigEndian;
            }
        }

        /// <summary>
        /// Verifies if this machine is using the big endian format for IEEE754.
        /// </summary>
        /// <returns><c>true</c>, if big endian was ised, <c>false</c> otherwise.</returns>
        private static bool IsBigEndian()
        {
            return (BitConverter.ToSingle(PI_BE, 0) == PI);
        }

        /// <summary>
        /// Verifies if this machine is using the little endian format for IEEE754.
        /// </summary>
        /// <returns><c>true</c>, if little endian was ised, <c>false</c> otherwise.</returns>
        private static bool IsLittleEndian()
        {
            return (BitConverter.ToSingle(PI_LE, 0) == PI);
        }

        /// <summary>
        /// Checks if a byte reversal is required.
        /// </summary>
        /// <returns><c>true</c>, if revert was musted, <c>false</c> otherwise.</returns>
        /// <param name="bigEndian">If set to <c>true</c> big endian.</param>
        internal static bool MustRevert(bool bigEndian)
        {
            return bigEndian != BigEndian;
        }

        /// <summary>
        /// Initializes the internal state of this class.
        /// </summary>
        static IEEE754Utils(){
            BigEndian = IsBigEndian();
            LittleEndian = IsLittleEndian();
        }

        /// <summary>
        /// Reverts the bytes of the specified byte array.
        /// </summary>
        /// <param name="b">The source byte array.</param>
        internal static void Revert(byte [] b)
        {
            if (b.Length > 0) {
                int start = 0;
                int end = b.Length - 1;
                while (start <= end)
                {
                    byte t = b[start];
                    b[start] = b[end];
                    b[end] = t;
                    start++;
                    end--;
                }
            }
        }

        /// <summary>
        /// Creates copy of the byte array segment but with its bytes reverted.
        /// </summary>
        /// <returns>The copy.</returns>
        /// <param name="src">Source byte array.</param>
        /// <param name="start">The starting position.</param>
        /// <param name="count">The number of bytes to copy.</param>
        internal static byte [] ReverseCopy(byte[] src, int start, int count)
        {
            byte[] ret;

            ret = new byte[count];
            for (int i = 0, j = start + count - 1; i < count; i++, j--)
            {
                ret[i] = src[j];
            }
            return ret;
        }

        /// <summary>
        /// Serializes the given float value into an array of bytes.
        /// </summary>
        /// <returns>The serialized value.</returns>
        /// <param name="v">The value.</param>
        /// <param name="bigEndian">If set to <c>true</c> for big endian.</param>
        public static byte [] Serialize(float v, bool bigEndian)
        {
            byte[] tmp;
            tmp = BitConverter.GetBytes(v);
            if (MustRevert(bigEndian))
            {
                IEEE754Utils.Revert(tmp);
            }
            return tmp;
        }

        /// <summary>
        /// Serializes the given double value into an array of bytes.
        /// </summary>
        /// <returns>The serialized value.</returns>
        /// <param name="v">The value.</param>
        /// <param name="bigEndian">If set to <c>true</c> for big endian.</param>
        public static byte[] Serialize(double v, bool bigEndian)
        {
            byte[] tmp;
            tmp = BitConverter.GetBytes(v);
            if (MustRevert(bigEndian))
            {
                IEEE754Utils.Revert(tmp);
            }
            return tmp;
        }

        /// <summary>
        /// Unserializes a float value.
        /// </summary>
        /// <remarks>
        /// The conversion will require at least 4 bytes.
        /// </remarks>
        /// <returns>The unserialized value.</returns>
        /// <param name="buff">The input buffer.</param>
        /// <param name="start">The start position.</param>
        /// <param name="bigEndian">If set to <c>true</c> big endian.</param>
        public static float UnserializeSingle(byte [] buff, int start, bool bigEndian)
        {
            if (MustRevert(bigEndian))
            {
                return BitConverter.ToSingle(ReverseCopy(buff, start, 4), 0);
            }
            else
            {
                return BitConverter.ToSingle(buff, start);
            }
        }

        /// <summary>
        /// Unserializes a double value.
        /// </summary>
        /// <remarks>
        /// The conversion will require at least 8 bytes.
        /// </remarks>
        /// <returns>The unserialized value.</returns>
        /// <param name="buff">The input buffer.</param>
        /// <param name="start">The start position.</param>
        /// <param name="bigEndian">If set to <c>true</c> big endian.</param>
        public static double UnserializeDouble(byte[] buff, int start, bool bigEndian)
        {
            if (MustRevert(bigEndian))
            {
                return BitConverter.ToDouble(ReverseCopy(buff, start, 8), 0);
            }
            else
            {
                return BitConverter.ToDouble(buff, start);
            }
        }
    }
}
