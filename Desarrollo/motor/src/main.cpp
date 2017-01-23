#include "Objects.h"


/**************************************** myGlutKeyboard() **********/

void Keyboard(unsigned char Key, int x, int y)
{
    switch(Key)
    {
        case 27:
        case 'q':
            exit(0);
            break;

    }

    glutPostRedisplay();
}

/**************************************** mySpecialKey() *************/

static void SpecialKey(int key, int x, int y)
{

    switch (key)
    {
        case GLUT_KEY_UP:
            escena.getObject(0)->rx-=0.1f;
            break;
        case GLUT_KEY_DOWN:
            escena.getObject(0)->rx+=0.1f;
            break;
        case GLUT_KEY_LEFT:
            escena.getObject(0)->rz-=0.1f;
            break;
        case GLUT_KEY_RIGHT:
            escena.getObject(0)->rz+=0.1f;
            break;
    }

    glutPostRedisplay();
}

/***************************************** myGlutMenu() ***********/

void Menu( int value )
{
  Keyboard( value, 0, 0 );
}

void Mouse(int button, int button_state, int x, int y ){}

void Render()
{
    escena.Render();
}

void Idle(){}

void Reshape(int x, int y){}

void Motion(int x, int y){}

/**************************************** main() ********************/
int main(int argc, char* argv[])
{
    // Inicializa GLUT and crea la ventana principal
    glutInit(&argc, argv);
    glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_STENCIL | GLUT_MULTISAMPLE );
    glutInitWindowPosition( 50, 50 );
    glutInitWindowSize( 1400, 800 );

    int main_window = glutCreateWindow( "Motor TAG" );

    // Inicializa los valores de OpenGL para esta Aplicación
    escena.InitGL();

    glutDisplayFunc( Render );
    GLUI_Master.set_glutReshapeFunc( Reshape );
    GLUI_Master.set_glutKeyboardFunc( Keyboard );
    GLUI_Master.set_glutSpecialFunc( SpecialKey );
    GLUI_Master.set_glutMouseFunc( Mouse );
    glutMotionFunc( Motion );

    // We register the idle callback with GLUI, *not* with GLUT
    GLUI_Master.set_glutIdleFunc( Idle );


    // Creación de objetos
    TPrimitiva* cube = new TPrimitiva(1, CUBE_ID);
    escena.AddObject(cube);



    // Regular GLUT main loop
    glutMainLoop();

    return EXIT_SUCCESS;
}

