CXX = g++
CPPFLAGS = -Wall -g

all: hashed

hashed: hashed.cpp Hashtable.h
	$(CXX) $(CPPFLAGS) $^ -o $@

.PHONY: clean
clean:
	rm -rf hashed