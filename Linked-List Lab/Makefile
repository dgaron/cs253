CXXFLAGS=-std=c++17 -Wall -Wextra -Wpedantic -Werror -Wfatal-errors -Winit-self -Wshadow -Wlogical-op -Wcomment -Wctor-dtor-privacy -Wold-style-cast -D_GLIBCXX_DEBUG -fno-diagnostics-show-option

link: main.o ll.o
	g++ $(CXXFLAGS) main.o ll.o -o link

main.o: main.cc ll.h
	g++ $(CXXFLAGS) -c main.cc

ll.o: ll.cc ll.h
	g++ $(CXXFLAGS) -c ll.cc

clean:
	-rm -f link *.o
