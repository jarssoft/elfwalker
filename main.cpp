// http://www.codebind.com/linux-tutorials/install-opengl-ubuntu-linux/

#include <time.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include "liiketaulukko.h"
#include "aly.h"
#include "tekoaly.h"
#include "vuoristo.h"
#include "fyysinenmaailma.h"
#include <chrono>
#include <thread>

const int ENNAKKO = 55;

void displayMe(void)
{
    bool todellisuus=true;

    srand(time(NULL));

    tekoaly::Liiketaulukko koetaulukko(2, 6); // 4, 4

    //double aistit[tekoaly::KOKO][tekoaly::LIHAKSET];
    //tekoaly::taytaArray(aistit, 0.5);
    //tekoaly::Som somk;

    //tekoaly::SomAly somaly(&koetaulukko, &somk);

    //double random=((double)rand()/RAND_MAX-0.5)*0.1;
    //Vuoristo vuoristo(-1.05+random, -1, 1, -0.6, 0.45);
    //Vuoristo vuoristo(-1, -0.6, 1, -0.6, 0.45);
    Vuoristo vuoristo(-1, -0.6, 1, -0.6, 0.15);
    vuoristo.makeLU(1000, 6);

    fysiikka::FyysinenMaailma maailma(&koetaulukko, &vuoristo);

    //double ent_ent_tulos = 0;
    //double ent_tulos = 0;
    //int tulos_maara = 0;

    for(int sp=0; sp<10000; sp++){

        ///maailma.getAistit(aistit);
        koetaulukko.setTime(maailma.getTime());
        //somaly.setTime(maailma.getTime(), aistit);
        //std::cout << "maailman aika: " << maailma.getTime() << std::endl;

        //siirto
        while (true){

            //std::cout << "-" ;

            //viimeisell‰ kerralla tosissaan
            todellisuus = !koetaulukko.next();

            maailma.currentTime();

            double tulos = 0;

            for (int aika = 0; aika<5+ENNAKKO; aika++)
            {
                if(todellisuus){
                    maailma.piirra();

                    std::this_thread::sleep_for(std::chrono::milliseconds(40));

                    if(aika>ENNAKKO){
                        break;
                    }
                }

                maailma.makePhysics(15);
            }

            tulos+=maailma.fitness(todellisuus);

            using namespace std;

            if(todellisuus){
                //siirret‰‰n aloituspisteen uuteen paikkaan
                maailma.set();
                todellisuus=false;
                break;
            }else{
                koetaulukko.arvostele(tulos);
            }
        }

    }
    exit(0);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Vuorikiipeilij√§");
    glutDisplayFunc(displayMe);
    glutMainLoop();

    return 0;
}
