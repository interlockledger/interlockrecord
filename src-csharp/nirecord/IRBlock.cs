using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace InterlockRecord
{
    public class IRBlock : IRContextObject
    {

        public IRBlock(IRContext parent, int handle): base(parent, handle)
        {
        }

        public byte [] Serialize()
        {
            throw new NotImplementedException();
        }

        public override void Dispose()
        {
            throw new NotImplementedException();
        }

        public bool CheckRoot()
        {
            throw new NotImplementedException();
        }

        public bool CheckParent(IRBlock parent)
        {
            throw new NotImplementedException();
        }
    }
}
