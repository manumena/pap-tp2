# suffixes used in implicit rules (first line clears default ones)
.SUFFIXES:
.SUFFIXES: .cpp .o

# flags used in implicit rules
CC=g++
CPPFLAGS=-g -pedantic -Wall -O2
CXXFLAGS=-std=c++11

EXECUTABLE=ej4
MAIN_OBJECT=$(addsuffix .o,$(EXECUTABLE))
TEST_OBJECT=test.o

.PHONY: all clean test

all: $(EXECUTABLE)

test: $(EXECUTABLE)
	./$(EXECUTABLE) -t

clean:
	rm -rf $(EXECUTABLE) $(MAIN_OBJECT) $(TEST_OBJECT)

$(MAIN_OBJECT): $(subst .o,.h,$(MAIN_OBJECT))

$(EXECUTABLE): $(MAIN_OBJECT) $(TEST_OBJECT)
	$(CC) $(CXXFLAGS) -o $@ $^
