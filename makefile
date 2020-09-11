MAIN = test
FLAGS = -ldl -g -Wall -Werror -Wpedantic

$(MAIN) : $(MAIN).o
	g++ $(FLAGS) -o $(MAIN) $(MAIN).o

$(MAIN).o : Deque.hpp $(MAIN).cpp
	g++ -c $(FLAGS) $(MAIN).cpp

clean :
	rm $(MAIN) $(MAIN).o
