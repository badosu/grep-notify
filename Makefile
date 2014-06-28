PREFIX    = /usr/local

LIBS = -lnotify -lgdk_pixbuf-2.0 -lgio-2.0 -lgobject-2.0 -lglib-2.0
SRC = grep-notify.c

all:
	gcc -o grep-notify -pthread -I/usr/include/gdk-pixbuf-2.0 -I/usr/include/libpng16 -I/usr/include/glib-2.0 -I/usr/lib/glib-2.0/include $(LIBS) $(SRC)

clean:
	rm -rf *o grep-notify

install: all
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	cp grep-notify $(DESTDIR)$(PREFIX)/bin/
	chmod 755 $(DESTDIR)$(PREFIX)/bin/grep-notify

uninstall:
	rm -f $(DESTDIR)$(PREFIX)/bin/grep-notify
