# gestor-vuelos #

## Instalación ##

Para llevar a cabo la instalación se debe tener en cuenta una distribución **GNU/Linux**,
por lo que seguramente si se utiliza en otro SO puede que dé problemas.

### MySQL-server ##

```bash 
$ sudo apt-get install mysql-server
$ sudo mysql -u root -p
$ sudo apt-get install libmysqlclient-dev
```

### usuario ###

```bash
$ sudo mysql -u root -p
> CREATE USER {USUARIO} @{HOST} IDENTIFIED BY {CONTRASEÑA};
> GRANT ALL PRIVILEGES ON * . * TO {USUARIO}@{HOST} ;
> FLUSH PRIVILEGES;
```

Posteriormente se deben ejecutar los scripts sql, para tener dicha información almacenada en nuestro computador, 
puede ser desde terminal, aunque puede ser más tedioso, o una mejor opción ejecutarlo de algun IDE 
como por ejemplo (WorkBench)[https://www.mysql.com/products/workbench/]. 

Si se cambió de usuario en mysql, se debe ingresar al archivo `Solicitudes.h` y ubicar donde están estas variables,
cambiar por las nuevas credenciales y ya se podría ejecutar el código.

## Ejecución ##

Para ejecutar este programa, se debe ingresar al directorio del proyecto y con el comando:

```bash 
$ make run 
```   

Con esto nuestro sistema ya estaría disponible para el uso del usuario. Para ingresar al menú operativo,
ya existe un usuario y una contraseña predefinidos, los cuales son:
```
usuario: dba_avi
contraseña: rastreo416
```
En caso de ingresar datos inválidos, no podrá acceder al sistema de este menú.

----
## Autores ##

* Joseph Valenciano @JosephV27
* Wilhelm Carstens @wolam
