##############################
# Compiler and compile flags #
##############################

PREFIX ?= /usr/local
LIBDIR ?= $(PREFIX)/lib
INCDIR ?= $(PREFIX)/include

MKDIR=mkdir -pv
RM=rm -vf

CC=g++
# Note: remove the '-g' and '-O0' flags below if you won't do debugging
CFLAGS=-Wall -Wextra -Werror -pedantic -g -O0 -fPIC -Iinclude -Itest

###################################
# Main target: the static lib one #
###################################

.PHONY: all
all: lib 

######################################
# Create 'obj' and 'lib' directories #
######################################

.PHONY: libdir
libdir:
	@$(MKDIR) lib

.PHONY: objdir
objdir:
	@$(MKDIR) obj

###################################
# Singly linked list object files #
###################################

obj/singly-linked-list-node.o: src/libdatastructures/list/singly-linked-list-node.c \
                               include/libdatastructures/list/singly-linked-list-node.h | objdir
	$(CC) -c $< -o $@ $(CFLAGS)

obj/singly-linked-list.o: src/libdatastructures/list/singly-linked-list.c \
                          include/libdatastructures/list/singly-linked-list.h \
                          include/libdatastructures/list/singly-linked-list-node.h | objdir
	$(CC) -c $< -o $@ $(CFLAGS)

###################################
# Doubly linked list object files #
###################################

obj/doubly-linked-list-node.o: src/libdatastructures/list/doubly-linked-list-node.c \
                               include/libdatastructures/list/doubly-linked-list-node.h | objdir
	$(CC) -c $< -o $@ $(CFLAGS)

obj/doubly-linked-list.o: src/libdatastructures/list/doubly-linked-list.c \
                          include/libdatastructures/list/doubly-linked-list.h \
                          include/libdatastructures/list/doubly-linked-list-node.h | objdir
	$(CC) -c $< -o $@ $(CFLAGS)

#####################
# Stack object file #
#####################

obj/stack.o: src/libdatastructures/stack/stack.c \
             include/libdatastructures/stack/stack.h \
             include/libdatastructures/list/singly-linked-list.h | objdir
	$(CC) -c $< -o $@ $(CFLAGS)

#####################
# Queue object file #
#####################

obj/queue.o: src/libdatastructures/queue/queue.c \
             include/libdatastructures/queue/queue.h \
             include/libdatastructures/list/singly-linked-list.h | objdir
	$(CC) -c $< -o $@ $(CFLAGS)

###########################################
# Deque (doubly-ended queue) object file #
###########################################

obj/deque.o: src/libdatastructures/deque/deque.c \
             include/libdatastructures/deque/deque.h \
             include/libdatastructures/list/doubly-linked-list.h | objdir
	$(CC) -c $< -o $@ $(CFLAGS)

#####################
# Tree object files #
#####################

obj/tree-node.o: src/libdatastructures/tree/tree-node.c \
                 include/libdatastructures/tree/tree-node.h | objdir
	$(CC) -c $< -o $@ $(CFLAGS)

obj/tree.o: src/libdatastructures/tree/tree.c \
            include/libdatastructures/tree/tree.h | objdir
	$(CC) -c $< -o $@ $(CFLAGS)

#############################
# Map and pair object files #
#############################

obj/pair.o: src/libdatastructures/map/pair.c \
            include/libdatastructures/map/pair.h | objdir
	$(CC) -c $< -o $@ $(CFLAGS)

obj/map.o: src/libdatastructures/map/map.c \
           include/libdatastructures/map/map.h \
           include/libdatastructures/map/pair.h \
           include/libdatastructures/tree/tree.h | objdir
	$(CC) -c $< -o $@ $(CFLAGS)

##################
# The static lib #
##################

lib/libdatastructures.a: obj/singly-linked-list-node.o obj/singly-linked-list.o \
                         obj/doubly-linked-list-node.o obj/doubly-linked-list.o \
                         obj/stack.o \
                         obj/queue.o \
                         obj/deque.o \
                         obj/pair.o \
                         obj/map.o \
                         obj/tree-node.o obj/tree.o | libdir
	ar rcs $@ $^

.PHONY: lib
lib: lib/libdatastructures.a

###########################
# Documentation (Doxygen) #
###########################

.PHONY: doc
doc:
	sed "s|\/path\/to\/libdatastructures|${PWD}|g" doc/Doxyfile > doc/Doxyfile.tmp
	doxygen doc/Doxyfile.tmp
	@echo To start reading the generated doc, please open ${PWD}/doc/html/index.html with your \
              favorite web browser.

########################################
# Auxiliary libs unit test simulations #
########################################

test/number/number.o: test/number/number.c test/number/number.h
	$(CC) -c $< -o $@ $(CFLAGS)

test/fruit/fruit.o: test/fruit/fruit.c test/fruit/fruit.h
	$(CC) -c $< -o $@ $(CFLAGS)

