#include <stdio.h>
#include <mysql.h>
#include "Constantes.h"

#define USR_DBA "wil_bd"
#define NMB_BD "bd_aviones"
#define CONTR "wil_bd_psswrd"
#define SRVR "localhost"


MYSQL *conexion;
MYSQL_RES *resultado;
MYSQL_ROW fila;

void
cerrar_conexion()
{
    //Terminar resultados y conexion
	mysql_free_result(resultado);
	mysql_close(conexion);

}


void realizar_conexion()
{
    conexion = mysql_init(NULL);
    
    if (!mysql_real_connect(conexion, SRVR, USR_DBA, 
                                CONTR, NMB_BD, 0, NULL, 0)) {
		fprintf(stderr,ERROR_CONEXION "%s\n", mysql_error(conexion));
        cerrar_conexion();
		exit(TRUE);
	}

}

const char* realizar_consulta(char* consulta)
{

    /* enviar consulta SQL */
	if (mysql_query(conexion, consulta)){
		//fprintf(stderr, ERROR_CONSULTA "%s\n", mysql_error(conexion));
		return mysql_error(conexion);
	}
	else{
		//resultado = mysql_use_result(conexion);

    	//while ((fila = mysql_fetch_row(resultado)) != NULL)
		//	printf("%s-%s\n", fila[0], fila[1]);
		return NULL;
	}
    

}
