message("stream library path ${LIBRARY_PATH}")

list(APPEND sources
	${LIBRARY_PATH}/src/stream.cpp
	${LIBRARY_PATH}/src/binarystream.cpp
	${LIBRARY_PATH}/src/textstream.cpp
	${LIBRARY_PATH}/src/outputstream.cpp
	${LIBRARY_PATH}/src/stringstream.cpp
)

include_directories(
	${LIBRARY_PATH}/src
)
