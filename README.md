# Audio Processor - Pipeline Polimorfic de Procesare Audio

### De ce am ales aceasta tema?
Am ales dezvoltarea unui procesor de efecte audio deoarece semnalele sonore reprezinta un caz ideal din lumea reala pentru aplicarea principiilor fundamentale de Programare Orientata pe Obiecte (OOP). Intr-un lant de procesare de studio (pedalboard / rack), fiecare modul de efect audio trebuie sa primeasca un semnal comun (un flux de esantioane `float*`), sa il modifice conform unei functii matematice proprii si sa il transmita mai departe, pastrand o interfata unitara.

Aceasta arhitectura ofera o reprezentare naturala si practica pentru:
1. **Polimorfism la executie**: Tratarea uniforma a diferitelor efecte prin pointeri catre o clasa de baza comuna.
2. **Gestiunea riguroasa a memoriei native**: Prelucrarea directa a bufferelor de date si utilizarea idiomului Copy-and-Swap pentru un container dinamic dedicat (`RackEfecte`), demonstrand alocarea si eliberarea corecta a resurselor fara scurgeri de memorie.
3. **Principiul Open/Closed (OCP)**: Posibilitatea de a adauga tipuri noi de procesoare de sunet (cum ar fi modului de reverb) prin simpla extindere a ierarhiei, fara a rescrie sau altera logica containerului existent.
4. **Tratarea robusta a starilor de eroare**: Separarea responsabilitatilor prin validarea domeniului parametrilor fizici si a pointerilor de date prin exceptii specifice.

---

## Schema Arhitecturii si Relatiilor dintre Clase

```text
               +-----------------------------------------+
               |             std::exception              |
               +--------------------+--------------------+
                                    |
               +--------------------+--------------------+
               |              EroareAudio                |
               +---------+----------+----------+---------+
                         |          |          |
         +---------------+          |          +----------------+
         |                          |                           |
+--------+-----------------+ +------+------------------+ +------+------------------------+
| ParametruAudioDepasitEx. | | BufferInvalidException  | | CapacitateRackDepasitaExcept. |
+--------------------------+ +-------------------------+ +-------------------------------+

==========================================================================================

                             +-----------------------+
                             |      EfectAudio       | (Clasa Abstracta / Baza)
                             +-----------------------+
                             | - nume: string        |
                             | - activ: bool         |
                             +-----------------------+
                             | + clone()             | [Virtual Pura]
                             | + proceseaza()        | [Virtual Pura - Business Logic]
                             | + afiseaza()          | [Non-virtuala - NVI]
                             | - descriere()         | [Virtuala Privata]
                             +-----------+-----------+
                                         |
         +-------------------------------+-------------------------------+
         |                               |                               |
+--------+--------+             +--------+--------+             +--------+--------+
|    EfectEcou    |             | EfectDistorsie  |             | FiltruTreceJos  |
+-----------------+             +-----------------+             +-----------------+
| - delaySamples  |             | - pragClipping  |             | - frecvCutoff   |
| - feedback      |             | - gain          |             | - coefAtenuare  |
+-----------------+             +-----------------+             +-----------------+
| + clone()       |             | + clone()       |             | + clone()       |
| + proceseaza()  |             | + proceseaza()  |             | + proceseaza()  |
| - descriere()   |             | - descriere()   |             | - descriere()   |
+-----------------+             +-----------------+             | + calibreaza()  | (Metoda
                                                                +-----------------+  specifica)
                                                                         ^
=========================================================================|================
                                                                         |
                             +-----------------------+                   |
                             |      RackEfecte       |                   |
                             +-----------------------+                   |
                             | - sloturi: EfectAudio** |                 |
                             | - capacitate: int     |                   |
                             | - dimensiune: int     |                   |
                             | - contorProcesariTot. | [Static]          |
                             +-----------------------+                   |
                             | + adaugaEfect()       | ---> foloseste clone()
                             | + proceseazaSemnal()  | ---> apeleaza efect->proceseaza()
                             | + calibreazaFiltre()  | ---> dynamic_cast pe FiltruTreceJos
                             | + operator=           | ---> Copy-and-Swap
                             +-----------------------+