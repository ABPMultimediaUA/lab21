 /\/\/\/\/\/\/\/\/\/\/\/\
( DireWolf Games - Lab21 )
 \/\/\/\/\/\/\/\/\/\/\/\/

VI.35 Sistema de predicci�n de movimiento multijugador en tiempo real

Se adjunta en Source parte de la clase encargada de la sincronizaci�n de los jugadores.

Se env�a la velocidad del jugador. En la m�quina remota mantendr� esta velocidad hasta que se realice un cambio de la misma. Cada 200ms se manda tambi�n la posici�n para ajustar posibles descuadres.