#include "../include/ExceptiiAudio.h"
#include <utility>

EroareAudio::EroareAudio(std::string mesaj)
    : mesaj(std::move(mesaj)) {}  //fara asta practic se aloca pe heap memorie noua si se duplica fiecare caracter

const char* EroareAudio::what() const noexcept {
    return mesaj.c_str(); //returneaza un pointer constant la un sir de caractere
}

ParametruAudioDepasitException::ParametruAudioDepasitException(const std::string& detalii)
    : EroareAudio("Eroare parametru audio invalid: " + detalii) {}

BufferInvalidException::BufferInvalidException()
    : EroareAudio("Eroare buffer audio: pointer nul sau dimensiune zero.") {}

CapacitateRackDepasitaException::CapacitateRackDepasitaException()
    : EroareAudio("Eroare rack audio: s-a depasit capacitatea maxima alocata.") {}