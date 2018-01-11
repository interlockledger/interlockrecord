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
