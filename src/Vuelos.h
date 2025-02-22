/**
 * INSTITUTO TECNOLOGICO DE COSTA RICA
 * I PROYECTO PROGRAMADO DE LENGUAJES DE PROGRAMACION
 * Estudiantes: Joseph Valenciano / Wilhelm Carstens
 * Carnets: 2019039864 / 2019344583
 * Profesor: Allan Rodriguez Davila
 * Fecha 05/10/2020
 */

/**
  * char *formatear_cons_vuelo(char *consulta, char *id_vuelo)
  * Entradas: Dos char de tipo puntero
  * Salidas: Un char de tipo puntero
  * Formatea la consulta, para llamar a dicho procedimiento en mysql
  */

char *formatear_cons_vuelo(char *consulta, char *id_vuelo)
{
	char *cons = calloc(TAM_CONSULTA, sizeof(char));
	strcpy(cons, consulta);
	strcat(cons, id_vuelo);
	strcat(cons, ")");
	return cons;
}

/**
  * void mostrar_info_vuelo(char *id_vuelo)
  * Entradas: Un char de tipo puntero
  * Salidas: No retorna nada
  * Muestra la info del vuelo al usuario.
  */

void mostrar_info_vuelo(char *id_vuelo)
{

	printf(VERDE "[Org] \t[Hora de Salida]\t[Dest]\t[Hora  de llegada] [Matricula]\n" END_CLR);
	realizar_consulta(formatear_cons_vuelo(CONSULTA_VUELO, id_vuelo));
	mostrar_registros();
}

 /**
  * int mostrar_asientos_en_vuelo(char *id_vuelo)
  * Entradas: Un char de tipo puntero
  * Salidas: Un entero
  * Muestra los asientos del vuelo.
  */

int mostrar_asientos_en_vuelo(char *id_vuelo)
{
	printf(VERDE "[ Class  ]  [Edad]   [Costo]\n[Asiento]\n" END_CLR);
	realizar_consulta(formatear_cons_vuelo(CONSULTA_COSTO_ASIENTOS, id_vuelo));
	mostrar_registros();

	printf(VERDE "[FILA] [ASIENTOS]\n" END_CLR);
	realizar_consulta(formatear_cons_vuelo(CONSULTA_POS_ASIENTOS, id_vuelo));
	int asientos = mostrar_registros_asientos();

	printf(VERDE "   Asientos\n[Libres] [Ocupados]\n" END_CLR);
	realizar_consulta(formatear_cons_vuelo(CONSULTA_CANT_ASIENTOS, id_vuelo));
	mostrar_registros();

	return asientos;
}

  /**
  * void mostrar_reservaciones_en_vuelo(char *id_vuelo)
  * Entradas: Un char de tipo puntero
  * Salidas: No retorna nada
  * Muestra las reservaciones que estan asociadas al vuelo.
  */

void mostrar_reservaciones_en_vuelo(char *id_vuelo)
{

	realizar_consulta(formatear_cons_vuelo(CONSULTA_INFO_RESRV_POR_VUELO, id_vuelo));
	printf(VERDE "[ID_Rsv] [Fila] [Tipo] [Numero] [Pasaporte] [Nombre]\n" END_CLR);
	mostrar_registros();

	realizar_consulta(formatear_cons_vuelo(CONSULTA_COSTO_RESRV_POR_VUELO, id_vuelo));
	printf(VERDE "[ID_Rsv] [Monto] [Num asientos]\n" END_CLR);
	mostrar_registros();
}

 /**
  * void estado_vuelo()
  * Entradas: No recibe parametros
  * Salidas: No retorna nada
  * Funcion general para mostrar el estado del vuelo,
  * llama a otras funciones para que realicen la accion.
  */

void estado_vuelo()
{
    char *id_vuelo;
    id_vuelo = (char *)calloc(10, sizeof(char));
    strcpy(id_vuelo, pedir_str_input("<ID DEL VUELO> "));

    mostrar_info_vuelo(id_vuelo);

    mostrar_asientos_en_vuelo(id_vuelo);

    mostrar_reservaciones_en_vuelo(id_vuelo);
}

/**
  * void mostrar_estadisticas_ventas()
  * Entradas: No recibe parametros
  * Salidas: No retorna nada
  * Muestra la estadisticas de los vuelos con mas ventas.
  */

void mostrar_estadisticas_ventas()
{
	if (!realizar_consulta(ESTADISTICAS_VENTAS))
	{
		printf(VERDE "VUELOS MAS VENDIDOS\n\nCOD.VUELO \tVENTAS \n" END_CLR);
		mostrar_registros();
	}
	else
	{
		printf(ERROR_CONSULTA "[ Verificar estadisticas de ventas ] \n");
	}
}

/**
  * void mostrar_estadisticas_reservaciones()
  * Entradas: No recibe parametros
  * Salidas: No retorna nada
  * Muestra la estadisticas de los vuelos con mas personas.
  */

void mostrar_estadisticas_reservaciones()
{
	if (!realizar_consulta(ESTADISTICAS_RESERVACIONES))
	{
		printf(VERDE "VUELOS MAS RESERVADOS\n\nCOD.VUELO \tRESERVACIONES \n" END_CLR);
		mostrar_registros();
	}
	else
	{
		printf(ERROR_CONSULTA "[ Verificar estadisticas de reservaciones ] \n");
	}
}

