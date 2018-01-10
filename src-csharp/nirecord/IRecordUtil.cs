using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace InterlockRecord
{
    /// <summary>
    /// This class implements utility functions used by this library.
    /// </summary>
    public class IRecordUtil
    {

        /// <summary>
        /// Converts a string into a null terminated UTF8 string.
        /// </summary>
        /// <param name="s">The string to be converted.</param>
        /// <returns>The byte array that contains the null terminated UTF8 string.</returns>
        public static byte[] ToUTF8(string s)
        {
            int len = Encoding.UTF8.GetByteCount(s);
            byte[] ret = new byte[len + 1];
            Encoding.UTF8.GetBytes(s, 0, s.Length, ret, 0);
            ret[ret.Length - 1] = 0;
            return ret;
        }

        /// <summary>
        /// Returns the length of a null terminated string.
        /// </summary>
        /// <param name="utf8">The null terminated string.</param>
        /// <returns>The lenght of the string or -1 if the string is not null terminated.</returns>
        public static int CStringLength(byte[] utf8)
        {
            return CStringLength(utf8, 0);
        }

        /// <summary>
        /// Returns the length of a null terminated string.
        /// </summary>
        /// <param name="utf8">The null terminated string.</param>
        /// <param name="index">The initial index.</param>
        /// <returns>The lenght of the string or -1 if the string is not null terminated.</returns>
        public static int CStringLength(byte[] utf8, int index)
        {
            try
            {
                int len = index;
                while (utf8[len] != 0)
                {
                    len++;
                }
                return (len - index);
            } catch (IndexOutOfRangeException e)
            {
                return -1;
            }
        }

        /// <summary>
        /// Converts a null terminated string to a string.
        /// </summary>
        /// <param name="utf8">A null terminated UTF8 string.</param>
        /// <returns>The string.</returns>
        public static string FromUTF8(byte[] utf8)
        {
            return FromUTF8(utf8, 0, CStringLength(utf8));
        }

        /// <summary>
        /// Converts a UTF8 data into a string.
        /// </summary>
        /// <param name="utf8">The UTF8 encoded data.</param>
        /// <param name="index">The initial index.</param>
        /// <param name="count">The number of bytes inside utf8.</param>
        /// <returns>The string.</returns>        
        public static string FromUTF8(byte[] utf8, int index, int count)
        {
            if (count < 0)
            {
                throw new ArgumentException("Invalid size.");
            }

            return Encoding.UTF8.GetString(utf8, index, count);
        }
    }
}
