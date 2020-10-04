
int GLOB_ID_RESV_ACTUAL = 0;

typedef struct reservacion
{
    char *pasaportes[MAX_PASAPORTES];
    char *asientos[MAX_PASAPORTES];
    char *id_vuelo;
}reservacion;

reservacion *ref_reservacion;

int incluir_pasaportes_reserv(char *pasaportes);
int incluir_asientos_reserv(char *asientos,char* id_vuelo);
int valida_pasaporte();
int valida_asiento();
char *tipo_pasaporte();
void formatear_pasaporte(char *consulta, char *pasaporte);
void formatear_asiento(char *asiento,char* id_vuelo);
int mostrar_asientos_en_vuelo(char *id_vuelo);

char *pedir_datos_reserv(char *msj)
{
    fflush(stdin);
    char *buffer_datos = malloc(TAM_USUARIO * sizeof(char));
    printf("%s", msj);
    fgets(buffer_datos, TAM_USUARIO, stdin);
    if ((strlen(buffer_datos) > 0) && (buffer_datos[strlen(buffer_datos) - 1] == '\n'))
        buffer_datos[strlen(buffer_datos) - 1] = '\0';
    return buffer_datos;
}

void realizar_reservacion()
{
    //ref_reservacion = (reservacion *)malloc(sizeof(reservacion));
    printf(VERDE "INGRESE DATOS RESERVACION\n" END_CLR);
    char* id_vuelo = pedir_datos_reserv("<ID DEL VUELO> ");
    //ref_reservacion->id_vuelo = 
    int asientos = mostrar_asientos_en_vuelo(id_vuelo);
    if (!asientos)
    {
        printf(ERROR_CONSULTA "<Vuelo no encontrado>\n");
    }
    else
    {
       // char *paspt = pedir_datos_reserv("<Escriba los pasaportes> ");
       // int datos_pasaportes = incluir_pasaportes_reserv(paspt);
       // paspt = NULL;
      //  free(paspt);
        //if (datos_pasaportes == COD_ERROR_RESRV)
       // {
        //    return;
       // }else
      //  {
        int datos_asientos = incluir_asientos_reserv(pedir_str_input("<Escriba los asientos>"),id_vuelo);
     }
        
}
//}

int incluir_pasaportes_reserv(char *pasaportes)
{
    char *pasaporte = strtok(pasaportes, ",");
    int total_pasaportes = 0;
    int pasaportes_incluidos = 0;
    while (pasaporte != NULL)
    {
        formatear_pasaporte(CONSULTA_VALID_PASPT, pasaporte);
        pasaportes_incluidos = valida_pasaporte();
        if (!pasaportes_incluidos)
        {
            printf(ERROR_CONSULTA "Pasaporte [%s] no encontrado\n", pasaporte);
            return COD_ERROR_RESRV;
        }
        else if (total_pasaportes > MAX_PASAPORTES)
        {

            printf(ERROR_CONSULTA "Pasaportes tiene de limite 10\n");
            return COD_ERROR_RESRV;
        }

        total_pasaportes++;
        formatear_pasaporte(CONSULTA_TIPO_PASPT, pasaporte);
        if (!strncmp(tipo_pasaporte(), "I", 1))
            total_pasaportes--;

        pasaporte = strtok(NULL, ",");
    }
    return total_pasaportes;
}

int incluir_asientos_reserv(char *asientos,char* id_vuelo)
{
    char *asiento = strtok(asientos, ",");
    int total_asientos = 0;
    int asientos_incluidos = 0;
    while (asiento != NULL)
    {
        formatear_asiento(asiento,id_vuelo);
        asientos_incluidos = valida_asiento();
        if (!asientos_incluidos)
        {
            printf(ERROR_CONSULTA "Asiento [%s] no encontrado\n", asiento);
            return COD_ERROR_RESRV;
        }
        else if (total_asientos > MAX_PASAPORTES)
        {

            printf(ERROR_CONSULTA "Asientos tiene de limite 10\n");
            return COD_ERROR_RESRV;
        }

        total_asientos++;
        asiento = strtok(NULL, ",");
    }
    return total_asientos;
}

int valida_pasaporte()
{
    //reg = mysql_fetch_row(resultado);
    int pasaporte_validado = atoi(reg[0]);
    mysql_free_result(resultado);
    mysql_next_result(conexion);
    return pasaporte_validado;
}

int valida_asiento()
{
    int asiento_valido = atoi(reg[0]);
    mysql_free_result(resultado);
    mysql_next_result(conexion);
    return asiento_valido;
}
char *tipo_pasaporte()
{
    char *tp = reg[0];
    mysql_free_result(resultado);
    mysql_next_result(conexion);
    return tp;
}

void formatear_pasaporte(char *consulta, char *pasaporte)
{
    char *cons_temp_formt = calloc(TAM_CONSULTA, sizeof(char));
    strcpy(cons_temp_formt, consulta);
    strcat(cons_temp_formt, pasaporte);
    strcat(cons_temp_formt, ")");
    realizar_consulta(cons_temp_formt);
    resultado = mysql_store_result(conexion);
    reg = mysql_fetch_row(resultado);
    //free(cons_temp_formt);
}

void formatear_asiento(char *asiento,char* id_vuelo)
{
    char fila[2];
    fila[0] = asiento[0];
    fila[1] = '\'';
    char *cons_temp_formt = calloc(50, sizeof(char));
    strcpy(cons_temp_formt, CONSULTA_VALID_ASIENTO);
    strcat(cons_temp_formt, strcat(fila, ","));
    cons_temp_formt[strlen(cons_temp_formt)] = asiento[1];
    strcat(cons_temp_formt, ",");
    strcat(cons_temp_formt, id_vuelo);
    strcat(cons_temp_formt, ")");
    realizar_consulta(cons_temp_formt);
    resultado = mysql_store_result(conexion);
    reg = mysql_fetch_row(resultado);
}
