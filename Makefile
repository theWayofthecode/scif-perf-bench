
CC=icc
LIBS=-lscif -lpthread
CFLAGS_HOST=-std=c++0x -Wall
CFLAGS_MIC=$(CFLAGS_HOST) -mmic

SRC_DIR=./src
BIN_DIR=./build

BINS= $(BIN_DIR)/source $(BIN_DIR)/sink

HEADERS=$(wildcard ./src/*.h)

all: $(BINS)

#MIC

$(BIN_DIR)/source: $(BIN_DIR)/source.o $(BIN_DIR)/MSGSender.o $(HEADERS)
	$(CC) $(CFLAGS_MIC) $(BIN_DIR)/source.o $(BIN_DIR)/MSGSender.o $(LIBS) -o $@

$(BIN_DIR)/source.o : $(SRC_DIR)/source.cpp $(HEADERS)
	$(CC) $(CFLAGS_MIC) -c $< -o $@

$(BIN_DIR)/MSGSender.o : $(SRC_DIR)/MSGSender.cpp $(HEADERS)
	$(CC) $(CFLAGS_MIC) -c $< -o $@

#HOST

$(BIN_DIR)/sink: $(BIN_DIR)/MSGReceiver.o $(BIN_DIR)/sink.o $(HEADERS)
	$(CC) $(CFLAGS_HOST) $(BIN_DIR)/MSGReceiver.o $(BIN_DIR)/sink.o $(LIBS) -o $@

$(BIN_DIR)/sink.o : $(SRC_DIR)/sink.cpp $(HEADERS)
	$(CC) $(CFLAGS_HOST) -c $< -o $@

$(BIN_DIR)/MSGReceiver.o : $(SRC_DIR)/MSGReceiver.cpp $(HEADERS)
	$(CC) $(CFLAGS_HOST) -c $< -o $@
	
clean:
	rm -f $(BIN_DIR)/*