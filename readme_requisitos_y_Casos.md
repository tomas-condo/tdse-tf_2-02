

 <img src="https://github.com/user-attachments/assets/15600b18-f73b-4ba3-a959-47f0048a1ab6" alt="image2" width="50%">


# **Juego Interactivo "Simón dice"**

 

**Autores: Tomás Ignacio Condo, Camila Trinidad Morasso y Francisco Javier Briones**

**Padrones: 111.457, 110.790, 110.058**

**Fecha: 2do cuatrimestre 2025**

 

 

 ### **1. Selección del proyecto a implementar**

#### **1.1 Objetivo del proyecto y resultados esperados**

El objetivo de este proyecto es diseñar e implementar un juego interactivo del tipo *“Simón dice”* . El sistema generará secuencias luminosas crecientes de manera pseudoaleatoria, empleando cuatro LEDs de distintos colores asociados a cuatro pulsadores que el usuario deberá utilizar para reproducir la secuencia mostrada, tal que cada secuencia sea mayor que la anterior.

Como objetivos adicionales, el sistema incluirá:

- Un **mecanismo de ajuste automático de brillo** mediante un sensor analógico de luz (LDR), que permitirá adaptar la intensidad de los LEDs según el nivel de iluminación del ambiente.
- Un **menú completo controlado exclusivamente con los mismos cuatro botones del juego**, con diferentes pantallas:  
  1. Pantalla de bienvenida al encender el sistema.  
  2. Pantalla de selección de dificultad (modo *Normal* y modo *Difícil*).  
  3. Pantalla de juego, donde se muestra el puntaje durante la partida.  
  4. Pantalla de despedida al apagar el juego.
- Un **modo de dificultad especial “Difícil”**, en el que al agregar un nuevo color a la secuencia solo se reproduce ese **nuevo** color, y no la secuencia completa (a diferencia del modo Normal, donde siempre se reproduce toda la secuencia acumulada).
- Una **memoria EEPROM externa**, destinada a almacenar datos persistentes como puntajes máximos, configuraciones de dificultad y, eventualmente, secuencias u otras estadísticas del juego.

Se pretende que el sistema sea robusto frente a rebotes mecánicos de los pulsadores, errores de temporización y entradas inválidas del usuario, utilizando una arquitectura modular basada en máquinas de estados. Al finalizar el proyecto se espera obtener un prototipo funcional, configurable, expandible y con capacidad de almacenamiento persistente para mejorar la experiencia de juego y permitir extensiones futuras.  



#### **1.2 Proyectos similares**

Se consideran tres tipos de proyectos posibles que cumplen con los objetivos y resultados esperados del trabajo, todos basados en juegos electrónicos de memoria con secuencias luminosas:

1. **Juego “Simón dice” Avanzado con STM32**, con cuatro LEDs, cuatro pulsadores, selección en menú interactivo, registro de puntaje y adaptabilidad al ambiente.
2. **Juego “Simón dice” Básico con STM32**, sólo con leds y teclas, sin interfaz interativa y de un tamaño reducido.  
3. **Juego “Simón dice” Básico con Arduino UNO**, similar a la versión básica.

Para comparar estas alternativas, se tienen en cuenta seis aspectos característicos:

1. **Disponibilidad del hardware:** Se evalúa si el proyecto es fácilmente implementable con hardware disponible en mercados regionales.  
2. **Calidad de la experiencia de juego:** Se refiere a qué tan interesante, inmersivo y variado resulta el juego para el usuario final (feedback visual, menús, niveles de dificultad, etc.).  
3. **Escalabilidad del sistema:** Se entiende como la facilidad para extender el proyecto en el futuro, incorporando nuevos modos de juego, más niveles de dificultad, almacenamiento de estadísticas adicionales, comunicación con PC, etc.  
4. **Tiempo de implementación:** Tiempo total que llevará diseñar, programar, integrar y depurar el proyecto seleccionado dentro del cuatrimestre.  
5. **Costo:** El costo total del proyecto, incluyendo la placa de desarrollo, la pantalla LCD, el buzzer, el sensor LDR, la EEPROM, los pulsadores, LEDs, resistencias y cableado.  
6. **Interés personal:** El grado de motivación e interés en trabajar con la plataforma STM32, aprender a utilizar sus periféricos (GPIO, ADC, timers, I2C/SPI, etc.) y desarrollar un juego que resulte atractivo de usar y de mejorar.  