test/rand-perm/rand-perm.o: test/rand-perm/rand-perm.c \
                            test/rand-perm/rand-perm.h
	$(CC) -c $< -o $@ $(CFLAGS)

###########################################
# Singly-linked list unit test simulation #
###########################################

test/singly-linked-list-test.o: test/singly-linked-list-test.c \
                                test/number/number.h \
                                include/libdatastructures/list/singly-linked-list.h
	$(CC) -c $< -o $@ $(CFLAGS)

test/singly-linked-list-test: test/number/number.o \
                              test/singly-linked-list-test.o \
                              lib/libdatastructures.a
	$(CC) -o $@ $^
	valgrind ./$@

###########################################
# Doubly-linked list unit test simulation #
###########################################

test/doubly-linked-list-test.o: test/doubly-linked-list-test.c \
                                test/number/number.h \
                                include/libdatastructures/list/doubly-linked-list.h
	$(CC) -c $< -o $@ $(CFLAGS)

test/doubly-linked-list-test: test/number/number.o \
                              test/doubly-linked-list-test.o \
                              lib/libdatastructures.a
	$(CC) -o $@ $^
	valgrind ./$@

##############################
# Stack unit test simulation #
##############################

test/stack-test.o: test/stack-test.c \
                   test/number/number.h \
                   include/libdatastructures/stack/stack.h
	$(CC) -c $< -o $@ $(CFLAGS)

test/stack-test: test/number/number.o \
                 test/stack-test.o \
                 lib/libdatastructures.a
	$(CC) -o $@ $^
	valgrind ./$@

##############################
# Queue unit test simulation #
##############################

test/queue-test.o: test/queue-test.c \
                   test/number/number.h \
                   include/libdatastructures/queue/queue.h
	$(CC) -c $< -o $@ $(CFLAGS)

test/queue-test: test/number/number.o \
                 test/queue-test.o \
                 lib/libdatastructures.a
	$(CC) -o $@ $^
	valgrind ./$@

###################################################
# Deque (doubly-ended queue) unit test simulation #
###################################################

test/deque-test.o: test/deque-test.c \
                   test/number/number.h \
                   include/libdatastructures/deque/deque.h
	$(CC) -c $< -o $@ $(CFLAGS)

test/deque-test: test/number/number.o \
                 test/deque-test.o \
                 lib/libdatastructures.a
	$(CC) -o $@ $^
	valgrind ./$@

##############################
# Tree unit test simulations #
##############################

test/tree-test.o: test/tree-test.c \
                  test/number/number.h \
                  include/libdatastructures/tree/tree.h
	$(CC) -c $< -o $@ $(CFLAGS)

test/tree-test: test/number/number.o \
                test/tree-test.o \
                lib/libdatastructures.a
	$(CC) -o $@ $^
	valgrind ./$@

test/random-elems-test.o: test/random-elems-test.c \
                          test/number/number.h \
                          test/rand-perm/rand-perm.h \
                          include/libdatastructures/tree/tree.h
	$(CC) -c $< -o $@ $(CFLAGS)

test/random-elems-test: test/random-elems-test.o \
                        test/number/number.o \
                        test/rand-perm/rand-perm.o \
                        lib/libdatastructures.a
	$(CC) -o $@ $^
	valgrind ./$@

############################
# Map unit test simulation #
############################

test/map-test.o: test/map-test.c \
                 test/fruit/fruit.h \
                 test/number/number.h \
                 include/libdatastructures/map/map.h \
                 include/libdatastructures/map/pair.h
	$(CC) -c $< -o $@ $(CFLAGS)

test/map-test: test/map-test.o \
               test/fruit/fruit.o \
               test/number/number.o \
               lib/libdatastructures.a
	$(CC) -o $@ $^
	valgrind ./$@

#####################################
# 'install' and 'uninstall' targets #
#####################################

.PHONY: install
install: lib
	find include/ -type f -exec install -vDm 664 {} $(PREFIX)/{} \;	
	install -vm 775 lib/libdatastructures.a $(PREFIX)/lib/

.PHONY: uninstall
uninstall:
	@$(RM) $(PREFIX)/include/libdatastructures
	@$(RM) $(PREFIX)/lib/libdatastructures.a

##################################
# 'clean' and 'mrproper' targets #
##################################

.PHONY: clean
clean:
	@$(RM) doc/Doxyfile.tmp
	@$(RM) -r doc/html
	@$(RM) -r obj
	@$(RM) test/*.o
	@$(RM) test/fruit/fruit.o
	@$(RM) test/number/number.o
	@$(RM) test/rand-perm/rand-perm.o
	@$(RM) test/singly-linked-list-test
	@$(RM) test/doubly-linked-list-test
	@$(RM) test/stack-test
	@$(RM) test/queue-test
	@$(RM) test/deque-test
	@$(RM) test/tree-test
	@$(RM) test/random-elems-test
	@$(RM) test/map-test

.PHONY: mrproper
mrproper: clean
	@$(RM) -r lib
