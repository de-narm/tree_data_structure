CC=gcc
CFLAGS=-Wall -Wextra
LIBS=-lm
TARGET=_test
FILES=main.c
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
