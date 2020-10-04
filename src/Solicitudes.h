#include <stdio.h>
#include <string.h>
#include <mysql.h>
#include <stdlib.h>
#include "Constantes.h"

MYSQL *conexion;
MYSQL_RES *resultado;
MYSQL_ROW reg;

void realizar_conexion()
{
	conexion = mysql_init(NULL);

	if (!mysql_real_connect(conexion, SRVR, USR_DBA,
							CONTR, NMB_BD, 0, NULL, 0))
	{
		fprintf(stderr, ERROR_CONEXION "%s\n", mysql_error(conexion));
		exit(EXIT_SUCCESS);
	}
}

void finalizar_conexion()
{
	mysql_close(conexion);
}

int realizar_consulta(char *consulta)
{

	/* enviar consulta SQL y verifica si hace error*/
	if (mysql_query(conexion, consulta))
	{
		if (!strncmp(mysql_error(conexion), ERROR_DUP, strlen(ERROR_DUP)))
			return COD_ERROR_DUP;
		else if (!strncmp(mysql_error(conexion), ERROR_FK, strlen(ERROR_FK)))
		{
			return COD_ERROR_FK;
		}
		else
		{
			// error de sintaxis de consulta
			return COD_ERROR_SINTX;
		}
	}
	else
	{
		return CONSULTA_EXITOSA;
	}
}

void mostrar_registros()
{
	resultado = mysql_store_result(conexion);
	int num_reg = mysql_num_rows(resultado);
	if (num_reg)
	{
		int i = 0;
		int col = mysql_field_count(conexion);
		while ((reg = mysql_fetch_row(resultado)) != NULL)
		{
			for (i = 0; i < col; i++)
				printf("%s \t", reg[i]);
			printf("\n\n");
		}
	}
	else
	{
		printf(REG_VACIOS);
	}
	mysql_free_result(resultado);
	mysql_next_result(conexion);
}


int mostrar_registros_asientos()
{
	resultado = mysql_store_result(conexion);
	int i_asiento = 1;
	int i_fila = 0;
	int num_reg = mysql_num_rows(resultado);
	char *fil_ant = "\0";
	while ((reg = mysql_fetch_row(resultado)) != NULL)
	{

		if (!strcmp(fil_ant, reg[i_fila]))
			printf("\t %s \t", reg[i_asiento]);
		else
		{
			printf("\n\n%s\t%s", reg[i_fila], reg[i_asiento]);
		}
		fil_ant = reg[i_fila];
	}

	printf("\n");

	mysql_free_result(resultado);
	mysql_next_result(conexion);
	return num_reg;
}


