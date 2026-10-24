#include "EfectReverb.h"
#include "ExceptiiAudio.h"
#include <utility>

EfectReverb::EfectReverb(std::string nume, bool activ, float marimeCamera, float timpDecadere)
    : EfectAudio(std::move(nume), activ),
      marimeCamera(marimeCamera),
      timpDecadere(timpDecadere) {
    if (this->marimeCamera <= 0.0f || this->marimeCamera > 1.0f) {
        throw ParametruAudioDepasitException("Marimea camerei pentru reverb trebuie sa fie in intervalul (0.0, 1.0].");
    }
    if (this->timpDecadere <= 0.0f) {
        throw ParametruAudioDepasitException("Timpul de decadere al reverbului trebuie sa fie strict pozitiv.");
    }
}

EfectAudio* EfectReverb::clone() const {
    return new EfectReverb(*this);
}

void EfectReverb::proceseaza(float* buffer, std::size_t dimensiune) {
    if (!esteActiv() || buffer == nullptr || dimensiune == 0) {
        return;
    }

    // Simulare de reflexie simpla 
    for (std::size_t i = 1; i < dimensiune; ++i) {
        buffer[i] += buffer[i - 1] * (marimeCamera * 0.3f);
    }
}

void EfectReverb::descriere(std::ostream& os) const {
    os << "Efect: " << getNume() << " | Stare: " << (esteActiv() ? "Activ" : "Inactiv")
       << " | Tip: Reverb (Marime Camera: " << marimeCamera << ", Decadere: " << timpDecadere << "s)";
}

float EfectReverb::getMarimeCamera() const {
    return marimeCamera;
}

float EfectReverb::getTimpDecadere() const {
    return timpDecadere;
}