 /\/\/\/\/\/\/\/\/\/\/\/\
( DireWolf Games - Lab21 )
 \/\/\/\/\/\/\/\/\/\/\/\/

1. TAG.Gestor de recursos: Parser de objetos en multiples formatos, salida en modo texto.

	En Main.cpp se llama a tagEngine.createNode(), una función temporal (para mostrar el funcionamiento del gestor) de la clase TAGEngine que crea 2 ResourceMesh con el mismo recurso. Se puede observar como en la consola indica cuando carga un nuevo recurso y cuando usa ya uno creado previamente.



2. TAG.Visualización: visualizador OpenGL 4.X de las entidades tipo malla. Shader básico. Integración con el motor. Sin materiales, texturas, cámara ni luces.

	Los dos cubos son dibujados por el método draw de la clase ResourceMesh, método que por ahora recibe los parámetros de posición y rotación.
	

3. TAG. Árbol de la escena: Tipos de datos para entidades tipo transformación. Salida en modo texto.

	Se utiliza una pila propia de matrices para el cálculo de la ModelView a partir de las matrices del árbol.

	
4. TAG. Árbol de la escena: Tipos de datos para entidades tipo malla. Salida en modo texto.
	
	Se crea la entidad de malla para los nodos del árbol; por el momento no se ha unificado junto a las mallas del visualizador.

------------
Rubén Moreno
Marina López