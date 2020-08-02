CFLAGS=-std=c11 -g -static
SRCS=$(wildcard *.c)
OBJS=$(SRCS: .c=.o)

$(OBJS): ncc.h

ncc: $(OBJS)
	$(CC) -o ncc $(OBJS) $(LDFLAGS)

test: ncc
	bash ./test.sh

clean:
	rm -f ncc *.o *~ tmp*

.PHONY: test clean
