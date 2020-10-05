# show databases;

#create database bd_aviones;

use bd_aviones;

# show tables;

# CREACION DE TABLAS

create table vuelo 
(id_vuelo int not null,
origen varchar(5) not null,
destino varchar(5) not null,
matricula_avion int not null,
salida varchar(40) not null,
llegada varchar(40) not null,
id_aerolinea int not null,
primary key(id_vuelo));

create table ciudad
(id_ciudad varchar(5) not null,
nombre_ciudad varchar(30) not null,
primary key(id_ciudad));

create table usuario
(pasaporte int not null,
nombre_cliente varchar(20) not null,
primer_apellido varchar(30) not null,
segundo_apellido varchar(30) not null, 
sexo varchar(1) not null,
fecha_nacimiento date not null,
primary key (pasaporte));

create table avion 
(matricula int not null,
marca varchar(20) not null,
modelo int not null,
anio int not null,
primary key (matricula));

create table aerolinea 
(id_aerolinea int not null,
nombre_aerolinea varchar(30) not null,
hub varchar(20) not null,
usuario_aerolinea varchar(20) not null,
contrasenia BLOB not null,
primary key (id_aerolinea));

create table reservacion 
(pasaporte int not null,
id_reservacion int not null,
id_vuelo int not null,
id_edad varchar(2) not null,
primary key (pasaporte, id_reservacion));

create table monto_reservacion
(id_reservacion int not null,
monto_total int not null,
id_vuelo int not null,
fecha_reserva date not null,
id_aerolinea int not null,
primary key (id_reservacion));

create table asiento 
(fila varchar(2) not null,
tipo_asiento varchar(3) not null,
num_asiento int not null,
pasaporte int,
id_reservacion int,
id_vuelo int not null,
primary key (id_vuelo, fila, tipo_asiento, num_asiento));

create table costo
(id_vuelo int not null,
tipo_asiento varchar(3) not null,
id_edad varchar(2) not null,
costo int not null);


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

alter table vuelo
add foreign key (id_aerolinea)
references aerolinea (id_aerolinea);

alter table reservacion 
add foreign key (pasaporte)
references usuario (pasaporte);

alter table reservacion 
add foreign key (id_vuelo)
references vuelo (id_vuelo);

alter table monto_reservacion 
add foreign key (id_aerolinea)
references aerolinea (id_aerolinea);

alter table asiento 
add foreign key (id_vuelo)
references vuelo (id_vuelo);

alter table costo 
add foreign key (id_vuelo)
references vuelo (id_vuelo);

alter table monto_reservacion 
add foreign key (id_vuelo)
references vuelo (id_vuelo);

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
    

insert into aerolinea (id_aerolinea, nombre_aerolinea, hub, usuario_aerolinea, contrasenia)
values 
	(416, 'Avianca', 'BOG', 'dba_avi', AES_ENCRYPT('rastreo416', 'fjm'));
    

insert into vuelo (id_vuelo, origen, destino, matricula_avion, salida, llegada, id_aerolinea)
values 
	(1, 'NYC', 'SJO', 7835, '2020/05/12 10:05', '2020/05/12 16:10', 416),
    (2, 'BOG', 'BER', 1035, '2020/07/02 11:15', '2020/07/03 02:35', 416),
    (3, 'SYD', 'RJ', 3289, '2020/02/15 16:15', '2020/02/16 10:15', 416),
    (4, 'MAD', 'SJO', 9741, '2019/04/19 14:25', '2019/04/19 23:15', 416),
    (5, 'PAR', 'MAD', 4510, '2020/08/11 08:32', '2020/08/11 11:40', 416),
    (6, 'LUX', 'BER', 2532, '2018/11/14 03:45', '2018/11/14 14:35', 416),
    (7, 'SJO', 'FL', 6812, '2020/01/23 11:25', '2020/01/23 02:35', 416),
    (8, 'TOK', 'PEK', 2532, '2017/02/27 13:12', '2017/02/27 20:15', 416),
    (9, 'FL', 'MAD', 1035, '2019/05/29 9:45', '2019/05/30 02:50', 416),
    (10, 'RJ', 'LUX', 5647, '2016/10/12 2:32', '2016/10/12 23:40', 416);


select * from costo;

