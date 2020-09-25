show databases;

create database bd_aviones;

use bd_aviones;

show tables;
# CREACION DE TABLAS

create table vuelo 
(id_vuelo int,
origen varchar(5),
destino varchar(5),
matricula_avion int,
salida varchar(40),
llegada varchar(40),
primary key(id_vuelo));

create table ciudad
(id_ciudad varchar(5),
nombre_ciudad varchar(30),
primary key(id_ciudad));

create table usuario
(pasaporte int,
nombre_cliente varchar(20),
primer_apellido varchar(30),
segundo_apellido varchar(30), 
sexo varchar(1),
fecha_nacimiento date,
primary key (pasaporte));

create table avion 
(matricula int,
marca varchar(20),
modelo int,
anio int,
primary key (matricula));

create table aerolinea 
(id_aerolinea int,
nombre_aerolinea varchar(30),
hub varchar(20),
usuario_aerolinea varchar(20),
contrasenia varchar(20),
primary key (id_aerolinea));

create table reservacion 
(pasaporte int,
id_reservacion int,
id_vuelo int,
id_aerolinea int, 
monto_total int,
fecha_reserva int,
primary key (pasaporte, id_reservacion));

create table asiento 
(nombre_asiento varchar(20),
tipo_asiento varchar(20),
pasaporte int,
id_reservacion int,
id_vuelo int,
primary key (nombre_asiento));

create table costo 
(id_vuelo int,
tipo_asiento varchar(20),
costo int,
primary key (id_vuelo, tipo_asiento));


# LLAVES FORANEAS

alter table vuelo
add foreign key (origen)
references ciudad (id_ciudad);

alter table vuelo
add foreign key (destino)
references ciudad (id_ciudad);

alter table vuelo
add foreign key (matricula_avion)
references avion (matricula);

alter table reservacion 
add foreign key (pasaporte)
references usuario (pasaporte);

alter table reservacion 
add foreign key (id_vuelo)
references vuelo (id_vuelo);

alter table reservacion 
add foreign key (id_aerolinea)
references aerolinea (id_aerolinea);

alter table asiento 
add foreign key (pasaporte, id_reservacion)
references reservacion (pasaporte, id_reservacion);

alter table asiento 
add foreign key (id_vuelo)
references vuelo (id_vuelo);

alter table costo 
add foreign key (id_vuelo)
references vuelo (id_vuelo);

alter table costo 
add foreign key (tipo_asiento) # revisar como hacer foranea de tipo_asiento
references asiento (tipo_asiento);

select COLUMN_NAME, CONSTRAINT_NAME, REFERENCED_COLUMN_NAME, REFERENCED_TABLE_NAME
from information_schema.KEY_COLUMN_USAGE
where TABLE_NAME = 'reservacion';


# INSERTS A TABLAS
insert into ciudad (id_ciudad, nombre_ciudad)
values 
	('NYC', 'NUEVA YORK'),
    ('SJO', 'SAN JOSE'),
    ('BOG','BOGOTA'),
    ('FL', 'FLORIDA'),
    ('RJ', 'RIO DE JANEIRO'),
    ('MAD', 'MADRID'),
    ('PAR', 'PARIS'),
    ('BER', 'BERLIN'),
    ('LUX', 'LUXEMBURGO'),
    ('PEK', 'PEKIN'),
    ('TOK', 'TOKIO'),
    ('SYD', 'SYDNEY');
    

insert into avion (matricula, marca, modelo, anio)
values 
	(7835, 'Boeing', 747, 2009),
	(6812, 'Boeing', 747, 2012),
    (9741, 'Airbus', 320, 2015),
    (5647, 'Airbus', 320, 2017),
    (2532, 'Bombardier', 200, 2008),
    (3289, 'Ilyushin', 200, 2010),
    (4510, 'Boeing', 747, 2011),
    (1035, 'Airbus', 320, 2007);
    
  
insert into vuelo (id_vuelo, origen, destino, matricula_avion, salida, llegada)
values 
	(1, 'NYC', 'SJO', 7835, '2020/05/12 10:05', '2020/05/12 16:10'),
    (2, 'BOG', 'BER', 1035, '2020/07/02 11:15', '2020/07/03 02:35'),
    (3, 'SYD', 'RJ', 3289, '2020/02/15 16:15', '2020/02/16 10:15'),
    (4, 'MAD', 'SJO', 9741, '2019/04/19 14:25', '2019/04/19 23:15'),
    (5, 'PAR', 'MAD', 4510, '2020/08/11 08:32', '2020/08/11 11:40'),
    (6, 'LUX', 'BER', 2532, '2018/11/14 03:45', '2018/11/14 14:35'),
    (7, 'SJO', 'FL', 6812, '2020/01/23 11:25', '2020/01/23 02:35'),
    (8, 'TOK', 'PEK', 2532, '2017/02/27 13:12', '2017/02/27 20:15'),
    (9, 'FL', 'MAD', 1035, '2019/05/29 9:45', '2019/05/30 02:50'),
    (10, 'RJ', 'LUX', 5647, '2016/10/12 2:32', '2016/10/12 23:40');

insert into aerolinea (id_aerolinea, nombre_aerolinea, hub, usuario_aerolinea, contrasenia)
values 
	(416, 'Avianca', 'BOG', 'dba_avi', 'rastreo416');


# DROP TABLAS 
# drop table reservacion;
# drop table aerolinea;
# drop table usuario;
# drop table vuelo;
# drop table ciudad;
# drop table avion;
# drop table asiento;
# drop table costo;
 
 







