// Tarea 1: Algoritmos y Complejidad (INF-221) Semestre 2026-2
// Autor: Martín Angelo Araya Díaz
// Rol: 202473646-9

En este readme se incluyen las instrucciones para poder ejecutar la tarea en su totalidad.
- Se asume que todos los paquetes necesarios para la ejecución de archivos o generación del reporte están instalados, de todas formas este es un resumen de lo necesario:

sudo apt update
sudo apt install -y texlive-full
sudo apt install -y python3-matplotlib python3-seaborn 
pip install matplotlib seaborn (en caso de que el anterior no funcione)

(paquetes puntuales de latex, recomiendo instalar el full para evitar problemas de todas formas)
sudo apt install -y texlive-latex-base texlive-latex-recommended \
                    texlive-latex-extra texlive-lang-spanish \
                    texlive-bibtex-extra texlive-science \
                    texlive-fonts-extra biber`

Comenzando para los algoritmos de ordenamiento
1. Crear los casos de prueba.
- Dirigirse a code/sorting/scripts y ejecutar en la consola el comando "python3 array_generator.py"
2. Crear los resultados y gráficos
- Irse al directorio code/sorting y ejecutar los comandos "make clean", "make" y luego "make test", esto puede tomar un tiempo, pero se borraron los casos de prueba de 10**7 debido a que me daba error la ejecución de QuickSort, de todas formas la implementación fue modificada, pero esto se detalla en el archivo del algoritmo y en el informe.
- Una vez que se termina de ejecutar, dirigirse a code/sorting/scripts y ejecutar en la consola el comando "python3 plot_generator.py"

Ahora para los algoritmos de matrices
1. Crear los casos de prueba
- Dirigirse a code/matrix_multiplication/scripts y ejecutar en la consola el comando "python3 matrix_generator.py"
2. Crear los resultados y gráficos
- Irse al directorio code/matrix_multiplication y ejecutar los comandos "make clean", "make" y luego "make test", esto debería tomar un tiempo pero se debería ejecutar correctamente. (Para 1024 se demoraba +10 minutos, entonces preferí dejar hasta 256 simplemente, si se desea probar se puede vovler a agregar en el código de matrix_generator.py, de todas formas el análisis es el mismo ya que Strassen sigue demorandose mas que Naive)
- Una vez que se termina de ejecutar, dirigirse a code/matrix_multiplication/scripts y ejecutar en la consola el comando "python3 plot_generator.py"

Una vez ejecutado todo esto se debe generar el informe, antes de esto quisiera hacer algunas aclaraciones:
1. Debido a la restricción de espacio, no pude incluir todos los gráficos que se generaron, intenté incorporar la mayor cantidad posible, los cuales yo consideré que enriquecian mas la comprensión de los algoritmos estudiados.
Prioricé aquellos que nos pueden demostrar la diferencia entre el comportamiento teórico y el práctico. 

Elaboración del informe:

Requisitos previos (solo la primera vez):
El informe se compila con pdflatex. En un sistema Ubuntu/WSL, se debe instalar la distribución junto con los paquetes
Pasos para generar report.pdf:
1. Ejecutar previamente los generadores de gráficos
   (`plot_generator.py` de sorting y de matrix_multiplication), ya que el
   informe incluye las imágenes directamente desde `code/*/data/plots/`.
2. Situarse en la carpeta del informe: `cd report`
3. Ejecutar `pdflatex report.tex`
4. El archivo `report.pdf` queda generado dentro de `report/`

- La bilbiografía se rellenó con la fuente de los algoritmos (aunque de todas formas están en el informe), pero no se agregaron debido a que en la tarea dice textualmente que NO se puede modificar report.tex, la única excepción fue para agregar implementations.tex, que tampoco se especifica donde debe ir ubicada, asique la ubiqué al final.
- Junto con el .zip de la tarea ya está generado el informe en caso de haber problemas con su compilación (aunque no debería).
- Se puede comprobar que se hace referencia a cada gráfico en la sección experiment_results.tex.
- Se menciona en el informe, pero de todas formas el link del repositorio de la tarea en github es: https://github.com/Maardiaz/Tarea1_algoco