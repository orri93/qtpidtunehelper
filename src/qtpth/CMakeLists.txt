list(APPEND qt_pid_tune_helper_source
  qtpidtunehelpermainwindow.cpp
  main.cpp)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS REQUIRED Core Gui Qml Quick Widgets)

list(APPEND qt_pid_tune_helper_libraries
  Qt5::Core)

if(MSVC)
  set(GOS_FILEDESCRIPTION "Qt PID tunning helper")
  set(GOS_INTERNALNAME "${qt_pid_tune_helper_target}")
  set(GOS_ORIGINALFILENAME "${qt_pid_tune_helper_target}.exe")
  set(GOS_PRODUCTNAME "${qt_pid_tune_helper_target}")
  configure_file("version.rc.in" "version.rc" @ONLY)
  list(APPEND qt_pid_tune_helper_source
    "${CMAKE_CURRENT_BINARY_DIR}/version.rc")
endif()

add_executable(${qt_pid_tune_helper_target} ${qt_pid_tune_helper_source})

target_include_directories(${qt_pid_tune_helper_target} PUBLIC
  ${qt_pid_tune_helper_include})

target_link_libraries(${qt_pid_tune_helper_target}
  ${qt_pid_tune_helper_libraries})

#target_compile_definitions(${qt_pid_tune_helper_target} PUBLIC GOS_SOME_DEF)

if(CLANG_TIDY_EXE)
  set_target_properties(${qt_pid_tune_helper_target} PROPERTIES
    CXX_CLANG_TIDY "${CMAKE_CXX_CLANG_TIDY}")
endif()

install(TARGETS ${nov_dlinkcli_target}
  LIBRARY DESTINATION bin
  ARCHIVE DESTINATION bin)