Se decide ponderar los aspectos de la siguiente manera, del 1 al 10:

- Disponibilidad del hardware: 10  
- Calidad de la experiencia de juego: 8  
- Escalabilidad del sistema: 6  
- Tiempo de implementación: 8  
- Costo: 5  
- Interés personal: 8  

La disponibilidad del hardware es crítica, ya que se busca trabajar con componentes accesibles y fáciles de conseguir sin depender de importaciones costosas o de plazos largos; por ello se asigna un peso 10. La calidad de la experiencia de juego se valora con peso 8, dado que el objetivo principal es obtener un juego entretenido y rejugable, con buena realimentación visual y sonora. La escalabilidad del sistema recibe un peso 6: es deseable que el proyecto sea ampliable, pero se prioriza primero obtener un prototipo estable y completo. El tiempo de implementación se pondera con 8, ya que se dispone de un período acotado y se requieren iteraciones de prueba y corrección de errores.

El costo tiene un peso 5, porque, si bien no es irrelevante, se prioriza el aprendizaje y la calidad del proyecto por sobre una minimización extrema del presupuesto. Por último, el interés personal se valora con 8, ya que se busca realizar un proyecto motivador, que permita practicar programación embebida sobre STM32 y que resulte atractivo para seguir ampliándolo más allá de la materia.  

La siguiente tabla (Tabla 1.2.1) muestra los valores ponderados asignados a cada proyecto considerado.  


<table>
    <thead>
        <tr>
            <th rowspan="2">Proyecto</th>
            <th colspan="2">Simón avanzado STM32<br>(LCD, LDR, EEPROM)</th>
            <th colspan="2">Simón básico STM32<br>(solo LEDs y pulsadores)</th>
            <th colspan="2">Simón básico Arduino UNO</th>
        </tr>
        <tr>
            <th>Puntaje</th>
            <th>Puntaje Ponderado</th>
            <th>Puntaje</th>
            <th>Puntaje Ponderado</th>
            <th>Puntaje</th>
            <th>Puntaje Ponderado</th>
        </tr>
    </thead>
    <tbody>
        <tr class="header-row">
            <td align ="center">Disponibilidad de Hardware <br>(peso : 10)</td>
            <td>8</td>
            <td>80</td>
            <td>9</td>
            <td>90</td>
            <td>10</td>
            <td>100</td>
        </tr>
        <tr>
            <td align ="center">Calidad de la experiencia de juego <br>(peso : 8)</td>
            <td>10</td>
            <td>80</td>
            <td>7</td>
            <td>56</td>
            <td>5</td>
            <td>40</td>
        </tr>
        <tr class="header-row">
            <td align ="center">Escalabilidad del sistema <br>(peso : 6)</td>
            <td>10</td>
            <td>60</td>
            <td>7</td>
            <td>42</td>
            <td>5</td>
            <td>30</td>
        </tr>
        <tr>
            <td align ="center">Tiempo de Implementación <br>(peso : 8)</td>
            <td>6</td>
            <td>48</td>
            <td>8</td>
            <td>64</td>
            <td>9</td>
            <td>72</td>
        </tr>
        <tr class="header-row">
            <td align ="center">Costo (peso : 5)</td>
            <td>6</td>
            <td>30</td>
            <td>8</td>
            <td>40</td>
            <td>9</td>
            <td>45</td>
        </tr>
        <tr>
            <td align ="center">Interés personal <br>(peso : 8)</td>
            <td>10</td>
            <td>80</td>
            <td>8</td>
            <td>64</td>
            <td>6</td>
            <td>48</td>
        </tr>
        <tr class="highlight-green">
            <td>Puntaje Total</td>
            <td>-</td>
            <td>378</td>
            <td>-</td>
            <td class="highlight-red">356</td>
            <td>-</td>
            <td>335</td>
        </tr>
    </tbody>
