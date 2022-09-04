prefix = /usr/local
bindir = $(prefix)/bin
sharedir = $(prefix)/share/urbanite

mkdiropts = -vp

BIN = bin
OBJ = obj
SRC = src
FONT = fonts

CC = g++
CFLAGS = -std=c++17 -O2 -Wall -DPREFIX_DIR=\"$(prefix)\" -Iinclude

LIBS = -lcurl

.PHONY: all tarball deb install uninstall clean

all: $(BIN)/urbanite

$(BIN)/urbanite: $(OBJ)/main.o $(OBJ)/help.o $(OBJ)/print.o $(OBJ)/other.o | $(BIN)
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

tarball: $(BIN)/urbanite
	@echo "Creating tarball..."
	@echo "\e[90mtar -cv -f bin/urbanite.tar bin/urbanite fonts Makefile"
	@tar -cv -f bin/urbanite.tar bin/urbanite fonts Makefile
	@echo "\e[0mCompressing tarball..."
	@echo "\e[90mxz -vf bin/urbanite.tar"
	@xz -vf bin/urbanite.tar
	@echo "\e[0m...done"

deb: $(BIN)/urbanite
	@echo "Running build-deb script..."
	@bash ./build-deb.sh 
	@echo "...done"

install:
	@echo "Installing Urbanite in $(bindir)..."
	@echo "\e[90minstall $(BIN)/urbanite $(bindir)\e[0m"
	@install $(BIN)/urbanite $(bindir)
	
	@echo "Installing the default fonts in $(sharedir)..."
	@echo "\e[90mmkdir $(mkdiropts) $(sharedir)"
	@mkdir $(mkdiropts) $(sharedir)
	@echo "install $(FONT)/* $(sharedir)"
	@install $(FONT)/* $(sharedir)
	@echo "\e[0m...done"

uninstall:
	@echo "Uninstalling Urbanite from $(bindir)..."
	@echo "\e[90mrm -i $(bindir)/urbanite\e[0m"
	@rm -i $(bindir)/urbanite

	@echo "Removing the $(sharedir) directory..."
	@echo "\e[90mrm -ir $(sharedir)\e[0m"
	@rm -ir $(sharedir)
	@echo "...done :("

clean:
	@echo "Cleaning build files..."
	@echo "\e[90mrm -rvf $(OBJ)"
	@rm -rvf $(OBJ)
	@echo "\e[0m"
#	@echo "\e[90mrm -rv $(BIN)\e[0m"
#	@rm -rvf $(BIN)