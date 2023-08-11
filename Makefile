CC := g++
CFLAGS := -Wall -g
TARGET := test

# $(wildcard *.cpp /xxx/xxx/*.cpp): get all .cpp files from the current directory and dir "/xxx/xxx/"
SRCS := $(wildcard *.cpp)
# $(patsubst %.cpp,%.o,$(SRCS)): substitute all ".cpp" file name strings to ".o" file name strings
OBJS := $(patsubst %.cpp,%.o,$(SRCS))

all: $(TARGET)
	./$(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $^ -Llib -lsfml-graphics -lsfml-window -lsfml-system
%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -Iinclude
clean:
	rm -rf $(TARGET) *.o
	
.PHONY: all clean