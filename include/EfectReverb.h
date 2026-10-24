#pragma once

#include "EfectAudio.h"
#include <cstddef>
#include <iostream>
#include <string>

class EfectReverb : public EfectAudio {
private:
    float marimeCamera;   // factor intre 0.1 si 1.0
    float timpDecadere;   // secunde

    void descriere(std::ostream& os) const override;

public:
    EfectReverb(std::string nume, bool activ, float marimeCamera, float timpDecadere);

    EfectAudio* clone() const override;
    void proceseaza(float* buffer, std::size_t dimensiune) override;

    float getMarimeCamera() const;
    float getTimpDecadere() const;
};