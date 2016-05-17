build:
	g++ src/main.cpp src/Settings.cpp src/StringUtils.cpp -o bin/cli
clear:
	rm bin/cli
run:
	bin/cli