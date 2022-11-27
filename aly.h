#ifndef ALY_H_INCLUDED
#define ALY_H_INCLUDED

namespace tekoaly {

    const int KOKO=10;

    const int LIHAKSET=7;

    /** Laittaa halutun numeron joka solun arvoksi. */
    void taytaArray(double array[][LIHAKSET], double numero);

    /** Arpoo taulukon kaikille soluille arvon v‰lilt‰ 0-1. */
    void alustaArray(double array[][LIHAKSET]);

    /** Muuttaa solujen arvoja satunnaisesti halutun m‰‰r‰n. */
    void mutateArray(double array[][LIHAKSET], double mutaatio);

    /** Kopioi taulukon. */
    void copyArray(double array1[][LIHAKSET], double array2[][LIHAKSET]);

    /** L‰hent‰‰ taulukkoa toiseen, eli kopioi osittain. */
    void copyArray(double array1[][LIHAKSET], double array2[][LIHAKSET], double maara);

    /** Siirt‰‰ taulukon soluja halutun verran 0:n p‰in. */
    void siirraArray(double array[][LIHAKSET], int siirtyma);

    /** Laskee taulukon solujen eron summan. */
    double eroArray(double array[][LIHAKSET], double array2[][LIHAKSET]);

    /** Tulostaa taulukon ruudulle. */
    void printArray(double array[][LIHAKSET]);
}

#endif // ALY_H_INCLUDED
