#include <stdio.h>
#include <stdbool.h>
#include "mysql_connect.h"

void bd_connect(MYSQL *bd_descriptor, const char *name_bd){
	//MYSQL bd_descriptor;
	const char *host = HOST_BD;
	const char *user = USER_BD;
	const char *passwd = PASSW_BD;
	printf("name BD = %s\n", name_bd);
	mysql_init(bd_descriptor);
	if (!mysql_real_connect(bd_descriptor, host, user, passwd, name_bd,  0, NULL, 0)){
		printf("Соединенине не удалось\n");
		printf("%s\n", mysql_error(bd_descriptor));
		//mysql_select_db(bd_descriptor, name_bd);
		//return bd_descriptor;
	}
	else{
		printf("Успешное соединенине с БД:%s\n", name_bd);
		//return NULL;
	}
	if (mysql_query(bd_descriptor, "SET NAMES utf8")){
		printf("Запрос не выполнен.");
		printf("Error %d:%s\n",mysql_errno(bd_descriptor),mysql_error(bd_descriptor));
	}
}

void disconnect(char *name){

}

