#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "constantes.h"

int abrir_archivo();
int solicitar_opcion();
void mostrar_menu(char* tipo_menu);

int
main()
{
    mostrar_menu("principal");   
    ejecutar_opcion_menu_principal(solicitar_opcion());
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
            printf(ROJO,
            ERROR_OPCION,
            ENDCOLOR);
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
    int opcion;
    printf("\nFavor digite una opción > ");
    scanf(" %d",&opcion);
    return opcion;
}