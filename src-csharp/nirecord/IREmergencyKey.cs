using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace InterlockRecord
{
    public class IREmergencyKey: IRContextObject
    {

        public IREmergencyKey(IRContext parent, int handle): base(parent, handle)
        {
        }

        public byte[] Serialize()
        {
            throw new NotImplementedException();
        }

        public override void Dispose()
        {
            throw new NotImplementedException();
        }
    }
}
