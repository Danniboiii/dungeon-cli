# Copyright (c) 2025 Daniel Sawczak
# This code is licensed under the MIT License. See LICENSE file for details.



# die quellcodedatein sind alle datein mit .cpp endung
SRCS := $(wildcard *.cpp) $(wildcard src/*.cpp)

# objektdatein werden aus allen quelldatein (.cpp endung) erstellt, indem die endung von .cpp zu .o geändert wird (text substitution)
OBJS := $(SRCS:.cpp=.o)

# name des entstehenden programms ist prog
TARGET = dungeon

# compiler ist g++ und compiler flags sind: alle warnungen und c++-standart ist c++17
CXX = g++
CXXFLAGS = -Wall -std=c++17 -g -Iinclude -lncurses

# für meine fertige datei calc brauche ich objektdatein zum zusammenfügen
$(TARGET): $(OBJS)
	$(CXX) $(CFLAGS) $(OBJS) -o $(TARGET)
# starte g++ mit den flags und c-std, verwende alle objektdatein, und linke sie zur zieldatei

#für die .o datein, die aus den .cpp datein entstehen gelten folgende regeln
# bzw. wenn du eine objektdatei brauchst (etwas.o), dann nimm etwas.cpp und erstelle sie daraus
# %.o ist ein platzhalter für die objektdatei, und %.cpp ist die dazugehörige quelldatei
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# '$<' bedeutet dass die eingabe datei .cpp ist, und $@ ist das ziel:
# g++ -Wall -std=c++17 -c main-calc.cpp -o main-calc.o


# alle erstellten objektdatein und die zieldatei prog wird gelöscht
clean:
	rm -f $(OBJS) $(TARGET)

#.PHONY: run
#run: $(TARGET)
#	./$(TARGET) 
# $(ARGS)

GREEN  := \033[0;32m
YELLOW := \033[1;33m
NC     := \033[0m  # No Color

ARGS := $(wordlist 2, $(words $(MAKECMDGOALS)), $(MAKECMDGOALS))

.PHONY: run
run: $(TARGET)
	@echo -e "$(GREEN)>>> Starte Programm: $(TARGET) $(ARGS)$(NC)"
	@./$(TARGET) $(ARGS)

%:
	@:

.PHONY: debug
debug: $(TARGET)
	cgdb ./$(TARGET)

.PHONY: valgrind
valgrind: $(TARGET)
	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all --error-exitcode=42 ./$(TARGET)

.PHONY: rebuild
rebuild: clean $(TARGET)

.PHONY: archive
archive:
	zip -r $(TARGET).zip *.cpp *.h makefile

.PHONY: info
info:
	@echo -e "$(YELLOW)--- Projektübersicht ---$(NC)"
	@echo -e "Quellcode-Dateien: $(SRCS)"
	@echo -e "Header-Dateien:    $(HEADERS)"
	@echo -e "Objektdateien:     $(OBJS)"
	@echo -e "Zielprogramm:      $(TARGET)"
	@echo -e "Compiler:          $(CXX)"
	@echo -e "Flags:             $(CXXFLAGS)"

# format Code based on different possible formats
# Possibilities: GOOGLE, WEBKIT, MICROSOFT, LLVM, MOZILLA, CHROMIUM, GNU
.PHONY: format
format:
	clang-format -i $(wildcard *.cpp) $(wildcard *.h) --style=WEBKIT

.PHONY: help
help:
	@echo "Verfügbare Commands:"
	@echo "  make         - baut das Programm"
	@echo "  make run     - startet das Programm"
	@echo "  make debug   - startet CGDB mit dem Programm"
	@echo "  make clean   - löscht .o-Dateien und Executable"
	@echo "  make format  - formatiert Quellcode mit clang-format"
	@echo "  make rebuild - baut alles neu"
	@echo "  make archive - speichert alle Datein als ZIP ab"
	@echo "  make info    - zeigt Datein, Compiler und Flags"

.DEFAULT_GOAL := $(TARGET)


