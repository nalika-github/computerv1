# C++ Polynomial Solver Project
NAME = computor

# Directories
SRC_DIR = src
HEADER_DIR = header
OBJ_DIR = obj
BIN_DIR = bin

# Source and Object files
SOURCES = $(SRC_DIR)/main.cpp \
		  $(SRC_DIR)/parseTree.cpp \

HEADERS = $(HEADER_DIR)/parseTree.h \
		  $(HEADER_DIR)/computor.h \
		  $(HEADER_DIR)/validation.h

OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SOURCES))

# Compiler settings
CXX = g++
CXXFLAGS = -Wall -Werror -Wextra -std=c++11 -I$(HEADER_DIR)
LDFLAGS = -lm

# Targets
all: $(BIN_DIR)/$(NAME)

$(BIN_DIR)/$(NAME): $(OBJECTS) | $(BIN_DIR)
	$(CXX) $(OBJECTS) -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(HEADERS) | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	@mkdir -p $(BIN_DIR)

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -rf $(BIN_DIR)

re: fclean all

run: all
	./$(BIN_DIR)/$(NAME)

debug:
	@echo "OBJECTS = $(OBJECTS)"

.PHONY: all clean fclean re run debug

re: fclean all

.PHONY : all clean fclean re