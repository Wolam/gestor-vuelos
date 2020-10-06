SET SQL_SAFE_UPDATES = 0;

SET GLOBAL log_bin_trust_function_creators = 1;

# PROCEDURE PARA MOTRAR AVIONES FILTRADOS POR MARCA

DELIMITER //
create procedure muestra_aviones(v_marca varchar(20))
BEGIN
	select matricula, modelo, anio
		from avion
		where marca = v_marca;
        
end
//

# CALL muestra_aviones('Boeing');

# FUNCION PARA ELIMINAR AVION

DELIMITER //
create function eliminar_avion (v_matricula int) returns varchar(30)
BEGIN 
	DECLARE avion int;
    DECLARE EXIT HANDLER FOR 1451
    begin 
		return 'AVION EN VUELO';
	end;

    select matricula into avion
		from avion
		where matricula = v_matricula;

	if avion is NULL then 
		return 'NO ENCONTRADO';
	else
		delete from avion where matricula = v_matricula;
		return 'ELIMINADO';
	end if;
end; //

DELIMITER ;
# select eliminar_avion(1035);

# PROCEDIMIENTOS PARA MOSTRAR EL ESTADO DE VUELO
  
DELIMITER //
create procedure consVuelo (in v_id_vuelo int)
begin  
	select origen, salida, destino, llegada, matricula_avion
		from vuelo 
		where id_vuelo = v_id_vuelo;
end 
//

# CALL consVuelo(1);

DELIMITER //
create procedure costo_asiento (in v_id_vuelo int)
begin  
	select tipo_asiento, costo
	from costo 
    where id_vuelo = v_id_vuelo;
end 
//

# CALL costo_asiento(1);


DELIMITER //
create procedure fila_asiento (in v_id_vuelo int)
begin  
	select fila, tipo_asiento,num_asiento
    from asiento
    where id_vuelo = v_id_vuelo
    order by fila,num_asiento;
end 
//

# CALL fila_asiento(1);


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
    where a.tipo_asiento LIKE '%_O' and a.id_vuelo = v_id_vuelo) as o;
//
 
 # CALL cant_asientos(1);

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

# CALL reservacion(1);

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

# CALL monto_reservacion(1);


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

# CALL estadistica_ventas;


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

# CALL estadistica_personas;


# FUNCION QUE VALIDA EL USUARIO Y LA CONSTRASEÑA

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
		return false;
	end if;
end; //

DELIMITER ;

# select valida_usuarios('dba_avi', 'rastreo416');


# FUNCION PARA VALIDAR PASAJEROS

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

# select valida_pasajeros(2019039864);

# FUNCION PARA EXTRAER LA EDAD DEL CLIENTE
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

# select conocer_edad(2048395209);

# VALIDA LAS POSICIONES DE LOS ASIENTOS INGRESADOS POR EL USUARIO PARA LA RESERVA

DELIMITER //
create function valida_pos_asiento (v_fila varchar(2), v_num_asiento int, v_id_vuelo int) returns boolean 
BEGIN 
	DECLARE f_fila varchar(2);
    DECLARE f_num_asiento int;
    
    select fila, num_asiento into f_fila, f_num_asiento
		from asiento
		where fila = v_fila and num_asiento = v_num_asiento and id_vuelo = v_id_vuelo and tipo_asiento LIKE '%_L';
    
	if f_fila is null or f_num_asiento is null then 
		return false;
	else 
		return true;
	end if;
end; //

DELIMITER ;

# select valida_pos_asiento('A', 1, 2);

# PROCEDIMIENTOS PARA LA INFORMACION DE LA RESERVA QUE ALIMENTA EL PDF

DELIMITER //
create procedure info_reservacion_pdf (in v_pasaporte int)
begin  

	select r.id_reservacion, v.id_vuelo, v.origen, v.salida, v.destino, v.llegada, mr.monto_total, a.nombre_aerolinea
		from vuelo v
		inner join reservacion r
			on v.id_vuelo = r.id_vuelo
		inner join monto_reservacion mr
			on r.id_reservacion = mr.id_reservacion
		inner join aerolinea a
			on mr.id_aerolinea = a.id_aerolinea
			where r.pasaporte = v_pasaporte;

end 
//

DELIMITER //
create procedure adultos_reservacion (in v_id_reservacion int)
begin  

select a.fila, a.num_asiento, a.pasaporte
	from monto_reservacion mr 
    inner join asiento a
		on mr.id_reservacion = a.id_reservacion
	where mr.id_reservacion = v_id_reservacion;
		
end 
//

select * from asiento;
call adultos_reservacion(2);

# call adultos_reservacion(1);

DELIMITER //
create procedure infantes_reservacion (in v_id_reservacion int)
begin  

select r.pasaporte
	from reservacion r
    inner join usuario u
		on r.pasaporte = u.pasaporte
	where year(curdate())-year(u.fecha_nacimiento) < 3 and r.id_reservacion = v_id_reservacion;
		
end 
//

# call infantes_reservacion(1);

# PROCEDIMIENTO DE INFORMACION DE RESERVA PARA C

