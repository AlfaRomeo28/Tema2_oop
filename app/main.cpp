#include <iostream>
#include "../include/EfectEcou.h"
#include "../include/EfectDistorsie.h"
#include "../include/FiltruTreceJos.h"
#include "../include/RackEfecte.h"
#include "../include/ExceptiiAudio.h"
#include "../include/EfectReverb.h"

//  afisarea continutului unui semnal audio
void printeazaSemnal(const char* eticheta, const float* buffer, std::size_t dimensiune) {
    std::cout << eticheta << ": [ ";
    for (std::size_t i = 0; i < dimensiune; ++i) {
        std::cout << buffer[i] << (i + 1 < dimensiune ? ", " : " ");
    }
    std::cout << "]\n";
}

int main() {
    std::cout << "=== TEST 1: Creare obiecte si adaugare in Rack (Clone) ===\n";
    try {
        // Instantiere rack cu o capacitate de 4 sloturi
        RackEfecte rackPrincipal(4);

        // Instantiere obiecte din derivate (constructorii valideaza parametrii)
        EfectEcou ecouChitara("Tape Delay", true, 2, 0.4f);
        EfectDistorsie overdrive("Tube Screamer", true, 0.8f, 2.0f);
        FiltruTreceJos filtruBas("Cab Simulator", true, 4500.0f, 0.6f);
        EfectReverb reverbSala("Hall Reverb", true, 0.75f, 2.5f);
        EfectReverb reverbSala("Hall Reverb", true, 0.75f, 2.5f);
        EfectReverb reverbSala("Hall Reverb", true, 0.75f, 2.5f);

        //  polimorfics in container (se fac copii profunde prin clone())
        rackPrincipal.adaugaEfect(ecouChitara);
        rackPrincipal.adaugaEfect(overdrive);
        rackPrincipal.adaugaEfect(filtruBas);
        rackPrincipal.adaugaEfect(reverbSala);

        // Afisare rack (apeleaza interfața non-virtuala afiseaza descrierea)
        rackPrincipal.afiseazaRack(std::cout);

        std::cout << "\n=== TEST 2: Procesare Semnal Audio prin Polimorfism ===\n";
        float semnalAudio[] = {0.1f, 0.5f, 0.9f, 0.3f, -0.7f, 1.2f};
        const std::size_t marimeSemnal = sizeof(semnalAudio) / sizeof(semnalAudio[0]);

        printeazaSemnal("Semnal initial", semnalAudio, marimeSemnal);

        // Fiecare efect din lant modifica semnalul prin apelul virtual proceseaza()
        rackPrincipal.proceseazaSemnal(semnalAudio, marimeSemnal);

        printeazaSemnal("Semnal dupa procesare", semnalAudio, marimeSemnal);

        std::cout << "\n=== TEST 3: Dynamic Cast (Recalibrare Filtre Trece-Jos) ===\n";
        rackPrincipal.calibreazaToateFiltrele(2500.0f);
        rackPrincipal.afiseazaRack(std::cout);

        std::cout << "\n=== TEST 4: Copy Constructor si Copy-and-Swap ===\n";

        RackEfecte copieRack = rackPrincipal;
        std::cout << "Copie creata cu succes. Capacitate copie: " << copieRack.getCapacitate()
                  << ", Efecte: " << copieRack.getDimensiune() << "\n";


        RackEfecte altRack(2);
        altRack = copieRack;
        std::cout << "Atribuire finalizata cu succes pe noul rack.\n";

        std::cout << "\n=== TEST 5: Contor Static ===\n";
        std::cout << "Total apeluri de procesare inregistrate: "
                  << RackEfecte::getContorProcesariTotale() << "\n";

    } catch (const EroareAudio& e) {
        std::cerr << "Exceptie audio prinsa: " << e.what() << "\n";
    } catch (const std::exception& e) {
        std::cerr << "Exceptie standard: " << e.what() << "\n";
    }

    std::cout << "\n=== TEST 6: Demonstratie Aruncare Exceptii (Tratare Erori) ===\n";

    //  Parametru invalid aruncat direct în constructor
    try {
        std::cout << "Incercare instantiere EfectEcou cu feedback invalid (> 1.0)...\n";
        EfectEcou ecouGresit("Ecou Defect", true, 2, 1.8f);
    } catch (const ParametruAudioDepasitException& e) {
        std::cout << "Prins cu succes: " << e.what() << "\n";
    }

    //  Buffer invalid transmis la procesare
    try {
        std::cout << "Incercare procesare semnal cu pointer nullptr...\n";
        RackEfecte rackTest(2);
        rackTest.proceseazaSemnal(nullptr, 0);
    } catch (const BufferInvalidException& e) {
        std::cout << "Prins cu succes: " << e.what() << "\n";
    }

    // Depașire capacitate rack
    try {
        std::cout << "Incercare adaugare peste capacitatea maxima a rack-ului...\n";
        RackEfecte rackMic(1);
        EfectDistorsie d1("D1", true, 0.5f, 1.5f);
        EfectDistorsie d2("D2", true, 0.5f, 1.5f);
        rackMic.adaugaEfect(d1);
        rackMic.adaugaEfect(d2); // aici se va arunca excepția
    } catch (const CapacitateRackDepasitaException& e) {
        std::cout << "Prins cu succes: " << e.what() << "\n";
    }

    std::cout << "\nToate testele au fost executate.\n";
    return 0;
}