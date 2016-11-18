CC=gcc
CFLAGS=-Wall -Wextra
LIBS=-lm
TARGET=tree
FILES=main.c btree/insert.c btree/delete.c btree/search.c btree/btree.c btree/svg.c btree/compare.c
.PHONY: clean all test

all: $(TARGET)
$(TARGET):	$(FILES)
	$(CC) -o $(TARGET) $(FILES) $(CFLAGS) $(LIBS)

clean:
	rm -f $(TARGET)
