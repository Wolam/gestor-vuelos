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
void solicitar_opcion_registro_av();
void eliminar_avion();
void mostrar_avion();


typedef struct avion{
	char* marca;
	char* modelo;
	char* anio;
	char* matricula;
}avion;

avion* solicitar_datos_av();

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

	/* enviar consulta SQL */
	if (mysql_query(conexion, consulta))
	{
		if (!strncmp(mysql_error(conexion), ERROR_DUP, strlen(ERROR_DUP)))
			return COD_ERROR_DUP;
		else if(!strncmp(mysql_error(conexion), ERROR_FK, strlen(ERROR_FK)))
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

void mostrar_registros_asientos()
{
	resultado = mysql_store_result(conexion);
//	int num_reg = mysql_num_rows(resultado);
	int i_asiento = 1; int i_fila = 0;
	char* fil_ant = "\0"; 
	while ((reg = mysql_fetch_row(resultado)) != NULL)
	{
		
		if(!strcmp(fil_ant,reg[i_fila]))
			printf("\t %s \t", reg[i_asiento]);
		else
		{	
			
			printf("\n\n%s\t%s",reg[i_fila],reg[i_asiento]);
		}
		fil_ant = reg[i_fila];
	}
		
	printf("\n");
	
	mysql_free_result(resultado);
	mysql_next_result(conexion);
}
char* formatear_cons_insercion_avion(avion* av_nuevo)
{
	char* cons;
	cons = calloc(TAM_CONSULTA,sizeof(char));
	strcpy(cons,CONSULTA_INSERCION_AVION);
	strcat(cons,av_nuevo->matricula);
	strcat(cons,av_nuevo->marca);
	strcat(cons,av_nuevo->modelo);
	strcat(cons,av_nuevo->anio);
	strcat(cons,")");
	return cons;
}

void insertar_avion(avion* av_nuevo)
{	
	int res = realizar_consulta(formatear_cons_insercion_avion(av_nuevo));
	if (!res)
		printf(VERDE"<Insertado avion %s>"END_CLR,av_nuevo->matricula);
	else 
	{
		printf(ERROR_CONSULTA"<Avion %s ya insertado> \n",av_nuevo->matricula);	
	}
	av_nuevo->anio = NULL; av_nuevo->marca=NULL; av_nuevo->modelo=NULL; av_nuevo->matricula=NULL;
	free(av_nuevo);

}

void mostrar_estadisticas_ventas()
{
	if (!realizar_consulta(ESTADISTICAS_VENTAS))
	{
		printf(VERDE "VUELOS MAS VENDIDOS\n\nCOD.VUELO \tVENTAS \n"END_CLR);
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
		printf(VERDE"VUELOS MAS RESERVADOS\n\nCOD.VUELO \tRESERVACIONES \n"END_CLR);
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

	printf(VERDE"[Org] \t[Hora de Salida]\t[Dest]\t[Hora  de llegada] [Matricula]\n"END_CLR);
	realizar_consulta(formatear_cons_vuelo(CONSULTA_VUELO, id_vuelo));
	mostrar_registros();
}

void mostrar_asientos_en_vuelo(char *id_vuelo)
{
	printf(VERDE"[ Tipo  ]  [Costo]\n[Asiento]\n"END_CLR);
	realizar_consulta(formatear_cons_vuelo(CONSULTA_COSTO_ASIENTOS, id_vuelo));
	mostrar_registros();
	

	printf(VERDE "[FILA] [ASIENTOS]\n" END_CLR);
	realizar_consulta(formatear_cons_vuelo(CONSULTA_POS_ASIENTOS, id_vuelo));
	mostrar_registros_asientos();

	printf(VERDE"   Asientos\n[Libres] [Ocupados]\n"END_CLR);
	realizar_consulta(formatear_cons_vuelo(CONSULTA_CANT_ASIENTOS, id_vuelo));
	mostrar_registros();

	
}

void mostrar_reservaciones_en_vuelo(char *id_vuelo)
{

	realizar_consulta(formatear_cons_vuelo(CONSULTA_INFO_RESRV_POR_VUELO, id_vuelo));
	printf(VERDE"[ID_Rsv] [Fila] [Tipo] [Numero] [Pasaporte] [Nombre]\n"END_CLR);
	mostrar_registros();


	realizar_consulta(formatear_cons_vuelo(CONSULTA_COSTO_RESRV_POR_VUELO, id_vuelo));
	printf(VERDE"[ID_Rsv] [Monto] [Num asientos]\n"END_CLR);
	mostrar_registros();
}
