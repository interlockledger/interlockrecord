/*
 * Copyright (c) 2017-2018 InterlockLedger Network
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using InterlockRecord.Native;

namespace InterlockRecord
{

    /// <summary>
    /// This class implements a .Net friendly wrapper to the InterlockRecord native library. It manages
    /// most of the threading issues and provides an easy to use abstraction on top of the library.
    /// </summary>
    /// <remarks>
    /// Do not mix calls from this class and direct calls to the native functions declared inside
    /// IRecordDll because direct calls may lead to undefined behavior of this wrapper.
    /// </remarks>
    public class IRecordLibrary
    {
        private static Object myLock = new object();

        private static volatile bool initialized;

        public static bool Initialized
        {
            get
            {
                return initialized;
            }
        }

        public void Initialize()
        {
            lock (myLock)
            {
                if (Initialized)
                {
                    throw new InvalidOperationException("The library is already initalized.");
                }
                IRErrorCode retval = (IRErrorCode)IRecordDll.IRInitialize();
                if (retval == IRErrorCode.IRE_SUCCESS)
                {
                    initialized = true;
                }
                else
                {
                    throw new IRException(retval, "IRInitialize() failed.");
                }
            }
        }

        public void Deinitialize()
        {
            EnsureInitialized();
            lock (myLock)
            {
                IRErrorCode retval = (IRErrorCode)IRecordDll.IRDeinitialize();
                if (retval == IRErrorCode.IRE_SUCCESS)
                {
                    initialized = false;
                } else
                {
                    throw new IRException(retval, "IRDeinitialize() failed.");
                }
            }
        }

        /// <summary>
        /// Ensures that the library is initialized. It throws an exception if the library is not properly initialized.
        /// </summary>
        /// <exception cref="InvalidOperationException">If the library is not initialized.</exception>
        private static void EnsureInitialized()
        {
            if (!Initialized)
            {
                throw new InvalidOperationException("The library is not initalized.");
            }
        }

        /// <summary>
        /// Returns the version string of the library.
        /// </summary>
        /// <remarks>
        /// This method can be executed even if the library is not initialized yet.
        /// </remarks>
        /// <returns>The version string.</returns>
        /// <exception cref="IRException">In case of error.</exception>
        public static string GetVersion()
        {
            int versionSize;
            IRErrorCode retval;
            byte[] versionBin;

            versionSize = 0;
            retval = (IRErrorCode)IRecordDll.IRGetVersion(ref versionSize, null);
            if (retval != IRErrorCode.IRE_BUFFER_TOO_SHORT)
            {
                throw new IRException(retval, "Unexpected error code.");
            }
            versionSize = versionSize + 1;
            versionBin = new byte[versionSize];
            retval = (IRErrorCode)IRecordDll.IRGetVersion(ref versionSize, versionBin);
            if (retval == IRErrorCode.IRE_SUCCESS)
            {
                return IRecordUtil.FromUTF8(versionBin);
            } else
            {
                throw new IRException(retval);
            }
        }

        public static void GetVersion(ref int major, ref int minor)
        {
            throw new NotImplementedException();
        }
    }
}
