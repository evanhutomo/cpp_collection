if(NOT BUILD_SAMPLE_CODE)
  return()
endif()

set(EXAMPLES_DIR ${CMAKE_CURRENT_SOURCE_DIR})
function(sample name)
  add_executable(kotobakoe_${name} ${name}.cpp)
  target_link_libraries(kotobakoe_${name} PUBLIC ${DIRECTORY_LIB})
  file(RELATIVE_PATH dir ${EXAMPLES_DIR} ${CMAKE_CURRENT_SOURCE_DIR})
#   set_property(GLOBAL APPEND PROPERTY FTXUI::EXAMPLES ${dir}/${name})
  target_compile_features(kotobakoe_${name} PRIVATE cxx_std_20)
endfunction(sample)

add_subdirectory(satu)