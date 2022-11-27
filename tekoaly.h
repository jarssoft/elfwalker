#ifndef TEKOALY_H_INCLUDED
#define TEKOALY_H_INCLUDED

namespace tekoaly {
    class Tekoaly {
        public:
            /** Palauttaa haluamansa lihaksen tilan tietyllä aikavälillä. */
            virtual double getLihas(double aika, int lihasNro)=0;
    };
}

#endif // TEKOALY_H_INCLUDED
