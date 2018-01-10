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

        internal IRContext(int handle): base(handle)
        {
        }

        protected override bool IsDisposed()
        {
            return (!IRecordLibrary.Initialized) || (this.Handle == -1);
        }

        public override void Dispose()
        {
            if (!Disposed)
            {
                if (IRecordLibrary.Initialized)
                {
                    // TODO Call dispose here.
                    this.Handle = -1;
                }
            }
        }
    }

}
