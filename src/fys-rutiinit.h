#include <cmath>

#ifndef MATE_H_INCLUDED
#define MATE_H_INCLUDED

namespace fysiikka {

    /** Fysiikan funktioita.*/

    // Laskee kahden pisteen v�lisen et�isyyden (Pythagoraan lause)
    double inline distance(double dX0, double dY0, double dX1, double dY1)
    {
        return sqrt((dX1 - dX0)*(dX1 - dX0) + (dY1 - dY0)*(dY1 - dY0));
    }

    // Laskee kahden pisteen v�lisen kulman
    double inline angle(double dX0, double dY0,
                    double dX1, double dY1)
    {
        return atan2(dY1 - dY0, dX1 - dX0);
    }

    // Laskee kahden pisteen v�lisen voiman niiden pyrkiess�
    // haluttuun et�isyyteen toisistaan.
    double inline voima(double dX0, double dY0,
                    double dX1, double dY1, double etaisyys)
    {
        return (distance(dX0, dY0, dX1, dY1)-etaisyys)*0.01;

    }

    // Laskee kahden pisteen v�lisen x-koordinaatin voiman niiden pyrkiess�
    // haluttuun et�isyyteen toisistaan.
    double inline voimaX(double dX0, double dY0,
                    double dX1, double dY1, double etaisyys)
    {
        return -voima(dX0, dY0, dX1, dY1, etaisyys)*
                cos(angle(dX0, dY0, dX1, dY1));
    }

    // Laskee kahden pisteen v�lisen y-koordinaatin voiman niiden pyrkiess�
    // haluttuun et�isyyteen toisistaan.
    double inline voimaY(double dX0, double dY0,
                    double dX1, double dY1, double etaisyys)
    {
        return -voima(dX0, dY0, dX1, dY1, etaisyys)*
                sin(angle(dX0, dY0, dX1, dY1));
    }
}

#endif //
