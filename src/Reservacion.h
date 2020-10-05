char *formatear_cons_vuelo(char *consulta, char *id_vuelo);

typedef struct reservacion
{
    char *pasaportes[MAX_PASAPORTES];
    char *asientos[MAX_PASAPORTES];
    char *id_vuelo;
    char edades[MAX_PASAPORTES];
} reservacion;

int GLOB_ID_RESV_ACTUAL = 5;
char *__INFO_RESERV__[8] = {"RESERVACION ", "VUELO ", "ORIGEN ",
                            "SALIDA ", "DESTINO ", "LLEGADA ",
                            "MONTO ", "AEROLINEA "};
reservacion *ref_reservacion;

int incluir_pasaportes_reserv(char *pasaportes);
int incluir_asientos_reserv(char *asientos);
int valida_pasaporte();
int valida_asiento(char *asiento);
int mostrar_asientos_en_vuelo(char *id_vuelo);
char tipo_pasaporte();
void formatear_pasaporte(char *consulta, char *pasaporte);
void formatear_asiento(char *asiento);
void actualizar_asientos();
void agregar_info_resv_txt(FILE *ref_archivo_txt);
void agregar_adultos_resv_txt(FILE *ref_archivo_txt, char *id_reservacion);
void agregar_infantes_resv_txt(FILE *ref_archivo_txt, char *id_reservacion);
void actualizar_monto();
void generar_pdf();

void mostrar_reservacion()
{

    char *id_resv;
    id_resv = (char *)calloc(10, sizeof(char));
    strcpy(id_resv, pedir_str_input("<ID DE RESV> "));
    unsigned int len = 8;
    for (int i = 0; i < len; i++)
    {
        printf(VERDE "%s\t" END_CLR, __INFO_RESERV__[i]);
    }
    printf("\n");
    realizar_consulta(formatear_cons_vuelo(CONSULTA_MOSTRAR_RESV_POR_ID, id_resv));
    mostrar_registros();
}

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
    ref_reservacion = (reservacion *)malloc(sizeof(reservacion));
    printf(VERDE "INGRESE DATOS RESERVACION\n" END_CLR);
    ref_reservacion->id_vuelo = (char *)calloc(MAX_PASAPORTES, sizeof(char));
    strcpy(ref_reservacion->id_vuelo, pedir_str_input("<ID DEL VUELO> "));
    int asientos = mostrar_asientos_en_vuelo(ref_reservacion->id_vuelo);
    if (!asientos)
    {
        printf(ERROR_CONSULTA "<Vuelo no encontrado>\n");
    }
    else
    {
        char *paspt = pedir_datos_reserv("<Escriba los pasaportes> ");
        int pasaportes_incluidos = incluir_pasaportes_reserv(paspt);
        if (pasaportes_incluidos == COD_ERROR_RESRV)
        {
        return;
        }

        int asientos_incluidos = incluir_asientos_reserv(pedir_str_input("<Escriba los asientos>"));
        if (asientos_incluidos != pasaportes_incluidos || asientos_incluidos == COD_ERROR_RESRV)
          {
            printf(ERROR_CONSULTA "<Asientos incorrectos>\n");
             return;
         }
        actualizar_asientos(asientos_incluidos);
        actualizar_monto();
    }
    
     generar_pdf();
     GLOB_ID_RESV_ACTUAL++;
}

int incluir_pasaportes_reserv(char *pasaportes)
{
    char *pasaporte = strtok(pasaportes, ",");
    int total_pasaportes = 0;
    unsigned int ind_pasp = 0;
    int pasaportes_incluidos = 0;
   // ref_reservacion->edades = (char *)calloc(MAX_PASAPORTES, sizeof(char));
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
        ref_reservacion->edades[ind_pasp] =tipo_pasaporte();
        if (ref_reservacion->edades[ind_pasp] =='I')
            total_pasaportes--;
        ref_reservacion->pasaportes[ind_pasp] = (char *)malloc(MAX_PASAPORTES);
        strcpy(ref_reservacion->pasaportes[ind_pasp], pasaporte);
        ind_pasp++;
        pasaporte = strtok(NULL, ",");
    }
    return total_pasaportes;
}

