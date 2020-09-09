MAIN = test
FLAGS = -ldl -g -Wall -Werror -Wpedantic

$(MAIN) : $(MAIN).o
	g++ -o $(MAIN) $(MAIN).o

$(MAIN).o : Deque.hpp $(MAIN).cpp
	g++ -c $(FLAGS) $(MAIN).cpp
