
<img width="1071" height="358" alt="387361653-15600b18-f73b-4ba3-a959-47f0048a1ab6" src="https://github.com/user-attachments/assets/783185ee-f430-4c1f-96fa-2ac4ad3de8b4" />

# **Juego Interactivo "Simón dice"  INFORME FINAL** 

**Autores: Tomás Ignacio Condo, Camila Trinidad Morasso y Francisco Javier Briones**

**Padrones: 111.457, 110.790, 110.058**

**Fecha: 2do cuatrimestre 2025**

### **RESUMEN**

  En este trabajo se realizó un juego del estilo "Simón dice" donde se iluminan luces led para que luego el jugador continue la secuencia mostrada, utilizando pulsadores correspondientes a cada una de las luces. 
Este, cuenta con un display LCD y un Light Dependent Resistor (Resistencia Dependiente de la Luz), un componente que cambia su valor de resistencia según la luz que recibe para cambiar el brillo de los leds. 
Al encenderlo cuenta con una pantalla de bienvenida para luego, dar paso a las instrucciones del manejo del "menú". Incorporado para agregar dinamismo, donde se pueden elegir las opciones "Jugar", para seleccionar la dificultad del mismo, y "Puntajes", donde se mostrarán las puntaciones alcanzadas más altas. 
En el menu de "Jugar" se pueden elegir entre 2 opciones, Normal y Difícil, donde el modo difícil es igual al normal con la diferencia de que la secuencia no es mostrada por completo para cada nuevo nivel y solo se muestra la luz correspondiente al nuevo color añadido a la secuencia. Mientras se juega la partida, se visualiza en el display el puntaje actual del jugador. Al perder se muestra el puntaje final junto a la pantalla "Game Over" indicando la finalización de la partida, al presionar "Escape", este será devuelto al menu inicial. Se utiliza una memoria EEPROM externa que almacena los tres puntajes máximos. 

  La implementación del mismo se realizó utilizando los lenguajes de código C++ y Python mediante el uso del entorno de desarrollo de Mbed en una placa Núcleo-F103RBTX proporcionada por la cátedra de Sistemas Embebidos de la Facultad de Ingeniería de la Universidad de Buenos Aires, y se utilizaron además diferentes módulos para el desarrollo del proyecto.


# Índice General

