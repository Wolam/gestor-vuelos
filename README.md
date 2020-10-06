# Proyecto-I-Lenguajes / Lenguaje Imperativo <img align="right" src=https://wstemproject.eu/files/2019/06/logo-tec-300x158.png width =200 height=120>
Sistema de gestión de vuelos <img src=https://seeklogo.com/images/A/airplane-logo-6885950420-seeklogo.com.png width =20 height=20>

## Documentación del proyecto

### Manual de Usuario <img src= https://raw.githubusercontent.com/fabiospampinato/vscode-terminals/master/resources/logo.png width =20 height=20>

Para iniciar a trabajar con nuestro proyecto se debe tener en cuenta que fue desarrollado en **ubuntu linux**,
por lo que seguramente si se utiliza en otra arquitectura puede que dé problemas. Además se utiliza como
motor de base de datos **MySQL**, por lo que sino está instalado en nuestro sistema operativo, debemos seguir
los siguientes pasos en nuestra terminal:

``` 
$ sudo apt-get install mysql-server
$ sudo mysql -u root -p
$ sudo apt-get install libmysqlclient-dev
```
Y ya estaría disponible este motor de base de datos en nuestro computador, luego de esto se puede crear
un usuario, pero es opcional, se puede trabajar con el "root" tranquilamente. Para crear el usuario se deben hacer
los siguientes pasos:
```
$ sudo mysql -u root -p
> CREATE USER 'nombre_usuario'@'localhost' IDENTIFIED BY 'tu_contrasena';
> GRANT ALL PRIVILEGES ON * . * TO 'nombre_usuario'@'localhost';
> FLUSH PRIVILEGES;
```
Posteriormente se deben ejecutar los scripts sql, para tener dicha información almacenada en nuestro computador, 
puede ser desde terminal, aunque puede ser más tedioso, o una mejor opción ejecutarlo de algun IDE 
como por ejemplo `WorkBench`. 

Si se cambió de usuario en mysql, se debe ingresar al archivo `Solicitudes.h` y ubicar donde están estas variables,
cambiar por las nuevas credenciales y ya se podría ejecutar el código.

Para ejecutar este programa, se debe ingresar al directorio del proyecto y con el comando:
``` 
$ make run 
```   
ya debería de correr, este comando fue definido en un make file almacenado en nuestro directorio de proyecto. En caso
de no compilar se puede hacer manualmente con los siguientes pasos:
```
gcc -o Sistema_vuelos $(mysql_config --cflags) Sistema_vuelos.c $(mysql_config --libs)
./Sistema_vuelos
```
Con esto nuestro sistema ya estaría disponible para el uso del usuario. Para ingresar al menú operativo,
ya existe un usuario y una contraseña predefinidos, los cuales son:
```
usuario: dba_avi
contraseña: rastreo416
```
En caso de ingresar datos inválidos, no podrá acceder al sistema de este menú.

### Pruebas de funcionalidad <img src= https://upload.wikimedia.org/wikipedia/commons/b/b0/Light_green_check.svg width=20 height=20>

**Cargar Usuarios**


<img src= https://github.com/Wolam/Proyecto-I-Lenguajes/blob/master/documentacion/screenshots/Captura%20de%20pantalla%20de%202020-10-02%2019-10-32.png width =400 height=300>



<img src= https://github.com/Wolam/Proyecto-I-Lenguajes/blob/master/documentacion/screenshots/Captura%20de%20pantalla%20de%202020-10-02%2019-11-49.png>


**Estado de vuelo**

<img src= https://github.com/Wolam/Proyecto-I-Lenguajes/blob/master/documentacion/screenshots/Captura%20de%20pantalla%20de%202020-10-02%2019-21-18.png >

**Estadisticas** 


<img src= https://github.com/Wolam/Proyecto-I-Lenguajes/blob/master/documentacion/screenshots/estadisticas.png width =200 height=170>

### Descripción del problema <img src= https://images.uncyclomedia.co/uncyclopedia/en/0/01/DramaticQuestionMark.png width =20 height=20>


