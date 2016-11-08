CC=g++
CFLAGS=-c -Wall -std=c++0x
LDFLAGS=
SOURCES=$(wildcard *.cpp)
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=konstpro
LIBS := -L/usr/local/lib -lwthttp -lwt -lboost_regex -lboost_signals -lboost_system -lboost_thread -lboost_filesystem -lboost_date_time -lwtdbo -lwtdbosqlite3

all: $(SOURCES) $(EXECUTABLE)
		
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@ $(LIBS)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm $(EXECUTABLE) $(OBJECTS)
