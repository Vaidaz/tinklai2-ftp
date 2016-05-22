build:
	g++ src/main.cpp src/Settings.cpp src/StringUtils.cpp src/Socket.cpp \
	src/StdioHelper.cpp src/FTP.cpp -o bin/cli
clear:
	rm bin/cli
run:
	bin/cli
t:
	@make build -s
	@make run -s