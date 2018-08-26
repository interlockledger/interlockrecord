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

    public class IRRootTemplate : IRContextObject
    {

        public IRRootTemplate(IRContext parent, int handle): base(parent, handle)
        {
        }

        public string FriendlyName
        {
            private set;
            get;
        }

        public string Owner
        {
            private set;
            get;
        }

        public string Comment
        {
            private set;
            get;
        }

        public IRBlock ParentRootRecord
        {
            private set;
            get;
        }

        public Int64 NetworkId
        {
            private set;
            get;
        }

        public IREmergencyKey EmergencyKey
        {
            private set;
            get;
        }

        public void SetFriendlyName(string s)
        {
            throw new NotImplementedException();
        }

        public void SetOwner(string s)
        {
            throw new NotImplementedException();
        }

        public void SetComment(string s)
        {
            throw new NotImplementedException();
        }

        public void SetParent(IRBlock parentRootRecord)
        {
            throw new NotImplementedException();
        }

        public void SetNework(Int64 networkId)
        {
            throw new NotImplementedException();
        }

        public void SetEmergencyKey(IREmergencyKey emergencyKey)
        {
            throw new NotImplementedException();
        }

        public override void Dispose()
        {
            throw new NotImplementedException();
        }
    }
}
