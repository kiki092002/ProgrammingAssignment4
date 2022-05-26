OBJS = inFest.o gridFlea.o P4.o
CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG) -g
LFLAGS = -Wall $(DEBUG) -g
p4: $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o P4
p4.o: P4.cpp 
	$(CC) $(CFLAGS) P4.cpp
inFest.o: inFest.cpp inFest.h
	$(CC) $(CFLAGS) inFest.cpp
gridFlea.o: gridFlea.cpp gridFlea.h
	$(CC) $(CFLAGS) gridFlea.cpp
clean:
	\rm *.o P4
