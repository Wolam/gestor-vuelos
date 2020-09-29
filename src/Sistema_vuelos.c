#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "constantes.h"

FILE* abrir_archivo(char* ruta);
void cargar_usuarios(FILE* ref_archivo_usuarios);
void insertar_usuario();
char* formatear_fecha(char* fecha);
char* formatear_usuario(char* usuario);

int solicitar_opcion();
void mostrar_menu(char* tipo_menu);
void ejecutar_opcion_menu_principal(int opcion);
void ejecutar_opcion_submenu_general(int opcion);
void ejecutar_opcion_submenu_operativo(int opcion);

int
main()
{
   FILE* usr = abrir_archivo("usuarios.txt");
   cargar_usuarios(usr);
   return 0;
}


void
ejecutar_opcion_menu_principal(int opcion)
{
    switch (opcion)
    {
        case OPCIONES_OPERATIVAS:
            mostrar_menu("operativo");
            ejecutar_opcion_submenu_operativo(solicitar_opcion());
            break;
        case OPCIONES_GENERALES:
            mostrar_menu("general");
            ejecutar_opcion_submenu_general(solicitar_opcion());
            break;
        case OPCION_SALIR:
            exit(TRUE);
        default:
            printf(ERROR_OPCION);
            break;
    }ejecutar_opcion_menu_principal(solicitar_opcion());
}


void
ejecutar_opcion_submenu_general(int opcion)
{
    switch (opcion)
    {
        case OPCION_CAMBIO_SUBMENU:
            mostrar_menu("operativo");
            ejecutar_opcion_submenu_operativo(solicitar_opcion());
            break;
        case OPCION_MENU_PRNCIPAL:
            mostrar_menu("principal");
            ejecutar_opcion_menu_principal(solicitar_opcion());
            break;
        case OPCION_RESERVAR_VLOS:
            printf("3\n");
            break;
        case OPCION_INFO_RESERV:
            printf("4\n");
            break;
        case OPCION_SALIR_GENERAL:
            exit(TRUE);
        default:
            printf(ERROR_OPCION);
            ejecutar_opcion_submenu_operativo(solicitar_opcion());
            break;
    }ejecutar_opcion_submenu_general(solicitar_opcion());
}

void
ejecutar_opcion_submenu_operativo(int opcion)
{
    switch (opcion)
    {
        case OPCION_CAMBIO_SUBMENU:
            mostrar_menu("general");
            ejecutar_opcion_submenu_general(solicitar_opcion());
            break;
        case OPCION_MENU_PRNCIPAL:
            mostrar_menu("principal");
            ejecutar_opcion_menu_principal(solicitar_opcion());
            break;
        case OPCION_REGISTRO_AVIONES:
            printf("3\n");
            break;
        case OPCION_CARGAR_USRIO:
            printf("4\n");
            break;
        case OPCION_ESTADO_VLO:
            printf("5\n");
            break;
        case OPCION_ESTADISTICAS:
            printf("6\n");
            break;
        case OPCION_SALIR_OPERATIVO:
            exit(TRUE);
        default:
            printf(ERROR_OPCION);
            //return CODIGO_ERROR;
    }ejecutar_opcion_submenu_operativo(solicitar_opcion());
}


void 
mostrar_menu(char* tipo_menu)
{
    char abrir_menu[20] = "cat menu_";
    strcat(abrir_menu,tipo_menu);
    system(abrir_menu);
}

int
solicitar_opcion()
{
    unsigned int opcion;
    printf("\nFavor digite una opción > ");
    scanf(" %d",&opcion);
    return opcion;
}


FILE *
abrir_archivo(char* ruta)
{
    FILE *ref_archivo;
    ref_archivo = fopen(ruta,"r");
    if (!ref_archivo)
    {
        printf("%s %s\n", ERROR_ARCHIVO,ruta);
        return NULL;
    
    }return ref_archivo;
   
}


void cargar_usuarios
(FILE* ref_archivo_usuarios)
{
    char usuario [TAM_USUARIO];
    unsigned int line_count = 0;
    while (fgets(usuario, TAM_USUARIO, ref_archivo_usuarios))
    {
        if (usuario[strlen(usuario) - 1] == '\n')
            usuario[strlen(usuario)-1] = '\0';
        insertar_usuario(usuario);   
    }
}



void 
insertar_usuario(char* usuario)
{
    char cons[TAM_CONSULTA] = "INSERT INTO usuario VALUES(";
    char* usuario_formateado = formatear_usuario(usuario); 
    char* fecha  = formatear_fecha(strcat(strrchr(usuario, ','),",'%Y-%m-%d'))"));
    strcat(cons,usuario_formateado);
    strcat(cons,fecha);
}

char* formatear_fecha(char* fecha)
{
    char* func_fecha  = calloc(TAM_FECHA,sizeof(char));
    strcpy(func_fecha,"STR_TO_DATE(");
    fecha[0] = ' ';
    strcat(func_fecha,fecha);
    return func_fecha;
}

char* formatear_usuario(char* usuario)
{
    char* usuario_formateado = calloc(TAM_USUARIO,sizeof(char));
    strncpy(usuario_formateado,usuario,strlen(usuario)-12);
    printf("FORMATED USR %s\n",usuario_formateado);
    return usuario_formateado;
}