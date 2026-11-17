CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17
TARGET = daytime_client
SRC = daytime_client.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)

.PHONY: all clean
