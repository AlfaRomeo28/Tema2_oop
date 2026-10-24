#pragma once
#include "EfectAudio.h"
#include <iostream>
#include <string>
#include <cstddef>

class EfectEcou : public EfectAudio {
   private:
       int delaySamples;
       float feedback;
       void descriere(std::ostream& os)const override;
   public:
    //constr pt apelarea constr de baza si valideaza parametrii
    EfectEcou(std::string nume ,bool activ, int delaySamples, float feedback);
    EfectAudio* clone() const override; //constr virtual
    //procesarea matematica secifica ecoului
    void proceseaza(float* buffer,  std::size_t dimensiune) override;
    int getDelaySamples()const ;
    float getFeedback()const ;

};