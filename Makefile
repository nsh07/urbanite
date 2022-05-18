prefix = /usr/local
bindir = $(prefix)/bin

mkdiropts = -vp

BIN = bin
OBJ = obj
SRC = src

CC = g++
CFLAGS = -O2 -Wall

LIBS = -lcurl

.PHONY: all install uninstall clean

all: $(BIN)/urbanite

$(BIN)/urbanite: $(OBJ)/main.o $(OBJ)/print.o $(OBJ)/other.o | $(BIN)
	@echo "Linking objects $^ into executable $@..."
	@echo "\e[90m${CC} $^ ${CFLAGS} ${LIBS} -o $@\e[0m"
	@${CC} $^ ${CFLAGS} ${LIBS} -o $@
	@echo "...done"

$(OBJ)/%.o: $(SRC)/%.cpp | $(OBJ)
	@echo "Compiling object $@ from source file $<..."
	@echo "\e[90m${CC} -c $< ${CFLAGS} -o $@\e[0m"
	@${CC} -c $< ${CFLAGS} -o $@

$(BIN):
	@echo "\e[90mmkdir $(mkdiropts) $(BIN)\e[0m"
	@mkdir $(mkdiropts) $(BIN)

$(OBJ):
	@echo "\e[90mmkdir $(mkdiropts) $(OBJ)\e[0m"
	@mkdir $(mkdiropts) $(OBJ)

install:
	@echo "Installing Urbanite in $(bindir)..."
	@echo "\e[90minstall $(BIN)/urbanite $(bindir)\e[0m"
	@install $(BIN)/urbanite $(bindir)
	@echo "...done"

uninstall:
	@echo "Uninstalling Urbanite from $(bindir)..."
	@echo "\e[90mrm -i $(bindir)/urbanite\e[0m"
	@rm -i $(bindir)/urbanite
	@echo "...done :("

clean:
	@echo "Cleaning build files..."
	@echo "\e[90mrm -rvf $(OBJ)\e[0m"
	@rm -rvf $(OBJ)
#	@echo "\e[90mrm -rv $(BIN)\e[0m"
#	@rm -rvf $(BIN)