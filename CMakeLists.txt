PROJECT(hts_ue1)

include_directories(include)
link_libraries(boost_serialization boost_thread ldap)
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build)

ADD_EXECUTABLE(client src/listmessage.cpp  src/serializer.cpp src/networkbase.cpp src/client/client.cpp src/client/client_main.cpp)
ADD_EXECUTABLE(server src/listmessage.cpp  src/serializer.cpp src/server/directory.cpp src/server/ldaplogin.cpp src/session.cpp src/networkbase.cpp src/server/server.cpp src/server/server_main.cpp)

