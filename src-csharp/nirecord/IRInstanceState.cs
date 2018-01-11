using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace InterlockRecord
{
    public class IRInstanceState : IRContextObject
    {

        public IRInstanceState(IRContext parent, int handle): base(parent, handle)
        {
        }


        public string Serialize()
        {
            throw new NotImplementedException();
        }

        public override void Dispose()
        {
            throw new NotImplementedException();
        }
    }
}
