CC = gcc
CFLAGS = -Wall -Wextra -O2
TARGET = secure_delete

all: $(TARGET)

$(TARGET): delete.c
	$(CC) $(CFLAGS) -o $(TARGET) delete.c

clean:
	rm -f $(TARGET)
