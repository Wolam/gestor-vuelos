show databases;

create database bd_aviones;

use bd_aviones;

create table vuelo 
(id_vuelo int,
origen varchar(5),
destino varchar(5),
avion varchar(10),
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
nombre_aerolinea varchar(30), 
monto_total int,
fecha_reserva int,
primary key (pasaporte, id_reservacion));

create table asiento 
(nombre_asiento varchar(20),
tipo_asiento varchar(20),
id_reservacion int,
id_vuelo int,
primary key (nombre_asiento));

create table costo 
(id_vuelo int,
tipo_asiento varchar(20),
costo int,
primary key (id_vuelo, tipo_asiento));



