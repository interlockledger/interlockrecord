using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace InterlockRecord
{
    /// <summary>
    /// This class abstracts an InterlockRecord context.
    /// </summary>
    public class IRContext: IRBaseObject
    {

        public IRContext(int handle): base(handle)
        {
        }

        protected override bool IsParentDisposed()
        {
            return !IRecordLibrary.Initialized;
        }

        public override void Dispose()
        {
            if (!Disposed)
            {
                if (IRecordLibrary.Initialized)
                {
                    // TODO Call dispose here.
                    this.HandleDisposed = true;
                }
            }
        }


        #region Emergency Key
        public IREmergencyKey CreateEmergencyKey(IRKeyType keyType, int size)
        {
            throw new NotImplementedException();
        }

        public IREmergencyKey LoadEmergencyKey(byte [] serialized)
        {
            throw new NotImplementedException();
        }
        #endregion

        #region Root Template
        public IRRootTemplate CreateRootTemplate()
        {
            throw new NotImplementedException();
        }
        #endregion

        #region Instance State
        public IRInstanceState CreateInstanceState()
        {
            throw new NotImplementedException();
        }

        public IRInstanceState LoadInstanceState(byte [] serialized)
        {
            throw new NotImplementedException();
        }
        #endregion

        #region Blocks
        public IRBlock LoadBlock(byte [] serialized)
        {
            throw new NotImplementedException();
        }

        public IRBlock CreateRootBlock(IRRootTemplate template, IRInstanceState state)
        {
            throw new NotImplementedException();
        }

        public IRBlock CreateDataBlock(bool lockKey, IRBlock parent, UInt64 applicationId, byte [] payload)
        {
            throw new NotImplementedException();
        }
        #endregion

        #region Closing Records
        public IRBlock CloseRecord(IRBlock parent, UInt64 applicationId, IRClosingReason reason, string comments, IRBlock successor)
        {
            throw new NotImplementedException();
        }

        public IRBlock EmergencyCloseRecord(IRBlock parent, UInt64 applicationId, IREmergencyKey key, IRClosingReason reason, string comments, IRBlock successor)
        {
            throw new NotImplementedException();
        }
        #endregion


    }

}
