

LIBS_FILE = -lpthread

CC=g++
CFLAGS=-g -O0 -DMACOS
OBJS= main.o JSThread.o JSTcpClient.o


BIN= peerClient
all: $(BIN)
peerClient: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS_FILE) -o $@
%.o:	%.cpp
	$(CC) $(CFLAGS) -c $<
clean:
	rm -rf $(OBJS) $(BIN) *.core