Se deberá crear un Sistema de Gestión de Vuelos en C que permita gestionar las principales
funciones de vuelos, reservas y facturación. El programa se utilizará a través de la consola, no se
implementará interfaz gráfica. La información se almacenará y consultará desde el motor de Bases
de Datos.

El programa deberá desplegar un menú al usuario con dos submenús o grupo de funciones (el
menú debe mostrarse recurrentemente después de cada opción realizada -a excepción del salir- y
tener la opción de subir al menú principal desde los menús secundarios) y salir.

**Opciones Operativas**
La solución debe disponer de una sección de opciones operativas en donde se accederá a todas
estas funcionalidades indicando un usuario y una contraseña encriptada (almacenadas en base de
datos).
Al indicar el usuario y la contraseña se habilitará un menú donde se habilitarán las siguientes
funcionalidades:

* Cambio de contraseña
* Información Aerolínea
* Registro de Aviones
* Carga de usuarios
* Registro de vuelo
* Estado de vuelo

**Opciones Generales**
Para acceder a estas funcionalidades el usuario deberá ingresar por medio del Menú Principal y se
deben habilitar las siguientes funcionalidades (Menú General):
* Consulta de vuelos
* Reservación de vuelo
* Información de reserva
* Cancelación de reservación
* Salir

### Diseño del programa <img src=https://cdn2.iconfinder.com/data/icons/creative-and-design-12/64/Creative-Development-idea-research-design-512.png width=20 height=20>

La implementacion del proyecto se utilizo un modelo de BD que permitiera asociar las entidades necesarias.

<img src= "https://github.com/Wolam/Proyecto-I-Lenguajes/blob/master/documentacion/Gestor_Vuelos-ER.png" width =900 height=700>

##### Procedimientos utilizados en la base de datos
La mayor cantidad de procedimientos utilizados en esta proyecto fue para consultar el estado de vuelos, 
para que a la hora de consultarlo desde C sea todo más sencillo, estos se describen a continuación:
```
consVuelo (in v_id_vuelo int)
costo_asiento (in v_id_vuelo int)
fila_asiento (in v_id_vuelo int)
cant_asientos (in v_id_vuelo int)
reservacion (in v_id_vuelo int)
monto_reservacion (in v_id_vuelo int)
```
Reciben como parámetro un entero, que en este caso sería el id del vuelo a consultar, 
devolviendo así la consulta, que será mostrada al usuario posteriormente desde C.

En la funcionalidad de registro de aviones se implementó un procedure y una función, en este caso 
para mostrar y eliminar aviones respectivamente.
```
muestra_aviones(v_marca varchar(20)
eliminar_avion (v_matricula int)
```

También se crearon dos procedimientos aparte, para mostrar las estadísticas de los vuelos,
los cuales no tienen parámetros.
```
estadistica_ventas()
estadistica_personas()
```
Se creó una función para lo que es la validación del usuario y contraseña ingresadas por el usuario
en el menú operativo, la cual recibe como parámetros dos `varchar` y retorna un `boolean`.
```
valida_usuarios (v_usuario varchar(20), v_contrasenia varchar(20))
```
Para las validaciones en la funcionalidad de reservacion, se utilizaron distintas funciones 
que retornan booleanos, también se desarrolló una función para conocer si la persona es adulta o infante, retornando un varchar para identificarlos.
```
valida_pasajeros (v_pasaporte int)
conocer_edad (v_pasaporte int)
valida_pos_asiento
```
Algunos de los últimos procedimientos fueron para brindarle la información al usuario de la reserva ya sea tanto c, como en el pdf.
```
info_reservacion_pdf (in v_pasaporte int)
clientes_reservacion (in v_id_reservacion int)
info_reservacion_c (in v_id_reservacion int)
```
Se crearon dos procedimientos para realizar la reservación del usuario:
```
actualizar_tipo_asiento (in v_id_vuelo int, in v_fila varchar(2), in v_num_asiento int)
actualiza_reserva_asiento (in v_fila varchar(2), in v_num_asiento int, in v_id_vuelo int, 
in v_pasaporte int, in v_id_reservacion int)
```
Y por último los procedimientos que se encargan de eliminar la reservación del cliente, a los cuales
les entra el código de la reservación.
```
cambiar_tipo_asiento (in v_id_reservacion int)
eliminar_reserva_asiento (in v_id_reservacion int)
eliminar_pasajeros_reserva (in v_id_reservacion int)
eliminar_reservacion (in v_id_reservacion int)
```
##### Funciones en C
Para lo que es la funcionalidad de registro de aviones se utilizarion las siguientes funciones:
```
void ejecutar_opcion_registro_av()
void insertar_avion(solicitar_datos_av())
void eliminar_avion()
void mostrar_aviones()
avion *solicitar_datos_av()
```
Ninguna de ellas retorna nada, y se encargar de lo que es la inserción, eliminación y muestra de aviones, 
dependiendo de lo que solicite el usuario, a excepción de `solicitar_datos_av()` que retorna la dirección
de memoria de los datos del avión.

