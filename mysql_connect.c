#include <stdio.h>
#include <stdbool.h>
#include <mysql.h>
#include "mysql_connect.h"

bool connect(const char *host, char *name, char *user, char *password){
	if (host) {
		printf("Удалось подсоединиться к БД %s.\n", name);
	}
	else {
		printf("Не удалось присоединиться к БД %s.\n", name);
	}
	return true;
}

bool disconnect(char *name){

}

