#include <iostream>
#include "vuorovaikutus.h"
#include "piste.h"

namespace fysiikka {
    void Vuorovaikutus::teeVuorovaikutus(){

        piste1.teeVuorovaikutus(piste2, t_etaisyys, t_voima);

    }

    void Vuorovaikutus::setEtaisyys(double et)
    {
        t_etaisyys = et;
    }

    double Vuorovaikutus::getEtaisyys() const
    {
        return t_etaisyys;
    }

    void Vuorovaikutus::vastavoima(double voimax, double voimay)
    {
        piste1.addNopeus(+voimax, +voimay);
        piste2.addNopeus(-voimax, -voimay);
    }
}
