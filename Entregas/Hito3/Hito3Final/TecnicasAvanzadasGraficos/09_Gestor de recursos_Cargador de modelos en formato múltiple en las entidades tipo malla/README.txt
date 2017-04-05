 /\/\/\/\/\/\/\/\/\/\/\/\
( DireWolf Games - Lab21 )
 \/\/\/\/\/\/\/\/\/\/\/\/

Se definen las clases necesarias para el gestor de recursos. Este gestor se encarga de que cuando se le solicita un recurso, comprueba si ya está cargado. Si lo está devuelve el puntero al recurso ya cargado en memoria y sino lo carga.

Resource		-> Clase base para los recursos.
ResourceMesh	-> Clase derivada de Resource que carga y contiene las mallas.
ResourceManager	-> Clase que se encarga de manejar las clases de recursos.

Se adjuntan las declaraciones y definiciones de las clases en el directorio source.

En el juego (directorio Hito3Final/Lab21Game) se puede ver la ejecución de estas clases y en source el proyecto en CodeBlocks.