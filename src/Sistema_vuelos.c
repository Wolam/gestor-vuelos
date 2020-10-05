#include "Solicitudes.h"
#include "Reservacion.h"
#include "Aviones.h"
#include "Vuelos.h"
#include "Usuarios.h"


void ejecutar_opcion_registro_av();
int verificar_credenciales(char *credenciales);
char* solicitar_credenciales();

int main()
{
    realizar_conexion();
    atexit(finalizar_conexion);
    //ejecutar_opcion_menu_principal();
    generar_pdf();
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
            verificar_credenciales(solicitar_credenciales());
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
            verificar_credenciales(solicitar_credenciales());
            break;
        case OPCION_MENU_PRINCIPAL:
            ejecutar_opcion_menu_principal();
            break;
        case OPCION_RESERVAR_VLOS:
            //printf("3\n");
            realizar_reservacion();
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
            ejecutar_opcion_registro_av();
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
    getchar();
    return opcion;
}
char *pedir_str_input(char *msj)
{
    fflush(stdin);
    char *buffer = (char*)malloc(TAM_RUTA * sizeof(char));
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

char* solicitar_credenciales()
{

    //char cons_temp [TAM_CONSULTA] = CONSULTA_CREDENCIALES;
    char* credenciales = calloc(TAM_RUTA,sizeof(char));
    strcpy(credenciales,CONSULTA_CREDENCIALES);
    char clave[15];
    char usuario[20];
    printf("<USUARIO OPERATIVO> ");
    scanf(" %s",usuario);
    printf("<CLAVE DE USUARIO> ");
    scanf(" %s",clave);
    strcat(credenciales,usuario);
    strcat(credenciales,"','");
    strcat(credenciales,clave);
    strcat(credenciales,"')");
    return credenciales;

}

int verificar_credenciales(char *credenciales)
{
    realizar_consulta(credenciales);
    resultado = mysql_store_result(conexion);
    reg = mysql_fetch_row(resultado);
    if(atoi(reg[0]))
    {
        printf(VERDE "CREDENCIALES ACEPTADOS" END_CLR "\n");
        ejecutar_opcion_submenu_operativo();
    }
    else{
        printf(ERROR_CREDENCIALES);
    }
}


void ejecutar_opcion_registro_av()
{
    char opcion_crud_av = pedir_caracter_input("<¿Insertar,eliminar,mostrar,salir?> [I/E/M/S] ");
    if (opcion_crud_av == OPCION_INSERTAR)
    {
        insertar_avion(solicitar_datos_av());
    }
    else if (opcion_crud_av == OPCION_ELIMINAR)
    {
        eliminar_avion();
    }
    else if (opcion_crud_av == OPCION_MOSTRAR)
    {
        mostrar_aviones();
    }
}

