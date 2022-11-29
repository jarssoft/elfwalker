#include <iostream>
#include "sidos.h"
#include "piste.h"

namespace fysiikka {
    void Sidos::teeVuorovaikutus(){

        piste1.teeVuorovaikutus(piste2, t_etaisyys, t_voima);

        /*
        const double etx = piste2.getX() - piste1.getX();
        const double ety = piste2.getY() - piste1.getY();
        const double et = sqrt(etx * etx + ety * ety);
        const double v = (et - t_etaisyys) * t_voima;

        //voimat eri koordinaateille
        const double xv = v * (etx / et);
        const double yv = v * (ety / et);

        //vastapisteiden nopeus muuttuu
        vastavoima(xv*aika, yv*aika);
        */
    }

    void Sidos::setEtaisyys(double et)
    {
        t_etaisyys = et;
    }

    double Sidos::getEtaisyys() const
    {
        return t_etaisyys;
    }

    void Sidos::vastavoima(double voimax, double voimay)
    {
        piste1.addNopeus(+voimax, +voimay);
        piste2.addNopeus(-voimax, -voimay);
    }
}