insert into costo (id_vuelo, tipo_asiento, id_edad, costo)
values 
	(1, 'BL', 'A', 1000),
    (1, 'BL', 'I', 300),
    (1, 'SL', 'A', 750),
    (1, 'SL', 'I', 200),
    (1, 'EL', 'A', 500),
    (1, 'EL', 'I', 100),
    (2, 'BL', 'A', 2000),
    (2, 'BL', 'I', 500),
    (2, 'SL', 'A', 1750),
    (2, 'SL', 'I', 300),
    (2, 'EL', 'A', 700),
    (2, 'EL', 'I', 250),
    (3, 'BL', 'A', 700),
    (3, 'BL', 'I', 200),
    (3, 'SL', 'A', 550),
    (3, 'SL', 'I', 100),
    (3, 'EL', 'A', 300),
    (3, 'EL', 'I', 75);
  
  
  insert into usuario (pasaporte, nombre_cliente, primer_apellido, segundo_apellido, sexo, fecha_nacimiento)
  values 
	(2019039864, 'Joseph', 'Valenciano', 'Madrigal', 'M', STR_TO_DATE('2015-5-01','%Y-%m-%d')),
    (2019344555, 'Wilhelm', 'Carstens', 'Soto', 'M', STR_TO_DATE('2001-5-01','%Y-%m-%d')),
    (2018874521, 'Jeremy', 'Valenciano', 'Madrigal', 'M', STR_TO_DATE('2017-5-01','%Y-%m-%d')),
    (2048395209, 'Randox', 'Valenciano', 'Madrigal', 'M', STR_TO_DATE('2020-5-01','%Y-%m-%d'));
    
    insert into monto_reservacion (id_reservacion, monto_total, id_vuelo, fecha_reserva, id_aerolinea)
	values 
	(1, 55000, 1, STR_TO_DATE('2020-9-22','%Y-%m-%d'), 416);

insert into reservacion (pasaporte, id_reservacion, id_vuelo, id_edad)
values 
	(2019039864, 1, 1, 'A'),
    (2019344555, 1, 1, 'A'),
    (2018874521, 1, 1, 'A'),
    (2048395209, 1, 1, 'I');
    

insert into asiento (fila, tipo_asiento, num_asiento, pasaporte, id_reservacion, id_vuelo)
values 
	('A', 'BL', 1, 2019039864, 1, 1),
    ('A', 'BL', 2, 2019344555, 1, 1),
    ('A', 'BL', 3, 2018874521, 1, 1),
    ('A', 'BL', 4, NULL, NULL, 1),
    ('B', 'BL', 1, NULL, NULL, 1),
    ('B', 'BL', 2, NULL, NULL, 1),
    ('C', 'SL', 1, NULL, NULL, 1),
    ('C', 'SL', 2, NULL, NULL, 1),
    ('D', 'SL', 1, NULL, NULL, 1),
    ('D', 'SL', 2, NULL, NULL, 1),
    ('D', 'SL', 3, NULL, NULL, 1),
    ('E', 'EL', 1, NULL, NULL, 1),
    ('E', 'EL', 2, NULL, NULL, 1),
    ('E', 'EL', 3, NULL, NULL, 1),
    ('E', 'EL', 4, NULL, NULL, 1);
    
    
insert into asiento (fila, tipo_asiento, num_asiento, pasaporte, id_reservacion, id_vuelo)
values 
	('A', 'BL', 1, NULL, NULL, 2),
    ('A', 'BL', 2, NULL, NULL, 2),
    ('B', 'BL', 1, NULL, NULL, 2),
    ('B', 'BL', 2, NULL, NULL, 2),
    ('C', 'SL', 1, NULL, NULL, 2),
    ('C', 'SL', 2, NULL, NULL, 2),
    ('D', 'SL', 1, NULL, NULL, 2),
    ('D', 'SL', 2, NULL, NULL, 2),
    ('E', 'EL', 1, NULL, NULL, 2),
    ('E', 'EL', 2, NULL, NULL, 2);
    
insert into asiento (fila, tipo_asiento, num_asiento, pasaporte, id_reservacion, id_vuelo)
values 
	('A', 'BL', 1, NULL, NULL, 3),
    ('A', 'BL', 2, NULL, NULL, 3),
    ('A', 'BL', 3, NULL, NULL, 3),
    ('B', 'BL', 1, NULL, NULL, 3),
    ('B', 'BL', 2, NULL, NULL, 3),
    ('B', 'BL', 4, NULL, NULL, 3),
    ('C', 'SL', 1, NULL, NULL, 3),
    ('C', 'SL', 2, NULL, NULL, 3),
    ('C', 'SL', 3, NULL, NULL, 3),
    ('D', 'SL', 1, NULL, NULL, 3),
    ('D', 'SL', 2, NULL, NULL, 3),
    ('D', 'SL', 3, NULL, NULL, 3),
    ('E', 'EL', 1, NULL, NULL, 3),
    ('E', 'EL', 2, NULL, NULL, 3),
    ('E', 'EL', 3, NULL, NULL, 3);
    

# DROP TABLAS 
# drop table costo;
# drop table asiento;
# drop table monto_reservacion;
# drop table reservacion;
# drop table vuelo;
# drop table aerolinea;
# drop table usuario;
# drop table ciudad;
# drop table avion;
