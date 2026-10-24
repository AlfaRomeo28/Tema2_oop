#include <iostream>
#include <vector>
#include "EfectAudio.h"
#include "EfectEcou.h"
#include "EfectDistorsie.h"
#include "FiltruTreceJos.h"
#include "EfectReverb.h"
#include "RackEfecte.h"
#include "ExceptiiAudio.h"

int main() {
    try {
        RackEfecte rack(5);

        EfectEcou ecou("Tape Delay", true, 2, 0.4f);
        EfectDistorsie dist("Tube Screamer", true, 0.8f, 2.0f);
        FiltruTreceJos filtru("Cab Simulator", true, 3000.0f, 0.6f);
        EfectReverb reverb("Hall Reverb", true, 0.75f, 2.5f);

        rack.adaugaEfect(ecou);
        rack.adaugaEfect(dist);
        rack.adaugaEfect(filtru);
        rack.adaugaEfect(reverb);

        std::vector<float> buffer = {0.1f, 0.5f, -0.3f, 0.8f, -0.2f};
        rack.proceseazaSemnal(buffer.data(), buffer.size());
        rack.calibreazaToateFiltrele(2500.0f);

        // Test copiere
        RackEfecte copie = rack;

        // Test tratare exceptie
        try {
            EfectEcou ecouGresit("EcouGresit", true, 2, 1.5f);
        } catch (const EroareAudio&) {
            
        }

        std::cout << "Executie finalizata cu succes.\n";
    } catch (const std::exception& e) {
        std::cerr << "Eroare: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
