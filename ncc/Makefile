CFLAGS=-std=c11 -g -static

ncc: ncc.c

test: ncc
	bash ./test.sh

clean:
	rm -f ncc *.o *~ tmp*

.PHONY: test clean
