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

            retval = IRecordDll.IRGetVersion(null, ref versionSize);
            Assert.AreEqual(IRErrorCode.IRE_BUFFER_TOO_SHORT, (IRErrorCode)retval);

            version = new byte[versionSize];
            retval = IRecordDll.IRGetVersion(version, ref versionSize);
            Assert.AreEqual(IRErrorCode.IRE_SUCCESS, (IRErrorCode)retval);
            Assert.AreEqual(versionSize - 1, IRecordUtil.CStringLength(version));
            Assert.AreEqual("0.1.0.0", IRecordUtil.FromUTF8(version));
        }
    }
}
