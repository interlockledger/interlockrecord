using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace InterlockRecord
{
    public abstract class IRContextObject: IRBaseObject
    {
        private readonly IRContext parent;

        public IRContextObject(IRContext parent, int handle): base(handle)
        {

        }

        protected override bool IsParentDisposed()
        {
            return parent.Disposed;
        }
    }
}
