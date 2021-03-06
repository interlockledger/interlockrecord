﻿/*
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
    /// This is the base class for all objects from the InterlockRecord library.
    /// </summary>
    public abstract class IRBaseObject : IDisposable
    {
        /// <summary>
        /// The handle of this object inside the native API.
        /// </summary>
        public int Handle
        {
            private set;
            get;
        }

        /// <summary>
        /// Internal flag used to determine if the handle have been disposed.
        /// </summary>
        protected bool HandleDisposed
        {
            get;
            set;
        }

        /// <summary>
        /// Indicates if this object is already disposed.
        /// </summary>
        public bool Disposed
        {
            get 
            {
                return (this.IsParentDisposed() || this.HandleDisposed);
            }
        }

        /// <summary>
        /// Creates a new instance of this class.
        /// </summary>
        /// <param name="handle">The value of the handle.</param>
        public IRBaseObject(int handle)
        {
            this.Handle = handle;
            this.HandleDisposed = false;
        }

        /// <summary>
        /// Disposes this instance and releases all associated resources.
        /// </summary>
        /// <remarks>
        /// This destructor will call the method Dispose() if it was not disposed yet.
        /// </remarks>
        ~IRBaseObject()
        {
            if (!this.Disposed)
            {
                this.Dispose();
            }
        }

        /// <summary>
        /// Call this method to ensure that the internal handle is still valid.
        /// </summary>
        /// <exception cref="InvalidOperationException">When the property Disposed is true.</exception>
        protected void EnsureNotDisposed()
        {
            if (this.Disposed)
            {
                throw new InvalidOperationException("This object is no longer valid.");
            }
        }

        /// <summary>
        /// This method is called by the property Disposed to determine if the parent of this
        /// object was disposed or not.
        /// </summary>
        /// <returns>true if the parent was disposed or false otherwise.</returns>
        protected virtual bool IsParentDisposed()
        {
            return false;
        }

        /// <summary>
        /// Disposes this object and releases associated resources.
        /// </summary>
        public abstract void Dispose();
    }
}