void actualizar_asientos(int asientos_incluidos)
{
    char* llamada_procdr = calloc(TAM_CONSULTA,sizeof(char));
    strcpy(llamada_procdr,CONSULTA_ACT_ASIENTOS);

    char* consulta_insercion = calloc(TAM_CONSULTA,sizeof(char));
    strcpy(consulta_insercion,CONSULTA_INSERCION_RESERV);

    for (int i =0; i<asientos_incluidos; i++)
    {
        char id_reservacion[5];
        sprintf(id_reservacion, "%d", GLOB_ID_RESV_ACTUAL);

        //call actualiza_reserva_asiento('B', 2, 1, 897498, 2);
        //insert into reservacion (pasaporte, id_reservacion, id_vuelo, id_edad) values (2019039864, 1, 1, 'A');

        strcat(llamada_procdr,ref_reservacion->asientos[i]);
        strcat(llamada_procdr,",");

        strcat(consulta_insercion,ref_reservacion->pasaportes[i]);
        strcat(consulta_insercion,",");

        strcat(llamada_procdr,ref_reservacion->id_vuelo);
        strcat(llamada_procdr,",");

        strcat(consulta_insercion,id_reservacion);
        strcat(consulta_insercion,",");

        strcat(llamada_procdr,ref_reservacion->pasaportes[i]);
        strcat(llamada_procdr,",");
        
        strcat(consulta_insercion,ref_reservacion->id_vuelo);
        strcat(consulta_insercion,",\'");

        strcat(llamada_procdr,id_reservacion);
        strcat(llamada_procdr,")");
 
        int len = strlen(consulta_insercion);
        consulta_insercion[len] =ref_reservacion->edades[i];
        consulta_insercion[len+1] = '\0'; 
        strcat(consulta_insercion,"\')");

        realizar_consulta(llamada_procdr);
        resultado = mysql_store_result(conexion);
        mysql_free_result(resultado);
	    mysql_next_result(conexion);


        realizar_consulta(consulta_insercion);
        resultado = mysql_store_result(conexion);
        mysql_free_result(resultado);
	    mysql_next_result(conexion);
       

       // printf("%s\n",consulta_insercion);
        //printf("%s\n",llamada_procdr);
        strcpy(llamada_procdr,CONSULTA_ACT_ASIENTOS);
        strcpy(consulta_insercion,CONSULTA_INSERCION_RESERV);
    }

}
void actualizar_monto()
{

    char* consulta_insercion = calloc(TAM_CONSULTA,sizeof(char));
    strcpy(consulta_insercion,CONSULTA_INSERCION_MONTO);

    char llamada_proc[50] = {CONSULTA_MONTO_RESRV};
    char id_reservacion[5];
    sprintf(id_reservacion, "%d", GLOB_ID_RESV_ACTUAL);
    strcat(llamada_proc,id_reservacion);
    strcat(llamada_proc,")");


    strcat(consulta_insercion,id_reservacion);
    strcat(consulta_insercion,",");

    strcat(consulta_insercion,llamada_proc);
    strcat(consulta_insercion,",");

    strcat(consulta_insercion,ref_reservacion->id_vuelo);
    strcat(consulta_insercion,",CURDATE(),416)");

    realizar_consulta(consulta_insercion);
    resultado = mysql_store_result(conexion);
    mysql_free_result(resultado);
	mysql_next_result(conexion);

    printf("%s\n",consulta_insercion);
    printf("%s\n",llamada_proc);

/*
insert into monto_reservacion (1,monto_total_reserva(1), 1, CURDATE(), 416);

id_reservacion, monto_total, id_vuelo, fecha_reserva, id_aerolinea

*/
}

