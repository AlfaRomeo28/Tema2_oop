#include "../include/EfectEcou.h"
#include "../include/ExceptiiAudio.h"

EfectEcou::EfectEcou(std::string nume, bool activ, int delaySamples, float feedback)
    : EfectAudio(std::move(nume), activ),
      delaySamples(delaySamples),
      feedback(feedback) {
    if (this->feedback < 0.0f || this->feedback > 1.0f) {
        throw ParametruAudioDepasitException("Feedback-ul trebuie sa fie in intervalul [0.0, 1.0].");
    }
    if (this->delaySamples <= 0) {
        throw ParametruAudioDepasitException("Delay-ul in esantioane trebuie sa fie strict pozitiv.");
    }
}

EfectAudio* EfectEcou::clone() const {

    return new EfectEcou(*this);
}

void EfectEcou::proceseaza(float* buffer, std::size_t dimensiune) {

    if (!esteActiv() || buffer == nullptr || dimensiune == 0) {
        return;
    }

    // fiecare eșantion adauga o fractiune din esantionul aflat cu delaySamples pozitii în urma
    for (std::size_t i = delaySamples; i < dimensiune; ++i) {
        buffer[i] += buffer[i - delaySamples] * feedback;
    }
}

void EfectEcou::descriere(std::ostream& os) const {

    os << "Efect: " << getNume() << " | Stare: " << (esteActiv() ? "Activ" : "Inactiv")
       << " | Tip: Ecou (Delay: " << delaySamples << " samples, Feedback: " << feedback << ")";
}

int EfectEcou::getDelaySamples() const {
    return delaySamples;
}

float EfectEcou::getFeedback() const {
    return feedback;
}