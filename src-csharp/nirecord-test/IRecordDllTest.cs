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
using System.Threading.Tasks;
using NUnit.Framework;
using InterlockRecord;
using InterlockRecord.Native;

namespace InterlockRecord.Tests
{
    public class IRecordDllTest
    {

        [Test]
        public void IRGetVersionIntTest()
        {
            int retval;
            int major = -1;
            int minor = -1;

            retval = IRecordDll.IRGetVersionInt(ref major, ref minor);
            Assert.AreEqual(IRErrorCode.IRE_SUCCESS, (IRErrorCode)retval);
            Assert.AreNotEqual(-1, major);
            Assert.AreNotEqual(-1, minor);
        }

        [Test]
        public void IRGetVersionTest()
        {
            int retval;
            byte[] version;
            int versionSize = 0;

            retval = IRecordDll.IRGetVersion( ref versionSize, null);
            Assert.AreEqual(IRErrorCode.IRE_BUFFER_TOO_SHORT, (IRErrorCode)retval);

            version = new byte[versionSize];
            retval = IRecordDll.IRGetVersion(ref versionSize, version);
            Assert.AreEqual(IRErrorCode.IRE_SUCCESS, (IRErrorCode)retval);
            Assert.AreEqual(versionSize - 1, IRecordUtil.CStringLength(version));
            Assert.AreEqual("0.1.0.0", IRecordUtil.FromUTF8(version));
        }
    }
}
