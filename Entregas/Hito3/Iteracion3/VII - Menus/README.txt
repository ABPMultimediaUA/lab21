 /\/\/\/\/\/\/\/\/\/\/\/\
( DireWolf Games - Lab21 )
 \/\/\/\/\/\/\/\/\/\/\/\/

La estructura e implementación de los Menus se ha rehecho completamente para que sea usada por nuestro propio motor gráfico.
Este apartado se entrega a parte dado que aun no se ha integrado el motor en el juego, pero una vez se integre, junto a este
se integrarán los menús y el HUD, que se entrega también en un ejecutable a parte.

La navegación entre los diferentes estados y menús del juego se realiza mediante teclas, ya que falta la implemetación correcta
de un receptor de eventos de SFML (teclas y ratón) en fachada por lo que hay llamadas a SFML donde futuramente se llamará al recepor. 
En poco tiempo la navegación se hará con el ratón y mediante clicks.

Una vez se ejecuta el entregable, en el terminal aparece información perteneciente al estado en el que nos encontremos y como avanzar
entre los menús y/o estados del juego.

La información es la siguiente:
/**************************************************/
Menu Principal
Pulsa 1 para iniciar partida 1 jugador
Pulsa 2 para iniciar partida online
Pulsa L para acceder a Logros
Pulsa O  para acceder a Opciones
Pulsa Escape para salir del juego
/**************************************************/
Menu Jugar Online
Aqui aparecera una lista de salas a las que unirte
Podras crear tu propia sala
Pulsa B para volver al Menu principal
/**************************************************/
Logros
Aqui aparecera una lista de logros conseguidos en el juego
Podras ver informacion de cada logro
Pulsa B para volver al Menu principal
/**************************************************/
Menu Opciones
Aqui se modificaran las opciones de juego
Pulsa B para volver al Menu principal