#include "EfectAudio.h"
#include "EfectEcou.h"
#include "EfectDistorsie.h"
#include "FiltruTreceJos.h"
#include "EfectReverb.h"
#include <cassert>
#include <iostream>

int main() {
    // Test EfectEcou 
    EfectEcou ecou("EcouTest", true, 5, 0.4f);
    assert(ecou.getNume() == "EcouTest");
    assert(ecou.esteActiv() == true);
    assert(ecou.getDelaySamples() == 5);
    assert(ecou.getFeedback() > 0.39f && ecou.getFeedback() < 0.41f);

    // Test EfectDistorsie 
    EfectDistorsie dist("DistTest", true, 0.8f, 2.0f);
    assert(dist.getPragClipping() > 0.79f && dist.getPragClipping() < 0.81f);
    assert(dist.getGain() > 1.99f && dist.getGain() < 2.01f);

    // Test FiltruTreceJos 
    FiltruTreceJos filtru("FiltruTest", true, 1000.0f, 0.5f);
    assert(filtru.getFrecventaCutoff() > 999.0f && filtru.getFrecventaCutoff() < 1001.0f);
    assert(filtru.getCoeficientAtenuare() > 0.49f && filtru.getCoeficientAtenuare() < 0.51f);

    // Test EfectReverb 
    EfectReverb reverb("ReverbTest", true, 0.7f, 1.5f);
    assert(reverb.getMarimeCamera() > 0.69f && reverb.getMarimeCamera() < 0.71f);
    assert(reverb.getTimpDecadere() > 1.49f && reverb.getTimpDecadere() < 1.51f);

    std::cout << "Toate testele unitare si getterele au fost verificate cu succes!\n"<<std::flush;
    return 0;
}
