CC = gcc
CFLAGS = -g

TARGET = simple-struct

all: $(TARGET)

$(TARGET): simple-struct.c ./../../serialize-deserialize.c
	$(CC) $(CFLAGS) simple-struct.c ./../../serialize-deserialize.c -o $(TARGET)

clean:
	rm -f $(TARGET)
