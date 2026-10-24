#pragma once //ca sa fie compilat directiva o singura data

#include <iostream>
#include <string>
#include <cstddef>

class EfectAudio {
    private:
       std::string nume;
       bool activ;
       virtual void descriere(std::ostream& os)const;
    //metoda virtuala prin care derivatele o pot suprascrie folosind friend
    public:
    EfectAudio(std::string nume, bool activ=true);
    virtual ~EfectAudio()=default;
    virtual EfectAudio* clone() const=0;
    virtual void proceseaza(float* buffer,std::size_t dimensiune)=0;
    void afiseaza(std::ostream& os)const;
    const std::string& getNume() const;
    bool esteActiv() const;
    friend std::ostream& operator<<(std::ostream& os, const EfectAudio& efect);
    
};