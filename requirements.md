Seleccionar un MCU de ST o NXP que presente un consumo en sleep mode inferior a 3 µA. Desarrollar un firmware que utilice un acelerómetro de ST configurado para operar con el menor consumo posible, permitiendo la activación del MCU mediante interrupción de movimiento (wake-up interrupt).
 
Al producirse la interrupción, el MCU deberá:
 
Despertar.
 
Hacer parpadear un LED durante 5 segundos.
 
Volver automáticamente al modo de bajo consumo, a la espera de una nueva interrupción.
 
Requisitos adicionales:
 
Documentar todo el proceso, incluyendo la justificación de las decisiones de diseño en el código, con referencias a las hojas de datos de los componentes utilizados.
 
Proponer una lista de pruebas para validar el correcto funcionamiento del sistema.
 
(Bonus) Entregar el cálculo teórico del consumo energético total del sistema.