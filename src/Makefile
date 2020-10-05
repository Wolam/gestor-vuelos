#Archivo make con las reglas  incluidas para compilar y ejecutar el programa

#dependencias y parametros
var_mysql_LIBS := $(shell mysql_config --libs_r)
var_mysql_FLAGS := $(shell mysql_config --cflags)
var_gcc_FLAGS := -g -o
var_ld_FLAGS := -lmcheck
var_es_FLAGS := --quiet -o - | ps2pdf -
var_encabezado := --header="HORA RESERVACION: $(shell date)" 

compile:
	@gcc $(var_gcc_FLAGS) Sistema_vuelos $(var_mysql_FLAGS) Sistema_vuelos.c $(var_mysql_LIBS) $(var_ld_FLAGS)
run: compile
	@./Sistema_vuelos
debug:
	@gdb -q Sistema_vuelos
clean:
	@rm Sistema_vuelos
pdf:
	@enscript $(var_encabezado) $(archivo_txt) $(var_es_FLAGS) $(addsuffix .pdf,$(archivo_txt:.txt=))
	@rm $(archivo_txt)