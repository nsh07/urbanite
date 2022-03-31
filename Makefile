prefix = /usr/local
bindir = $(prefix)/bin

mkdiropts = -vp

BIN = bin
SRC = src

CC = g++
CFLAGS = -O2 -Wall -Wextra
LIBS = -lcurl

all: $(SRC)/main.cpp
	mkdir $(mkdiropts) $(BIN)
	${CC} $(SRC)/main.cpp ${CFLAGS} ${LIBS} -o $(BIN)/urbanite

install: $(BIN)/urbanite
	install $(BIN)/urbanite $(bindir)

uninstall:
	rm -i $(bindir)/urbanite

clean:
	rm -rf $(BIN)