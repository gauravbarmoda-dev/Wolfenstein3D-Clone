CXX = g++
CXXFLAGS = -Wall -Wextra -O2
LDFLAGS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

SRCS = game.cpp player.cpp map2D.cpp map3D.cpp sprite.cpp screen.cpp
BIN_DIR = bin
OBJS = $(addprefix $(BIN_DIR)/, $(SRCS:.cpp=.o))
EXEC = $(BIN_DIR)/doom_game

all: $(EXEC)

$(EXEC): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(OBJS) -o $(EXEC) $(LDFLAGS)

$(BIN_DIR)/%.o: %.cpp
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

run:
	$(MAKE) clean
	$(MAKE) all
	./$(EXEC)

clean:
	rm -rf $(BIN_DIR)
