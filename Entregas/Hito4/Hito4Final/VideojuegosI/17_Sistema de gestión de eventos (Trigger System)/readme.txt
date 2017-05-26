/\/\/\/\/\/\/\/\/\/\/\/\
( DireWolf Games - Lab21 )
 \/\/\/\/\/\/\/\/\/\/\/\/

 El sistema de triggers gestiona los triggers, que se encargan de generar eventos en el juego. Los actualiza en cada iteración y se encarga de borrar los que ya no sean necesarios.

 La región de activación de los triggers está implementada con box2D para gestionar las colisiones.

 Las puertas y los generadores se activan cuando el jugador pulsa la tecla acción (E por defecto) dentro de la región de sus triggers.

 Los consumables (botiquines, cajas de munición y adrenalina) se recogen al tocar el trigger.

 Al disparar se genera un trigger de sonido que pueden oír los enemigos que estén dentro de su radio.

 Los enemigos tienen un trigger que representa su rango de visión. Cuando el jugador entra dentro de ese rango, es visto por el enemigo.

 Cuando los enemigos atacan generan un trigger de daño que al colisionar con el jugador le quitan puntos de vida (en función del ataque del enemigo).