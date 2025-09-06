# Control de Velocidad de Motor AC con Control de Ángulo de Fase

## Descripción

Este proyecto implementa un control de velocidad en tiempo real para un motor de corriente alterna (AC) utilizando una placa ESP32 y un circuito de potencia basado en un TRIAC. La velocidad del motor se regula ajustando el ángulo de disparo del TRIAC, el cual se recibe a través de comandos enviados por el puerto serie. Para sincronizar con precisión el pulso de disparo con la onda de AC, se utiliza un circuito de detección de cruce por cero.

## Características

*   **Ajuste de Velocidad en Tiempo Real:** Modifica la velocidad del motor enviando comandos a través del monitor serie.
*   **Control de Ángulo de Fase:** Técnica digital para regular la potencia entregada al motor.
*   **Detección de Cruce por Cero:** Sincronización precisa con la señal de AC para un control estable.

## Hardware Requerido

*   **Placa de Desarrollo ESP32**
*   **Circuito de control de potencia con TRIAC**
*   **Circuito de detección de cruce por cero** (conectado al pin `GPIO 17`)
*   **Control de la compuerta (gate) del TRIAC** (conectado al pin `GPIO 16`)

## Software

*   **Plataforma:** Arduino IDE
*   **Lenguaje:** C++ (para Arduino)

## Cómo Utilizarlo

1.  **Montaje del Hardware:** Conecta el circuito de potencia del TRIAC y el detector de cruce por cero a la placa ESP32 como se especifica en la sección de pines.
2.  **Cargar el Firmware:** Sube el código `ac_motor_control.ino` a tu placa ESP32 usando el Arduino IDE.
3.  **Abrir el Monitor Serie:** Inicia la comunicación serie con una velocidad de `115200` baudios.
4.  **Enviar Comandos:** Para controlar la velocidad del motor, envía un valor numérico entre `0` y `180` (que representa el ángulo de disparo en grados) seguido de un salto de línea.
5.  **Observar el Resultado:** El motor ajustará su velocidad dinámicamente según el ángulo de disparo que hayas enviado.

## Detalles del Código

El programa principal monitorea constantemente la señal del detector de cruce por cero. Cuando se detecta un cruce, calcula un retardo basado en el `firingAngle` (ángulo de disparo) y, transcurrido ese tiempo, envía un pulso corto a la compuerta del TRIAC para activarlo. Los comandos para actualizar el ángulo se reciben de forma asíncrona a través del puerto serie.

## Configuración de Pines

| Función                  | Pin (GPIO) |
| ------------------------ | :--------: |
| Compurta del TRIAC       |     16     |
| Entrada de Cruce por Cero |     17     |

## Licencia

Este proyecto está licenciado bajo la Licencia MIT. Consulta el archivo `LICENSE` para más detalles.

## Autores

*   Rafael Ignacio Gonzalez Chong
*   Jaime Joel Olivas Muñoz
