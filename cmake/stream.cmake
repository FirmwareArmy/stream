list(APPEND sources
	${PACKAGE_PATH}/src/stream.cpp
	${PACKAGE_PATH}/src/binarystream.cpp
	${PACKAGE_PATH}/src/textstream.cpp
	${PACKAGE_PATH}/src/outputstream.cpp
	${PACKAGE_PATH}/src/stringstream.cpp
)

include_directories(
	${PACKAGE_PATH}/src
)
