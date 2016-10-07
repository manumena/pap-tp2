EXERCISES=ej1 ej2 ej3 ej4

.PHONY: all clean test $(EXERCISES)

all:
	$(foreach exercise,$(EXERCISES), $(MAKE) all -C $(exercise);)

test:
	$(foreach exercise,$(EXERCISES), $(MAKE) test -C $(exercise);)

clean:
	$(foreach exercise,$(EXERCISES), $(MAKE) clean -C $(exercise);)
