build:
	g++ src/main.cpp src/Settings.cpp src/StringUtils.cpp src/Socket.cpp \
	src/StdioHelper.cpp -o bin/cli
clear:
	rm bin/cli
run:
	bin/cli