CC = g++
CFlags = -Wall -Werror -pedantic -std=c++14
LIBS = -lboost_unit_test_framework -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
DEPS = CircularBuffer.h StringSound.h

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -o $@ -c $<

KSGuitarSim: CircularBuffer.o StringSound.o KSGuitarSim.o
	$(CC) $(CFLAGS) -o KSGuitarSim $^ $(LIBS)

all: KSGuitarSim

clean:
	rm *.o KSGuitarSim
