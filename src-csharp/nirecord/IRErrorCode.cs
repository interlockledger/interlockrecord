using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace InterlockRecord
{
    /// <summary>
    /// Error codes returned by the InterlockRecord implementation.
    /// </summary>
    public enum IRErrorCode
    {
        /// <summary>
        /// Unknown error.
        /// </summary>
        IRE_UNKNOWN_ERROR = -1,

        /// <summary>
        /// Success of the operation.
        /// </summary>
        IRE_SUCCESS = 0,

        /// <summary>
        /// Invalid context.
        /// </summary>
        IRE_INVALID_CONTEXT = 1,

        /// <summary>
        /// Invalid state. It happens when a given operation cannot be executed due to
        /// an invalid state.
        /// </summary>
        IRE_INVALID_STATE = 2,

        /// <summary>
        /// The buffer is too short to hold the information.
        /// </summary>
        IRE_BUFFER_TOO_SHORT = 3,

        //TODO Add more errors

        #region Parameters
        // TODO Add documentation
        IRE_INVALID_PARAM_BASE = 0x7FFFFFF0,
        IRE_INVALID_PARAM_00 = (int)IRE_INVALID_PARAM_BASE + 0,
        IRE_INVALID_PARAM_01 = (int)IRE_INVALID_PARAM_BASE + 1,
        IRE_INVALID_PARAM_02 = (int)IRE_INVALID_PARAM_BASE + 2,
        IRE_INVALID_PARAM_03 = (int)IRE_INVALID_PARAM_BASE + 3,
        IRE_INVALID_PARAM_04 = (int)IRE_INVALID_PARAM_BASE + 4,
        IRE_INVALID_PARAM_05 = (int)IRE_INVALID_PARAM_BASE + 5,
        IRE_INVALID_PARAM_06 = (int)IRE_INVALID_PARAM_BASE + 6,
        IRE_INVALID_PARAM_07 = (int)IRE_INVALID_PARAM_BASE + 7,
        IRE_INVALID_PARAM_08 = (int)IRE_INVALID_PARAM_BASE + 8,
        IRE_INVALID_PARAM_09 = (int)IRE_INVALID_PARAM_BASE + 9,
        IRE_INVALID_PARAM_10 = (int)IRE_INVALID_PARAM_BASE + 10,
        IRE_INVALID_PARAM_11 = (int)IRE_INVALID_PARAM_BASE + 11,
        IRE_INVALID_PARAM_12 = (int)IRE_INVALID_PARAM_BASE + 12,
        IRE_INVALID_PARAM_13 = (int)IRE_INVALID_PARAM_BASE + 13,
        IRE_INVALID_PARAM_14 = (int)IRE_INVALID_PARAM_BASE + 14,
        IRE_INVALID_PARAM_15 = (int)IRE_INVALID_PARAM_BASE + 15,
        #endregion
    }
}
