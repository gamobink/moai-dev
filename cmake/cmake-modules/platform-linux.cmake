 #find_package ( OpenGL REQUIRED )
  set ( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DPOSIX -std=gnu99 -DNDEBUG -DHAVE_MEMMOVE" )
  set ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DPOSIX " )