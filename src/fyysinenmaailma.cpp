#include <iostream>
#include <iterator>
#include <assert.h>
#include <list>
#include <cstdlib>
#include <cmath>
#include <GL/glut.h>
#include "fyysinenmaailma.h"

namespace fysiikka {

    int flop=0;

    FyysinenMaailma::FyysinenMaailma(tekoaly::Suunnitelma* lt, Maasto* vuor){

        liiketaulukko=lt;
        vuoristo=vuor;
        aika=0;
        alkuaika=0;

        double y=-0.5, x=-0.8;

        alkupiste1=*new Piste(0.1+x, 0.0+y);
        alkupiste2=*new Piste(0.4+x, 0.0+y);
        alkupiste3=*new Piste(0.0+x, 0.5+y);
        alkupiste4=*new Piste(0.5+x, 0.5+y);
        alkupiste5=*new Piste(0.25+x, 1.5+y);

        piste1=alkupiste1;
        piste2=alkupiste2;
        piste3=alkupiste3;
        piste4=alkupiste4;
        piste5=alkupiste5;

        pisteet.clear();
        pisteet.push_back(&piste1);
        pisteet.push_back(&piste2);
        pisteet.push_back(&piste3);
        pisteet.push_back(&piste4);
        pisteet.push_back(&piste5);

        sidos1=new Vuorovaikutus(piste1, piste4, 0.16);
        sidos3=new Vuorovaikutus(piste1, piste3, 0.16);
        sidos4=new Vuorovaikutus(piste2, piste4, 0.16);
        sidos5=new Vuorovaikutus(piste3, piste4, 0.16);
        sidos6=new Vuorovaikutus(piste2, piste3, 0.16);
        sidos7=new Vuorovaikutus(piste5, piste3, 0.16);
        sidos8=new Vuorovaikutus(piste5, piste4, 0.16);

        sidokset.clear();
        sidokset.push_back(sidos1);
        sidokset.push_back(sidos3);
        sidokset.push_back(sidos4);
        sidokset.push_back(sidos5);
        sidokset.push_back(sidos6);
        sidokset.push_back(sidos7);
        sidokset.push_back(sidos8);

        lihas1=new Lihas(*sidos1, 0.0);
        lihas3=new Lihas(*sidos3, 0.0);
        lihas4=new Lihas(*sidos4, 0.0);
        lihas5=new Lihas(*sidos5, 0.0);
        lihas6=new Lihas(*sidos6, 0.0);
        lihas7=new Lihas(*sidos7, 0.2);
        lihas8=new Lihas(*sidos8, 0.2);

        //list<fysiikka::Lihas*> lihakset;
        lihakset.clear();
        lihakset.push_back(lihas1);
        lihakset.push_back(lihas3);
        lihakset.push_back(lihas4);
        lihakset.push_back(lihas5);
        lihakset.push_back(lihas6);
        lihakset.push_back(lihas7);
        lihakset.push_back(lihas8);

        poly1=new Poly(piste1, piste4, piste3, 0.7, 0.6, 0.2);
        poly2=new Poly(piste2, piste4, piste3, 0.4, 0.4, 0.2);
        poly3=new Poly(piste5, piste4, piste3, 0.7, 0.5, 0.4);

        //list<Poly> polyt;
        polyt.clear();
        polyt.push_back(poly1);
        polyt.push_back(poly2);
        polyt.push_back(poly3);
    }

    void FyysinenMaailma::currentTime(){

        piste1.replace(alkupiste1);
        piste2.replace(alkupiste2);
        piste3.replace(alkupiste3);
        piste4.replace(alkupiste4);
        piste5.replace(alkupiste5);
        aika=alkuaika;
    }

    void FyysinenMaailma::set(){

        alkupiste1=piste1;
        alkupiste2=piste2;
        alkupiste3=piste3;
        alkupiste4=piste4;
        alkupiste5=piste5;
        alkuaika=aika;
    }

    double FyysinenMaailma::getTime(){

        return aika;

    }

    void FyysinenMaailma::piirra(){

        glClearColor(0.7f, 0.9f, 1.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glPushMatrix();

        for(std::list<Poly*>::iterator po = polyt.begin();
                po != polyt.end(); ++po)
        {
            (*po)->piirra();
        }

        vuoristo->piirra(8);

        glFlush();
    }

     double FyysinenMaailma::fitness(bool todellisuus){

         //suositaan pystyasentoa
         double pysty = (piste5.getY() - piste1.getY()) + (piste5.getY() - piste2.getY());
         //double pysty = 10 - fabs(piste5.getX() * 2 - (piste1.getX() + piste2.getX()));

         double vaaka = (piste5.getX() + piste2.getX() + piste1.getX())*0.75 +
                        (piste5.getX() + piste2.getXNopeus() + piste1.getXNopeus())*0.25;

         if(todellisuus){
             if(vaaka>0.8){
                 kerroin=-1;
             }
             if(vaaka<-0.8){
                 kerroin=1;
             }
         }

         return pysty*0.0 + vaaka * kerroin;
     }

     void FyysinenMaailma::makePhysics(const float resoluutio){
        //fysiikka päivitetään n. 10 kertaa yhden framen aikana

        const float vastaluku = 1.0 / resoluutio;
        const float liike = vastaluku * 10;

        for(int t=1;t<=resoluutio;t++){
            aika+=vastaluku;

            //pisteiden vuorovaikutus eli vetovoima
            assert(sidokset.size()==7);
            for(std::list<fysiikka::Vuorovaikutus*>::iterator it = sidokset.begin();
                    it != sidokset.end(); ++it){
                (*it)->teeVuorovaikutus();
            }

            //pisteiden sijainnin päivittäminen
            std::list<fysiikka::Piste*>::const_iterator p;
            p = pisteet.begin();
            while(p != pisteet.end()) {
                (*p)->paivitaSijainti(liike);
                (*p)->teeMaaVuorovaikutus(*vuoristo, 1);
                p++;
            }

            setLihakset();
        }
     }

    void FyysinenMaailma::setLihakset(){
        //muutetaan lihaksien toivottua pituutta suunnitelman mukaan
        int l=0;
        for(std::list<fysiikka::Lihas*>::iterator it = lihakset.begin();
                it != lihakset.end(); ++it)
        {
            (*it)->setArvo((*liiketaulukko).getLihas(aika, l));
            l++;
        }
    }

}
