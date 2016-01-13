

LIBS_FILE = -lpthread $(shell pkg-config --libs libpjproject)

CC=g++
CFLAGS=-g -O0 -DMACOS $(shell pkg-config --cflags libpjproject)
OBJS= main.o JSThread.o JSTcpClient.o JSPeerClient.o JSPeerProtocol.o icedemo.o JSIceClient.o

BIN= peerClient
all: $(BIN)
peerClient: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS_FILE) -o $@
%.o:	%.cpp
	$(CC) $(CFLAGS) -c $<
clean:
	rm -rf $(OBJS) $(BIN) *.core

