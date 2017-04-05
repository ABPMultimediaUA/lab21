 /\/\/\/\/\/\/\/\/\/\/\/\
( DireWolf Games - Lab21 )
 \/\/\/\/\/\/\/\/\/\/\/\/

VII.26 Implementaci�n del HUD


Este entregable contiene:

- Carpeta "Capturas" con capturas de pantalla del HUD en el juego, "HUDGame.png" y "HUDGameZoom.png"
- Carpeta "source" con los archivos mediante los que se implementa el HUD. Los archivos "AnimatedSprite.hpp", "AnimatedSprite.cpp", "Animation.hpp" y "Animation.cpp" no son propios: <<Copyright (C) 2014 Maximilian Wagenbach (aka. Foaly) (foaly.f@web.de)>> y se permite su uso.
 Podemos encontrar en el juego estos archivos mediante las rutas "src/classes" y "src/graphics".

Elementos del HUD:

- A la izquierda una zona para mostrar el arma en uso as� como la cantidad de munici�n de la misma, y las granadas disponibles. 
- Al cambiar de arma ocurre una animaci�n y cambian el dibujo y la munici�n, correspondientes a la nueva arma.
- A la derecha una barra de vida que asciende y desciende seg�n la vida actual. Tambi�n la cantidad de botiquines disponibles 

(Nota 1: para cambiar de arma, se han de coger dos esferas en el juego que representan las otras dos armas que tendr� el jugador, y se encuentran nada m�s ejecutar el juego, a la izquierda del personaje un poco m�s arriba)
(Nota 2: para perder vida, chocar con los enemigos, para ganarla, consumir un botiqu�n (tecla 4, s�lo si se tiene alg�n botiqu�n se) que se puede encontrar caminando hacia la izquierda)