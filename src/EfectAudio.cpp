#include "../include/EfectAudio.h"
#include <utility>


EfectAudio::EfectAudio(std::string nume, bool activ)
    : nume(std::move(nume)), activ(activ) {}


void EfectAudio::descriere(std::ostream& os) const {
    os << "Efect: " << nume << " | Stare: " << (activ ? "Activ" : "Inactiv");
}

void EfectAudio::afiseaza(std::ostream& os) const {
    descriere(os);
}


const std::string& EfectAudio::getNume() const {
    return nume;
}

bool EfectAudio::esteActiv() const {
    return activ;
}

std::ostream& operator<<(std::ostream& os, const EfectAudio& efect) {
    efect.afiseaza(os);
    return os;
}