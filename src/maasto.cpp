#include <iostream>
#include <time.h>
#include <cstdlib>
#include <GL/gl.h>
#include <assert.h>
#include "maasto.h"
#include "fys-rutiinit.h"

struct vuoristoJako {
    Maasto *vasen;
    Maasto *oikea;
};

void Maasto::toString(){

    using namespace std;
    cout << "-- Vuoristo --" << endl;
    cout << "x1: " << x1 << ", y1: " << y1 << endl;
    cout << "x2: " << x2 << ", y2: " << y2 << endl;

}

//täyttää lookup-taulukon nopeampaa hakua varten
void Maasto::makeLU(const int resoluutio, const int syvyys)
{
    lookup_askel = (x2-x1) / resoluutio;
    index_askel = 1.0 / lookup_askel;
    lookup.clear();

    for(int x=0;x<=resoluutio;x++){
        lookup.push_back(getKorkeus(x * lookup_askel + x1, syvyys));
    }
}

struct korkeusJaKaltevuus Maasto::getKorkeusLU(float x)
{
    if(x<x1){
        return lookup.front();
    }
    if(x>x2) {
        return lookup.back();
    }

    int i = (int)((x-x1) * index_askel);
    /*
    assert(x>=x1);
    assert(x<=x2);
    assert(index_askel);
    assert(i>=0);
    assert(i<lookup.size());
    */
    return lookup.at(i);
}

struct vuoristoJako Maasto::jaa(){

    using namespace std;

    if(vasenP==NULL){
        //satunnaisluku johdetaan x-koordinaatista
        double xv=(x1+x2)/2;
        srand(xv*RAND_MAX);
        //rand();rand();rand();rand();rand();

        double epatas[] = {1, 2, 5, 2, 4, 2, 50};
        double muutos=((double)rand()/RAND_MAX-0.5)*epatasaisuus*epatas[syvyys];

        double yv=(y1+y2)/2+muutos;

        vasenP = new Maasto(x1,y1,xv,yv,epatasaisuus/2);
        oikeaP = new Maasto(xv,yv,x2,y2,epatasaisuus/2);
    }

    //Vuoristo *vasen = *vasenP;

    //Vuoristo vasen = Vuoristo(x1, y1, xv, yv, epatasaisuus/2, syvyys+1);
    //Vuoristo oikea = Vuoristo(xv, yv, x2, y2, epatasaisuus/2, syvyys+1);

    //delete vasenP;
    //delete oikeaP;

    //vasen = new Vuoristo(x1,y1,xv,yv,50);
    //oikea = new Vuoristo(xv,yv,x2,y2,50);

    //Vuoristo jako[] = {vasen,oikea};
    //jako[0].toString();

    //struct vuoristoJako tmp;
    //tmp.vasen=&vasen;
    //tmp.oikea=&oikea;
    //return tmp;

    vuoristoJako tmp = {vasenP,oikeaP};

    //struct vuoristoJako tmp;
    //tmp.vasen=&vasen;
    //tmp.oikea=&oikea;

    return tmp;

}

void Maasto::piirra(int syv){

    int syvyys=syv-1;
    if(syvyys>0){
        struct vuoristoJako jako=jaa();
        jako.vasen->piirra(syvyys);
        jako.oikea->piirra(syvyys);
    }else{
        //toString();
        glBegin(GL_TRIANGLES);
            glColor3f(0.0, 0.5, 0.0);
            glVertex2f(x1, y1);
            glVertex2f(x2, y2);
            glVertex2f(x1, -1);
        glEnd();
        glBegin(GL_TRIANGLES);
            glColor3f(0.0, 0.5, 0.0);
            glVertex2f(x2, y2);
            glVertex2f(x1, -1);
            glVertex2f(x2, -1);
        glEnd();
    }

}

double yksikkovektori_j(double i, double j){

    if(i+j==0){
        return 0;
    }

    double et = fysiikka::distance(0, 0, i, j);
    i/=et;
    j/=et;
    //assert(fabs(i)+fabs(j) > 0.6);
    //assert(fabs(i)+fabs(j) < 1.4);

    assert(i >= -1 && i <= 1);

    return j;

}

struct korkeusJaKaltevuus Maasto::getKorkeus(float x, int syv){

    int syvyys = syv - 1;
    if(syvyys>0){
        struct vuoristoJako jako = jaa();
        if(jako.vasen->x2>x){
            return jako.vasen->getKorkeus(x,syvyys);
        }else{
            return jako.oikea->getKorkeus(x,syvyys);
        }
    }else{
        double korkeus = y1+(y2-y1)*((x-x1)/(x2-x1));
        double kaltevuus = yksikkovektori_j(x2-x1, y2-y1);
        korkeusJaKaltevuus tmp = {korkeus, kaltevuus};
        return tmp;
    }

}

/*
int main(int argc, char **argv){
    //srand(1);
    Vuoristo vuoristo(0, 0, 320, 200, 50);
    //vuoristo.toString();
    //Vuoristo* jako = vuoristo.jaa();
    //vuoristo.jaa().vasen.toString();

    using namespace std;
    cout << "Eka piirto";
    vuoristo.piirra(4);
    cout << "Toka piirto";
    vuoristo.piirra(4);
    cout << "Korkeus";
    vuoristo.getKorkeus(201, 4);


    using namespace std;
    cout << "y: "  << vuoristo.getKorkeus(201, 5).korkeus << endl;

    srand(1000);rand();rand();rand();rand();rand();
    cout << "rand: "  << rand() << endl;


    //struct vuoristoJako jako=vuoristo.jaa();
    //jako.vasen.toString();
    //jako.oikea.toString();

    //tmp.vasen->toString();

    //tmp.oikea=&oikea;

    //jako[0].toString();
    //jako[0].toString();
    //jako[1].toString();
}

*/
