/\/\/\/\/\/\/\/\/\/\/\/\
( DireWolf Games - Lab21 )
 \/\/\/\/\/\/\/\/\/\/\/\/


Los enemigos toman decisiones a través de un árbol de comportamiento. Lo utilizan en cada iteración para realizar sus acciones.

El árbol implementado para los enemigos utiliza su percepción para ver al jugador. Si oye o ve al jugador, guarda en su memoria la posición de éste. Si está a rango de ataque del jugador, le ataca. En caso contrario, comprueba su memoria para ver hacia dónde moverse, o vuelve a su patrulla si no tiene memoria. Finalmente realiza pathfinding para crear una ruta hacia su objetivo y se mueve.