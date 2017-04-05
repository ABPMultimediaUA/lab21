 /\/\/\/\/\/\/\/\/\/\/\/\
( DireWolf Games - Lab21 )
 \/\/\/\/\/\/\/\/\/\/\/\/

VII.26 Implementación del HUD


Este entregable contiene:

- Carpeta "Capturas" con capturas de pantalla del HUD en el juego, "HUDGame.png" y "HUDGameZoom.png"
- Carpeta "source" con los archivos mediante los que se implementa el HUD. Los archivos "AnimatedSprite.hpp", "AnimatedSprite.cpp", "Animation.hpp" y "Animation.cpp" no son propios: <<Copyright (C) 2014 Maximilian Wagenbach (aka. Foaly) (foaly.f@web.de)>> y se permite su uso.
 Podemos encontrar en el juego estos archivos mediante las rutas "src/classes" y "src/graphics".

Elementos del HUD:

- A la izquierda una zona para mostrar el arma en uso así como la cantidad de munición de la misma, y las granadas disponibles. 
- Al cambiar de arma ocurre una animación y cambian el dibujo y la munición, correspondientes a la nueva arma.
- A la derecha una barra de vida que asciende y desciende según la vida actual. También la cantidad de botiquines disponibles 

(Nota 1: para cambiar de arma, se han de coger dos esferas en el juego que representan las otras dos armas que tendrá el jugador, y se encuentran nada más ejecutar el juego, a la izquierda del personaje un poco más arriba)
(Nota 2: para perder vida, chocar con los enemigos, para ganarla, consumir un botiquín (tecla 4, sólo si se tiene algún botiquín se) que se puede encontrar caminando hacia la izquierda)