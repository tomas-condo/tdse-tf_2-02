
<img width="1071" height="358" alt="387361653-15600b18-f73b-4ba3-a959-47f0048a1ab6" src="https://github.com/user-attachments/assets/783185ee-f430-4c1f-96fa-2ac4ad3de8b4" />

# **Juego Interactivo "Simón dice  INFORME FINAL"** 

**Autores: Tomás Ignacio Condo, Camila Trinidad Morasso y Francisco Javier Briones**

**Padrones: 111.457, 110.790, 110.058**

**Fecha: 2do cuatrimestre 2025**

### **RESUMEN**

En este trabajo se realizo un juego del estilo "Simón dice" donde se iluminan luces led para que luego el jugador continue la secuencia mostrada por el juego utilizando pulsadores correspondientes a cada uno de las luces. Para agregarle más dinamica al juego tambien se le agrego un menu para selección de juego con una pantalla LED y un LDR para, a partir de la luz del ambiente cambiar el brillo de la pantalla. En el menu mencionado se puede seleccionar entre las opciones de juego principal y puntajes más altos previos luego de que se le da una introducción al jugador y se le explicaron las instrucciones de como manejar el menu. En el menu de juego se pueden elegir entre 2 opciones, Normal y Dificil, donde el modo dificil es igual al normal con la diferencia de que la secuencia no es mostrada por completo para cada nuevo nivel y solo se muestra la luz correspondiente al nuevo color añadido a la secuencia. Mientras continua el juego se mostrara en el display el puntaje actual del jugador con tambien el puntaje máximo global. Luego de terminar el juego se mostrara el puntaje final del jugador y este será devuelto al menu inicial. Durante todo el proceso el juego utiliza una memoria EEPROM externa que almacena datos persistentes como puntajes máximos,o las configuraciones de dificultad. 

La implementación del mismo se realizó utilizando los lenguajes de código C++ y Python mediante el uso del entorno de desarrollo de Mbed en una placa Núcleo-F103RBTX proporcionada por la cátedra de Sistemas Embebidos de la Facultad de Ingeniería de la Universidad de Buenos Aires, y se utilizaron además diferentes módulos para el desarrollo del proyecto.


# Índice General

- [**Introducción general**](#introducción-general)
  - [1.1 Análisis de necesidad y objetivos](#11-análisis-de-necesidad-y-objetivos)
  - [1.2 Módulos e Interfaz](#12-módulos-e-interfaces-de-smartlock)
- [**Introducción específica**](#introducción-específica)
  - [2.1 Requisitos](#21-requisitos)
  - [2.2 Uso](#22-casos-de-uso)
  - [2.3 Descripción de los Módulos del sistema](#23-descripción-de-los-módulos-del-sistema)
    - [2.3.1 Alimentación](#231-alimentación)
    - [2.3.2 Microcontrolador](#232-microcontrolador)
    - [2.3.3 LDR](#234-LDR)
    - [2.3.4 Pantalla Led](#235-Pantalla-Led)
    - [2.3.5 Pulsadores](#236-Pulsadores)
- [**Diseño e Implementación**](#diseño-e-implementación)
  - [3.1 Diseño del Hardware](#31-diseño-del-hardware)
    - [3.1.1 Diseño de la alimentación](#311-diseño-de-la-alimentación)
    - [3.1.2 Diseño de los indicadores e interruptores](#312-diseño-de-los-indicadores-e-interruptores)
    - [3.1.3 Diseño del LDR](#313-diseño-del-LDR)
    - [3.1.4 Diseño del hardware con la placa NUCLEO-F103RBTX](#318-diseño-del-hardware-con-la-placa-nucleo-F103RBTX)
  - [3.2 Firmware del Juego](#32-firmware-del-juego)
    - [3.2.1 Módulo pantalla led](#321-módulo-pantalla-led)
    - [3.2.2 Módulo pulsadores](#322-módulo-pulsadores)
    - [3.2.3 Módulo LDR](#323-módulo-ldr)
    - [3.2.4 Módulo System](#327-módulo-system)
  - [3.3 Diseño de la aplicación y manejo de paquetes](#35-diseño-de-la-aplicación-y-manejo-de-paquetes)
- [**Ensayos y Resultados**](#ensayos-y-resultados)
  - [4.1 Pruebas funcionales de funcionamiento](#41-pruebas-funcionales-de-funcionamiento)
  - [4.2 Cumplimiento de requisitos](#42-cumplimiento-de-requisitos)
  - [4.3 Comparación con otros sistemas similares](#43-comparación-con-otros-sistemas-similares)
  - [4.4 Documentación del desarrollo realizado](#44-documentación-del-desarrollo-realizado)
- [**Conclusiones**](#conclusiones)
  - [5.1 Resultados obtenidos](#51-resultados-obtenidos)
  - [5.2 Próximos pasos](#52-próximos-pasos)
- [**Bibliografía**](#bibliografía)


# **Introducción general** 
## **1.1 Análisis de necesidad y objetivos**
