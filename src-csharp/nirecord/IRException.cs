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