</table>
<p align="center"><em>Tabla 1.2.1: Comparación de proyectos</em></p>



#### **1.3 Selección de proyecto**

Considerando la Tabla 1.2.1, se elige implementar el juego “Simón dice” avanzado con STM32, utilizando LEDs, pulsadores, pantalla LCD, buzzer, sensor LDR y memoria EEPROM externa. Si bien el juego básico con Arduino UNO presenta una excelente disponibilidad de hardware y un costo reducido, no permite aprovechar en profundidad los periféricos del STM32 ni desarrollar una arquitectura modular más compleja. Además, limita la posibilidad de escalar el proyecto hacia nuevas funcionalidades, como distintos modos de juego, almacenamiento de récords o futuras comunicaciones con otros dispositivos.

Por otro lado, el juego “Simón dice” básico con STM32 constituye una opción intermedia: mantiene la plataforma STM32 pero con una interfaz simple, sin menú, sin ajuste automático de brillo y sin persistencia de datos. Sus tiempos de implementación son menores, pero la experiencia de juego es más limitada y se desaprovecha la oportunidad de trabajar con periféricos adicionales.

El juego avanzado con STM32 se destaca porque combina:

- Una **experiencia de usuario más rica** (secuencias luminosas, sonidos asociados a cada color, melodías de acierto y error).  
- Un **menú de múltiples pantallas** (bienvenida, selección de dificultad, puntaje en juego y despedida), controlado únicamente con los mismos cuatros botones del juego.  
- La **adaptación automática del brillo** mediante el sensor LDR.  
- La **persistencia de datos** mediante EEPROM externa.  

Esto lo convierte en un proyecto ideal para integrar conocimientos de programación embebida, diseño de máquinas de estados, gestión de tiempos, uso de ADC y buses de comunicación, y modularidad del código.

En el contexto local, existen numerosos juegos comerciales del tipo “Genius” o “Simón” disponibles como juguetes o aplicaciones de celular. Sin embargo, suelen ser dispositivos cerrados que no permiten modificar las reglas del juego ni acceder a su implementación interna. Este proyecto apunta a desarrollar una plataforma abierta y programable, pensada tanto para entretenimiento como para aprendizaje en el ámbito de la ingeniería electrónica, donde el alumno pueda experimentar con nuevas reglas, efectos sonoros, modos de dificultad y sistemas de almacenamiento de récords.

Los desafíos principales del proyecto se centran en la correcta generación de secuencias pseudoaleatorias, la sincronización precisa de tiempos para la reproducción de la secuencia y la lectura de las respuestas del usuario, el diseño de un esquema robusto de antirrebote, la implementación de un menú navegable solo con los botones de juego y la organización del firmware en módulos y máquinas de estado claras, que faciliten la depuración y la futura expansión del juego.  



###### **1.3.1 Diagrama en bloques**

En la Figura 1.3.1 se muestra el diagrama en bloques del sistema con los principales módulos del proyecto.  

<p align="center">
  <img src="ruta/a/diagrama_en_bloques_simondice_actualizado.png" alt="Diagrama en bloques del sistema SimonDice STM32">
</p>

<p align="center"><em>Figura 1.3.1: Diagrama en bloques del sistema</em></p>



---
 deshabilita temporalmente la opción de reinicio hasta que se reinicie el dispositivo o se recupere la condición. |

<p align="center"><em>Tabla 2.4: Caso de uso 3: El usuario consulta o reinicia el puntaje máximo</em></p>
