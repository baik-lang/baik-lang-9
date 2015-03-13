
CC?=gcc
CFLAGS?=-DUSE_GD -DUSE_CGI -DUSE_WEBSTYLE -DUSE_MYSQL -DUSE_SQLITE -DLINUX
CFLAGS+=-I/usr/include -I/usr/local/include -I/usr/include/mysql -L/usr/lib -L/usr/local/lib -L/usr/lib64/mysql
#CFLAGS+=-Wall -Wwrite-strings -pedantic -std=gnu99
LDFLAGS+=-lpthread -lm -lsqlite3 -lgd -lmysqlclient
LDLIBS=

GENERIC_OBJS=tbaik.o baik_ident.o baik_stack.o baik_expression.o \
			baik_compare.o baik_factor.o interpreter.o interpreterSub.o \
			interpreterClass.o sqlite_common.o my_common.o

.PHONY: all clean install

all: baik

%.o : %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

baik: $(GENERIC_OBJS)
	$(CC) $(LDFLAGS) -o baik $+ $(LDLIBS)

clean:
	rm -f baik *.o
	rm -rf dist

install:	
	mkdir -p $(DESTDIR)/usr/bin/
	cp baik $(DESTDIR)/usr/bin/
