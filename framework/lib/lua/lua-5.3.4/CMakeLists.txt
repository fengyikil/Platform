aux_source_directory(src LIB_SRC)
list(REMOVE_ITEM LIB_SRC src/lua.c;src/luac.c)
message(${LIB_SRC})


set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

#动态库

add_library(liblua SHARED ${LIB_SRC})

#add_definitions("-DLUA_BUILD_AS_DLL") #老式添加宏的方法,影响整个范围
set_target_properties(liblua PROPERTIES COMPILE_DEFINITIONS "LUA_BUILD_AS_DLL") #新式添加宏的方法,只影响当前目标(target)
set_target_properties(liblua PROPERTIES OUTPUT_NAME "lua53")

#静态库
add_library(liblua_static STATIC ${LIB_SRC})
set_target_properties(liblua_static PROPERTIES OUTPUT_NAME "lua53s")

#解析器
add_executable(lua src/lua.c)
target_link_libraries(lua liblua)

#编译器
add_executable(luac src/luac.c)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
target_link_libraries(luac liblua_static)




