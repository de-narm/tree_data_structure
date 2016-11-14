CC=gcc
CFLAGS=-Wall -Wextra
LIBS=-lm
TARGET=_test
FILES=main.c btree_test.c svg_test.c assert.c ../btree/insert.c ../btree/search.c ../btree/btree.c ../btree/svg.c
.PHONY: clean all test

all: $(TARGET)
$(TARGET):	$(FILES)
	$(CC) -o $(TARGET) $(FILES) $(CFLAGS) $(LIBS)
test:
	make all
	./_test

clean:
	rm -f $(TARGET)
	rm -f *.test.svg