- [**Introducción general**](#introducción-general)
  - [1.1 Análisi objetivos](#11-análisis-de-objetivos)
  - [1.2 Equipo](#12-Equipo)
- [**Introducción específica**](#introducción-específica)
  - [2.1 Requisitos](#21-requisitos)
  - [2.2 Casos de uso](#22-casos-de-uso)
  - [2.3 Descripción de los Módulos del sistema](#23-descripción-de-los-módulos-del-sistema)
    - [2.3.1 Memoria](#231-memoria)
    - [2.3.2 Microcontrolador](#232-microcontrolador)
    - [2.3.3 LDR](#234-LDR)
    - [2.3.4 Pantalla Led](#235-Pantalla-Led)
    - [2.3.5 Pulsadores](#236-Pulsadores)
- [**Diseño e Implementación**](#diseño-e-implementación)
  - [3.1 Diseño del Hardware](#31-diseño-del-hardware)
    - [3.1.1 Diseño de los indicadores e interruptores](#312-diseño-de-los-indicadores-e-interruptores)
  - [3.2 Firmware del Juego](#32-firmware-del-juego)
    - [3.2.1 Módulo display](#321-módulo-display)
    - [3.2.2 Módulo LDR](#322-módulo-ldr)
    - [3.2.3 Módulo Menu](#323-módulo-Menu)
    - [3.2.4 Módulo Gameplay](#327-módulo-gamplay)
    - [3.2.5 Módulo Sensores](#327-módulo-sensores)
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
## **1.1 Análisis de objetivos**

?  El objetivo del proyecto es crear un juego del estilo "Simon dice" para su uso en competencias, capaz de garantizar calidad, precisión y consistencia en el proceso, bajo estándares de competencias profesionales y amateur del juego de memoria.

  En el mercado existen diversos productos relacionados con juegos de memoria y reflejos, desde el clásico “Simon” de Hasbro hasta juguetes electrónicos genéricos y aplicaciones móviles que imitan el mismo concepto. Estos dispositivos suelen ofrecer distintas combinaciones de luces y sonidos, pero en general son sistemas cerrados, con lógica de juego fija y sin posibilidad de modificación por parte del usuario.

  Como primer competidor puede mencionarse el juego electrónico comercial tipo “Simon”, que ofrece una secuencia de luces y sonidos que el jugador debe repetir. Si bien la experiencia es entretenida, el usuario no tiene acceso al hardware ni al software interno, por lo que no puede cambiar reglas, niveles de dificultad ni integrar el juego con otros sistemas. Nuestro proyecto se diferencia en que está completamente implementado sobre una plataforma de desarrollo STM32, permitiendo modificar el firmware y experimentar con nuevas funciones.

  Un segundo competidor lo constituyen las aplicaciones de juego de memoria para teléfonos celulares, ampliamente disponibles en tiendas digitales. Estas aplicaciones pueden ofrecer gráficos y sonidos avanzados, pero pierden el componente tangible de interactuar con botones físicos y LEDs reales, y no permiten practicar el diseño de sistemas embebidos. El presente proyecto recupera ese aspecto físico y educativo, brindando un entorno ideal para ejercitar programación en C++ sobre STM32 y diseño de interfaces hombre-máquina simples pero efectivas.

  En resumen, el mercado de juegos electrónicos de memoria es amplio y competitivo, pero la posibilidad de personalización y experimentación técnica que ofrece un prototipo basado en STM32 permite desarrollar un producto único, orientado tanto al entretenimiento como a la formación académica, destacándose además por el ajuste dinámico de brillo (LDR), el menú manejado solo con botones y la presencia de memoria EEPROM externa.


## **1.2. Equipo y estructura**

  Las conexiones de los componentes se pueden visualizar en el siguiente esquema:
  
<img width="724" height="726" alt="image" src="https://github.com/user-attachments/assets/a1e3b36f-eb38-4426-bb8a-c1dbc95ac64c" />
Imagen 1: Esquema de conexiones.

  Cada pulsador cuenta con una resistencia pull-up de 10 kΩ y cada diodo LED cuenta con una resistencia de polarización de 100 Ω. También se observa la conexión del LDR y, además, se indicó a través de etiquetas los diversos pines correspondientes a la placa Núcleo-F103RBTX. 

MODIFICAR ITEMIS -> Por otro lado, el juego esta dividido en varios estados donde cada uno se ve reflejado en la pantalla durante su uso. Se pueden visualizar en el siguinte statechart:

<img width="1075" height="650" alt="image" src="https://github.com/user-attachments/assets/e5fc5258-00b3-48d0-beeb-8da4056bef89" />


# **Introducción específica** 

#### **2.1 Requisitos del proyecto**

En la Tabla 2.1 se detallan los principales requisitos funcionales del sistema.
| Grupo | ID | Descripción |
| :---- | :---- | :---- |
| Juego | 1.1 | El sistema generará una secuencia de LEDs pseudoaleatoria de longitud creciente. |
|  | 1.2 | El sistema permitirá al jugador repetir la secuencia mediante cuatro pulsadores asociados a los cuatro LEDs. |
|  | 1.3 | El sistema comparará la secuencia ingresada por el jugador con la secuencia objetivo y determinará si es correcta. |
|  | 1.4 | En caso de acierto, el sistema incrementará la longitud de la secuencia y avanzará al siguiente nivel. |
|  | 1.5 | En caso de error, el sistema finalizará la ronda y mostrará el resultado al jugador. |
|  | 1.6 | En modo Normal, al iniciar cada nivel se reproducirá la secuencia completa acumulada. |
|  | 1.7 | En modo Difícil, al iniciar cada nivel solo se reproducirá el **nuevo color agregado** a la secuencia. |
| Interfaz luminosa | 2.1 | Cada LED estará asociado a un color fijo y a un pulsador específico. |
|  | 2.2 | Durante la reproducción de la secuencia, el LED correspondiente se encenderá de forma claramente distinguible. |
|  | 2.3 | Al presionar un pulsador, el LED asociado se encenderá mientras dure la pulsación. |
|  | 2.4 | El sistema implementará antirrebote por software para los cuatro pulsadores. |
|  | 2.5 | El sistema deberá registrar pulsaciones rápidas sin perder eventos. |
|  | 2.6 | El brillo de los LEDs se ajustará automáticamente según el valor leído en el sensor LDR. |
| Sensor LDR | 3.1 | El sistema contará con un sensor de luz LDR conectado a una entrada analógica del STM32. |
|  | 3.2 | El sistema leerá periódicamente el valor de la LDR mediante el ADC. |
|  | 3.3 | El sistema ajustará el ciclo de trabajo PWM de los LEDs en función de la luminosidad ambiente. |
| Pantalla LCD | 4.1 | El sistema contará con una pantalla LCD para mostrar información de estado. |
|  | 4.2 | Al encender el sistema, el LCD mostrará una pantalla de bienvenida durante unos segundos. |
|  | 4.3 | Luego de la bienvenida, el LCD mostrará una pantalla de selección de dificultad (Normal / Difícil). |
|  | 4.4 | Durante el juego, el LCD mostrará el puntaje actual del jugador. |
|  | 4.5 | Al apagar o finalizar el juego, el LCD mostrará una pantalla de despedida. |
| Menú con botones | 5.1 | Todos los menús se manejarán exclusivamente con los cuatro botones del juego. |
|  | 5.2 | Al menos un botón permitirá avanzar entre opciones y otro confirmará la selección. |
|  | 5.3 | El sistema indicará en pantalla las opciones seleccionadas y confirmadas. |
| Audio | 6.1 | El sistema contará con un buzzer para producir señales sonoras. |
|  | 6.2 | Cada color del juego tendrá asignado un tono característico reproducido por el buzzer. |
|  | 6.3 | El sistema reproducirá una melodía corta al superar un nivel. |
|  | 6.4 | El sistema reproducirá una secuencia de error cuando el jugador falle la secuencia. |
|  | 6.5 | El sistema podrá emitir sonidos breves al navegar por el menú. |
| Modos de juego y dificultad | 7.1 | El sistema contará al menos con dos niveles de dificultad: Normal y Difícil. |
|  | 7.2 | La dificultad podrá afectar la velocidad de reproducción de la secuencia y/o el tiempo de respuesta permitido. |
|  | 7.3 | En Normal se reproducirá la secuencia completa en cada nivel; en Difícil, solo el nuevo color agregado. |
| Persistencia y estadísticas (EEPROM) | 8.1 | El sistema almacenará el puntaje máximo alcanzado en memoria EEPROM externa. |
|  | 8.2 | El sistema permitirá leer y mostrar el puntaje máximo guardado al inicio o desde un menú de estadísticas. |
|  | 8.3 | El sistema permitirá reiniciar el récord (borrar el puntaje máximo guardado) desde el menú. |
|  | 8.4 | La EEPROM podrá usarse para almacenar configuraciones de dificultad u otros parámetros del juego. |
| Seguridad y robustez | 9.1 | El sistema deberá iniciar siempre en un estado seguro, con LEDs y buzzer apagados hasta que el usuario interactúe. |
|  | 9.2 | El sistema organizará su lógica en una máquina de estados para evitar bloqueos y comportamientos impredecibles. |
|  | 9.3 | El sistema deberá indicar mediante mensajes en la pantalla y señales sonoras si ocurre un error interno o condición inesperada. |

<p align="center"><em>Tabla 2.1: Requisitos del proyecto</em></p>

## ** Casos de uso** 

 **Caso de uso 1: El usuario juega una partida en modo clásico**

| Elemento | Definición |
| :---- | :---- |
| Disparador | El jugador quiere iniciar una nueva partida en modo clásico (Normal o Difícil). |
| Precondiciones | El sistema está encendido. Se ha mostrado la pantalla de bienvenida. El jugador ha seleccionado una dificultad en la pantalla correspondiente utilizando los botones del juego. Todos los LEDs están apagados y el buzzer en silencio. |
| Flujo principal | El jugador navega el menú utilizando los botones y selecciona la opción “Nuevo juego”. El sistema genera una secuencia pseudoaleatoria inicial de un solo LED y la reproduce con luz y sonido (según el modo: secuencia completa o solo el nuevo color). El jugador repite la secuencia utilizando los cuatro pulsadores; por cada pulsación correcta se enciende el LED correspondiente y se reproduce su tono. Si el jugador ingresa correctamente toda la secuencia, el sistema incrementa la longitud en un elemento, actualiza el nivel y el puntaje y muestra el nuevo puntaje en la pantalla LCD. Este ciclo se repite hasta que el jugador comete un error o decide abandonar la partida. |
| Flujos alternativos | a) El jugador se equivoca en alguna pulsación: el sistema reproduce un sonido de error, muestra un mensaje de “Secuencia incorrecta” en el LCD y finaliza la partida mostrando el puntaje final.  b) El jugador excede el tiempo máximo para ingresar la secuencia: el sistema considera la jugada como incorrecta, reproduce un sonido de error y finaliza la partida.  c) El jugador presiona una combinación de botones para cancelar la partida: el sistema detiene el juego, guarda el puntaje si corresponde (por ejemplo, si es un nuevo récord) y vuelve al menú principal. |

<p align="center"><em>Tabla 2.2: Caso de uso 1: El usuario juega una partida</em></p>



 ** Caso de uso 2: El usuario cambia la dificultad del juego**

| Elemento | Definición |
| :---- | :---- |
| Disparador | El jugador quiere cambiar el nivel de dificultad del juego (Normal / Difícil). |
| Precondiciones | El sistema está encendido. No hay una partida en curso. El juego se encuentra en el menú principal o en el menú de configuración. |
| Flujo principal | El jugador accede a la pantalla de selección de dificultad utilizando los botones del juego. En el LCD se muestran las opciones “Normal” y “Difícil”. Mediante uno o más botones se avanza entre las opciones y se selecciona la deseada con otro botón (por ejemplo, “Confirmar”). El sistema almacena la nueva dificultad seleccionada (posiblemente en EEPROM), actualiza los parámetros internos (forma de reproducir la secuencia, tiempos, etc.) y vuelve al menú principal mostrando la dificultad activa. |
| Flujos alternativos | a) El jugador sale del menú de dificultad sin confirmar ningún cambio (por ejemplo, con una combinación de botones): el sistema mantiene la dificultad previamente establecida.  b) Se produce una lectura inválida de los botones (por rebote o secuencia inconsistente): el sistema descarta la entrada y solicita al usuario que vuelva a seleccionar, manteniendo el estado anterior. |

<p align="center"><em>Tabla 2.3: Caso de uso 2: El usuario cambia la dificultad del juego</em></p>



 ** Caso de uso 3: El usuario consulta o reinicia el puntaje máximo**

| Elemento | Definición |
| :---- | :---- |
| Disparador | El jugador quiere consultar o reiniciar el puntaje máximo almacenado en la memoria EEPROM. |
| Precondiciones | El sistema está encendido. No hay una partida en curso. El juego se encuentra en el menú principal. La EEPROM ha sido inicializada correctamente. |
| Flujo principal | El jugador navega hasta el menú de “Estadísticas” utilizando los mismos botones del juego. El sistema lee de la EEPROM el puntaje máximo almacenado y lo muestra en la pantalla LCD, junto con el último puntaje obtenido (si se desea). El jugador puede desplazarse con los botones hasta la opción “Reiniciar récord” y seleccionarla con el botón de confirmación. El sistema solicita confirmación adicional (por ejemplo, mostrando “¿Confirmar borrado? Sí/No”). Si el jugador confirma, el sistema borra o reinicia el valor de récord en la EEPROM (por ejemplo, a 0) y muestra un mensaje indicando que el récord fue reiniciado correctamente. |
| Flujos alternativos | a) El jugador decide no reiniciar el récord al momento de la confirmación (por ejemplo, seleccionando “No” con los botones): el sistema conserva el puntaje máximo y vuelve al menú anterior.  b) Se produce un error en el acceso a la EEPROM (por ejemplo, fallo de comunicación): el sistema muestra un mensaje de error en el LCD, reproduce un sonido de falla, descarta la operación de borrado y deshabilita temporalmente la opción de reinicio hasta que se reinicie el dispositivo o se recupere la condición. |

<p align="center"><em>Tabla 2.4: Caso de uso 3: El usuario consulta o reinicia el puntaje máximo</em></p>


## **2.3 Descripción de los Módulos del sistema**
## **2.3.1 Memoria**

El sistema utiliza una memoria At24c256 que se muestra en la siguiente imagen:

<img width="500" height="500" alt="image" src="https://github.com/user-attachments/assets/65b4cff7-fc20-4808-9c69-925c4ad1f505" />

**Figura 2.3.1**: Memoria At24c256.

Tiene comunicación I2c y dispone de 256 Kb, organizados en 32.768.

## **2.3.2 Microcontrolador**
Como controlador principal del sistema se utiliza la placa NUCLEO-F103RBTX. La elección de esta placa recayó en la disponibilidad ya que fue la ofrecida por los profesores, teniendo además como requerimiento la cantidad de memoria, pines y periféricos de la placa. La placa se programó en C++ a través de la plataforma STMCUBE32IDE.

<img width="700" height="500" alt="image" src="https://github.com/user-attachments/assets/a657bf6e-783d-4a81-aee4-6a8a7ba27641" />

**Figura 2.3.2**: Placa NUCLEO-F103RBTX.

## **2.3.3 LDR**

Utilizamos el sensor LDR Gl5539 de la siguiente imagen: 

<img width="442" height="500" alt="image" src="https://github.com/user-attachments/assets/0886f18a-fa2f-44a9-8f7c-94493d16a883" />

**Figura 2.3.3**: LDR.

## **2.3.4 Pantalla Led**
Para el display usamos la pantalla Lcd 1602 Hd44780 con Backlight Azul de la siguiente imagen:

<img width="400" height="400" alt="image" src="https://github.com/user-attachments/assets/925e7613-ac74-4276-904e-c581b1f05a5e" />

**Figura 2.3.4**: Display Lcd 1602 Hd44780.

## **2.3.4 Pulsadores**
Finalmente utilizamos los siguientes pulsadores como dispositivos de entrada para que utilice el usuario: 

<img width="360" height="207" alt="image" src="https://github.com/user-attachments/assets/62e9b6a6-9033-4ab8-8a83-9f85e7107e29" />

**Figura 2.3.5**: Pulsadores.


# **CAPÍTULO 3** 

# **Diseño e implementación** 

## **3.1 Diseño del Hardware** 

Para el diseño y montaje de la placa se siguio el siguiente esquematico:

<img width="1126" height="1107" alt="image" src="https://github.com/user-attachments/assets/3990b17a-3344-4455-83da-e05cc1961415" />

**Figura 3.1.a**: Esquematico hadrware.

Y luego lo soldamos a una placa y lo juntamos con la placa nucelo
 
<img width="720" height="1280" alt="image" src="https://github.com/user-attachments/assets/2c723df3-fae7-4dc8-9fd2-f3bba5a00451" />

**Figura 3.1.b**: Placa completa

<img width="720" height="1280" alt="image" src="https://github.com/user-attachments/assets/f4339288-c7a9-48e7-bb29-b9b3b09779f2" />

**Figura 3.1.c**: Placa sin display y placa nucleo

<img width="720" height="1280" alt="image" src="https://github.com/user-attachments/assets/1468ce48-de36-4c78-9ecc-c05b97675642" />

**Figura 3.1.d**: Conexiones de soldadura


## **3.1.1 Diseño de los indicadores e interruptores** 

En la figura 3.1.1 se ve el esquematico de como se conectan los pulsadores, luces led y LDR a la placa nucleo.

![WhatsApp Image 2025-12-29 at 19 45 05](https://github.com/user-attachments/assets/aed0ac79-74b7-4d58-9a46-c2d75eb80a89)

**Figura 3.1.1**: Esquematico para pulsadores, LDR, y luces led del sistema.

Las luces led y los interruptes se configuraron de manera que cuando un boton es precionado esto libere la corriente y a su vez se mande una señal a los pines correspondiente a interruptor para notificar al sistema que efectivamente hubo una interaccion con el boton. Una vez que esta señal es recibida por el sistema se manda una al pin correspondiente para que la luz led del boton presionado se encienda.

## **3.2 Firmware del *juego*** 

Para la impementacion del firmaware del juego utilizamos el lenguaje C++. Con el y utilizando archivos usados para otros trabajos previos pudimos programarlo para su funcionamiento.

## **3.2.1 Módulo display** 
Este módulo se encarda de mostrarle al usuario la informacion del estado del juego u menu utilizando el display. Lo primero que hace este moódulo es generar las conexiones de la placa experimental con el display como se muestra en la siguiente figura: 
<img width="665" height="283" alt="image" src="https://github.com/user-attachments/assets/bca28950-2379-4853-8c99-fcfa59e57d7d" />

**Figura 3.2.1.a**: Conexiones de pines

Con esas conexiones se realiza un data bus para que la informacion pueda ser transmitida al display:

<img width="552" height="725" alt="image" src="https://github.com/user-attachments/assets/d4a41a73-12b8-4d5a-847a-f2ca6c641509" />

**Figura 3.2.1.b**: Data Bus

<img width="472" height="746" alt="image" src="https://github.com/user-attachments/assets/592fd532-e6b3-409d-acd4-32b77b594d04" />

**Figura 3.2.1.c**: Logica del display

Y luego finalmente dependiendo del estado utiliza el tipo de función **displayCodeWrite** para mostrar en el display la pantalla deseada. 

## **3.2.2 Módulo Memoria** 
Este modulo se encarga de a partir de los datos adquiridos guardarlo a la memoria EEPROM utilizada. La gestión de la memoria no volátil (EEPROM) se trata como una tarea de almacenamiento utilizando la función (task_storage). Esta tarea se encarga de garantizar la persistencia de datos, como puntajes o configuraciones, utilizando el bus I2C.

En el archivo app.c, la memoria se gestiona a través de task_cfg_list, que define el ciclo de vida de cada componente del software.

Se inicializa con task_storage_init el cual se ejecuta una sola vez al arrancar el sistema dentro de app_init() este verificar la presencia de la memoria y cargar los datos guardados. Periodicamente se actualizan los datos con task_storage_update, esta función es llamada en app_update(), en lugar de escribir constantemente, lo que dañaría la vida útil de la EEPROM, esta tarea suele revisar si hubo cambios en los datos del juego y solo realiza la escritura cuando haya algun cambio.

La tarea de almacenamiento depende directamente del periférico I2C1 configurado en el archivo principal main.c. Esto lo hace la función MX_I2C1_Init(), esta funcion tambien configura los pines físicos. Tiene una velocidad de 100,000 Hz el cual es el modo estándar de comunicación I2C. Tambien aparece como tick de Control g_task_storage_tick_cnt, el contador que sincroniza la frecuencia de ejecución de la tarea. La interacción con la EEPROM sigue un flujo estrictamente controlado por el sistema de ticks. Como cada milisegundo, la función HAL_SYSTICK_Callback() incrementa el contador g_task_storage_tick_cnt, el bucle principal en app_update() detecta que el tiempo ha transcurrido y cede el control a task_storage_update() pero para evitar que la escritura en la EEPROM detenga el juego, la lógica de app.c mide el tiempo de ejecución de cada tarea con el WCET para asegurar que el sistema no se sature.

Dentro de task_storage.c vemos que se realizan 2 cosas importantes, la lectura de los datos de puntaje más altos recuperar los tres mejores puntajes de la EEPROM al iniciar o cuando se solicita. Y tambien realiza la escritura de ellos guardar de forma permanente los nuevos puntajes cuando el juego termina, evitando la pérdida de datos al apagar el equipo.

No hace estas cosas todo a la vez cuando se le solicitan, sino que llama a la función task_storage_statechart() donde para escribir sigue los siguientes pasos, con EV_STORAGE_SAVE_SCORES, pasa al estado WRITE_SCORE_1 el cual envía el comando de escritura para el primer puntaje y carga el valor de tick con 5 ms, luego pasa a WAIT_1 aqui el sistema sale de la función y permite que otras tareas sigan funcionando; solo cuando el tick llega a cero, avanza al siguiente estado. Este proceso se repite para los puntajes 2 y 3 hasta regresar al estado IDLE. El ciclo de lectura funciona de manera similar, pero con tiempos de espera menores de 1 ms. Al finalizar la lectura de los tres puntajes, la tarea ejecuta una acción de comunicación entre procesos envia put_event_task_menu(EV_MEN_SCORES_UPDATED) para avisar a la tarea del manu que los puntajes ya están listos para ser mostrados en pantalla.

Esta logica es importante ya que lo hace mas eficiente ya que el procesador no gasta ciclos esperando al bus I2C y al respetar los tiempos de STORAGE_WRITE_DELAY_MS, se asegura que la EEPROM termine de grabar físicamente los electrones en la celda de memoria antes de recibir el siguiente dato.


## **3.2.3 Módulo Menu** 
Este modulo se usa para atravesar los distintos menus del juego, es el mas complejo ya que se encarga de pasar de menu a menu, y tomar los inputs del usurio para que este pueda hacer lo que desee, sea ver el puntaje o jugar con el modo de juego que desee. Para todos los menus se sigue la misma logica, toma los datos que introduce el usuario a base de los pulsadores, siendo asignados cada color como una opcion, ENTER, NEXT, y ESC donde enter se usa para introducir la opción deseada, next para cambiar de selección, y esc para volcer al menu anterior. De esa manera moviendo un indice que cambia entre las opciones del menu en el que actualmente esta el usaurio. Esto qeuda en los eventos EV_MEN_DER, EV_MEN_IZQ, EV_MEN_ENTER y EV_MEN_ESC. 

Se utiliza task_display_set_line(n, "texto") para actualizar dinámicamente las líneas del display LCD. El contenido de la pantalla cambia según el estado actual por ejemplo, mostrando "SIMON SAYS" en reposo o el puntaje en tiempo real durante el juego.

Un evento del sistema presente en este modulo es EV_MEN_UPDATE_SCORE que actualiza los puntajes cuando hay uno nuevo que supera algun record, una vez finalizado pasa a EV_MEN_SCORES_UPDATED que indica que la tarea de almacenamiento ha terminado de leer los puntajes de la EEPROM y ya se pueden mostrar en el ranking.

## **3.2.4 Módulo Gameplay**
En este modulo podemos ver el gameplay en su de los distintos modos de juego como tambien como luego de terminar de jugar se pasa a memoria el puntaje que pueda considerarse lo suficientemente bueno como para ser mostrado en el ranking.El juego dependiendo de que modo de juego es el que selecciono el usuario, sea este normal o dificl, muestra la secuencia añadiendo un color más por nivel para el modo de juego normal, o solo muestra el nuevo color para el dificil. Y luego se muestra en el display un mensaje, "Tu Turno" para que el jugador sepa que ahora puede volver a introducir la secuencia.

Para comenzar task_gameplay_dta es la estructura central que almacena el estado actual de la máquina de estados, el evento activo, la secuencia de colores, que llega hasta 100, la puntuación actual y el nivel de dificultad. Toma como variables los puntajes mas altos como high_score1, 2, 3 que son almacenadas para ser mostradas cuando el usuario lo deseo o al finalizar una partida. brillo_juego almacena el valor capturado del sensor LDR al inicio del juego para ajustar opcionalmente la respuesta visual.

Al iniciar el modulo realiza una lectura del entorno con el ADC1 para calibrar el sensor LDR según la luz ambiente. Luego recupera los puntajes máximos almacenados en la EEPROM mediante eeprom_read_score. Si la memoria es nueva y tiene el valor 0xFFFF, los inicializa en cero.

El flujo del juego se gestiona mediante la función task_gameplay_statechart, que opera de forma no bloqueante utilizando los siguientes estados principales, ST_GAME_IDLE cuando el sistema esta en reposo. ST_GAME_INIT_ROUND genera un nuevo color aleatorio y lo añade a la secuencia. ST_GAME_PLAY_SEQ_ON/OFF controla el encendido y apagado de los LEDs con ticks que varían según la dificultad 400ms para el modo dificil y 800 para el normal. ST_GAME_WAIT_INPUT donde el sistema queda a la espera de que el usuario presione los botones, ST_GAME_VERIFY que verifica que los inputs del usuario son correctos si falla este es mandado al ultimo estado ST_GAME_GAME_OVER que compara el puntaje actual con los historicos y si hay un nuevo récord, actualiza la lista y envía el evento EV_STORAGE_SAVE_SCORES para que la tarea de almacenamiento guarde los datos en la EEPROM en segundo plano; finalmente notifica para que sean mostrados los puntajes finales.


## **3.2.5 Módulo Sensores**
Este modulo se encarga de que sea minimizar el rebote y registrar los inputs del usuario. Decimos que cuando el sietema esta en estado idle el boton esta arriba, y luego de qeu es presionado pasara por los eventos, falling, down, y rising en ese orden.

<img width="407" height="176" alt="image" src="https://github.com/user-attachments/assets/fead9fdf-bcdc-4300-b34f-80211c47cb12" />

**Figura 3.2.5.a**: Estados boton arriba 

<img width="460" height="320" alt="image" src="https://github.com/user-attachments/assets/a4ba246d-ec56-4267-bb7a-9f1eb0547952" />

**Figura 3.2.5.a**: Estados boton cayendo 

<img width="407" height="182" alt="image" src="https://github.com/user-attachments/assets/0c65e9a8-3eb5-4dd9-a46e-3ec3a0b89b96" />

**Figura 3.2.5.a**: Estados boton abajo

<img width="427" height="323" alt="image" src="https://github.com/user-attachments/assets/2ac4ba15-2d72-4e8d-a01e-a0024113e3c2" />

**Figura 3.2.5.b**: Estados boton subiendo

Para todos los botones p_task_sensor_dta es utilizado para almacenar datos como el estado actual del botón en la máquina de estados, el evento detectado por el hardware y finalmente p_task_sensor_dta->tick funciona como un temporizador para el proceso de antirebote, asegurando que el botón se mantenga en un estado estable antes de confirmar una pulsación.

El ultimo sensor usado es el LDR, el cual funciona mediante la conversión de una señal analógica de luz en un valor digital que el microcontrolador puede procesar. El sensor LDR entrega una variación de voltaje proporcional a la intensidad de luz ambiental. Para capturar esto, el archivo main.c configura el periférico ADC1, se utiliza el ADC_CHANNEL_1.

Está configurado en modo simple con ADC_SCAN_DISABLE y ContinuousConvMode = DISABLE, el sistema solicita una lectura específica cada vez que la necesita, en lugar de leer constantemente. La conversión se inicia por software mediante la instrucción ADC_SOFTWARE_START y esta configurado en 1.5 ciclos usando ADC_SAMPLETIME_1CYCLE_5, lo que permite una captura rápida de la señal.

En task_adc.c a diferencia de una lectura simple que detiene el procesador, aquí se utiliza una técnica de interrupciones y temporización, utilizando ADC_REFRESH_RATE_MS el sensor no se lee en cada ciclo del programa. Se definio un tiempo de refresco de 200 ms, esto optimiza el uso del CPU. Antes de iniciar una lectura, el sistema verifica si el ADC está ocupado utilizando el booleando adc_is_converting. Tambien se utiliza la función HAL_ADC_Start_IT(&hadc1) que permite que el microcontrolador siga ejecutando otras tareas mientras el hardware del ADC realiza la conversión por su cuenta.

Una vez que el hardware termina la conversión, se ejecuta automáticamente la función de callback con HAL_ADC_ConvCpltCallback, esta función recupera el valor digital (de 0 a 4095) mediante HAL_ADC_GetValue. Finalmente adc_value almacena el valor numerico de la intensidad de luz y adc_end_of_conversion se pone en true para avisar a otras tareas que hay un dato nuevo listo.

# **CAPÍTULO 4** 

# **Ensayos y resultados** 

## **4.1 Pruebas funcionales de funcionamiento**  

Las pruebas funcionales del hardware se realizaron por módulos. Todas se pueden ver en el video demostrativo.

Para verificar el funcionamiento del modulo display se verifico que este enciende correctamente y muestre los menus iniciales. En conjunto se verifico la funcionalidad del modulo de menu que pase de pantalla en panatlla como debecon el input de los botones. Justamente los sensores son probados con ambos modelos anteriores para navegar el menu con los botones y para ajustar el brillo con el sensor LDR acorde al entorno. El modelo de game play se verifica entrando al mismo menu de juego y seleccionando ambas dificultades y probandolas, al finalizar se prueba el funcionamiento de la memoria para poder grabar y mostrar algun nuevo "high score". 

Para las pruebas de software se debuggearon los archivos tal que cada funcion realice su trabajo como es esperado, siguiendo los estados y procesos en el orden en el que deben estar.

## **4.2 Cumplimiento de requisitos**  

Una vez finalizado el trabajo, se realizó una tabla con los requisitos iniciales, agregando el estado de los mismos. Esto se observa en la tabla 4.2.
| Grupo | ID | Descripción | Estado |
| :---- | :---- | :---- | :---- |
| Juego | 1.1 | El sistema generará una secuencia de LEDs pseudoaleatoria de longitud creciente. | Completo |
|  | 1.2 | El sistema permitirá al jugador repetir la secuencia mediante cuatro pulsadores asociados a los cuatro LEDs. | Completo |
|  | 1.3 | El sistema comparará la secuencia ingresada por el jugador con la secuencia objetivo y determinará si es correcta. | Completo |
|  | 1.4 | En caso de acierto, el sistema incrementará la longitud de la secuencia y avanzará al siguiente nivel. | Completo |
|  | 1.5 | En caso de error, el sistema finalizará la ronda y mostrará el resultado al jugador. | Completo |
|  | 1.6 | En modo Normal, al iniciar cada nivel se reproducirá la secuencia completa acumulada. | Completo |
|  | 1.7 | En modo Difícil, al iniciar cada nivel solo se reproducirá el **nuevo color agregado** a la secuencia. | Completo |
| Interfaz luminosa | 2.1 | Cada LED estará asociado a un color fijo y a un pulsador específico. | Completo |
|  | 2.2 | Durante la reproducción de la secuencia, el LED correspondiente se encenderá de forma claramente distinguible. | Completo |
|  | 2.3 | Al presionar un pulsador, el LED asociado se encenderá mientras dure la pulsación. | Completo |
|  | 2.4 | El sistema implementará antirrebote por software para los cuatro pulsadores. | Completo |
|  | 2.5 | El sistema deberá registrar pulsaciones rápidas sin perder eventos. | Completo |
|  | 2.6 | El brillo de los LEDs se ajustará automáticamente según el valor leído en el sensor LDR. | Completo |
| Sensor LDR | 3.1 | El sistema contará con un sensor de luz LDR conectado a una entrada analógica del STM32. | Completo |
|  | 3.2 | El sistema leerá periódicamente el valor de la LDR mediante el ADC. | Completo |
|  | 3.3 | El sistema ajustará el ciclo de trabajo PWM de los LEDs en función de la luminosidad ambiente. | Completo |
| Pantalla LCD | 4.1 | El sistema contará con una pantalla LCD para mostrar información de estado. | Completo |
|  | 4.2 | Al encender el sistema, el LCD mostrará una pantalla de bienvenida durante unos segundos. | Completo |
|  | 4.3 | Luego de la bienvenida, el LCD mostrará una pantalla de selección de dificultad (Normal / Difícil). | Completo |
|  | 4.4 | Durante el juego, el LCD mostrará el puntaje actual del jugador. | Completo |
|  | 4.5 | Al apagar o finalizar el juego, el LCD mostrará una pantalla de despedida. | Completo |
| Menú con botones | 5.1 | Todos los menús se manejarán exclusivamente con los cuatro botones del juego. | Completo |
|  | 5.2 | Al menos un botón permitirá avanzar entre opciones y otro confirmará la selección. | Completo |
|  | 5.3 | El sistema indicará en pantalla las opciones seleccionadas y confirmadas. | Completo |
| Audio | 6.1 | El sistema contará con un buzzer para producir señales sonoras. | Cancelado |
|  | 6.2 | Cada color del juego tendrá asignado un tono característico reproducido por el buzzer. | Cancelado |
|  | 6.3 | El sistema reproducirá una melodía corta al superar un nivel. | Cancelado |
|  | 6.4 | El sistema reproducirá una secuencia de error cuando el jugador falle la secuencia. | Cancelado |
|  | 6.5 | El sistema podrá emitir sonidos breves al navegar por el menú. | Cancelado |
| Modos de juego y dificultad | 7.1 | El sistema contará al menos con dos niveles de dificultad: Normal y Difícil. | Completo |
|  | 7.2 | La dificultad podrá afectar la velocidad de reproducción de la secuencia y/o el tiempo de respuesta permitido. | Completo |
|  | 7.3 | En Normal se reproducirá la secuencia completa en cada nivel; en Difícil, solo el nuevo color agregado. | Completo |
| Persistencia y estadísticas (EEPROM) | 8.1 | El sistema almacenará el puntaje máximo alcanzado en memoria EEPROM externa. | Completo |
|  | 8.2 | El sistema permitirá leer y mostrar el puntaje máximo guardado al inicio o desde un menú de estadísticas. | Completo |
|  | 8.3 | El sistema permitirá reiniciar el récord (borrar el puntaje máximo guardado) desde el menú. | Completo |
|  | 8.4 | La EEPROM podrá usarse para almacenar configuraciones de dificultad u otros parámetros del juego. | Completo |
| Seguridad y robustez | 9.1 | El sistema deberá iniciar siempre en un estado seguro, con LEDs y buzzer apagados hasta que el usuario interactúe. | Completo |
|  | 9.2 | El sistema organizará su lógica en una máquina de estados para evitar bloqueos y comportamientos impredecibles. | Completo |
|  | 9.3 | El sistema deberá indicar mediante mensajes en la pantalla y señales sonoras si ocurre un error interno o condición inesperada. | Completo |

<p align="center"><em>Tabla 4.1: Cumplimiento de requisitos</em></p>

**Tabla 4.2**: Requisitos del proyecto y estados de cumplimiento.

Se observa que la gran mayoría de los requisitos se cumplieron para este proyecto. Solamente resta agregar el audio que no se realizo debido al tiempo limite del proyecto. Este siendo el requisito mas inconsequente de todos, por mas que sea una aydua al jugador una indicacion de audio esto no impide el juego al usuario y puede ser usado de todas maneras.

## **4.3 Documentación del desarrollo realizado**

<table><thead>
  <tr>
    <th>Elemento</th>
    <th>Referencia</th>
  </tr></thead>
<tbody>
  <tr>
    <td>Presentación del proyecto</td>
    <td>Capı́tulo 1</td>
  </tr>
  <tr>
    <td>Listado de requisitos</td>
    <td>Tabla 2.1</td>
  </tr>
  <tr>
    <td>Casos de uso del proyecto</td>
    <td>Tablas 2.2 a 2.3</td>
  </tr>
  <tr>
    <td>Diagrama en bloques del sistema</td>
    <td>Figura 3.1</td>
  </tr>
  <tr>
    <td>Diseño de hardware y conexiones</td>
    <td>Tabla 3.1</td>
  </tr>
  <tr>
    <td>Implementación del hardware</td>
    <td>Sección 3.1</td>
  </tr>
  <tr>
    <td>Módulos de software</td>
    <td>Sección 3.2</td>
  </tr>
  <tr>
    <td>Cumplimiento de requisitos</td>
    <td>Tabla 4.1</td>
  </tr>
  <tr>
    <td>Conclusiones finales</td>
    <td>Capı́tulo 5</td>
  </tr>
</tbody>
</table>

**Tabla 4.3**: Desarrollo del proyecto.

# **CAPÍTULO 5** 

# **Conclusiones** 

## **5.1 Resultados obtenidos**

Se obtuve el juego deseado, nos comprometio el tiempo como para poder finalizar el modulo de audio. Pero a pesar de este percanse de no poder agregar ese modulo pudimos generar el juego y circuito que deseabamos. Se logro el funcionamiento de todos los modulos y sensores de manera que todos funcionan interconectados perfectamente. Cada modulo depende de otro y trabajan casi en simultaneo sin pisarse utilizando el contador interno donde se ordenan para que todo pueda funcionar como debe.

## **5.2 Próximos pasos** 

Para continuar este proyecto podemos rediseñar la interfaz del usuario para que con mayor presupuesto podamos agregar una caracasa exterior y botones más grandes que sean más satisfactorios para presionar y asi brindar una mejor experiencia al usuario. Tambien consideramos agregar el sonido que no pudimos incluir por restricciones de tiempo.

# **Bibliografía** 

