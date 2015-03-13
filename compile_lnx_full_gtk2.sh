

gcc -m64 -o baik -DUSE_ALSA -DUSE_CGI -DUSE_WEBSTYLE -DUSE_SSL -DUSE_GTK2 -DUSE_MYSQL -DUSE_SQLITE -DLINUX -I/usr/include -I/usr/include/mysql -I/usr/local/include -L/usr/lib -L/usr/lib64 -L/usr/local/lib -L/usr/lib64/mysql -L/usr/lib/mysql `pkg-config --cflags --libs gtk+-2.0` tbaik.c baik_ident.c baik_stack.c baik_expression.c baik_compare.c baik_factor.c interpreter.c interpreterSub.c interpreterClass.c my_common.c sqlite_common.c pq_common.c -lpthread -lm -lssl -lsqlite3 -lmysqlclient -lgd -lasound `pkg-config --cflags --libs gtk+-2.0`


