# Minishell - @42 Málaga

## 📝 Descripción
Minishell es un proyecto del Common Core de 42 que consiste en desarrollar un propio intérprete de comandos (shell) en lenguaje C. El objetivo es profundizar en el conocimiento de la creación de procesos, la gestión de descriptores de archivo y el manejo de señales en sistemas Unix.

Este proyecto recrea el comportamiento básico de Bash, funcionando de manera interactiva y procesando comandos de forma síncrona.

## 🚀 Funcionalidades

- **Prompt interactivo:** Muestra un prompt funcional a la espera de comandos.
- **Historial:** Gestión de comandos anteriores mediante la librería `readline`.
- **Ejecución de binarios:** Localización y ejecución de comandos a través de la variable de entorno `PATH` o mediante rutas relativas y absolutas.
- **Built-ins implementados:**
  - `echo` con la opción `-n`.
  - `cd` con rutas relativas o absolutas.
  - `pwd`, `export`, `unset`, `env` y `exit`.
- **Gestión de Comillas:**
  - Comillas simples (`' '`): Evitan que la shell interprete metacaracteres.
  - Comillas dobles (`" "`): Evitan la interpretación de metacaracteres, permitiendo únicamente la expansión de variables (`$`).
- **Redirecciones:**
  - `<` Redirección de entrada.
  - `>` Redirección de salida (sobrescritura).
  - `<<` Here-doc (lectura hasta encontrar un delimitador).
  - `>>` Redirección de salida (modo append/añadir).
- **Pipes (`|`):** Redirección de la salida de un comando hacia la entrada del siguiente en la tubería.
- **Variables de Entorno:** Expansión de variables de entorno (`$VAR`) y del valor de salida del último comando ejecutado (`$?`).
- **Señales:** Manejo de señales `Ctrl-C`, `Ctrl-D` y `Ctrl-\` para imitar el comportamiento de Bash en modo interactivo.

## 🛠️ Detalles Técnicos
- **Lenguaje:** C.
- **Gestión de Memoria:** Control estricto de fugas de memoria (leaks) en el proceso principal y en los hijos.
- **Llamadas al sistema principales:** `fork`, `execve`, `waitpid`, `pipe`, `dup2`, `sigaction`, `readline`.

## 💻 Instalación y Uso

1. **Requisitos:** Es necesario tener instalada la librería `readline`.
2. **Clonado, compilación y ejecución:**
   ```bash
   git clone https://github.com/seilanmoore/minishell.git
   cd minishell
   make
   ./minishell
