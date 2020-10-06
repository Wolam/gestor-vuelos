/**
 * INSTITUTO TECNOLOGICO DE COSTA RICA
 * I PROYECTO PROGRAMADO DE LENGUAJES DE PROGRAMACION
 * Estudiantes: Joseph Valenciano / Wilhelm Carstens
 * Carnets: 2019039864 / 2019344583
 * Profesor: Allan Rodriguez Davila
 * Fecha 05/10/2020
 */

/**
  * int insertar_usuario(char *usuario)
  * Entradas: Un puntero de tipo char
  * Salidas: retorna un entero
  * Inserta el usuario en la base de datos.
  */

int insertar_usuario(char *usuario)
{
	char cons[TAM_CONSULTA] = CONSULTA_INSERCION_USR;
	strcat(cons, formatear_usuario(usuario));
	strcat(cons, formatear_fecha(strcat(strrchr(usuario, ','), "','%Y-%m-%d'))")));
	return realizar_consulta(cons);
}

/**
  * void cargar_usuarios(char *nombre_archivo)
  * Entradas: Un puntero de tipo char
  * Salidas: No retorna nada
  * Se encarga de cargar el usuario de manera general 
  * llama a todas las funciones necesarias para formatear e insertar el usuario.
  */

void cargar_usuarios(char *nombre_archivo)
{

    char ruta_archivo[TAM_RUTA] = {"usuarios/"};
    strcat(ruta_archivo, nombre_archivo);
    FILE *ref_archivo_usuarios;
    ref_archivo_usuarios = abrir_archivo(ruta_archivo, "r");

    if (ref_archivo_usuarios != NULL)
    {
        char usuario[TAM_USUARIO];
        char ruta_reporte[TAM_RUTA] = {"reportes/reporte_"};

        strcat(ruta_reporte, nombre_archivo);
        FILE *ref_archivo_reporte = abrir_archivo(ruta_reporte, "w+");
        while (fgets(usuario, TAM_USUARIO, ref_archivo_usuarios))
        {
            if (usuario[strlen(usuario) - 1] == '\n')
                usuario[strlen(usuario) - 1] = '\0';

            fseek(ref_archivo_reporte, 0, SEEK_END);
            fputs(obtener_reporte(insertar_usuario(usuario)), ref_archivo_reporte);
        }
        fclose(ref_archivo_reporte);
        fclose(ref_archivo_usuarios);
    }
    else
    {
        printf("\n<ASEGURESE QUE EL ARCHIVO EXISTA>\n");
        return;
    }
}

/**
  * char *obtener_reporte(int res_consulta)
  * Entradas: Un entero
  * Salidas: Un char de tipo puntero
  * Genera el reporte de la carga de los usuarios
  */

char *
obtener_reporte(int res_consulta)
{
    char *reporte = calloc(13, sizeof(char));
    if (!res_consulta)
        strcpy(reporte, "AGREGADO\n");
    else if (res_consulta == COD_ERROR_SINTX)
        strcpy(reporte, "ERROR\n");
    else
    {
        strcpy(reporte, "DUPLICADO\n");
    }
    return reporte;
}

 /**
  * char *formatear_fecha(char *fecha)
  * Entradas: Un char de tipo puntero
  * Salidas: Un char de tipo puntero
  * Concatena la fecha, para poder realizar la consulta a mysql
  */

char *formatear_fecha(char *fecha)
{
    fecha[0] = '\'';
    char *func_fecha = calloc(TAM_FECHA, sizeof(char));
    strcpy(func_fecha, "STR_TO_DATE(");
    strcat(func_fecha, fecha);
    return func_fecha;
}

  /**
  * char *formatear_usuario(char *usuario)
  * Entradas: Un char de tipo puntero
  * Salidas: Un char de tipo puntero
  * Concatena el usuario, para poder realizar la consulta a mysql
  */

char *formatear_usuario(char *usuario)
{
    char *usuario_formateado = calloc(TAM_USUARIO, sizeof(char));
    char *usuario_sin_fecha = calloc(TAM_USUARIO - 10, sizeof(char));
    strncpy(usuario_sin_fecha, usuario, strlen(usuario) - 10);
    char *palabra_actual = strtok(usuario_sin_fecha, ",");
    while (palabra_actual != NULL)
    {
        char tmp[15] = {"\'"};
        strcat(tmp, palabra_actual);
        strcat(tmp, "\'");
        strcat(usuario_formateado, tmp);
        palabra_actual = strtok(NULL, ",");
        usuario_formateado[strlen(usuario_formateado)] = ',';
    }
    usuario_sin_fecha = NULL;
    free(usuario_sin_fecha);
    return usuario_formateado;
}
