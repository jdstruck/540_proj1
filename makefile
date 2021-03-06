#MAIN = main
MAIN = test
FLAGS = -ldl -O3 -Wall -Werror -Wpedantic

$(MAIN) : $(MAIN).o
	g++ $(FLAGS) -o $(MAIN) $(MAIN).o

$(MAIN).o : Deque.hpp $(MAIN).cpp
	g++ -c $(FLAGS) $(MAIN).cpp

clean :
	rm $(MAIN) $(MAIN).o

run : $(MAIN)
	./$(MAIN)

memcheck : $(MAIN)
	valgrind --show-leak-kinds=all --track-origins=yes --leak-check=full ./$(MAIN)
