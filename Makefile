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

ifeq (, $(shell which tput))
	GRAY = ""
	RESET = ""
else
	GRAY = $(shell tput setaf 8)
	RESET = $(shell tput sgr0)
endif

.PHONY: all tarball deb install uninstall clean

all: $(BIN)/urbanite

$(BIN)/urbanite: $(OBJ)/main.o $(OBJ)/help.o $(OBJ)/print.o $(OBJ)/other.o | $(BIN)
	@echo "Linking objects $^ into executable $@..."
	@echo "${GRAY}${CC} $^ ${CFLAGS} ${LIBS} -o $@${RESET}"
	@${CC} $^ ${CFLAGS} ${LIBS} -o $@
	@echo "...done"

$(OBJ)/%.o: $(SRC)/%.cpp | $(OBJ)
	@echo "Compiling object $@ from source file $<..."
	@echo "${GRAY}${CC} -c $< ${CFLAGS} -o $@${RESET}"
	@${CC} -c $< ${CFLAGS} -o $@

$(BIN):
	@echo "${GRAY}mkdir $(mkdiropts) $(BIN)${RESET}"
	@mkdir $(mkdiropts) $(BIN)

$(OBJ):
	@echo "${GRAY}mkdir $(mkdiropts) $(OBJ)${RESET}"
	@mkdir $(mkdiropts) $(OBJ)

tarball: $(BIN)/urbanite
	@echo "Creating tarball..."
	@echo "${GRAY}tar -cv -f bin/urbanite.tar bin/urbanite fonts Makefile"
	@tar -cv -f bin/urbanite.tar bin/urbanite fonts Makefile
	@echo "${RESET}Compressing tarball..."
	@echo "${GRAY}xz -vf bin/urbanite.tar"
	@xz -vf bin/urbanite.tar
	@echo "${RESET}...done"

deb: $(BIN)/urbanite
	@echo "Running build-deb script..."
	@bash ./build-deb.sh 
	@echo "...done"

install:
	@echo "Installing Urbanite in $(bindir)..."
	@echo "${GRAY}install $(BIN)/urbanite $(bindir)${RESET}"
	@install $(BIN)/urbanite $(bindir)
	
	@echo "Installing the default fonts in $(sharedir)..."
	@echo "${GRAY}mkdir $(mkdiropts) $(sharedir)"
	@mkdir $(mkdiropts) $(sharedir)
	@echo "install $(FONT)/* $(sharedir)"
	@install $(FONT)/* $(sharedir)
	@echo "${RESET}...done"

uninstall:
	@echo "Uninstalling Urbanite from $(bindir)..."
	@echo "${GRAY}rm -i $(bindir)/urbanite${RESET}"
	@rm -i $(bindir)/urbanite

	@echo "Removing the $(sharedir) directory..."
	@echo "${GRAY}rm -ir $(sharedir)${RESET}"
	@rm -ir $(sharedir)
	@echo "...done :("

clean:
	@echo "Cleaning build files..."
	@echo "${GRAY}rm -rvf $(OBJ)"
	@rm -rvf $(OBJ)
	@echo "${RESET}"
#	@echo "${GRAY}rm -rv $(BIN)${RESET}"
#	@rm -rvf $(BIN)