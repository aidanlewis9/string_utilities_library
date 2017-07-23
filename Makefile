CC=		gcc
CFLAGS=		-g -gdwarf-2 -Wall -std=gnu99
LD=		gcc
LDFLAGS=	-L.
AR=		ar
ARFLAGS=	rcs

TARGETS=	libstringutils.a \
		libstringutils.so \
		translate-static \
		translate-dynamic

all:		$(TARGETS)

stringutils.o: stringutils.c
	$(CC) $(CFLAGS) -fPIC -c -o $@ $^

libstringutils.a: stringutils.o
	$(AR) $(ARFLAGS) $@ $^

libstringutils.so: stringutils.o
	$(LD) $(LDFLAGS) -shared -o $@ $^

translate.o: translate.c
	$(CC) $(CFLAGS) -c -o $@ $^

translate-dynamic: translate.o
	$(LD) $(LDFLAGS) -o $@ $^ -lstringutils

translate-static: translate.o
	$(LD) $(LDFLAGS) -static -o $@ $^ -lstringutils

# TODO: Add rules for libstringutils.a libstringutils.so

test:			test-libstringutils test-translate

test-libstringutils:	libstringutils.so test_stringutils.py
	./test_stringutils.py -v

test-translate:		libstringutils.so test_translate.py
	./test_translate.py -v

clean:
	rm -f $(TARGETS) *.o
