#include "İcOdul.hpp"

//Nadirlik değeri hesapla.
long double infrequencyCalculation(long double x, std::vector<long double> L){
    long double min = LDBL_MAX, max = LDBL_MIN;
    for(int i = 0; i < L.size(); i++){
        long double h = abs(x-L.at(i));
        if(h < min) min = h;
    }
    for(int i = 0; i < L.size()-1; i++){
        long double h;
        for(int l = 0; l < L.size(); l++){
            h = abs(L.at(i) - L.at(l));
            if(h > max) max = h;
        }
    }
    return min/max;
}
//İç ödül hesapla.
long double inversiveValue(long double weight, long double infrequencyValue){
    long double inverseWeight;
    if(infrequencyValue <= 1) inverseWeight = 1;
    else inverseWeight = weight;
    return infrequencyValue * inverseWeight;
}