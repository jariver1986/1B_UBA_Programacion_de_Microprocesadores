Descarga Doxygen desde: https://www.doxygen.nl/download.html



En bash genera un doxifile
doxygen -g Doxyfile

Abrelo y editalo
PROJECT_NAME           = "Documentación STM32"
OUTPUT_DIRECTORY       = "docs"         # Carpeta donde se guardará la documentación
INPUT                 = "src/ led/"     # Directorios con los archivos a documentar
FILE_PATTERNS         = *.c *.h         # Extensiones de archivos a incluir
RECURSIVE             = YES             # Incluir archivos dentro de subcarpetas
GENERATE_HTML         = YES             # Generar documentación en HTML
GENERATE_LATEX        = NO              # No generar PDF (opcional)
HAVE_DOT              = YES             # Habilitar gráficos de dependencias
DOT_PATH              = /usr/bin/dot    # Ubicación de Graphviz (para gráficos)

Guarda y cierra
Ahora genera el documento
doxygen Doxyfile
Esto creará la documentación dentro de la carpeta docs/html/.
Para visualizarla, abre el archivo:
docs/html/index.html

Subir a Github
git checkout --orphan gh-pages
git rm -rf .

mv docs/html/* .

git add .
git commit -m "Publicación de documentación con Doxygen"
git push origin gh-pages


para ver con el visualizador de Gothub Pages se hace lo siguiente:
Ve a GitHub > Settings > Pages.
En Source, selecciona la rama gh-pages y guarda.
hace click en el link que te aparece y podras ver la documentacion.


![image](https://github.com/user-attachments/assets/c268f5ba-de04-4ef2-b6b6-48d8d4108e56)

![image](https://github.com/user-attachments/assets/850e8e74-be7e-47b0-9f2e-78e10dfc3673)


