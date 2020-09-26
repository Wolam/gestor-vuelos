#include <mysql.h>
#include <stdio.h>

main() {
	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	
	char *server = "192.168.0.10";
	char *user = "JosephV27";
	char *password = "Saprisista47"; /* set me first */
	char *database = "bd_aviones";
	
	conn = mysql_init(NULL);
	
	/* Connect to database */
	if (!mysql_real_connect(conn, server, user, password, 
                                      database, 0, NULL, 0)) {
		fprintf(stderr, "%s\n", mysql_error(conn));
		exit(1);
	}
	
	/* send SQL query */
	if (mysql_query(conn, "select * from ciudad")){
		fprintf(stderr, "%s\n", mysql_error(conn));
		exit(1);
	}
   
	res = mysql_use_result(conn);
	
	/* output table name */
	printf("MySQL Tables in mysql database:\n");
   
	while ((row = mysql_fetch_row(res)) != NULL)
		printf("%s-%s\n", row[0], row[1]);

   
	/* close connection */
	mysql_free_result(res);
	mysql_close(conn);
}