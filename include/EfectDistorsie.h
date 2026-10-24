#pragma once

#include "EfectAudio.h"
#include <cstddef>
#include <iostream>
#include <string>

class EfectDistorsie : public EfectAudio {
      private:
        float pragClipping;
        float gain;
        void descriere(std::ostream &os) const override;
      public:
        EfectDistorsie(std::string nume,bool activ,float pragClipping, float gain);
        EfectAudio* clone() const override;
        void proceseaza(float* buffer, std::size_t dimensiune) override;
        float getPragClipping() const;
        float getGain() const;
};