CC = g++
LD = g++
LD_FLAGS = -static -lgmp -static -std=c++0x
INCLUDE_DIRS = -I. -I../third_parth/gmp/include 
CC_FLAGS = $(INCLUDE_DIRS) -std=c++0x -g -c -Wall -Werror --pedantic 
SRC = ElGamalBase.cpp  ElGamalDecrypter.cpp  ElGamalEncrypter.cpp  GmpWraper.cpp  Larginteger.cpp   Primality.cpp main.cpp DBManager.cpp
OBJ = $(subst .cpp,.o,$(SRC) )

out: $(OBJ)
	$(LD)  $(OBJ) $(LD_FLAGS) -o out
lib: $(OBJ)
	ar rsc libargithmetics.a ElGamalBase.o  ElGamalDecrypter.o  ElGamalEncrypter.o  GmpWraper.o  Larginteger.o   Primality.o

%.o : %.cpp  
	$(CC)  $(CC_FLAGS) -L../third_parth/gmp/lib-lgmp $< -o $@

clean: 
	rm -rf *o out libargithmetics.a
