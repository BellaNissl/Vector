all: main.cpp
	clang++ -std=c++14 -fsized-deallocation -o vector main.cpp -Wall -Wextra -Werror -pedantic

run: gcc
	./vector

gcc: main.cpp
	g++ -std=c++14 -o vector main.cpp -Wall -Wextra -Werror -pedantic

clean:
	rm -f vector