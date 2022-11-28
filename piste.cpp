#include <math.h>
#include <iostream>
#include "mate.h"
#include "piste.h"
#include "vuoristo.h"

namespace fysiikka {

    Piste::Piste(double x, double y){
        koord.p.x=x;
        koord.p.y=y;
        koord.n.x=0;
        koord.n.y=0;
        paine=0;
    }

    /* Fysiikan perusyksikk�. */
    void Piste::teeVuorovaikutus(Piste &piste, double &etaisyys, double voimakerroin) {

        /*
        //double e = distance(koord.p.x, koord.p.y, piste.koord.p.x, piste.koord.p.y);
        double v = voima(koord.p.x, koord.p.y, piste.koord.p.x, piste.koord.p.y, etaisyys) * voimakerroin;
        double k = angle(koord.p.x, koord.p.y, piste.koord.p.x, piste.koord.p.y);

        //suuri voima muuttaa et�isyytt�
        //if(etaisyys<e-taittuvuus) etaisyys=e-taittuvuus;
        //if(etaisyys>e+taittuvuus) etaisyys=e+taittuvuus;

        //voimat eri koordinaateille
        double xv = v * cos(k);
        double yv = v * sin(k);

        //using namespace std;
        //cout << "Distance = " <<
        //        distance(0.0, 0.0, 0.0, 1.0) << endl;
        */

        const double etx = piste.koord.p.x - koord.p.x;
        const double ety = piste.koord.p.y - koord.p.y;
        const double et = sqrt(etx * etx + ety * ety);
        const double v = (et - etaisyys) * voimakerroin;

        //voimat eri koordinaateille
        const double xv = v * (etx / et);
        const double yv = v * (ety / et);

        //vastapisteiden nopeus muuttuu
        koord.n.x += xv;
        koord.n.y += yv;
        piste.koord.n.x -= xv;
        piste.koord.n.y -= yv;
    }

    void Piste::toString(){
        using namespace std;
        cout << "-- Piste --" << endl;
        cout << "p.x: " << koord.p.x << ", p.y: " << koord.p.y << endl;
        cout << "n.x: " << koord.n.x << ", n.y: " << koord.n.y << endl;
    }

    const double ILMAKITKA = 0.975;

    void Piste::paivitaSijainti(double aika){

        //lis�t��n nopeus koordinaatteihin
        koord.p.x+=koord.n.x*aika;
        koord.p.y+=koord.n.y*aika;

        //Kitka l�mp�liikkeen hidastamiseksi
        koord.n.x*=ILMAKITKA;
        koord.n.y*=ILMAKITKA;

        //painovoima
        koord.n.y-=0.0001*0.15;
    }

    void Piste::teeMaaVuorovaikutusY(korkeusJaKaltevuus kjk, double aika){
        teeMaaVuorovaikutusY(kjk.kaltevuus, kjk.korkeus, aika);
    }

    void Piste::teeMaaVuorovaikutusY(double kaltevuus, double maanpintaY, double aika){
        if(koord.p.y<maanpintaY){

            // Kuinka suuri voima pinnasta kohdistuu
            paine = (maanpintaY-koord.p.y) * (maanpintaY-koord.p.y) - 2 * koord.n.y;

            // Kiihtyvyys suuntautuu pinnasta poisp�in
            koord.n.y += paine * 0.4 * (1 - abs(kaltevuus)) * aika;
            koord.n.x += paine * 0.4 * (-kaltevuus) * aika;

            // Lepo vai liikekitka
            double kitkakerroin=2/fabs(koord.n.x);
            double kitkavoina = 1 + paine * kitkakerroin;

            koord.n.x /= (kitkavoina * aika / (1 - abs(kaltevuus)));
        }
    }

    void Piste::teeMaaVuorovaikutus(double kaltevuus, double korkeus, double aika){
        teeMaaVuorovaikutusY(kaltevuus, korkeus + koord.p.x * kaltevuus + 0.2, aika);
    }

    void Piste::teeMaaVuorovaikutus(Vuoristo& vuoristo, double aika){
        teeMaaVuorovaikutusY(vuoristo.getKorkeusLU(koord.p.x), aika);
    }

    void Piste::addNopeus(double x, double y){
        using namespace std;
        //cout << "nopeusmuutos" << endl;
        koord.n.x+=x;
        koord.n.y+=y;
    }

    double Piste::getX(){
        return koord.p.x;
    }

    double Piste::getY(){
        return koord.p.y;
    }

    double Piste::getKulma(Piste piste){
        return angle(koord.p.x, koord.p.y, piste.koord.p.x, piste.koord.p.y);
    }

    double Piste::getPaine(){
        if(paine>-10 && paine<10){
            return paine;
        }else{
            return -10;
        }
    }

    double Piste::getXNopeus(){
        return koord.n.x;
    }

    double Piste::getYNopeus(){
        return koord.n.y;
    }

    void Piste::replace(Piste piste){
        this->koord = piste.koord;
        this->paine = piste.paine;
    }



    /*
    int main(int argc, char **argv){
        Piste piste1(0,0);
        Piste piste2(0,-2);

        piste1.toString();
        piste2.toString();

        piste2.teeVuorovaikutus(piste1);

        piste1.toString();
        piste2.toString();
    }
    */
}