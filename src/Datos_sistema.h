#include <stdio.h>
#include <string.h>
#include <mysql.h>
#include "Constantes.h"

#define USR_DBA "wil_bd"
#define NMB_BD "bd_aviones"
#define CONTR "wil_bd_psswrd"
#define SRVR "localhost"


#define ESTADISTICAS_VENTAS "CALL estadistica_ventas"
#define ESTADISTICAS_RESERVACIONES "CALL estadistica_personas"


MYSQL *conexion;
MYSQL_RES *resultado;
MYSQL_ROW reg;

void
cerrar_conexion()
{
    //Terminar resultados y conexion
	mysql_free_result(resultado);
	mysql_close(conexion);
	exit(SALIDA_EXITOSA);

}


void realizar_conexion()
{
    conexion = mysql_init(NULL);
    
    if (!mysql_real_connect(conexion, SRVR, USR_DBA, 
                                CONTR, NMB_BD, 0, NULL, 0)) {
		fprintf(stderr,ERROR_CONEXION "%s\n", mysql_error(conexion));
        cerrar_conexion();
		exit(TIEMPO_EJECUCION);
	}

}

int realizar_consulta(char* consulta)
{

    /* enviar consulta SQL */
	if (mysql_query(conexion, consulta)){
		//fprintf(stderr, ERROR_CONSULTA "%s\n", mysql_error(conexion));
		if (!strncmp(mysql_error(conexion),ERROR_DUP,strlen(ERROR_DUP)))
			return COD_ERROR_DUP;
		else{
			// error de sintaxis de consulta
			return COD_ERROR_SINTX;
		}
	}
	else{
		return SALIDA_EXITOSA;
	}
}


void mostrar_estadisticas_ventas()
{
	if (realizar_consulta(ESTADISTICAS_VENTAS)==1){
		resultado = mysql_store_result(conexion);
		while ((reg = mysql_fetch_row(resultado)) != NULL){
			printf("VUELOS MAS VENDIDOS\n\nCOD.VUELO [%s] VENTAS: %s\n\n", reg[0], reg[1]);
		}
	
	} else{
		printf(ERROR_CONSULTA "[ Verificar estadisticas de ventas ] \n");
		//mysql_free_result(resultado);
	}
	mysql_next_result(conexion);
}

void mostrar_estadisticas_reservaciones()
{
	if (realizar_consulta(ESTADISTICAS_RESERVACIONES)== 1){
		resultado = mysql_store_result(conexion);
		while ((reg = mysql_fetch_row(resultado)) != NULL){
			printf("VUELOS MAS RESERVADOS\n\nCOD.VUELO [%s] RESERVACIONES: %s\n\n", reg[0], reg[1]);
		}
	}else{
		printf(ERROR_CONSULTA "[ Verificar estadisticas de reservaciones ] \n");
	}
	mysql_free_result(resultado);
	mysql_next_result(conexion);
}