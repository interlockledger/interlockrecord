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
        public static extern int IRGetVersion(byte[] version, ref int versionSize);

        [DllImport("irecord.dll", EntryPoint = "IRGetVersionInt", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        public static extern int IRGetVersionInt(ref int major, ref int minor);

        [DllImport("irecord.dll", EntryPoint = "IRBlockDispose", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        public static extern int IRBlockDispose(IRContext context, int hBlock);

        [DllImport("irecord.dll", EntryPoint = "IRBlockLoad", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        public static extern int IRBlockLoad(IRContext context, int blockSize, byte[] block, ref int hBlock);

        [DllImport("irecord.dll", EntryPoint = "IRBlockParameter", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        public static extern int IRBlockParameter(IRContext context, int hBlock, int param, ref ulong value);

        [DllImport("irecord.dll", EntryPoint = "IRBlockSerialize", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        public static extern int IRBlockSerialize(IRContext context, int hBlock, ref int buffSize, byte[] buff);

        [DllImport("irecord.dll", EntryPoint = "IRCheckEmergencyClosing", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        public static extern int IRCheckEmergencyClosing(IRContext context, int hBlock, int hRootBlock);

        [DllImport("irecord.dll", EntryPoint = "IRCheckParent", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        public static extern int IRCheckParent(IRContext context, int hBlock, int hParentBlock);

        [DllImport("irecord.dll", EntryPoint = "IRCheckRoot", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        public static extern int IRCheckRoot(IRContext context, int hRootBlock);

        [DllImport("irecord.dll", EntryPoint = "IRClose", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        public static extern int IRClose(IRContext context, int hState, int hParentBlock, int reason, byte[] comments, int hSucessor, ref int hBlock);

        [DllImport("irecord.dll", EntryPoint = "IRContextCreate", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        public static extern int IRContextCreate(byte[] configFile, ref IRContext context);

        [DllImport("irecord.dll", EntryPoint = "IRContextDispose", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        public static extern int IRContextDispose(IRContext context);

        [DllImport("irecord.dll", EntryPoint = "IRDataBlockAdd", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        public static extern int IRDataBlockAdd(IRContext context, int hState, int lockKey, int hParentBlock, ulong applicationId, int payloadSize, byte[] payload, ref int hBlock);

        [DllImport("irecord.dll", EntryPoint = "IREmergencyClose", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        public static extern int IREmergencyClose(IRContext context, int hState, int hParentBlock, int hEmerngencyKey, int reason, byte[] comments, ref int hBlock);

        [DllImport("irecord.dll", EntryPoint = "IREmergencyKeyCreate", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        public static extern int IREmergencyKeyCreate(IRContext context, int type, int size, ref int hKey);

        [DllImport("irecord.dll", EntryPoint = "IREmergencyKeyDispose", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        public static extern int IREmergencyKeyDispose(IRContext context, int hKey);

        [DllImport("irecord.dll", EntryPoint = "IREmergencyKeyLoad", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        public static extern int IREmergencyKeyLoad(IRContext context, int buffSize, byte[] buff, ref int hKey);

        [DllImport("irecord.dll", EntryPoint = "IREmergencyKeySerialize", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        public static extern int IREmergencyKeySerialize(IRContext context, int hKey, ref byte[] buffSize, ref byte[] buff);

        [DllImport("irecord.dll", EntryPoint = "IRInstanceStateCreate", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        public static extern int IRInstanceStateCreate(IRContext context, ref int hState);

        [DllImport("irecord.dll", EntryPoint = "IRInstanceStateDispose", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        public static extern int IRInstanceStateDispose(IRContext context, int hState);

        [DllImport("irecord.dll", EntryPoint = "IRInstanceStateLoad", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        public static extern int IRInstanceStateLoad(IRContext context, int stateSize, byte[] state, ref int hState);

        [DllImport("irecord.dll", EntryPoint = "IRInstanceStateSerialize", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        public static extern int IRInstanceStateSerialize(IRContext context, int hState, ref byte[] buffSize, ref byte[] buff);

        [DllImport("irecord.dll", EntryPoint = "IRInstanceStateSetParam", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        public static extern int IRInstanceStateSetParam(IRContext context, ref int hState, int param, int value);

        [DllImport("irecord.dll", EntryPoint = "IRRootBlockCreate", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        public static extern int IRRootBlockCreate(IRContext context, int hTemplate, int hState, ref int hBlock);

        [DllImport("irecord.dll", EntryPoint = "IRRootTemplateCreate", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        public static extern int IRRootTemplateCreate(IRContext context, ref int hTemplate);

        [DllImport("irecord.dll", EntryPoint = "IRRootTemplateDispose", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        public static extern int IRRootTemplateDispose(IRContext context, int hTemplate);

        [DllImport("irecord.dll", EntryPoint = "IRRootTemplateParam", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        public static extern int IRRootTemplateParam(IRContext context, int hTemplate, int param, byte[] value);

        [DllImport("irecord.dll", EntryPoint = "IRRootTemplateSetEmergencyKey", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        public static extern int IRRootTemplateSetEmergencyKey(IRContext context, int hTemplate, int hKey);

        [DllImport("irecord.dll", EntryPoint = "IRRootTemplateSetNetwork", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        public static extern int IRRootTemplateSetNetwork(IRContext context, int hTemplate, ulong networkID);

        [DllImport("irecord.dll", EntryPoint = "IRRootTemplateSetParent", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        public static extern int IRRootTemplateSetParent(IRContext context, int hTemplate, int parentRootRecord);

    }
}
