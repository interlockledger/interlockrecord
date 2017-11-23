
# Force the build with a static copy of the CRT
macro(msvc_set_static)
	if (MSVC)
		foreach (flag_var
				 CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
				 CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO)
			string(REPLACE "/MD" "-MT" ${flag_var} "${${flag_var}}")
		endforeach()
	endif()	
endmacro()
