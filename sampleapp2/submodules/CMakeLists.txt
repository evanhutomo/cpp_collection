# if (NUMCPP)
# 	message(STATUS "add NumCPP")
# 	add_subdirectory(NumCpp)
# endif()

if (OBSERVABLE)
	message(STATUS "add observable")
	add_subdirectory(observable)
endif()
