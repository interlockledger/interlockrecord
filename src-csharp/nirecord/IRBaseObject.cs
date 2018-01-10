using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace InterlockRecord
{
    public abstract class IRBaseObject : IDisposable
    {
        public int Handle
        {
            protected set;
            get;
        }

        public bool Disposed
        {
            get 
            {
                return this.IsDisposed();
            }
        }

        internal IRBaseObject(int handle)
        {
            this.Handle = handle;
        }

        ~IRBaseObject()
        {
            if (!this.Disposed)
            {
                this.Dispose();
            }
        }

        protected abstract bool IsDisposed();

        public virtual void Dispose()
        {
        }
    }
}
