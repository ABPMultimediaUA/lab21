En el proyecto Game tenemos incorporados un árbol de comportamiento y una máquina de estados.

ÁRBOL DE COMPORTAMIENTO:

El árbol hace que el npc humanoide (visualmente, el hada) compruebe si la puerta que tiene delante está abierta.
Si está cerrada, caminará hacia ella el línea recta, la abrirá, y cuando esté abierta pasará a través de ella y acto seguido la cerrará a su espalda. Esto es lo que vemos al ejecutarlo.
En el caso de que la puerta estuviera ya abierta, ocurrirá lo mismo que en el caso anterior, salvo que no se para a abrir la puerta, sino que camina hasta atravesarla.

MÁQUINA DE ESTADOS:

La máquina de estados pone para cada tipo de NPC diferentes "estados". Sólo estará activo uno en cada momento, para cada NPC. Cambiarán de un estado a otro al recibir ciertos estímulos, al pasar el tiempo, etc.
En el Game actualmente no se puede comprobar visualmente su total funcionamiento. La parte que se puede ver es que el enemigo similar a un perro, que tiene una textura color amarillo claro, aparece con una textura azulada, puesto que el estado en el que se encuentra es DORMIDO.  Para el alpha del hito1 se jugará de esta forma con el color de textura para mostrar cómo cambia de estado (puesto que ahora sólo se ve uno, no cambia de estado).