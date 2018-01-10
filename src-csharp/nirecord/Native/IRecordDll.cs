using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

namespace InterlockRecord.Native
{
    /// <summary>
    /// This class implements the declaration of all functions implemented by the InterlockRecord
    /// native library.
    /// </summary>
    /// <remarks>
    /// This class grants low level access to the native library and should not be used directly from
    /// managed applications. Use the IRecordLibrary class instead.
    /// </remarks>
    /// <see cref="IRecordLibrary"/>
    public class IRecordDll
    {
        /// <summary>
        /// Initializes the library. It is used to prepare the library for the first use.
        /// It must be called only once after the library is loaded and before the first
        /// use of the library.
        /// </summary>
        /// <returns>IRErrorCode.IRE_SUCCESS on success or other error code in case of failure.</returns>
        [DllImport("irecord.dll", EntryPoint="IRInitialize", CallingConvention=CallingConvention.Cdecl, CharSet=CharSet.Ansi)]
        public static extern int IRInitialize();

        [DllImport("irecord.dll", EntryPoint = "IRDeinitialize", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        public static extern int IRDeinitialize();

        [DllImport("irecord.dll", EntryPoint = "IRGetVersion", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        public static extern int IRGetVersion(byte [] version, ref int versionSize);

        [DllImport("irecord.dll", EntryPoint = "IRGetVersionInt", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        public static extern int IRGetVersionInt(ref int major, ref int minor);

    }
}
