#include <stdlib.h>
#include <string.h>
#include "Datos_sistema.h"

FILE* abrir_archivo(char* ruta,char* modo);
void cargar_usuarios (FILE* ref_archivo_usuarios,char* nombre_archivo);
const char* insertar_usuario();
char* formatear_fecha(char* fecha);
char* formatear_usuario(char* usuario);
char* obtener_reporte(const char* res_consulta);
char solicitar_opcion();
void mostrar_menu(char* tipo_menu);
void ejecutar_opcion_menu_principal();
void ejecutar_opcion_submenu_general();
void ejecutar_opcion_submenu_operativo();

int
main()
{
   //realizar_conexion();
  // FILE* usr = abrir_archivo("usuarios/usuarios.txt","r");
  // cargar_usuarios(usr,"usuarios");
  // cerrar_conexion();
   ejecutar_opcion_menu_principal();
   return 0;
}


void
ejecutar_opcion_menu_principal()
{   
    mostrar_menu("principal");
    do { char opcion = solicitar_opcion();
        switch (opcion){
        case OPCIONES_OPERATIVAS:
            ejecutar_opcion_submenu_operativo();
            break;
        case OPCIONES_GENERALES:
            ejecutar_opcion_submenu_general();
            break;
        case OPCION_SALIR:
            exit(SALIDA);
        default:
            printf(ERROR_OPCION);
            break;
    }}while(TIEMPO_EJECUCCION);
}


void
ejecutar_opcion_submenu_general()
{
    mostrar_menu("general");
    char opcion = '\0';
    do { opcion = solicitar_opcion();
     switch (opcion){
        case OPCION_CAMBIO_SUBMENU:
            ejecutar_opcion_submenu_operativo();
            break;
        case OPCION_MENU_PRNCIPAL:
            ejecutar_opcion_menu_principal();
            break;
        case OPCION_RESERVAR_VLOS:
            printf("3\n");
            break;
        case OPCION_INFO_RESERV:
            printf("4\n");
            break;
        case OPCION_SALIR_GENERAL:
            exit(SALIDA);
        default:
            printf(ERROR_OPCION);
            break;
    }} while(opcion != OPCION_SALIR_GENERAL);
}
void
ejecutar_opcion_submenu_operativo()
{   
    mostrar_menu("operativo");
    char opcion = '\0';
    do { opcion = solicitar_opcion(); switch (opcion){
        case OPCION_CAMBIO_SUBMENU:
            ejecutar_opcion_submenu_general();
            break;
        case OPCION_MENU_PRNCIPAL:
            ejecutar_opcion_menu_principal();
            break;
        case OPCION_REGISTRO_AVIONES:
            printf("3\n");
            break;
        case OPCION_CARGAR_USRIO:
            //ajustar la ruta del usuario 
            printf("4\n");
            break;
        case OPCION_ESTADO_VLO:
            printf("5\n");
            break;
        case OPCION_ESTADISTICAS:
            printf("6\n");
            break;
        case OPCION_SALIR_OPERATIVO:
            exit(SALIDA);
        default:
            printf(ERROR_OPCION);
    }}while(opcion != OPCION_SALIR_OPERATIVO);
}


void 
mostrar_menu(char* tipo_menu)
{
    char abrir_menu[20] = "cat menus/menu_";
    strcat(abrir_menu,tipo_menu);
    system(abrir_menu);
}

char
solicitar_opcion()
{
    char opcion;
    printf("\n <OPCION A ELEGIR> ");
    scanf(" %c",&opcion);
    return opcion;
}


FILE *
abrir_archivo(char* ruta,char* modo)
{
    FILE *ref_archivo;
    ref_archivo = fopen(ruta,modo);
    if (!ref_archivo)
    {
        printf("%s %s\n", ERROR_ARCHIVO,ruta);
        return NULL;
    
    }return ref_archivo;
   
}


void cargar_usuarios
(FILE* ref_archivo_usuarios,char* nombre_archivo)
{
    char usuario [TAM_USUARIO];
    char ruta_reporte[TAM_RUTA] = {"reportes/reporte_"};
    strcat(ruta_reporte,nombre_archivo);
    FILE* ref_archivo_reporte = abrir_archivo(ruta_reporte,"w+");
    while (fgets(usuario, TAM_USUARIO, ref_archivo_usuarios))
    {
        if (usuario[strlen(usuario) - 1] == '\n')
            usuario[strlen(usuario)-1] = '\0';

        fseek(ref_archivo_reporte,0,SEEK_END);
        fputs(obtener_reporte(insertar_usuario(usuario)), ref_archivo_reporte);
    }
    fclose(ref_archivo_reporte);
    fclose(ref_archivo_usuarios);
}

const char* 
insertar_usuario(char* usuario)
{
    char cons[TAM_CONSULTA] = "INSERT INTO usuario VALUES(";
    char* usuario_formateado = formatear_usuario(usuario); 
    char* fecha  = formatear_fecha(strcat(strrchr(usuario, ','),",'%Y-%m-%d'))"));
    strcat(cons,usuario_formateado);
    strcat(cons,fecha);
    return realizar_consulta(cons);
}

char*
obtener_reporte(const char* res_consulta)
{

    char* reporte = calloc(11,sizeof(char));
    if(res_consulta == NULL)
        strcpy(reporte,"AGREGADO\n");
    else if(strncmp(ERROR_SINTX,res_consulta,strlen(ERROR_SINTX)) == 0)
        strcpy(reporte,"ERROR\n");
    else{
        strcpy(reporte,"DUPLICADO\n");
    }
    return reporte;
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
    return usuario_formateado;
}