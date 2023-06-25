CC = gcc
CFLAGS = -g

TARGET1=client
TARGET2=server

all: $(TARGET1) $(TARGET2)

$(TARGET1): $(TARGET1).c config.h
	$(CC) $(CFLAGS) $(TARGET1).c -o $(TARGET1)

$(TARGET2): $(TARGET2).c config.h
	$(CC) $(CFLAGS) $(TARGET2).c -o $(TARGET2)

clean:
	rm -f $(TARGET1) $(TARGET2)
