#include <GL/gl.h>
#include "poly.h"
#include "piste.h"

void Poly::piirra(){

    glBegin(GL_TRIANGLES);

        glColor3f(red, green, blue);
        glVertex2f(piste1.getX(), piste1.getY());

        glColor3f(red, green, blue);
        glVertex2f(piste2.getX(), piste2.getY());

        glColor3f(red, green, blue);
        glVertex2f(piste3.getX(), piste3.getY());

    glEnd();

}
