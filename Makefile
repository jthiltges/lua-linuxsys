DESTDIR=
LUALIB=/usr/lib/lua/5.1
LUAPKG=/usr/share/lua/5.1
DOC=/usr/share/doc/lua-linuxsys

NAME= linuxsys
CFLAGS= $(WARN) -O2 -fPIC
WARN= -ansi -pedantic -Wall

LIB= $(NAME)_c
T= $(LIB).so
OBJS= $(LIB).o

all:	$T

o:	$(LIB).o

so:	$T

$T:	$(OBJS)
	$(CC) -o $@ -shared $(OBJS)

clean:
	rm -f $(OBJS) $T core core.* a.out

install: all
	mkdir -p            $(DESTDIR)/$(LUALIB)
	install $T          $(DESTDIR)/$(LUALIB)
	mkdir -p            $(DESTDIR)/$(LUAPKG)
	install $(NAME).lua $(DESTDIR)/$(LUAPKG)
	mkdir -p            $(DESTDIR)/$(DOC)
	install README.md   $(DESTDIR)/$(DOC)

