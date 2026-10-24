#pragma once
#include <exception>  //gestionare erorilor ce apar in timpul executarii
#include <string>

class EroareAudio : public std::exception {
    private:
         std::string mesaj;
    public:
       explicit EroareAudio(std::string mesaj); //previne crearea accidentale de obiect
       const char* what() const noexcept override;
};

//Categoria 1: parametru numeric invalid (aruncată în constructorul derivatelor)

class ParametruAudioDepasitException : public EroareAudio {
    public:
        explicit ParametruAudioDepasitException(const std::string& detalii);
};

// Categoria 2: date audio inexistente sau pointer invalid (aruncată la procesare)

class BufferInvalidException : public EroareAudio {
    public:
          BufferInvalidException();

};

// Categoria 3: limita de capacitate a managerului atinsă (aruncată în manager)

class CapacitateRackDepasitaException : public EroareAudio {
public:
    CapacitateRackDepasitaException();
};