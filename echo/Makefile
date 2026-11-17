CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17
TARGET = echo_client
SRC = echo_client.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)

.PHONY: all clean
