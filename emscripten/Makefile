CC=emcc
CFLAGS=-g -Wall -std=gnu++11 --emrun


SRC=$(wildcard ../src/*.cc)
OBJ=$(patsubst ../src/%.cc, ./%.o, $(SRC))
TGT=../index.html

print-%:
	@echo '$*=$($*)'

.PHONY: all clean

$(TGT):$(SRC)
	$(CC) $(CFLAGS) $^ -o $@

all:$(TGT)
	emrun --browser=chrome $(TGT)

clean:
	rm -f $(TGT) $(OBJ) ../index.js