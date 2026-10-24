#include "../include/EfectDistorsie.h"
#include "../include/ExceptiiAudio.h"
#include <utility>

EfectDistorsie::EfectDistorsie(std::string nume, bool activ, float pragClipping, float gain)
    :EfectAudio(std::move(nume), activ),
      pragClipping(pragClipping),
      gain(gain) {

    if (this->pragClipping <= 0.0f) {
        throw ParametruAudioDepasitException("Pragul de clipping trebuie sa fie strict pozitiv.");
    }
    if (this->gain <= 0.0f) {
        throw ParametruAudioDepasitException("Factorul de gain trebuie sa fie strict pozitiv.");
    }
}

EfectAudio* EfectDistorsie::clone() const {
    return new EfectDistorsie(*this);
}

void EfectDistorsie::proceseaza(float* buffer, std::size_t dimensiune) {
    if (!esteActiv() || buffer == nullptr || dimensiune == 0) {
        return;
    }

    //  amplificare urmata de taiere la prag
    for (std::size_t i = 0; i < dimensiune; ++i) {
        buffer[i] *= gain;

        if (buffer[i] > pragClipping) {
            buffer[i] = pragClipping;
        } else if (buffer[i] < -pragClipping) {
            buffer[i] = -pragClipping;
        }
    }
}

void EfectDistorsie::descriere(std::ostream& os) const {
    os << "Efect: " << getNume() << " | Stare: " << (esteActiv() ? "Activ" : "Inactiv")
       << " | Tip: Distorsie (Prag: " << pragClipping << ", Gain: " << gain << "x)";
}

float EfectDistorsie::getPragClipping() const {
    return pragClipping;
}

float EfectDistorsie::getGain() const {
    return gain;
}


