
# This module let's the change of the CRT used by the compiler when using MSVC.
# When the option MSVC_STATIC_CRT is set to ON, the default /MD flag will be
# replaced by the /MT flag. Furthermore, the variable MSVC_CRT_FLAG will hold
# the name of the flag used "MD" or "MT".
if(__WINDOWS_MSVCCRT)
  return()
endif()
set(__WINDOWS_MSVCCRT 1)

if (MSVC)
	option(MSVC_STATIC_CRT "Instructs the compiler to use the static CRT instead of the dynamic one.")
	if (MSVC_STATIC_CRT)
		set(MSVC_CRT_FLAG "MT")
		foreach(lang C CXX)
			foreach (flag_var
					CMAKE_${lang}_FLAGS
					CMAKE_${lang}_FLAGS_DEBUG
					CMAKE_${lang}_FLAGS_DEBUG_INIT
					CMAKE_${lang}_FLAGS_INIT
					CMAKE_${lang}_FLAGS_MINSIZEREL
					CMAKE_${lang}_FLAGS_MINSIZEREL_INIT)
				string(REPLACE "/MDd " "/MTd " ${flag_var} "${${flag_var}}")
				string(REPLACE "/MD " "/MT " ${flag_var} "${${flag_var}}")
			endforeach()
		endforeach()
	else()
		set(MSVC_CRT_FLAG "MD")
	endif()
	message(STATUS "The MSVC CRT flag is ${MSVC_CRT_FLAG}.")
endif()	
