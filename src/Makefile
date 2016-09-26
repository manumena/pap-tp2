# suffixes used in implicit rules (first line clears default ones)
.SUFFIXES:
.SUFFIXES: .cpp .o

# flags used in implicit rules
CC=g++
CPPFLAGS=-g -pedantic -Wall -O2
CXXFLAGS=-std=c++11

EXECUTABLES_BASE=ej1 ej2 ej3 ej4
EXECUTABLES=$(addsuffix _solver, $(EXECUTABLES_BASE))
MAIN_OBJECT=main.o
OTHER_OBJECTS=solver.o test.o
OTHER_OBJECTS_DIR=$(foreach exe,$(EXECUTABLES_BASE),$(addprefix $(exe)/,$(OTHER_OBJECTS)))

.PHONY: all clean test $(addsuffix test-, $(EXECUTABLES_BASE))

all: $(EXECUTABLES)

test: $(addprefix test-,$(EXECUTABLES_BASE))

clean:
	rm -rf $(EXECUTABLES) $(MAIN_OBJECT) $(addsuffix /*.o,$(EXECUTABLES_BASE))

$(MAIN_OBJECT): $(subst .o,.h,$(MAIN_OBJECT))

.SECONDEXPANSION:

# any changes to exercise headers force rebuilding
$(OTHER_OBJECTS_DIR): $$(dir $$@)/$$(subst /,.h,$$(dir $$@))

$(EXECUTABLES): $(MAIN_OBJECT) $$(addprefix $$(subst _solver,,$$@)/,$(OTHER_OBJECTS))
	$(CC) $(CXXFLAGS) -o $@ $^

$(addprefix test-, $(EXECUTABLES_BASE)): $$(addsuffix _solver,$$(subst test-,,$$@))
	./$(addsuffix _solver,$(subst test-,,$@)) -t
