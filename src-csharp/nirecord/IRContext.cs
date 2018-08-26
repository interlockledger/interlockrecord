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
