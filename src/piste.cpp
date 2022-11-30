#include <math.h>
#include <iostream>
#include "fys-rutiinit.h"
#include "piste.h"
#include "maasto.h"

namespace fysiikka {

    Piste::Piste(double x, double y){
        koord.p.x=x;
        koord.p.y=y;
        koord.n.x=0;
        koord.n.y=0;
    }

    /* Fysiikan perusyksikkö. */
    void Piste::teeVuorovaikutus(Piste &piste, double &etaisyys, double voimakerroin) {

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
    const double MAAKITKA = 0.6;

    void Piste::paivitaSijainti(double aika){

        //Kitka lämpöliikkeen hidastamiseksi
        koord.n.x*=ILMAKITKA;
        koord.n.y*=ILMAKITKA;



        //lisätään nopeus koordinaatteihin
        koord.p.x+=koord.n.x*aika;
        koord.p.y+=koord.n.y*aika;
    }

    void Piste::teeMaaVuorovaikutusY(korkeusJaKaltevuus kjk, double aika){
        teeMaaVuorovaikutusY(kjk.kaltevuus, kjk.korkeus, aika);
    }

    void Piste::teeMaaVuorovaikutusY(double kaltevuus, double maanpintaY, double aika){

        //painovoima
        koord.n.y-=0.0001*0.10;

        if(koord.p.y<maanpintaY){

            //const double lepo = (fabs(koord.n.x) < 0.00009 ? 2 : 1);
            const double lepo = (1+fabs(koord.n.x)*1000) * (1+fabs(koord.n.x)*1000);

            //Kitka maan sisällä
            koord.n.x *= MAAKITKA / lepo;
            koord.n.y *= MAAKITKA / lepo;

            // Kuinka suuri voima pinnasta kohdistuu
            const double paine = (maanpintaY-koord.p.y) * (maanpintaY-koord.p.y); // - 2 * koord.n.y;

            // Kiihtyvyys suuntautuu pinnasta poispäin
            koord.n.y += paine * 0.4 * (1 - abs(kaltevuus)) * aika;
            koord.n.x += paine * 0.4 * (-kaltevuus) * aika;

        }
    }

    void Piste::teeMaaVuorovaikutus(double kaltevuus, double korkeus, double aika){
        teeMaaVuorovaikutusY(kaltevuus, korkeus + koord.p.x * kaltevuus + 0.2, aika);
    }

    void Piste::teeMaaVuorovaikutus(Maasto& vuoristo, double aika){
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

    double Piste::getXNopeus(){
        return koord.n.x;
    }

    double Piste::getYNopeus(){
        return koord.n.y;
    }

    void Piste::replace(Piste piste){
        this->koord = piste.koord;
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
