#archivo make con las reglas  incluidas para compilar y ejecutar el programa

#dependencias y parametros
var_mysql_LIBS := $(shell mysql_config --libs_r)
var_mysql_FLAGS := $(shell mysql_config --cflags)
var_gcc_FLAGS := -g -o
compile:
	gcc $(var_gcc_FLAGS) Sistema_vuelos $(var_mysql_FLAGS) Sistema_vuelos.c $(var_mysql_LIBS)
run: compile
	./Sistema_vuelos
debug:
	gdb Sistema_vuelos
clean:
	rm Sistema_vuelos
