PLATFORM =
CC = $(PLATFORM)gcc

MAIN_SRC = mymain
LIB_SRC1 = mylib_func_1
LIB_SRC2 = mylib_func_2

all : $(MAIN_SRC)

$(MAIN_SRC) : $(MAIN_SRC).o $(LIB_SRC1).o $(LIB_SRC2).o
	gcc -o $(MAIN_SRC) $(MAIN_SRC).o $(LIB_SRC1).o $(LIB_SRC2).o

$(MAIN_SRC).o : $(MAIN_SRC).c
	gcc -c $(MAIN_SRC).c

$(LIB_SRC1).o : $(LIB_SRC1).c
	gcc -c $(LIB_SRC1).c

$(LIB_SRC2).o : $(LIB_SRC2).c
	gcc -c $(LIB_SRC2).c

clean :
	rm -f *.o $(MAIN_SRC)