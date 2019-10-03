# Multi-thread find
Buscador multi-hilo sobre archivos de texto desarrollado en C++. Este proyecto forma parte de la asignatura **Sistemas Operativos II** del grado en Ingeniería Informática en la ESI-CR (UCLM).

# Enunciado
El enunciado oficial de la práctica se puede ver [aquí](practica2_ssooII.pdf).

# Observaciones
El buscador da los mismos resultados en número de ocurrencias que el buscador de vscode.
Además, tiene en cuenta que no exista palabra sucesora o antecesora. El tratamiento de 
símbolos y tildes lo realiza mediante un algoritmo que cuenta el número de caracteres iguales encontrados consecutivamente en la palabra que se compara con la buscada.

Si se quiere buscar sobre archivos distintos a los del ejemplo se tendría que cambiar el [makefile](Codigo Fuente/Makefile)

# Ejecución
La compilación y ejecución es automática mediante make, y hay que seguir los siguientes pasos:
1. Compilar: make
2. Ejecutar una opción de las disponibles:
    * make test
    * make book1
    * make book2
    * make book3
3. Eliminar los archivos creados: make clean

En el caso de que se quiera ejecutar sin hacer uso de la herramienta make habría que 
seguir los siguientes pasos:
1. Situarse en la carpeta donde se encuentra el proyecto (donde esta src,include)
2. Crear directorios necesarios: mkdir -p obj/ exec/
3. Compilar:
    1. g++ -Iinclude/ -c  src/SSOOIIGLE.cpp -o obj/SSOOIIGLE.o -pthread -std=c++11
    2. g++ -o exec/SSOOIIGLE obj/SSOOIIGLE.o -pthread -std=c++11
4. Ejecutar: ./exec/SSOOIIGLE <fichero> <palabra> <numero_hilos>
5. Eliminar los archivos creados: rm -rf *~ core obj/ exec/ include/*~ src/*~
