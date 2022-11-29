#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <math.h>
#include <assert.h>
#include "aly-rutiinit.h"

namespace tekoaly {

    void taytaArray(double array[][LIHAKSET], double numero){
        for(int tx=0;tx<KOKO;tx++)
            for(int ty=0;ty<LIHAKSET;ty++)
                array[tx][ty]=numero;
    }

    void alustaArray(double array[][LIHAKSET]){
        for(int t=0;t<KOKO;t++)
            for(int l=0;l<LIHAKSET;l++)
                array[t][l]=(double)rand()/RAND_MAX;
    }

    void mutateArray(double array[][LIHAKSET], double mut){
        for(int t=0;t<KOKO;t++){
            for(int l=0;l<LIHAKSET;l++){

                //mutatoidaan alkua vähemmän
                double mutaatio=mut;
                //if(t<1) mutaatio/=4;

                array[t][l]+=((double)rand()/RAND_MAX-0.5)*mutaatio;
                if(array[t][l]<0)array[t][l]=0;
                if(array[t][l]>1)array[t][l]=1;
            }
        }
    }

    void copyArray(double array1[][LIHAKSET], double array2[][LIHAKSET]){
        for(int t=0;t<KOKO;t++)
            for(int l=0;l<LIHAKSET;l++)
                array2[t][l]=array1[t][l];
    }

    void copyArray(double array1[][LIHAKSET], double array2[][LIHAKSET], double maara){
        assert(maara>=0 && maara<=1);
        for(int tx=0;tx<KOKO;tx++)
            for(int ty=0;ty<LIHAKSET;ty++){
                using namespace std;
                //cout << "array1[][]:" << array1[tx][ty] << endl;
                assert(array1[tx][ty]>=-10 && array1[tx][ty]<=10);
                assert(array2[tx][ty]>=-10 && array2[tx][ty]<=10);
                array2[tx][ty]=
                        array2[tx][ty]*(1-maara)+
                        array1[tx][ty]*maara;
            }
    }

    void siirraArray(double array[][LIHAKSET], int siirtyma){
        for(int t=siirtyma;t<KOKO;t++)
            for(int l=0;l<LIHAKSET;l++)
                array[t-siirtyma][l]=array[t][l];
    }

    double eroArray(double array[][LIHAKSET], double array2[][LIHAKSET]){
        double ero=0;
        for(int t=0;t<KOKO;t++)
            for(int l=0;l<LIHAKSET;l++)
                ero+=fabs(array[t][l]-array2[t][l]);
        return ero;
    }

    void printArray(double array[][LIHAKSET]){
        using namespace std;
        for(int ty=0;ty<KOKO;ty++){
            for(int tx=0;tx<LIHAKSET;tx++){
                std::cout << " " << array[tx][ty];
            }
            std::cout << std::endl;
        }
    }

    /*
    int main(int argc, char **argv){
         double taulukko[KOKO][LIHAKSET];

         using namespace std;

         alustaArray(taulukko);
         cout << "rand:" << taulukko[8][2] << endl;

         mutateArray(taulukko,0.1);
         cout << "mutate:" << taulukko[8][2] << endl;

         double uusiTaulukko[KOKO][LIHAKSET];
         copyArray(taulukko, uusiTaulukko);
         cout << "copy:" << uusiTaulukko[8][2] << endl;
    }
    */
}
