#include <stdio.h>
#include <string.h>
#include <mysql.h>
#include "Constantes.h"

// Funciones de prototipo
FILE *abrir_archivo(char *ruta, char *modo);
int insertar_usuario(char *usuario);
char *formatear_fecha(char *fecha);
char *formatear_usuario(char *usuario);
char *obtener_reporte(int res_consulta);
char *pedir_str_input(char *msj);
char pedir_caracter_input(char *msj);
void mostrar_menu(char *tipo_menu);
void ejecutar_opcion_menu_principal();
void ejecutar_opcion_submenu_general();
void ejecutar_opcion_submenu_operativo();
void cargar_usuarios(char *nombre_archivo);
void estado_vuelo();

MYSQL *conexion;
MYSQL_RES *resultado;
MYSQL_ROW reg;

void cerrar_conexion()
{
	//Terminar resultados y conexion
	mysql_close(conexion);
	exit(SALIDA_EXITOSA);
}

void realizar_conexion()
{
	conexion = mysql_init(NULL);

	if (!mysql_real_connect(conexion, SRVR, USR_DBA,
							CONTR, NMB_BD, 0, NULL, 0))
	{
		fprintf(stderr, ERROR_CONEXION "%s\n", mysql_error(conexion));
		cerrar_conexion();
		exit(TIEMPO_EJECUCION);
	}
}

int realizar_consulta(char *consulta)
{

	/* enviar consulta SQL */
	if (mysql_query(conexion, consulta))
	{
		if (!strncmp(mysql_error(conexion), ERROR_DUP, strlen(ERROR_DUP)))
			return COD_ERROR_DUP;
		else
		{
			// error de sintaxis de consulta
			return COD_ERROR_SINTX;
		}
	}
	else
	{
		return SALIDA_EXITOSA;
	}
}


void mostrar_registros()
{
	resultado = mysql_store_result(conexion);
	int num_reg = mysql_num_rows(resultado);
	if (num_reg)
	{
		int i = 0; int col = mysql_field_count(conexion);
		while ((reg = mysql_fetch_row(resultado)) != NULL)
		{
			for (i=0; i<col; i++)
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

void mostrar_estadisticas_ventas()
{
	if (!realizar_consulta(ESTADISTICAS_VENTAS))
	{
		printf("VUELOS MAS VENDIDOS\n\nCOD.VUELO \tVENTAS \n");
		mostrar_registros();
	}
	else
	{
		printf(ERROR_CONSULTA "[ Verificar estadisticas de ventas ] \n");
	}
}

void mostrar_estadisticas_reservaciones()
{
	if (!realizar_consulta(ESTADISTICAS_RESERVACIONES))
	{
		printf("VUELOS MAS RESERVADOS\n\nCOD.VUELO \tRESERVACIONES \n");
		mostrar_registros();
	}
	else
	{
		printf(ERROR_CONSULTA "[ Verificar estadisticas de reservaciones ] \n");
	}
}

char *formatear_cons_vuelo(char *consulta, char *id_vuelo)
{
	char *cons = calloc(TAM_CONSULTA, sizeof(char));
	strcpy(cons, consulta);
	strcat(cons, id_vuelo);
	strcat(cons, ")");
	return cons;
}

void mostrar_info_vuelo(char *id_vuelo)
{

	printf("MOSTRANDO INFO VUELO\n");
	realizar_consulta(formatear_cons_vuelo(CONSULTA_VUELO, id_vuelo));
	mostrar_registros();
}

void mostrar_asientos_en_vuelo(char *id_vuelo)
{
	printf("MOSTRANDO INFO ASIENTOS\n");
	realizar_consulta(formatear_cons_vuelo(CONSULTA_COSTO_ASIENTOS, id_vuelo));
	mostrar_registros();
	

	printf("MOSTRANDO POS ASIENTOS\n");
	realizar_consulta(formatear_cons_vuelo(CONSULTA_POS_ASIENTOS, id_vuelo));
	mostrar_registros();

	printf("MOSTRANDO POS ASIENTOS\n");
	realizar_consulta(formatear_cons_vuelo(CONSULTA_CANT_ASIENTOS, id_vuelo));
	mostrar_registros();

	
}

void mostrar_reservaciones_en_vuelo(char *id_vuelo)
{

	realizar_consulta(formatear_cons_vuelo(CONSULTA_INFO_RESRV_POR_VUELO, id_vuelo));
	printf("MOSTRANDO INFO RESERVA\n");
	mostrar_registros();


	realizar_consulta(formatear_cons_vuelo(CONSULTA_COSTO_RESRV_POR_VUELO, id_vuelo));
	printf("MOSTRANDO COSTO RESERVA\n");
	mostrar_registros();
}
