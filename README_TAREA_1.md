# Sistema de Gestión de TICKETS DE PACIENTES en Hospital

## Descripción

Este sistema permite a los usuarios gestionar la atención de pacientes en un hospital. Los usuarios pueden registrar nuevos pacientes, asignar prioridades, ver la lista de espera, buscar por ID los tickets, y procesarlos según su tiempo de llegada y prioridad asignada. Esta herramienta está diseñada para mejorar la eficiencia en la atención de los pacientes, asegurando que aquellos en situaciones críticas reciban atención lo más pronto posible.

## Cómo compilar y ejecutar

Este sistema ha sido desarrollado en lenguaje C y puede ejecutarse fácilmente utilizando **Visual Studio Code** junto con una extensión para C/C++, como **C/C++ Extension Pack** de Microsoft. Para comenzar a trabajar con el sistema en tu equipo local, sigue estos pasos:

### Requisitos previos:

- Tener instalado [Visual Studio Code](https://code.visualstudio.com/).
- Instalar la extensión **C/C++** (Microsoft).
- Tener instalado un compilador de C (como **gcc**). Si estás en Windows, se recomienda instalar [MinGW](https://www.mingw-w64.org/) o utilizar el entorno [WSL](https://learn.microsoft.com/en-us/windows/wsl/).

### Pasos para compilar y ejecutar:

1. **Descarga y descomprime el** archivo `.zip` en una carpeta de tu elección.
2. **Abre el proyecto en Visual Studio Code**
    - Inicia Visual Studio Code.
    - Selecciona `Archivo > Abrir carpeta...` y elige la carpeta donde descomprimiste el proyecto.
3. **Compila el código**
    - Abre el archivo principal (por ejemplo, `tarea1.c`).
    - Abre la terminal integrada (`Terminal > Nueva terminal`).
    - En la terminal, compila el programa con el siguiente comando (ajusta el nombre si el archivo principal tiene otro nombre):
        
        ```bash
        gcc tdas/*.c tarea1.c -Wno-unused-result -o tarea1
        ```
        
4. **Ejecuta el programa**
    - Una vez compilado, puedes ejecutar la aplicación con:
        
        ```
        ./tarea1
        ```
        

## Funcionalidades

### Funcionando correctamente:

- Registrar pacientes ingresando un ID y una descripción.
- Modificar la prioridad inicial (Baja) de los pacientes.
- Ver la lista de espera de pacientes, ordenada por prioridad y hora de registro.
- Poder ver un Ticket ingresando una ID.
- Atender al siguiente paciente, respetando el orden de prioridad.

### Problemas conocidos:

- La funcionalidad clear que debería limpiar la consola no funciona correctamente.

### A mejorar:

- Implementar una interfaz de usuario más amigable.
- Permitir la edición de la descripción de los pacientes.
- No tener que presionar muchas veces para continuar.

## Ejemplo de uso

**Paso 1: Registrar un Nuevo Paciente**

Se comienza registrando un nuevo paciente que acaba de llegar al hospital.

```
Opción seleccionada: 1) Registrar paciente
Ingrese el ID: 3141592653589793238464
Ingrese la descripción: Alex Mamani - 19 años - Hernia estomacal
```

El sistema registra el id 3141592653589793238464 con una prioridad inicial "Bajo" y guarda la hora actual de registro con un contador que cada vez que se añade aumenta en 1. La prioridad inicial puede ser ajustada más tarde basada en una evaluación médica más detallada.

**Paso 2: Asignar Prioridad a un Paciente**

Tras una evaluación inicial, el médico determina que el estado de Alex Mamani requiere atención prioritaria.

```
Opción seleccionada: 2) Asignar prioridad a paciente
Ingrese el ID: 3141592653589793238464
Seleccione el nuevo nivel de prioridad (Alto, Medio, Bajo): Alto
```

El sistema actualiza la prioridad de Alex Mamani a "Alto", asegurando que será una de las próximas pacientes en ser atendido.

**Paso 3: Ver la Lista de Espera**

El usuario revisa la lista de espera para ver todos los pacientes y sus prioridades.

```
Opción seleccionada: 3) Mostrar lista de espera
```

La lista muestra a Alex Mamani en la parte superior, indicando su prioridad alta y que es la siguiente en línea para recibir atención.

**Paso 4: Atender al Siguiente Paciente**

Alex Mamani es llamado para ser atendido basándose en su prioridad.

```
Opción seleccionada: 4) Atender al siguiente paciente
```

El sistema muestra que Alex Mamani está siendo atendido y la elimina de la lista de espera.

**Paso 5: Buscar un Ticket por su ID**

```
Opción seleccionada: 5) Buscar y mostrar Ticket por ID
```

El sistema muestra que Alex Mamani fue atendido y por ende, mostrará que no hay nada cuando se ingrese su ID.