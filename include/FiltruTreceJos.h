#pragma once

#include "EfectAudio.h"
#include <cstddef>
#include <iostream>
#include <string>

class FiltruTreceJos : public EfectAudio {
private:
    float frecventaCutoff;
    float coeficientAtenuare;

    void descriere(std::ostream& os) const override;

public:
    FiltruTreceJos(std::string nume, bool activ, float frecventaCutoff, float coeficientAtenuare);

    EfectAudio* clone() const override;
    void proceseaza(float* buffer, std::size_t dimensiune) override;


    void calibreazaFrecventa(float frecventaNoua);

    float getFrecventaCutoff() const;
    float getCoeficientAtenuare() const;
};