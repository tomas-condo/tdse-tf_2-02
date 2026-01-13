
<img width="822" height="275" alt="387361653-15600b18-f73b-4ba3-a959-47f0048a1ab6" src="https://github.com/user-attachments/assets/783185ee-f430-4c1f-96fa-2ac4ad3de8b4" />

# **Juego Interactivo "Simón dice"  INFORME FINAL** 

**Autores: Tomás Ignacio Condo, Camila Trinidad Morasso y Francisco Javier Briones**

**Padrones: 111.457, 110.790, 110.058**

**Fecha: 2do cuatrimestre 2025**

<div align="justify">
  
### **RESUMEN**
  En este trabajo se realiza el diseño e implementación del juego "Simon Dice" basado en la arquitectura ARM Cortex-M3. Este sistema tiene por objetivo proporcionar una plataforma de entretenimiento y entrenamiento cognitivo, permitiendo al usuario ejercitar su memoria a corto plazo mediante la reproducción de secuencias aleatorias de luces. El sistema cuenta con características avanzadas como regulación automática de brillo ambiental mediante sensores LDR, almacenamiento no volátil de puntajes máximos en memoria EEPROM y una interfaz de usuario rica visualizada en un display LCD de 20x4 caracteres.

  La implementación del mismo se realizó bajo el paradigma Bare Metal (sin sistema operativo), utilizando lenguaje C y manipulando directamente los registros del microcontrolador STM32 Nucleo-F103RB. El diseño de software se estructura estrictamente mediante Máquinas de Estados Finitos (FSM) jerárquicas y modularizadas, garantizando un código robusto, escalable y mantenible.

  En esta memoria se presenta la motivación del proyecto, el diseño del hardware y firmware, y los resultados de los ensayos funcionales.
  
