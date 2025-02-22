/**
 * INSTITUTO TECNOLOGICO DE COSTA RICA
 * I PROYECTO PROGRAMADO DE LENGUAJES DE PROGRAMACION
 * Estudiantes: Joseph Valenciano / Wilhelm Carstens
 * Carnets: 2019039864 / 2019344583
 * Profesor: Allan Rodriguez Davila
 * Fecha 05/10/2020
 */

//Status del programa
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
#define TAM_RUTA 60
#define MAX_PASAPORTES 10

//ERRORES del programa
#define ERROR_ARCHIVO "\033[1;31m NO SE ENCONTRO EL ARCHIVO: \033[0m"
#define ERROR_OPCION "\033[1;31m REINGRESE LA OPCION NUEVAMENTE\n \033[0m"
#define ERROR_CONEXION "\033[1;31m ERROR EN LA CONEXION: \033[0m"
#define ERROR_CONSULTA "\033[1;31m ERROR AL REALIZAR CONSULTA: \033[0m"
#define REG_VACIOS "\033[0;34mNO HAY DATOS\n \033[0m"
#define ERROR_CREDENCIALES "\033[1;31mERROR EN LOS CREDENCIALES\033[0m \n"


// --- Constantes de MySQL ---

// CODIGOS MySQL en consultas
#define COD_ERROR_DUP 1062
#define COD_ERROR_SINTX 1064
#define COD_ERROR_FK 1451
#define COD_ERROR_RESRV -1
#define CONSULTA_EXITOSA 0

// NOMBRES DE ERRORES/Msjs MySQL en consultas
#define ERROR_DUP "Duplicate entry"
#define ERROR_SINTX "You have an error in your SQL syntax"
#define ERROR_FK "Cannot delete or update a parent row"
#define ERROR_ELIMINACION "Entry not found"

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
#define CONSULTA_VALID_ASIENTO "SELECT valida_pos_asiento("
#define CONSULTA_INFO_RESRV_POR_VUELO "CALL reservacion("
#define CONSULTA_COSTO_RESRV_POR_VUELO "CALL monto_reservacion("
#define CONSULTA_VALID_PASPT "SELECT valida_pasajeros("
#define CONSULTA_TIPO_PASPT "SELECT conocer_edad("
#define CONSULTA_CREDENCIALES "SELECT valida_usuarios('"
#define CONSULTA_MOSTRAR_AVIONES "CALL muestra_aviones(" 
#define CONSULTA_MOSTRAR_RESV_POR_ID "CALL info_reservacion_c("
#define CONSULTA_ACT_ASIENTOS "call actualiza_reserva_asiento("
#define CONSULTA_MONTO_RESRV "monto_total_reserva("
#define INFO_RESV_PDF "call info_reservacion_pdf("
#define ADULT_RESV "call adultos_reservacion("
#define INFANTES_RESV "call infantes_reservacion("


//Opciones de registro de aviones
#define OPCION_INSERTAR 'I'
#define OPCION_ELIMINAR 'E'
#define OPCION_MOSTRAR 'M'

//Llamadas de CRUD

#define CONSULTA_INSERCION_USR "INSERT INTO usuario VALUES("
#define CONSULTA_INSERCION_AVION "INSERT INTO avion VALUES("
#define CONSULTA_ELIMINAR_AVION "SELECT eliminar_avion("
#define CONSULTA_INSERCION_RESERV "INSERT INTO reservacion VALUES("
#define CONSULTA_INSERCION_MONTO "INSERT INTO monto_reservacion VALUES("
#define CONSULTA_NUEVO_ID "select crear_id_reservacion()"

//Macros adicionales
#define VERDE "\033[0;32m"
#define END_CLR "\033[0m"
#define BLUE "\033[0;34m"

//Informacion de txt
#define GENERAR_PDF "make pdf archivo_txt="

// Funciones de prototipo
FILE *abrir_archivo(char *ruta, char *modo);
char *formatear_fecha(char *fecha);
char *formatear_usuario(char *usuario);
char *obtener_reporte(int res_consulta);
char *pedir_str_input(char *msj);
char pedir_caracter_input(char *msj);
void mostrar_menu(char *tipo_menu);
void ejecutar_opcion_menu_principal();
void ejecutar_opcion_submenu_general();
void ejecutar_opcion_submenu_operativo();
void cargar_usuarios(char *nombre_archivo);
