#ifndef MYSQL_CONNECT_H
#define MYSQL_CONNECT_H
bool connect(const char *host, char *name, char *user, char *password);
bool disconnect(char *name);

#endif // MYSQL_CONNECT_H