# Índice 
1. [Introducción general](#introducción-general)
     - [1.1 Análisis de objetivos](#11-análisis-de-objetivos)
     - [1.2 Análisis de mercado](#12-análisis-de-mercado)
2. [Introducción específica](#introducción-específica)
    - [2.1 Requisitos del proyecto](#21-requisitos-del-proyecto)
    - [2.2 Elementos obligatorios de hardware](#22-elementos-obligatorios-de-hardware)
        - [2.2.1 Buttons](#221-buttons)
        - [2.2.2 Leds Diodos Emisores de Luz)](#222-leds-diodos-emisores-de-luz)
        - [2.2.3 LDR Sensor Analógico](#223-ldr-sensor-analógico)
        - [2.2.4 Display LCD](#224-display-lcd)
        - [2.2.5 Memoria E2PROM Externa](#225-memoria-e2prom-externa)
3. [Diseño de implementación](#diseño-e-implementación)
    - [3.1 Documentar esquema eléctrico y conexión de placas](#31-documentar-esquema-eléctrico-y-conexión-de-placas)
    - [3.2 Descripción del Esquema Eléctrico](#32-descripción-del-esquema-eléctrico)
    - [3.3 Descripción del comportamiento](#33-descripción-del-comportamiento)
    - [3.4 Firmware del Simon Says](#34-firmware-del-simon-says)
        - [3.4.1 Task Actuator](#341-task-actuator)
        - [3.4.2 Task Sensor](#342-task-sensor)
        - [3.4.3 Task ADC](#343-task-adc)
        - [3.4.4 Task PWM](#344-task-pwm)
        - [3.4.5 Task Gameplay](#345-task-gameplay)
        - [3.4.6 Task Storage](#346-task-storage)
        - [3.4.7 Task I2C](#347-task-i2c)
        - [3.4.8 Task Display](#348-task-display)
        - [3.4.9 Task Menu](#349-task-menu)
4. [Ensayos y resultados](#ensayos-y-resultados)
    - [4.1 Medición y análisis de consumo](#41-medición-y-análisis-de-consumo)
    - [4.2 Medición y análisis de tiempos de ejecución (WCET)](#42-medición-y-análisis-de-tiempos-de-ejecución-de-cada-tarea-wcet)
    - [4.3 Cálculo del Factor de Uso (U) de la CPU](#43-cálculo-del-factor-de-uso-u-de-la-cpu)
5. [Conclusiones](#conclusiones)
6. [Bibliografía](#bibliografia)


# **Introducción general** 
## 1.1 Análisis de objetivos

El objetivo del proyecto es repensar el juego “Simon dice”. Al ser un juego que desafía la memoria visual, la concentración y los reflejos, mejorando la capacidad de atención y la resolución de problemas creemos que puede ser llevado al ámbito de la rehabilitación cognitiva, la prevención del deterioro cognitivo y en desarrollo infantil para estimular la neuroplasticidad ya que, al requerir un enfoque visual constante mejora la atención sostenida, la capacidad de retener información a corto plazo y la memoria episódica y semántica.
## 1.2 ANÁLISIS DE MERCADO
En el mercado existen diversos productos relacionados con juegos de memoria y reflejos, desde el clásico “Simon” de Hasbro, hasta juguetes electrónicos genéricos y aplicaciones móviles que imitan el mismo concepto. 

El juguete clásico no guarda el historial de las diversas partidas y, al tener una dificultad fija que se acelera demasiado rápido para un paciente en rehabilitación o un niño con dificultades de aprendizaje vimos una oportunidad de mejora y de inclusión. 

Se tomó como referente Lumosity, CogniFit y Peak, aplicaciones de ejercicios mentales en tablet/celular para analizar las diversas opciones que el mercado ofrece. Estás tienen la desventaja de la barrera tecnológica, a los adultos mayores les cuesta usar pantallas táctiles, por lo que, un botón físico grande e iluminado es más intuitivo. Además, al ser utilizadas en pantallas táctiles no trabajan la motricidad fina ni la propiocepción de la misma forma que presionar un botón mecánico real. 

El presente proyecto recupera ese aspecto físico y educativo, brindando un entorno ideal para el desarrollo de estimulación neurocognitiva que, a diferencia de los juguetes comerciales, que carecen de registros de progreso, este desarrollo propone una solución de bajo costo brindando esta posibilidad, sumado a la personalización de modos de juego, visibilidad y diversos parámetros como tiempo de encendido de luz a través de este prototipo basado en STM32. 

# Introducción específica
## 2.1 Requisitos del proyecto
## 2.2 Elementos obligatorios de hardware:

<h3>2.2.1 Buttons (Pulsadores)</h3>

<table>
  <tr>
    <td width="60%" valign="top">
      <p>Se utilizó el pulsador <strong>Touch Switch de 7.5mm</strong> como dispositivo de entrada principal.</p>
      <p><strong>Funcionalidad:</strong></p>
      <ul>
        <li>Navegación por el menú.</li>
        <li>Selección de dificultad.</li>
        <li>Ingreso de secuencia de colores (Gameplay).</li>
      </ul>
      <p><strong>Implementación Técnica:</strong><br>
      Se utilizaron mecanismos de <em>debounce por software</em> para filtrar el ruido mecánico y garantizar una lectura limpia de la señal.</p>
    </td>
    <td width="40%" align="center">
      <img src="https://github.com/user-attachments/assets/6a23cbbe-e4e6-4d44-b88c-07d74bc2121b" width="250">
      <br><br>
      <sub><em>Imagen 1: Pulsador de base grande utilizado.</em></sub>
    </td>
  </tr>
</table>

<h3>2.2.2 Leds (Diodos Emisores de Luz)</h3>
<table>
  <tr>
    <td width="60%" valign="top">
      <p>Como actuadores visuales principales, se emplearon cuatro LEDs de alto brillo en colores rojo, verde, azul y amarillo. Presentan la secuencia que el usuario debe memorizar y replicar.</p>
      <p>Cada LED está controlado por un canal PWM, permitiendo no solo el encendido y apagado (ON/OFF), sino también la regulación de la intensidad lumínica según las condiciones ambientales.</p>
    </td>
    <td width="40%" align="center">
      <img src="https://github.com/user-attachments/assets/a923bc55-ecc7-4221-8a0b-ecd35c741caf" width="200">
      <br><br>
      <sub><em>Imagen 2: Diodos LEDs utilizados.</em></sub>
    </td>
  </tr>
</table>

### 2.2.3 LDR (Sensor Analógico)
<table>
  <tr>
    <td width="60%" valign="top">
      <p>Para dotar al sistema de capacidad adaptativa, se integró un sensor analógico LDR (Light Dependent Resistor o Fotorresistencia). Este sensor mide la intensidad de la luz ambiental en tiempo real al prender el juego.</p>
    </td>
    <td width="40%" align="center">
      <img src="https://github.com/user-attachments/assets/0886f18a-fa2f-44a9-8f7c-94493d16a883" width="176">
      <br><br>
      <sub><em>Imagen 3: Sensor LDR utilizado.</em></sub>
    </td>
  </tr>
</table>

<h3>2.2.4 Display LCD</h3>
<table>
  <tr>
    <td width="60%" valign="top">
      <p>Para la visualización de datos alfanuméricos, se utilizó un módulo LCD (Liquid Crystal Display). Constituye la interfaz principal de comunicación con el usuario (HMI), mostrando el menú de bienvenida, instrucciones, puntaje actual, entre otras pantallas.</p>
    </td>
    <td width="40%" align="center">
      <img src="https://github.com/user-attachments/assets/925e7613-ac74-4276-904e-c581b1f05a5e" width="200">
      <br><br>
      <sub><em>Imagen 4: Display LCD utilizado.</em></sub>
    </td>
  </tr>
</table>
### 2.2.5 Memoria E2PROM Externa 
Se incorporó un módulo de memoria no volátil externa tipo EEPROM (familia AT24Cxxx) conectada a través del bus I2C. Se utiliza para almacenar la tabla de los tres mejores puntajes históricos, ya que conserva la información cuando el dispositivo se desconecta de la alimentación. Esto es vital para el enfoque de rehabilitación cognitiva del proyecto, ya que permite llevar un registro del progreso y desempeño del usuario a lo largo de las sesiones.
  <div align="center">
  <img width="200" height="200" alt="image" src="https://github.com/user-attachments/assets/65b4cff7-fc20-4808-9c69-925c4ad1f505" />
  <p><em>Imagen 5: Memoria externa utilizada.</em></p>
</div>

falta: 
  <div align="center">
  <img width="280" height="200" alt="image" src="https://github.com/user-attachments/assets/a657bf6e-783d-4a81-aee4-6a8a7ba27641" />
  <p><em>Imagen 6: Placa NUCLEO-F103RBTX utilizada.</em></p>
</div>

# 3. Diseño de implementación 
## 3.1 Documentar esquema eléctrico y conexión de placas
Para la integración física del sistema se soldó a una placa experimental de (15 x 20) cm. Para garantizar la robustez mecánica y eléctrica del prototipo. 
El circuito se centra en la placa de desarrollo STM32, la cual gestiona los periféricos mediante las siguientes interfaces:

Interfaz de Entrada (GPIO):

Interfaz de Salida (PWM): Los 4 LEDs de alto brillo se conectan a través de resistencias limitadoras de corriente para proteger los puertos del microcontrolador. Se utilizan canales de Timer para permitir la modulación de brillo (PWM).

Bus de Comunicación (I2C):

Sensores Analógicos (ADC):
  <div align="center">
  <img width="200" height="200" alt="image" src="https://github.com/user-attachments/assets/65b4cff7-fc20-4808-9c69-925c4ad1f505" />
  <p><em>Imagen 7: IOC.</em></p>
</div>

# CAMBIAR IMAGENES!!!!!!!

## 3.2 Descripción del Esquema Eléctrico 
El sistema se alimenta por USB de la Nucleo 


  <div align="center">
  <img width="500" height="500" alt="image" src="https://github.com/user-attachments/assets/a2a4f49f-4e85-42ec-a75d-7384a59d4de3" />
  <p><em>Imagen 8: esquema eléctrico.</em></p>
</div>

## 3.3 Descripción del comportamiento
aca iria el itemis o en su defecto un diagrama:


  <div align="center">
  <img width="915" height="500" alt="image" src="https://github.com/user-attachments/assets/0f13ce68-b4d7-48bd-afe8-7cd573a6255f" />
  <p><em>Imagen 9: Diagrama de estados.</em></p>
</div>


## 3.4 Firmware del Simon Says:
### 3.4.1 Task Actuator

Módulo encargado de administrar estados básicos de los leds mediante una MEF. Esto permite desacoplar la lógica del juego del manejo directo de los pines. 

### 3.4.2 Task Sensor

Este módulo es responsable de la gestión de la interfaz de entrada física mediante una MEF. Su función principal es realizar el filtrado digital de las señales (software debouncing) para eliminar los rebotes mecánicos inherentes a los botones.

### 3.4.3 Task adc

Esta tarea administra el Conversor Analógico-Digital (ADC) del STM32F103RB. Se encarga de disparar la conversión del canal conectado al sensor LDR (resistencia dependiente de la luz) y realizar un promedio de las lecturas para filtrar ruido eléctrico. El valor digital resultante representa la intensidad de luz ambiental y es puesto a disposición del sistema para el ajuste de brillo.

### 3.4.4 Task pwm

Responsable de la gestión de los Timers (TIM2 y TIM3) configurados en modo Pulse Width Modulation. Este módulo toma el valor procesado por la task adc y ajusta dinámicamente el Duty Cycle (ciclo de trabajo) de las señales que alimentan los LEDs. Su objetivo es mantener una visibilidad óptima de la secuencia de juego, aumentando la intensidad en ambientes iluminados y atenuándola en la oscuridad para confort visual.

### 3.4.5 Task gameplay
Es el núcleo lógico del proyecto. Implementa una  MEF que gestiona las reglas de "Simon Dice". Sus responsabilidades incluyen:
- Generación de la secuencia pseudoaleatoria incremental.
- Control de los tiempos de espera entre turnos.
- Validación de la entrada del usuario contra la secuencia guardada.
- Gestión de los niveles de dificultad ("Normal" y "Difícil").
- Determinación de las condiciones de victoria o derrota (Game Over).

### 3.4.6 Task Storage

Este módulo implementa la lógica de persistencia de datos. Se encarga de verificar si el puntaje obtenido al finalizar una partida califica como un "Récord Histórico". Si es así, gestiona la estructura de datos (Puntaje + Iniciales) y solicita su escritura en la memoria no volátil. Al inicio del sistema, recupera y ordena estos datos para su visualización.

### 3.4.7 Task i2c

Módulo de bajo nivel que implementa el protocolo de comunicación I2C. Provee primitivas (Start, Stop, Write Byte, Read Ack) a la task storage. Su función crítica es manejar los tiempos de escritura (tWR) de la memoria EEPROM y asegurar la integridad de la transmisión de datos sin bloquear el resto del sistema.

### 3.4.8 Task display

Actúa como MEF intermedia entre display.c (librería de bajo nivel de abstracción) y task menu (manejo de display de alto nivel). Gestiona un buffer de pantalla para optimizar la escritura, verificando que se imprima 1 caracter por cada milisegundo.

### 3.4.9 Task menu

Módulo encargado de la navegación del sistema cuando no se está en una partida activa. Gestiona las pantallas de bienvenida, la selección de dificultad y la visualización de los puntajes históricos. Interpreta las pulsaciones de los botones (provenientes de task sensor) como comandos de navegación ("Izquierda", "Derecha", "Enter" y "Back") en lugar de colores de juego.

# falta: resumen, tabla de requisitos, escribir sleep, escribir mejor calculo cpu y conclusion (por esto, no pasé el apartado 4. prefiero que se escriba bien en el doc y dps pasarlo aca), hacer que funcione el índice xd, agregar bibliografía. Estaría bueno describir las tareas con las cosas que pidieron en las prácticas (bloqueante, no bloqueante, etc)

# 4. Ensayos y resultados
## 4.1 Medición y análisis de consumo

## 4.2 Medición y análisis de tiempos de ejecución (WCET)

## 4.3 Cálculo del Factor de Uso (U) de la CPU

# 5.Bibliografía
https://www.alldatasheet.com/datasheet-pdf/view/75272/MICRO-ELECTRONICS/MBB51D.html 

https://www.alldatasheet.com/datasheet-pdf/view/574755/ATMEL/AT24C256.html 

https://www.nubbeo.com.ar/productos/modulo-memoria-at24c256-i2c-256kbits-32kbytes-arduino-nubbeo/

https://embeddedprojects101.com/how-to-interface-an-i2c-eeprom-with-stm32/#:~:text=I2C%20de%20Microchip.-,Configuraci%C3%B3n%20de%20pines%20y%20direcciones%20de%20la%20EEPROM,En%20nuestro%20caso%2C%20son%201010.

https://deepbluembedded.com/stm32-eeprom-flash-emulation-fee-read-write-examples/#:~:text=STM32%20microcontrollers%20don't%20have,to%20implement%20in%20this%20tutorial. 

https://wiki.st.com/stm32mcu/wiki/Getting_started_with_I2C 

https://campusgrado.fi.uba.ar/course/view.php?id=1217&section=21#tabs-tree-starthttps://campusgrado.fi.uba.ar/course/view.php?id=1217&section=22#tabs-tree-start


















