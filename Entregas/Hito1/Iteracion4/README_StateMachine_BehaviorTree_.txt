En el proyecto Game tenemos incorporados un �rbol de comportamiento y una m�quina de estados.

�RBOL DE COMPORTAMIENTO:

El �rbol hace que el npc humanoide (visualmente, el hada) compruebe si la puerta que tiene delante est� abierta.
Si est� cerrada, caminar� hacia ella el l�nea recta, la abrir�, y cuando est� abierta pasar� a trav�s de ella y acto seguido la cerrar� a su espalda. Esto es lo que vemos al ejecutarlo.
En el caso de que la puerta estuviera ya abierta, ocurrir� lo mismo que en el caso anterior, salvo que no se para a abrir la puerta, sino que camina hasta atravesarla.

M�QUINA DE ESTADOS:

La m�quina de estados pone para cada tipo de NPC diferentes "estados". S�lo estar� activo uno en cada momento, para cada NPC. Cambiar�n de un estado a otro al recibir ciertos est�mulos, al pasar el tiempo, etc.
En el Game actualmente no se puede comprobar visualmente su total funcionamiento. La parte que se puede ver es que el enemigo similar a un perro, que tiene una textura color amarillo claro, aparece con una textura azulada, puesto que el estado en el que se encuentra es DORMIDO.  Para el alpha del hito1 se jugar� de esta forma con el color de textura para mostrar c�mo cambia de estado (puesto que ahora s�lo se ve uno, no cambia de estado).