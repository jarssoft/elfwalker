#include <assert.h>
#include "lihas.h"

namespace fysiikka {

    void Lihas::setArvo(double arvo){
        assert (arvo>=0);
        assert (arvo<=1);
        sidos.setEtaisyys(min_etaisyys + arvo * kerroin);
    }

}