La funcionalidad para cargar usuario está compuesta por las siguientes funciones:
```
void cargar_usuarios(char *nombre_archivo)
FILE* abrir_archivo(ruta_archivo, "r");
char* obtener_reporte(insertar_usuario(usuario))
int insertar_usuario(usuario)
```
Estas funciones se encargan de interactuar con el txt de ingreso, insertar los usarios en la  base de datos,
y obtener los resultados de estas inserciones.

El estado de vuelo es nutrida por las siguientes funciones:
```
void estado_vuelo()
void mostrar_info_vuelo(id_vuelo)
int mostrar_asientos_en_vuelo(id_vuelo)
void mostrar_reservaciones_en_vuelo(id_vuelo);
```
Se encargan de todas las validaciones necesarias para mostrar la información obtenida de los vuelos
que se encuentran almacenados en la base de datos.

Para mostrar las estadísticas al usuario, se utilizan las siguientes dos funciones:
```
void mostrar_estadisticas_reservaciones()
void mostrar_estadisticas_ventas()
```
Estas funciones son alimentadas por otras, que son las encargadas de realizar las consultas
y mostrar los registos en C.
```
int realizar_consulta()
void mostrar_registros()
```
`realizar_consulta()` valida si el `query` es correcto, y `mostrar_registros()` mediante un ciclo imprime 
las filas y columnas de la tabla. 

Existen también funciones para solicitar y validar las credenciales del usuario operativo.
```
char* solicitar_credenciales()
int verificar_credenciales(char *credenciales)
```
los cuales retornan un puntero char con las credenciales del usuario y un int, para validar si son correctos
o no los datos ingresados por dicho usuario.

En general para realizar las consultas a la base de datos con los datos ingresados por el usuario, fue mediante la 
concatenación de los chars, que contenían el cuerpo de la consulta, y los datos del usuario, nos apoyamos de las funciones `strcat()`, `strncat()` de la librería `string.h`.

Para lo que es la conexión a la base de datos se utilizaron las siguientes funciones:
```
void realizar_conexion()
void finalizar_conexion()
```
### Librerías usadas <img src=https://image.flaticon.com/icons/png/512/130/130304.png width=20 height=20>
Para la correcta funcionalidad de este proyecto, son necesarias las siguientes librerías:
```
#include <stdio.h>
#include <string.h>
#include <mysql.h>
#include <stdlib.h>
```
### Análisis de resultados

##### Objetivos logrados 
* Funcionalidad del menú
* Registro de Aviones
* Carga de usuarios
* Estado de vuelos
* Estadisticas
* Estas funcionalidades con sus respectivas validaciones
* Validar el usuario y contraseña del usuario operativo

### Bitácora

---
Autores:

**Joseph Valenciano @josephv27**

**Wilhelm Carstens @wolam**
