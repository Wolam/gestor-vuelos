#include <stdlib.h>
#include "Datos_sistema.h"

int main()
{
    realizar_conexion();
    atexit(finalizar_conexion);
    ejecutar_opcion_menu_principal();
    return 0;
}

void ejecutar_opcion_menu_principal()
{
    mostrar_menu("principal");
    do
    {
        char opcion = pedir_caracter_input("<OPCION DESEADA> ");
        switch (opcion)
        {
        case OPCIONES_OPERATIVAS:
            ejecutar_opcion_submenu_operativo();
            break;
        case OPCIONES_GENERALES:
            ejecutar_opcion_submenu_general();
            break;
        case OPCION_SALIR:
            exit(EXIT_SUCCESS);
        default:
            printf(ERROR_OPCION);
            break;
        }
    } while (TIEMPO_EJECUCION);
}

void ejecutar_opcion_submenu_general()
{
    mostrar_menu("general");
    char opcion = '\0';
    do
    {
        opcion = pedir_caracter_input("<OPCION DESEADA> ");
        switch (opcion)
        {
        case OPCION_CAMBIO_SUBMENU:
            ejecutar_opcion_submenu_operativo();
            break;
        case OPCION_MENU_PRINCIPAL:
            ejecutar_opcion_menu_principal();
            break;
        case OPCION_RESERVAR_VLOS:
            printf("3\n");
            break;
        case OPCION_INFO_RESERV:
            printf("4\n");
            break;
        case OPCION_SALIR_GENERAL:
            exit(EXIT_SUCCESS);
        default:
            printf(ERROR_OPCION);
            break;
        }
    } while (opcion != OPCION_SALIR_GENERAL);
}
void ejecutar_opcion_submenu_operativo()
{
    mostrar_menu("operativo");
    char opcion = '\0';
    do
    {
        opcion = pedir_caracter_input("<OPCION DESEADA> ");
        switch (opcion)
        {
        case OPCION_CAMBIO_SUBMENU:
            ejecutar_opcion_submenu_general();
            break;
        case OPCION_MENU_PRINCIPAL:
            ejecutar_opcion_menu_principal();
            break;
        case OPCION_REGISTRO_AVIONES:
            solicitar_opcion_registro_av();
            break;
        case OPCION_CARGAR_USRIO:
            cargar_usuarios(pedir_str_input("<NOMBRE DEL ARCHIVO> "));
            break;
        case OPCION_ESTADO_VLO:
            estado_vuelo();
            break;
        case OPCION_ESTADISTICAS:
            mostrar_estadisticas_reservaciones();
            mostrar_estadisticas_ventas();
            break;
        case OPCION_SALIR_OPERATIVO:
            exit(EXIT_SUCCESS);
        default:
            printf(ERROR_OPCION);
        }
    } while (opcion != OPCION_SALIR_OPERATIVO);
}

void mostrar_menu(char *tipo_menu)
{
    char abrir_menu[20] = "cat menus/menu_";
    strcat(abrir_menu, tipo_menu);
    system(abrir_menu);
}

char pedir_caracter_input(char *msj)
{
    char opcion;
    printf("%s", msj);
    scanf(" %c", &opcion);
    return opcion;
}
char *pedir_str_input(char *msj)
{
    fflush(stdin);
    char *buffer = malloc(TAM_RUTA * sizeof(char));
    printf("%s", msj);
    fgets(buffer, TAM_RUTA, stdin);
    if ((strlen(buffer) > 0) && (buffer[strlen(buffer) - 1] == '\n'))
        buffer[strlen(buffer) - 1] = '\0';
    return buffer;
}

FILE *
abrir_archivo(char *ruta, char *modo)
{
    FILE *ref_archivo;
    ref_archivo = fopen(ruta, modo);
    if (!ref_archivo)
    {
        printf("%s %s\n", ERROR_ARCHIVO, ruta);
        return NULL;
    }
    return ref_archivo;
}

void solicitar_opcion_registro_av()
{
    char opcion_crud_av = pedir_caracter_input("<¿Insertar,eliminar,mostrar,salir?> [I/E/M/S] ");
    if (opcion_crud_av=='I')
    {
        insertar_avion(solicitar_datos_av());

    }
    else if(opcion_crud_av == 'E'){
        eliminar_avion();

    }
    else if(opcion_crud_av == 'M'){
        mostrar_avion();

    }

}
void eliminar_avion()
{
    char *cons = calloc(TAM_CONSULTA,sizeof(char));
    strcpy(cons,CONSULTA_ELIMINAR_AVION);
    strcat(cons,pedir_str_input("<Matricula a eliminar> "));
    strcat(cons,")");
    int res = realizar_consulta(cons);
    if (res== COD_ERROR_FK){
        printf(ERROR_CONSULTA "<Avion se encuentra en vuelo>\n");
    }
    else if(!res){
        printf(VERDE "<Avion removido>\n" END_CLR);
    }
    else{
         printf(ERROR_CONSULTA "<Avion no registrado>\n");
    }
}

void mostrar_avion()
{
    char *cons = calloc(TAM_CONSULTA,sizeof(char));
    strcpy(cons,CONSULTA_MOSTRAR_AVIONES);
    realizar_consulta(cons);
    printf(VERDE "[MATRICULA]  [MARCA]  [MOD]  [ANIO]\n"END_CLR,(char)164);
    mostrar_registros();

}



avion *solicitar_datos_av()
{
    avion* ref_av;
    ref_av = (avion* )malloc(sizeof(avion));

    char *matricula = pedir_str_input("<MATRICULA AVION> ");
    strcat(matricula, ",");
    ref_av->matricula = matricula;

    char *marca = pedir_str_input("\n<MARCA AVION> ");
    strcat(marca, ",");
    ref_av->marca = marca;

    char *modelo = pedir_str_input("\n<MODELO AVION> ");
    strcat(modelo, ",");
    ref_av->modelo=modelo;

    char *anio = pedir_str_input("\n<AÑO AVION> ");
    ref_av->anio=anio;

    return ref_av;
}

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

int insertar_usuario(char *usuario)
{
    char cons[TAM_CONSULTA] = CONSULTA_INSERCION_USR;
    strcat(cons, formatear_usuario(usuario));
    strcat(cons, formatear_fecha(strcat(strrchr(usuario, ','), "','%Y-%m-%d'))")));
    return realizar_consulta(cons);
}

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

char *formatear_fecha(char *fecha)
{
    fecha[0] = '\'';
    char *func_fecha = calloc(TAM_FECHA, sizeof(char));
    strcpy(func_fecha, "STR_TO_DATE(");
    strcat(func_fecha, fecha);
    return func_fecha;
}

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

void estado_vuelo()
{
    char *id_vuelo;
    id_vuelo = (char*)calloc(10,sizeof(char));
    strcpy(id_vuelo, pedir_str_input("<ID DEL VUELO> "));

    mostrar_info_vuelo(id_vuelo);

    mostrar_asientos_en_vuelo(id_vuelo);

    mostrar_reservaciones_en_vuelo(id_vuelo);
}
