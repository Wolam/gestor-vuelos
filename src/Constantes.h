
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

// --- Constantes de MySQL ---


// CODIGOS MySQL en consultas
#define COD_ERROR_DUP 1062
#define COD_ERROR_SINTX 1064

// NOMBRES DE ERRORES/Msjs MySQL en consultas
#define ERROR_DUP "Duplicate entry"
#define ERROR_SINTX "You have an error in your SQL syntax"
#define REG_VACIOS "\033[0;34m NO HAY DATOS\n \033[0m"
// Datos a la conexion de MySQL

#define USR_DBA "wil_bd"
#define NMB_BD "bd_aviones"
#define CONTR "wil_bd_psswrd"
#define SRVR "localhost"

//Llamadas a funcionalidades de la bd
#define ESTADISTICAS_VENTAS "CALL estadistica_ventas"
#define ESTADISTICAS_RESERVACIONES "CALL estadistica_personas"

#define CONSULTA_VUELO "CALL consVuelo("
#define CONSULTA_COSTO_ASIENTOS "CALL costo_asiento("
#define CONSULTA_POS_ASIENTOS "CALL fila_asiento("
#define CONSULTA_CANT_ASIENTOS "CALL cant_asientos("
#define CONSULTA_INFO_RESRV_POR_VUELO "CALL reservacion("
//#define CONSULTA_INFO_RESRV_POR_ID "CALL reservacion("
#define CONSULTA_COSTO_RESRV_POR_VUELO "CALL monto_reservacion("
