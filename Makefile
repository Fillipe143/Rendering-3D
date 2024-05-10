.SILENT:

CXX = g++
CXXFLAGS = -std=c++20 -Wall -lraylib

f=cube
SRCS = src/$(f).cpp
TARGET = bin/$(f)

build:
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

run: build
	./$(TARGET)
