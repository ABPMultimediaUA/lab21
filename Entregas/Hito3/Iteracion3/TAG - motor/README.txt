 /\/\/\/\/\/\/\/\/\/\/\/\
( DireWolf Games - Lab21 )
 \/\/\/\/\/\/\/\/\/\/\/\/

1. Fachada: creación de una fachada entre el motor y la aplicación.
Se adapta la fachada del juego que llamaba al motor Irrlicht para actuar de fachada intermedia entre el juego y la fachada del motor de TAG. Esta fachada intermedia contendrá funciones específicas para creación de personajes y demás elementos específicos del juego mientras que TAGEngine contiene la creación de nodos y mallas.
El main llama a la fachada intermedia (GraphicsEngine) que a su vez llama a la fachada del motor de TAG (TAGEngine).
Se ha separado la gestión de la ventana de gráficos mediante SFML para que esté en GraphicsEngine.


2. Visualización: visualizador OpenGL 4.X de las entidades tipo malla. Shader básico. Con cámaras y luces de varios tipos. Visualización con registro de cámaras y luces.
Se crean 3 cubos obtenidos de un fichero obj para mostrar la creación del arbol y de nodos malla hijos de otros. El cubo de la parte inferior es hijo del cubo de la derecha, teniendo el desplazamiento en x a cero.
Se crea una cámara y una luz, registrándose estas en el momento de la creación de las mismas.


3. Visualización: visualizador OpenGL 4.X simple, con datos por fichero. Shader básico.
Se retoma esta tarea ya finalizada para una optimización del dibujado en OpenGL mediante el uso de buffers OpenGL.