int incluir_asientos_reserv(char *asientos)
{
    char *asiento = strtok(asientos, ",");
    char temp_asiento[5];
    int total_asientos = 0;
    int asientos_incluidos = 0;
    while (asiento != NULL)
    {
        strcpy(temp_asiento, asiento);
        formatear_asiento(temp_asiento);
        asientos_incluidos = valida_asiento(temp_asiento);
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
        ref_reservacion->asientos[total_asientos] = (char *)malloc(MAX_PASAPORTES);
        strcpy(ref_reservacion->asientos[total_asientos], temp_asiento);
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

int valida_asiento(char *asiento)
{
    char *cons_temp_formt = calloc(TAM_CONSULTA, sizeof(char));
    strcpy(cons_temp_formt, CONSULTA_VALID_ASIENTO);
    strcat(cons_temp_formt, asiento);
    strcat(cons_temp_formt, ",");
    strcat(cons_temp_formt, ref_reservacion->id_vuelo);
    strcat(cons_temp_formt, ")");
    realizar_consulta(cons_temp_formt);
    resultado = mysql_store_result(conexion);
    reg = mysql_fetch_row(resultado);
    int asiento_valido = atoi(reg[0]);
    mysql_free_result(resultado);
    mysql_next_result(conexion);
    return asiento_valido;
}
char tipo_pasaporte()
{
    char tp = reg[0][0];
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
}

void formatear_asiento(char *asiento)
{
    char fila[4] = {"\'"};
    fila[1] = asiento[0];
    fila[2] = '\'';
    char num_asiento[2];
    num_asiento[0] = ',';
    num_asiento[1] = asiento[1];
    strcpy(asiento, fila);
    strncat(asiento, num_asiento, 2);
}

void generar_pdf()
{
    char ruta_txt[TAM_RUTA] = {"reportes/"};
    char id_reservacion[5];
    sprintf(id_reservacion, "%d", GLOB_ID_RESV_ACTUAL);
    strcat(ruta_txt, id_reservacion);
    strcat(ruta_txt, "_reservacion.txt");
    FILE *ref_archivo_txt;
    ref_archivo_txt = abrir_archivo(ruta_txt, "w+");

    agregar_info_resv_txt(ref_archivo_txt);

    agregar_adultos_resv_txt(ref_archivo_txt, id_reservacion);

    agregar_infantes_resv_txt(ref_archivo_txt, id_reservacion);

    fclose(ref_archivo_txt);

    char generar_pdf[TAM_RUTA] = GENERAR_PDF;
    strcat(generar_pdf, ruta_txt);
    system(generar_pdf);
}
void agregar_adultos_resv_txt(FILE *ref_archivo_txt, char *id_reservacion)
{
    char cons_temp[TAM_CONSULTA] = ADULT_RESV;
    strcat(cons_temp, id_reservacion);
    strcat(cons_temp, ")");
    realizar_consulta(cons_temp);
    fputs("FILA \t ASIENTO \t Pasaporte\n", ref_archivo_txt);
    resultado = mysql_store_result(conexion);
    while ((reg = mysql_fetch_row(resultado)) != NULL)
    {
        for (int col = 0; col < 3; col++)
        {
            fputs(reg[col], ref_archivo_txt);
            fputs("\t\t", ref_archivo_txt);
        }
        fputs("\n", ref_archivo_txt);
    }
    fputs("\n", ref_archivo_txt);

    mysql_free_result(resultado);
    mysql_next_result(conexion);
}
void agregar_infantes_resv_txt(FILE *ref_archivo_txt, char *id_reservacion)
{
    char cons_temp[TAM_CONSULTA] = INFANTES_RESV;
    strcat(cons_temp, id_reservacion);
    strcat(cons_temp, ")");
    realizar_consulta(cons_temp);
    fputs("INFANTES\n", ref_archivo_txt);
    resultado = mysql_store_result(conexion);
    while ((reg = mysql_fetch_row(resultado)) != NULL)
    {
        fputs(reg[0], ref_archivo_txt);
        fputs("\n", ref_archivo_txt);
    }
    fputs("\n", ref_archivo_txt);

    mysql_free_result(resultado);
    mysql_next_result(conexion);
}

void agregar_info_resv_txt(FILE *ref_archivo_txt)
{

    char cons_temp[TAM_CONSULTA] = INFO_RESV_PDF;
    strcat(cons_temp, ref_reservacion->pasaportes[0]);
    strcat(cons_temp, ")");
    realizar_consulta(cons_temp);
    resultado = mysql_store_result(conexion);
    unsigned int col = 0;
    reg = mysql_fetch_row(resultado);
    while (col < mysql_field_count(conexion))
    {
        fputs(__INFO_RESERV__[col], ref_archivo_txt);
        fputs(reg[col], ref_archivo_txt);
        fputs("\n", ref_archivo_txt);
        col++;
    }
    fputs("\n", ref_archivo_txt);

    mysql_free_result(resultado);
    mysql_next_result(conexion);
}
