#include <assert.h>
#include <iostream>
#include "suunnitelma.h"

namespace tekoaly {
    Suunnitelma::Suunnitelma(int sis, int van){

        //using namespace std;
        //cout << "Alustettiin " << lihas1[2] << endl;

        sisarukset=sis;
        syvyys=van;
        aika=0;

        arvosana=-10000;
        sisarus=0;
        tila = ALUSTETTU;
        aikakorjaus=0;

        onAlin=true;

        alustaArray(lihakset);

        if(van==0){

        }else{
            //Liiketaulukko uusivanhempi(sis, van-1);
            //vanhempi = &uusivanhempi;
            Suunnitelma *uusivanhempi;
            uusivanhempi = new Suunnitelma(sis, van-1);
            vanhempi = uusivanhempi;
            vanhempi->onAlin=false;
            //Liiketaulukko* new(sis,van-1);
            // Varataan int-muuttujan verran muistia ja otetaan osoite talteen.
            //lkm = new int;
        }
    }

    void Suunnitelma::poista(){
        tila = POISTETTU;
        if(syvyys>0)
            vanhempi->poista();
        delete vanhempi;
    }

    void Suunnitelma::palautaVanhemmalta(){
        copyArray(vanhempi->lihakset, lihakset);
    }

    void Suunnitelma::vieVanhemmalle(){
        copyArray(lihakset, vanhempi->lihakset);
    }

    Suunnitelma* Suunnitelma::getYlin(){
        if(syvyys==1){
            vanhempi->tila=VALMIS;
            return vanhempi;
        }
        else
            return vanhempi->getYlin();
    }

    bool Suunnitelma::next(){

        sisarus++;

        //jos parempi kuin vanhempi, viedään ylös
        if(arvosana > vanhempi->arvosana){
            vanhempi->arvosana = arvosana;
            vieVanhemmalle();
        }

        //jos sisarus on viimeinen,
        //eikä ylempää saada uutta mutaatiota,
        //palautetaan false.
        if(sisarus>sisarukset){

            //jos omistaa vanhemman, jolla on vanhempi
            if(syvyys>1){
                if(vanhempi->next()){
                    //jos ylhäältä löytyi vielä sisarus,
                    //jatketaan metodia ja nollataan sisarus
                    sisarus=0;
                    lahtoarvosana=vanhempi->arvosana;
                }else{
                    //jos ylemmät mutaatiot on tehty
                    if(onAlin) tila = VALMIS;                    
                    return false;
                }
            }else{
                //jos ollaan ylimmäisessä (ylempää ei saada uusia)
                //palautaVanhemmalta();
                if(onAlin) tila = VALMIS;
                return false;
            }

        }

        //periytetään uusi mutaatio vanhemmalta

        palautaVanhemmalta();

        double mutaatio=(0.5-sisarus*0.1)*0.3;

        mutateArray(lihakset, mutaatio);

        if(onAlin){
            tila = MUTATOITU;
        }
        return true;
    }

    double Suunnitelma::getLihas(double h_aika, int lihasNro){

        const double l_aika = (h_aika-aika)/10+aikakorjaus;

        assert(l_aika>=0);
        assert(l_aika<KOKO);
        assert(lihasNro>=0);
        assert(lihasNro<=LIHAKSET);

        assert(tila==MUTATOITU || tila==LUETTU || tila==VALMIS);
        tila = LUETTU;

        //const float pal1 = lihakset[(int)l_aika][lihasNro];
        //const float pal2 = lihakset[(int)l_aika+1][lihasNro];

        //assert(pal>=0 && pal<=1);
        //if(!(pal>=0 && pal<=1))
        //    std::cout << "lihakset " << pal << std::endl;
        //return  (l_aika - (int)l_aika) * pal2 + (1 - (l_aika - (int)l_aika)) * pal1;
        return  lihakset[(int)l_aika][lihasNro];

    }

    void Suunnitelma::arvostele(double arv){

        assert(tila==LUETTU);
        arvosana=arv;
        tila = ARVOSTELTU;

    }

    void Suunnitelma::addTime(double siirtyma){

        aikakorjaus+=siirtyma;
        while(aikakorjaus>0.999999){
            aikakorjaus-=1;
            siirraArray(lihakset, 1);
            //alustaArray(lihakset);
            //taytaArray(lihakset,0.5);
        }

        //alustaArray(lihakset);
    }

    void Suunnitelma::setTime(
            double uusi_aika){

        double ero = uusi_aika - aika;

        //aikaistetaan taulukkoa jos tarpeen
        addTime(ero);

        //ehdotus vaikuttaa tietyn prosenttimäärän per siirto
        //copyArray(ehdotus, lihakset, (ero/5) * 0.2);
        //printArray(ehdotus);

        aika=uusi_aika;

        sisarus=0;
        arvosana=-10000;
        tila = ALUSTETTU;

        if(syvyys>0)
            vanhempi->setTime(uusi_aika);
    }

}
