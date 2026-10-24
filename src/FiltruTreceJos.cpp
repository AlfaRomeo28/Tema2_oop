#include "../include/FiltruTreceJos.h"
#include "../include/ExceptiiAudio.h"
#include <utility>

FiltruTreceJos::FiltruTreceJos(std::string nume, bool activ, float frecventaCutoff, float coeficientAtenuare)
    : EfectAudio(std::move(nume), activ),
      frecventaCutoff(frecventaCutoff),
      coeficientAtenuare(coeficientAtenuare) {
    if (this->frecventaCutoff <= 20.0f || this->frecventaCutoff >= 20000.0f) {
        throw ParametruAudioDepasitException("Frecventa cutoff trebuie sa fie in spectrul audibil (20Hz - 20000Hz).");
    }
    if (this->coeficientAtenuare <= 0.0f || this->coeficientAtenuare >= 1.0f) {
        throw ParametruAudioDepasitException("Coeficientul de atenuare trebuie sa fie in intervalul (0.0, 1.0).");
    }
}

EfectAudio* FiltruTreceJos::clone() const {
    return new FiltruTreceJos(*this);
}

void FiltruTreceJos::proceseaza(float* buffer, std::size_t dimensiune) {
    if (!esteActiv() || buffer == nullptr || dimensiune == 0) {
        return;
    }

    // Filtru single-pole low-pass:
    // eșantionul curent devine o combinatie ponderata intre el si cel precedent
    for (std::size_t i = 1; i < dimensiune; ++i) {
        buffer[i] = coeficientAtenuare * buffer[i] + (1.0f - coeficientAtenuare) * buffer[i - 1];
    }
}

void FiltruTreceJos::calibreazaFrecventa(float frecventaNoua) {
    if (frecventaNoua <= 20.0f || frecventaNoua >= 20000.0f) {
        throw ParametruAudioDepasitException("Frecventa noua de calibrare este invalida.");
    }
    this->frecventaCutoff = frecventaNoua;
}

void FiltruTreceJos::descriere(std::ostream& os) const {
    os << "Efect: " << getNume() << " | Stare: " << (esteActiv() ? "Activ" : "Inactiv")
       << " | Tip: Filtru Trece-Jos (Cutoff: " << frecventaCutoff << " Hz, Coef: " << coeficientAtenuare << ")";
}

float FiltruTreceJos::getFrecventaCutoff() const {
    return frecventaCutoff;
}

float FiltruTreceJos::getCoeficientAtenuare() const {
    return coeficientAtenuare;
}