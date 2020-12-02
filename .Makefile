CXX = g++
EXEC = main
srcs = main.cpp
srcs += thing/thing.cpp
srcs += listthing.cpp

$(EXEC):
	$(CXX) -std=c++2a -o $@ -c $(srcs)

.PHONY: $(EXEC)
