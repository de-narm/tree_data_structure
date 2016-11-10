CC=gcc
CFLAGS=-Wall-Wextra
TARGET=tree
FILES=main.c

.PHONY: clean all

all: $(TARGET)
$(TARGET):	$(FILES)
	$(CC) -o $(TARGET) $(FILES) $(CFLAGS)

clean:
	rm -f $(TARGET)
