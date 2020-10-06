/**
 * INSTITUTO TECNOLOGICO DE COSTA RICA
 * I PROYECTO PROGRAMADO DE LENGUAJES DE PROGRAMACION
 * Estudiantes: Joseph Valenciano / Wilhelm Carstens
 * Carnets: 2019039864 / 2019344583
 * Profesor: Allan Rodriguez Davila
 * Fecha 05/10/2020
 */

typedef struct avion
{
	char *marca;
	char *modelo;
	char *anio;
	char *matricula;
} avion;

/**
  * avion *solicitar_datos_av()
  * Entradas: no tiene entradas
  * Salidas: devuelve un puntero al struct 
  * Pide los datos del avion y los inserta en el struct
  */

avion *solicitar_datos_av()
{
    avion *ref_av;
    ref_av = (avion *)malloc(sizeof(avion));

    char *matricula = pedir_str_input("<MATRICULA AVION> ");
    strcat(matricula, ",");
    ref_av->matricula = matricula;

    char *marca = pedir_str_input("\n<MARCA AVION> ");
    char tmp[15] = {"\'"};
    strcat(tmp, marca);
    strcat(tmp, "\'");
    strcat(tmp, ",");
    ref_av->marca = tmp;

    char *modelo = pedir_str_input("\n<MODELO AVION> ");
    strcat(modelo, ",");
    ref_av->modelo = modelo;

    char *anio = pedir_str_input("\n<AÑO AVION> ");
    ref_av->anio = anio;

    return ref_av;
}

/**
  * char *formatear_cons_insercion_avion(avion *av_nuevo)
  * Entradas: Un puntero que apunta al struct
  * Salidas: Un char de tipo puntero
  * Formatea estos datos para poder insertarlos a la base de datos
  */

char *formatear_cons_insercion_avion(avion *av_nuevo)
{
	char *cons;
	cons = calloc(TAM_CONSULTA, sizeof(char));
	strcpy(cons, CONSULTA_INSERCION_AVION);
	strcat(cons, av_nuevo->matricula);
	strcat(cons, av_nuevo->marca);
	strcat(cons, av_nuevo->modelo);
	strcat(cons, av_nuevo->anio);
	strcat(cons, ")");
	return cons;
}

/**
  * void insertar_avion(avion *av_nuevo)
  * Entradas: Un puntero que apunta al struct
  * Salidas: No devuelve nada
  * Valida e inserta el avion a la base de datos
  */

void insertar_avion(avion *av_nuevo)
{
	int res = realizar_consulta(formatear_cons_insercion_avion(av_nuevo));
	if (!res)
	{
		av_nuevo->matricula[strlen(av_nuevo->matricula)-1] = '\0';
		printf(VERDE "<Insertado avion %s> \n" END_CLR, av_nuevo->matricula);
	}	
	else
	{
		printf(ERROR_CONSULTA "<Avion %s ya insertado> \n", av_nuevo->matricula);
	}
	av_nuevo->anio = NULL;
	av_nuevo->marca = NULL;
	av_nuevo->modelo = NULL;
	av_nuevo->matricula = NULL;
	free(av_nuevo);
}

/**
  * void eliminar_avion()
  * Entradas: No tiene parametros
  * Salidas: No devuelve nada
  * Valida y elimina el avion de la base de datos
  */

void eliminar_avion()
{
	char *cons = calloc(TAM_CONSULTA, sizeof(char));
	strcpy(cons, CONSULTA_ELIMINAR_AVION);
	strcat(cons, pedir_str_input("<Matricula a eliminar> "));
	strcat(cons, ")");
	int res = realizar_consulta(cons);
	if (res == COD_ERROR_FK)
	{
		printf(ERROR_CONSULTA "<Avion se encuentra en vuelo>\n");
	}
	else if (res == COD_ERROR_SINTX)
	{
		printf(ERROR_CONSULTA "<Matricula incorrecta>\n");
	}
	else
	{
		printf(BLUE "RESULTADO ELIMINACION:" END_CLR);
		mostrar_registros();
	}
	free(cons);
}

/**
  * void mostrar_aviones()
  * Entradas: No tiene parametros
  * Salidas: No devuelve nada
  * Muestra los aviones al usuario, filtrados por la marca.
  */

void mostrar_aviones()
{
	char *cons = calloc(TAM_CONSULTA, sizeof(char));
	strcpy(cons, CONSULTA_MOSTRAR_AVIONES);
	char tmp[15] = {"\'"};
	strcat(tmp, pedir_str_input("<MARCA A MOSTRAR> "));
	strcat(tmp, "\'");
	strcat(cons, tmp);
	strcat(cons, ")");
	printf(VERDE "[MATRICULA]\t[MOD]\t[ANIO]\n" END_CLR);
	realizar_consulta(cons);
	mostrar_registros();
	free(cons);
}