DELIMITER //
create procedure info_reservacion_c (in v_id_reservacion int)
begin  

	select mr.id_reservacion, v.id_vuelo, v.origen, v.salida, v.destino, v.llegada, mr.fecha_reserva, mr.monto_total, a.nombre_aerolinea
		from vuelo v
		inner join monto_reservacion mr
			on v.id_vuelo = mr.id_vuelo
		inner join aerolinea a
			on mr.id_aerolinea = a.id_aerolinea
			where mr.id_reservacion = v_id_reservacion;
            
end 
//

# call info_reservacion_c(1);

# PROCEDIMIENTOS PARA REALIZAR UNA RESERVACION

DELIMITER //
create procedure actualiza_reserva_asiento (in v_fila varchar(2), in v_num_asiento int, in v_id_vuelo int, in v_pasaporte int, in v_id_reservacion int)
begin  
	if conocer_edad(v_pasaporte) = 'A' then
		update asiento 
				set pasaporte = v_pasaporte, id_reservacion = v_id_reservacion, tipo_asiento = replace(tipo_asiento, "L", "O")
				where fila = v_fila and num_asiento = v_num_asiento and id_vuelo = v_id_vuelo;
	end if;
		
		
end 
//

# call actualiza_reserva_asiento('B', 2, 1, 2019039864, 2);

# PROCEDIMIENTOS PARA CANCELAR RESERVACION

DELIMITER //
create procedure eliminar_reserva_asiento (in v_id_reservacion int)
begin  
	update asiento 
			set pasaporte = NULL, id_reservacion = NULL, tipo_asiento = replace(tipo_asiento, "O", "L")
			where id_reservacion = v_id_reservacion;
		
end 
//

# call eliminar_reserva_asiento(1);

DELIMITER //
create procedure eliminar_pasajeros_reserva (in v_id_reservacion int)
begin  
	delete from reservacion
		where id_reservacion = v_id_reservacion;
end 
//

# call eliminar_pasajeros_reserva(1);

DELIMITER //
create procedure eliminar_reservacion (in v_id_reservacion int)
begin  
	delete from monto_reservacion
		where id_reservacion = v_id_reservacion;
end 
//

#call eliminar_reservacion(1);

# FUNCION PARA CALCULAR MONTO_TOTAL
DELIMITER //
create function monto_total_reserva (v_id_reservacion int) returns int
BEGIN 
	DECLARE monto_adulto int;
    DECLARE monto_infante int;
    DECLARE asiento_mas_caro varchar(3);
    DECLARE precio int;
    
	select sum(c.costo) into monto_adulto
		from costo c
        inner join asiento a 
			on c.id_vuelo = a.id_vuelo
		where a.id_reservacion = v_id_reservacion and c.tipo_asiento = a.tipo_asiento and c.id_edad = 'A';
        
    select max(p) into precio from(    
    select c.tipo_asiento, max(c.costo) as p 
		from costo c
        inner join asiento a 
			on c.id_vuelo = a.id_vuelo
		where a.id_reservacion = 2 and c.tipo_asiento = a.tipo_asiento and c.id_edad = 'A'
        group by c.tipo_asiento) as T;
        
	select c.tipo_asiento into asiento_mas_caro
		from costo c
        inner join asiento a
        on c.id_vuelo = a.id_vuelo
        where c.costo = precio and a.id_reservacion = v_id_reservacion
	LIMIT 1;
        
    select sum(c.costo) into monto_infante
		from costo c
        inner join reservacion r
		on c.id_vuelo = r.id_vuelo
	where r.id_edad = 'I' and c.tipo_asiento = asiento_mas_caro and r.id_reservacion = v_id_reservacion and c.id_edad = 'I';
    
    if monto_infante is null then
		set monto_infante = 0;
	end if;
    
	return monto_adulto + monto_infante;
    
end; //

DELIMITER ;

DELIMITER //
create function crear_id_reservacion () returns int
BEGIN 
	DECLARE numero int;
    
	update indice 
		set id = id + 1;
        
	select id into numero
		from indice;
        
	return numero;
    
end; //

DELIMITER ;

select crear_id_reservacion();

# DROPS DE PROCEDIMIENTOS

--     drop procedure consVuelo;
--     drop procedure costo_asiento;
--     drop procedure fila_asiento;
--     drop procedure cant_asientos;
--     drop procedure reservacion;
--     drop procedure monto_reservacion;
--     drop procedure estadistica_ventas;
--     drop procedure estadistica_personas;
--     drop function valida_usuarios;
--     drop function valida_pasajeros;
--     drop function conocer_edad;
--     drop function valida_pos_asiento;
--     drop procedure info_reservacion_pdf;
--     drop procedure adultos_reservacion;
--     drop procedure infantes_reservacion;
--     drop procedure info_reservacion_c;
--     drop procedure actualiza_reserva_asiento;
--     drop procedure eliminar_reserva_asiento;
--     drop procedure eliminar_pasajeros_reserva;
--     drop function monto_total_reserva;
--     drop procedure muestra_aviones;
--     drop function eliminar_avion;
--     drop procedure eliminar_reservacion;
--     drop function select crear_id_reservacion;
