PREFIX	:= /usr/local

LIBS = $(shell pkg-config --libs --cflags libnotify)
SRC = grep-notify.c

all:
	gcc -o grep-notify $(LIBS) $(SRC)

clean:
	rm -rf *o grep-notify

install: all
	install -m0755 -D grep-notify $(DESTDIR)$(PREFIX)/bin/grep-notify

uninstall:
	rm -f $(DESTDIR)$(PREFIX)/bin/grep-notify
