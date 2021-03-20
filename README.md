# pw_auto
PowherWheels modificado que se estaciona automáticamente.  

El cerebro del vehículo es una TIVA C EK-TM4C1294XL  
https://www.ti.com/tool/EK-TM4C1294XL  

> Tiva C Series  
> Connected LaunchPad  
> Booster Pack 2  
> TM4C1294  
> EK - TM4C1294XL  
> ARM Cortex M4F-Based  

## Ambientes de desarrollo
Se puede programar con las herramientas que proporciona Texas Instruments o con Energia IDE  
CCS IDE https://www.ti.com/tool/CCSTUDIO  
TivaWare https://www.ti.com/tool/SW-TM4C  
¿Editor online? https://dev.ti.com/  

Energia IDE se puede descargar sin registrarse y es como Arduino  
https://energia.nu/  
Tarjetas soportadas  
https://energia.nu/pinmaps/  

### Usando Energia
Descargar y abrir el IDE Energia. Instalar el paquete para programar Tiva C
en el menú Herramientas / Placas / Gestor de tarjetas, buscar TM, instalar.  

Conectar la tarjeta a la computadora usando el conector debug.
(parece que el otro conector es USB OTG)  

Guide to the TM4C129 Connected LaunchPad (EK-TM4C1294XL)  
https://energia.nu/pinmaps/ek-tm4c1294xl/  

Language reference (se parece a Arduino)  
https://energia.nu/reference/  

### Usando Code Composer Studio (CCS)
Iniciar el instalador y seleccionar el tipo de procesador de la tarjeta para instalar definiciones y compiladores.  

---

### Algoritmo
El vehículo se puede controlar de forma manual o funcionar en modo automático.
Cuando está en modo automático usa 4 sensores ultrasónicos. Dos sensores están instalados en el costado izquierdo del vehículo,
un sensor está instalado en la parte frontal y otro en la parte trasera.

Estado 0  
El vehículo avanza en línea recta. Hasta que los dos sensores laterales encuentran espacio suficiente para estacionarse.  
¿Necesita condiciones especiales para evitar errores?  
Los sensores pueden detectar suficiente espacio desde el inicio.  
Los sensores pueden detectar obstáculos desde el inicio (condición ideal).  
Un sensor detecta obstáculo y el otro ve un espacio libre. ¿Debe avanzar hacia adelante siempre?  
Al avanzar desde la condición ideal detectando obstáculos con los dos sensores laterales, ¿debe detectarse espacio con el sensor frontal primero?  
Lo más fácil es avanzar hasta que los dos sensores laterales detectan espacio.  

Estado 1  
Cuando los sensores laterales detectaron espacio. El vehículo sigue avanzando hasta que el sensor lateral frontal detecta obstáculo.  
Es importante notar que en los estados no se usan temporizadores,
solo se leen valores de los sensores para actuar. De esa forma la velocidad de desplazamiento se puede ajustar sin modificiar otras partes del programa.  

Estado 2  
La dirección gira a la izquierda y el vehículo comienza a avanzar en reversa.
El vehículo se introduce en el espacio disponible hasta que el sensor trasero detecta obstáculo.  
La distancia de detección de obstáculo debe ser un poco mayor a la distancia de estados anteriores.  

Estado 3  
La dirección gira a la derecha y el vehículo sigue avanzando en reversa.  
Con este movimiento el vehículo se va alineando al rectángulo disponible para estacionarse.  
Se detiene cuando detecta de nuevo un obstáculo con el sensor trasero.  

Estado 4  
Reposo. El vehículo ya está estacionado. En teoría debería quedar alineado y los sensores laterales deberían detectar un obstáculo cercano.  
Tal vez se puede mover un poco para que los sensores frontal y trasero detecten la misma distancia a sus respectivos obstáculos.  

Prevención de colisiones.  
Cada estado usa las lecturas de sensores específicos para determinar si debe cambiar al siguiente estado,
sin embargo, se usan los 4 sensores todo el tiempo. Si se detecta un objeto cercano en un momento inesperado, el vehículo se detiene.  


----
¿Ejemplo BLE?  
https://www.ti.com/tool/TIDM-TM4C129XBLE  
