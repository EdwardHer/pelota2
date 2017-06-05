#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>

using namespace std;

int frameNumber;   // Numero de frames 

float scale = 2;  // escala en  x, y, and z

float rotateX, rotateY;  // variables para rotación con teclas especiales 

//VARIALBES QUE GUARDARA EL AVANCE EN LA POSICION DE LA PELOTA.
float up=1, rigth, altura=1.0, fisica;
bool a=false;
float c=0;

void display() {
       // LLamada a función dibujo 

    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_PROJECTION);  // Set up the projection.
    glLoadIdentity();
    glOrtho(-scale,scale,-scale,scale,-2*scale,2*scale);
    glMatrixMode(GL_MODELVIEW);
    
    glLoadIdentity();             // configuración de matrix de identidad. 
   /* glRotatef(rotateY,0,1,0);
    glRotatef(rotateX,1,0,0);
  */
    // Agregar Codigo acá, para dibujar
   // glColor3f(1.0,0.0,0.0);
   /* if (c==0)
    {
      glutWireTeapot(1.0);
      c=1;
    }
    else{
     glutSolidCube(1.0); 
     c=0;
    
    }*/
   // glPushMatrix();
    glTranslatef(-0.8+rigth,up,0);
    glutSolidSphere(0.40, 20, 20);
    //glPopMatrix();
    glFlush ();
    glutSwapBuffers();    
}


// --------------- Para animación  ------------------------------------------

int animating = 0;      // 0 sin animación 
                        // Se cambia con la llamada a las funciones startAnimation() and pauseAnimation()

void pauseAnimation() {
       // Llamamo a la función para detener la animación 
    animating = 0;
}

void updateFrame() {
   // En esta funcion agregamos el codigo que hara la secuencia de cada escena como si fuera un fotograma 
  //moviento de la pelota******
  //funsion para la altura
  if (up>=-1 & a==false)
  {
    up-=0.05;
    rigth+=0.01;
    /* code */
  }

else{
    fisica= fisica - 0.008;
    if (a==false)
    {
      altura -=(altura/2)- fisica;
      a=true;
      
      /* code */
    }
  
    if (up<=altura)
    {
      up+=0.05;/* code */
      rigth+=0.01;
    }
    else
    { 
      a=false;
    } 
  }
glColor3f(altura,1.0,-00.002+fisica);
	//Hacemos que la tetera gire 
	for (int i=3; i<=100; i++){
		rotateY=rotateY-= i;
	}
   //Verificamos el numero de frames para detener animación 
  if (frameNumber<=190)
    {
      /* code */
      glPushMatrix();
      glTranslatef(0,c+0.9,0);
      glPopMatrix();
      c-=0.008;
    }else{
      glPushMatrix();
      glTranslatef(0,c+0.9,0);
      glPopMatrix();
    }
   if(frameNumber==200 )
		{
			pauseAnimation();
			frameNumber=0;
		}
  //Almacenamos el numero de frames 
  frameNumber++;
  printf ("Numero de Frame: %d \n", up);
}

void timerFunction(int timerID) {
      // Invocamos la funcion para controlar el tiempo de la ejecucion de funciones 
    if (animating) {
        updateFrame();
        glutTimerFunc(30, timerFunction, 0);
        glutPostRedisplay();
    }
}

void startAnimation() {
      // llamamos la función para iniciar la animación 
   if ( ! animating ) {
       animating = 1;
       glutTimerFunc(30, timerFunction, 1);
   }
}



// ------------- Manejo de Teclado-----------------------------------------------

void key(unsigned char key, int x, int y) {
        // La animación inicia al presionar la tecla espaciadora de igual forma se detiene
    if ( key == ' ' ) {
		if ( animating )
		   pauseAnimation();
	
		else
		   startAnimation();
	}
	if (key == 27){
		exit(0);
	}
}

void special(int key, int x, int y) {
		   // control de teclas especiales 
    if ( key == GLUT_KEY_LEFT )
       rotateY -= 15;
    else if ( key == GLUT_KEY_RIGHT )
       rotateY += 15;
    else if ( key == GLUT_KEY_DOWN)
       rotateX += 15;
    else if ( key == GLUT_KEY_UP )
       rotateX -= 15;
    else if ( key == GLUT_KEY_HOME )
       rotateX = rotateY = 0;
    glutPostRedisplay();
}

// ----------------------  Funcion principal ------------------

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(100,100);
    glutCreateWindow("OpenGL Tetera");
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutSpecialFunc(special);
    glEnable(GL_DEPTH_TEST);

    frameNumber = 0;
    rotateX = rotateY = 0;
    
    // Activar iluminación 
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_NORMALIZE);
    
    // Descomentar si queremos que la animación inicie al levantar el script
    startAnimation();

    glutMainLoop();
    return 0;
}