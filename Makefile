CFLAGS=

all: 0hh1 animate

%: %.c
	gcc $(CFLAGS) -o $@ $<
