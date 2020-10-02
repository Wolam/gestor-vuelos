# PROCEDIMIENTOS
  
DELIMITER //
create procedure consVuelo (in v_id_vuelo int)
begin  
	select origen, salida, destino, llegada, matricula_avion
		from vuelo 
		where id_vuelo = v_id_vuelo;
end 
//

CALL consVuelo(1);


DELIMITER //
create procedure costo_asiento (in v_id_vuelo int)
begin  
	select tipo_asiento, costo
	from costo 
    where id_vuelo = v_id_vuelo;
end 
//

CALL costo_asiento(1);


DELIMITER //
create procedure fila_asiento (in v_id_vuelo int)
begin  
	select fila, tipo_asiento
	from asiento 
    where id_vuelo = v_id_vuelo;
end 
//

CALL fila_asiento(1);


DELIMITER //
create procedure cant_asientos(in v_id_vuelo int)
select l.cantidad_asientos_libres, o.cantidad_asientos_ocupados
from 
(select count(a.tipo_asiento) as cantidad_asientos_libres
	from asiento a
    where a.tipo_asiento LIKE '%_L' and a.id_vuelo = v_id_vuelo) as l
NATURAL JOIN
(select count(a.tipo_asiento) as cantidad_asientos_ocupados
	from asiento a
    where a.tipo_asiento = '%_O' and a.id_vuelo = v_id_vuelo) as o;
//

CALL cant_asientos(1);

DELIMITER //
create procedure reservacion(in v_id_vuelo int)
begin
select mr.id_reservacion, a.fila, a.tipo_asiento, a.num_asiento, a.pasaporte, u.nombre_cliente
	from monto_reservacion mr 
    inner join asiento a
		on mr.id_reservacion = a.id_reservacion
	inner join usuario u
		on a.pasaporte = u.pasaporte
	where mr.id_vuelo = v_id_vuelo;
end
//

CALL reservacion(1);

DELIMITER //
create procedure monto_reservacion(in v_id_vuelo int)
begin
select mr.id_reservacion, mr.monto_total , count(a.num_asiento) as asientos_adquiridos
	from monto_reservacion mr 
    inner join asiento a
		on mr.id_reservacion = a.id_reservacion
	where mr.id_vuelo = v_id_vuelo
	group by mr.id_reservacion;
end
//

CALL monto_reservacion(1);


# PROCEDIMIENTOS CON ESTADISTICAS DE VUELOS

DELIMITER //
create procedure estadistica_ventas()
begin
	select  v.id_vuelo, sum(mr.monto_total) as suma_total
			from monto_reservacion mr
            inner join vuelo v
				on mr.id_vuelo = v.id_vuelo
			group by v.id_vuelo
			order by suma_total desc 
			LIMIT 3;
end
//

CALL estadistica_ventas;


DELIMITER //
create procedure estadistica_personas()
begin
	select v.id_vuelo, count(r.id_reservacion) as reservas
			from vuelo v
			inner join reservacion r
				on v.id_vuelo = r.id_vuelo
			group by v.id_vuelo
			order by reservas desc
			LIMIT 3;
end 
//

CALL estadistica_personas;


# funcion para validar usuario y contrasena

SET GLOBAL log_bin_trust_function_creators = 1;

DELIMITER //
create function valida_usuarios (v_usuario varchar(20), v_contrasenia varchar(20)) returns boolean
BEGIN 
	DECLARE usuario varchar(20);
    DECLARE contra BLOB;

	select usuario_aerolinea, contrasenia into usuario, contra
		from aerolinea
	where usuario_aerolinea = v_usuario and AES_DECRYPT(contrasenia, 'fjm') = v_contrasenia;
	
    if usuario is not NULL then
		if contra is NULL then 
			return false;
		else
			return true;
		end if;
	else
		return False;
	end if;
end; //

DELIMITER ;

select valida_usuarios('dba_avi', 'rastreo416');


# funcion para validar pasajeros 

DELIMITER //
create function valida_pasajeros (v_pasaporte int) returns boolean
BEGIN 
	DECLARE pasajero int;
    
    select pasaporte into pasajero
		from usuario
	where pasaporte = v_pasaporte;

	if pasajero is NULL then 
		return false;
	else
		return true;
	end if;
end; //

DELIMITER ;

select valida_pasajeros(2019039864);

# funcion para verificar edad
DELIMITER //
create function conocer_edad (v_pasaporte int) returns varchar(2)
BEGIN 
	DECLARE edad int;
    
    SELECT TIMESTAMPDIFF(YEAR,fecha_nacimiento,CURDATE()) into edad
     FROM usuario
		where pasaporte = v_pasaporte;

	if edad >= 3 then
		return 'A';
	else
		return 'I';
	end if;
end; //

DELIMITER ;

select conocer_edad(2048395209);

DELIMITER //
create function valida_asientos (v_cantidad_asientos int, v_id_vuelo int) returns boolean 
BEGIN 
	DECLARE cantidad_asientos int;
    
    select count(a.tipo_asiento) into cantidad_asientos 
	from asiento a
    where a.tipo_asiento LIKE '%_L' and a.id_vuelo = v_id_vuelo;
    
    if cantidad_asientos >= v_cantidad_asientos then 
		return true;
	else 
		return false;
	end if;
end; //

DELIMITER ;

select valida_asientos (3, 1);
    

# DROPS DE PROCEDIMIENTOS

# drop procedure consVuelo;
# drop procedure costo_asiento;
# drop procedure fila_asiento;
# drop procedure cant_asientos;
# drop procedure reservacion;
# drop procedure monto_reservacion;
# drop procedure estadistica_ventas;
# drop procedure estadistica_personas;
# drop function valida_usuarios;