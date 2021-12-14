
TARGET= run.out
CC= gcc
CFLAGS= -ansi -g -pedantic
OBJS= game.o round.o player.o deck.o vector.o main.o sort.o ui.o

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)
	
game.o: game.c 
	$(CC) $(CFLAGS) -I./ -c game.c

round.o : round.c
	$(CC) $(CFLAGS) -I./ -c round.c

player.o : player.c 
	$(CC) $(CFLAGS) -I./ -c player.c

deck.o : deck.c
	$(CC) $(CFLAGS) -I./ -c deck.c

vector.o : vector.c
	$(CC) $(CFLAGS) -I./  -c vector.c

ui.o : ui.c ui.h
	$(CC) $(CFLAGS) -I./ -c ui.c

main.o : main.c 
	$(CC) $(CFLAGS) -I./ -c main.c


sort.o : /home/leon/HeartGame/sort.c 
	$(CC) $(CFLAGS) -I/home/leon/HeartGame/ -c /home/leon/HeartGame/sort.c


clean:
	rm -f $(TARGET) $(OBJS)
