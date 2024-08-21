CXXFLAGS:=-Wall -Wextra -pedantic -std=c++20 -ggdb -I.
LDFLAGS:=
OBJS:=main.o lexer.o

all: $(OBJS)
	$(CXX) $(CXXFLAGS) -o main $^ $(LDFLAGS)

main.o: main.cc
	$(CXX) $(CXXFLAGS) -c -o $@ $<

%.o: %.cc %.hh
	$(CXX) $(CXXFLAGS) -c -o $@ $<

.PHONY: clean compile_flags
clean: ; rm -rf *.o main
compile_flags: ; echo $(CXXFLAGS) | xargs -n1 > compile_flags.txt
