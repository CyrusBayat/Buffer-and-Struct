
FIRSTNAME=Cyrus
LASTNAME=Bayat
ROOTNAME=$(LASTNAME)_$(FIRSTNAME)
W=32
FOPTION=_main
RUNOPTIONS=$(FIRSTNAME) $(LASTNAME) "In linguistics and grammar, a sentence is a linguistic expression, such as the English example The quick brown fox jumps over the lazy dog. In traditional grammar it is typically defined as a string of words that expresses a complete thought, or as a unit consisting of a subject and predicate. In non-functional linguistics it is typically defined as a maximal unit of syntactic structure such as a constituent." $(TESTOPTIONS)

CC=gcc
CFLAGS= -g -I.
LIBS =
DEPS = 
ARCH = $(shell uname -m)

ifeq ($(ARCH), aarch64)
	ARCHOBJ=dd2M1.o
else
	ARCHOBJ=dd2.o
endif

OBJ = $(ROOTNAME)$(W)$(FOPTION).o $(ARCHOBJ)

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(ROOTNAME)$(W)$(FOPTION): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)  $(LIBS)

clean:
	rm $(ROOTNAME)$(W)$(FOPTION).o $(ROOTNAME)$(W)$(FOPTION)

run: $(ROOTNAME)$(W)$(FOPTION)
	./$(ROOTNAME)$(W)$(FOPTION) $(RUNOPTIONS) $(TESTOPTIONS)

vrun: $(ROOTNAME)$(W)$(FOPTION)
	valgrind ./$(ROOTNAME)$(W)$(FOPTION) $(RUNOPTIONS) $(TESTOPTIONS)

