#include "piste.h"

#ifndef POLY_H_INCLUDED
#define POLY_H_INCLUDED

/** Polygonin esitys piirtämistä varten. */
class Poly {
    public:
        Poly(fysiikka::Piste &p1, fysiikka::Piste &p2, fysiikka::Piste &p3,
                double r, double g, double b) :
                piste1(p1), piste2(p2),  piste3(p3),
                red(r), green(g), blue(b) {}
        void piirra();
    private:
        fysiikka::Piste &piste1;
        fysiikka::Piste &piste2;
        fysiikka::Piste &piste3;
        double red, green, blue;
};

#endif // POLY_H_INCLUDED
