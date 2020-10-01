
//Status del programa
#define SALIDA_EXITOSA 0
#define TIEMPO_EJECUCION 1

//Opciones del menu principal
#define OPCIONES_OPERATIVAS '1'
#define OPCIONES_GENERALES '2'
#define OPCION_SALIR '3'


//Opciones del menu general
#define OPCION_RESERVAR_VLOS '3'
#define OPCION_INFO_RESERV '4'
#define OPCION_SALIR_GENERAL '5'


//Opciones del menu operativo
#define OPCION_REGISTRO_AVIONES '3'
#define OPCION_CARGAR_USRIO '4'
#define OPCION_ESTADO_VLO '5'
#define OPCION_ESTADISTICAS '6'
#define OPCION_SALIR_OPERATIVO '7'

//Opciones de ambos submenus
#define OPCION_CAMBIO_SUBMENU '1'
#define OPCION_MENU_PRINCIPAL '2'


//Tamaños de variables
#define TAM_USUARIO 200 
#define TAM_CONSULTA 300
#define TAM_FECHA 40    
#define TAM_RUTA 40
#define ATRIBS_USUARIO 6

//ERRORES del programa
#define ERROR_ARCHIVO "\033[1;31m NO SE ENCONTRO EL ARCHIVO: \033[0m"
#define ERROR_OPCION "\033[1;31m REINGRESE LA OPCION NUEVAMENTE \033[0m"
#define ERROR_CONEXION "\033[1;31m ERROR EN LA CONEXION: \033[0m"
#define ERROR_CONSULTA "\033[1;31m ERROR AL REALIZAR CONSULTA: \033[0m"


// CODIGOS MySQL en consultas
#define COD_ERROR_DUP 1062
#define COD_ERROR_SINTX 1064

// NOMBRES DE ERRORES MySQL en consultas
#define ERROR_DUP "Duplicate entry"
#define ERROR_SINTX "You have an error in your SQL syntax"
