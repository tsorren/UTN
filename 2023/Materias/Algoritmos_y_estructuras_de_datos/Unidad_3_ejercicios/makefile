#Make it so it compiles the latest changed file
make clean:
	{ \
	rm -f test; \
	clear; \
	make test; \
	printf "\n"; \
	echo " |-----------------| "; \
	printf " | Running code... |\n"; \
	echo " |-----------------| "; \
	printf "\n"; \
	./test; \
	}

test:
	g++ -o test -std=c++17 -Wall -Werror -Wpedantic ./9.cpp 
