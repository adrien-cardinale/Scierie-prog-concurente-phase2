CSRCS=$(wildcard *.cpp)
COBJS=$(patsubst %.cpp,%.o,$(CSRCS))
EXEC?=scierie.out

CC=clang++
CFLAGS=-std=c++14 -g -Wall -pedantic
LDFLAGS=-lsfml-graphics -lsfml-window -lsfml-system -pthread

all: build

build: $(EXEC)

-include $(COBJS:.o=.d)

$(EXEC): $(COBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CC) -c $(CFLAGS) -o $@ $< -MMD -MF $(@:.o=.d)

lib: lib$(EXEC).so

lib$(EXEC).so: $(CSRCS)
	$(CC) -shared -o $@ $^ -fPIC

clean:
	$(RM) $(EXEC) *.o a.out lib$(EXEC).so $(COBJS:.o=.d)

.PHONY: all format build lib test
