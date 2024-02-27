
CC = gcc
CFLAGS = -Wall -DPLATFORM_DESKTOP

SRC = main.c
TARGET = even-or-odd 

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -f $(TARGET)

