using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace InterlockRecord
{
    /// <summary>
    /// This exception is used to indicate errors while calling functions of the InterlockRecord API.
    /// </summary>
    public class IRException: Exception
    {
        /// <summary>
        /// The associated error code.
        /// </summary>
        public IRErrorCode Error
        {
            private set;
            get;
        }

        public IRException(IRErrorCode error) : this(error, error.ToString(), null)
        {
        }

        public IRException(IRErrorCode error, string message) : this(error, message, null)
        {
        }

        public IRException(IRErrorCode error, string message, Exception innerException) : base(message, innerException)
        {
            this.Error = error;
        }
    }
}
