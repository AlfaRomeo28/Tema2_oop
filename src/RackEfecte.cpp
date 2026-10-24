#include "../include/RackEfecte.h"
#include "../include/FiltruTreceJos.h"
#include "../include/ExceptiiAudio.h"
#include <utility>


int RackEfecte::contorProcesariTotale = 0;

RackEfecte::RackEfecte(int capacitate)
    : capacitate(capacitate), dimensiune(0) {
    if (this->capacitate <= 0) {
        throw ParametruAudioDepasitException("Capacitatea rack-ului trebuie sa fie strict pozitiva.");
    }
    sloturi = new EfectAudio*[this->capacitate];
    for (int i = 0; i < this->capacitate; ++i) {
        sloturi[i] = nullptr;
    }
}

RackEfecte::~RackEfecte() {
    for (int i = 0; i < dimensiune; ++i) {
        delete sloturi[i];
    }
    delete[] sloturi;
}

//  aloca un array nou și clonează polimorfic fiecare element
RackEfecte::RackEfecte(const RackEfecte& other)
    : capacitate(other.capacitate), dimensiune(other.dimensiune) {
    sloturi = new EfectAudio*[capacitate];
    for (int i = 0; i < capacitate; ++i) {
        if (i < dimensiune && other.sloturi[i] != nullptr) {
            sloturi[i] = other.sloturi[i]->clone();
        } else {
            sloturi[i] = nullptr;
        }
    }
}

// Idiomul Copy-and-Swap
void swap(RackEfecte& first, RackEfecte& second) noexcept {
    using std::swap;
    swap(first.sloturi, second.sloturi);
    swap(first.capacitate, second.capacitate);
    swap(first.dimensiune, second.dimensiune);
}

RackEfecte& RackEfecte::operator=(RackEfecte other) {
    swap(*this, other);
    return *this;
}

void RackEfecte::adaugaEfect(const EfectAudio& efect) {
    if (dimensiune >= capacitate) {
        throw CapacitateRackDepasitaException();
    }
    sloturi[dimensiune] = efect.clone();
    ++dimensiune;
}

void RackEfecte::proceseazaSemnal(float* buffer, std::size_t lungimeBuffer) {
    if (buffer == nullptr || lungimeBuffer == 0) {
        throw BufferInvalidException();
    }

    // Apelul funcției virtuale prin pointer de baza
    for (int i = 0; i < dimensiune; ++i) {
        if (sloturi[i] != nullptr) {
            sloturi[i]->proceseaza(buffer, lungimeBuffer);
        }
    }

    ++contorProcesariTotale;
}

void RackEfecte::calibreazaToateFiltrele(float frecventaNoua) {
    // Parcurgerea pointerilor de baza și folosirea dynamic_cast 
    for (int i = 0; i < dimensiune; ++i) {
        if (sloturi[i] != nullptr) {
            auto* filtru = dynamic_cast<FiltruTreceJos*>(sloturi[i]);
            if (filtru != nullptr) {
                filtru->calibreazaFrecventa(frecventaNoua);
            }
        }
    }
}

void RackEfecte::afiseazaRack(std::ostream& os) const {
    os << "=== Stare Rack Audio (Efecte conectate: " << dimensiune << "/" << capacitate << ") ===\n";
    for (int i = 0; i < dimensiune; ++i) {
        os << "Slot [" << i << "]: ";
        if (sloturi[i] != nullptr) {
            sloturi[i]->afiseaza(os);
        }
        os << "\n";
    }
}

int RackEfecte::getContorProcesariTotale() {
    return contorProcesariTotale;
}

int RackEfecte::getDimensiune() const {
    return dimensiune;
}

int RackEfecte::getCapacitate() const {
    return capacitate;
}