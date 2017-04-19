 /\/\/\/\/\/\/\/\/\/\/\/\
( DireWolf Games - Lab21 )
 \/\/\/\/\/\/\/\/\/\/\/\/

VI.35 Sistema de predicción de movimiento multijugador en tiempo real

Se adjunta en Source parte de la clase encargada de la sincronización de los jugadores.

Se envía la velocidad del jugador. En la máquina remota mantendrá esta velocidad hasta que se realice un cambio de la misma. Cada 200ms se manda también la posición para ajustar posibles descuadres.