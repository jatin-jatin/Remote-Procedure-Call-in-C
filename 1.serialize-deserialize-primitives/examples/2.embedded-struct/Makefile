CC = gcc
CFLAGS = -g

TARGET = embedded-struct

all: $(TARGET)

$(TARGET): $(TARGET).c ./../../serialize-deserialize.c employee_t.c
	$(CC) $(CFLAGS) $(TARGET).c ./../../serialize-deserialize.c employee_t.c -o $(TARGET)

clean:
	rm -f $(TARGET)
