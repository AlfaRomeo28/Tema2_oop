#pragma once

#include "EfectAudio.h"
#include <cstddef>
#include <iostream>

class RackEfecte {
private:
    EfectAudio** sloturi;
    int capacitate;
    int dimensiune;


    static int contorProcesariTotale;

public:

    explicit RackEfecte(int capacitate = 5);
    ~RackEfecte();


    RackEfecte(const RackEfecte& other);

    //  friend swap pentru idiomul Copy-and-Swap
    friend void swap(RackEfecte& first, RackEfecte& second) noexcept;

    // operator de atribuire prin Copy-and-Swap (pass-by-value)
    RackEfecte& operator=(RackEfecte other);

    // Adaugare polimorfica (folosește clone())
    void adaugaEfect(const EfectAudio& efect);

    // Apelul functiei virtuale prin pointer de baza
    void proceseazaSemnal(float* buffer, std::size_t lungimeBuffer);


    void calibreazaToateFiltrele(float frecventaNoua);

    // Afișare completă a lanțului de efecte
    void afiseazaRack(std::ostream& os) const;


    static int getContorProcesariTotale();

    int getDimensiune() const;
    int getCapacitate() const;
};