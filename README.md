# TrendSetter — Simulator de Influență și Stil

Proiectul simulează parcursul unui influencer în industria modei, gestionând resursele financiare și stilul personal pentru a atinge succesul în mediul online și la evenimente exclusiviste.

## Scopul jocului

Jucătorul (Influencerul) trebuie să își construiască o garderobă strategică, achiziționând piese vestimentare și accesorii care să îi maximizeze scorul de impact. Obiectivul este acumularea unui punctaj total de stil suficient de mare pentru a participa la evenimente de prestigiu (Gala, Street-Style, Business) și pentru a câștiga followeri.

## Logica și regulile jocului

- **Resurse inițiale:** Influencerul pornește cu un nume și un buget inițial definit de utilizator.
- **Garderoba:** Este formată din piese vestimentare împărțite în mai multe categorii, fiecare având un impact diferit asupra scorului final:
  - **Haine:** Oferă bonusuri în funcție de material (ex: Mătasea aplică un multiplicator x1.5, Pielea x1.4, Casmirul x1.3) și funcționalitate (hainele impermeabile adaugă +15 puncte).
  - **Încălțăminte:** Influențează scorul prin nivelul de confort — formula: `punctajStil + (confort * 2)`.
  - **Bijuterii:** Obiecte de lux cu multiplicator în funcție de metal — Platină x3.0, Aur x2.5, Argint x1.5.
  - **Accesorii:** Elementele de lux dublează impactul (x2.2), cele standard rămân la valoarea de bază.
- **Sistemul de achiziții:**
  - Fiecare piesă are un preț de bază. Dacă bugetul scade sub prețul piesei dorite, sistemul aruncă o excepție `BugetInsuficientException` și tranzacția este anulată.
  - Piesele sunt gestionate prin pointeri inteligenți (`std::unique_ptr`), eliminând gestiunea manuală a memoriei.
  - Piesele pot fi adăugate manual sau selectate dintr-un **catalog predefinit** generat prin Factory.
- **Calculul punctajului (Impactul):**
  - Scorul fiecărei piese se bazează pe un punctaj de stil de bază (0–100) la care se aplică modificatori specifici tipului.
  - La participarea la un eveniment, piesele recomandate pentru acel eveniment primesc un **multiplicator suplimentar x1.5**.
  - Algoritmul de calcul al scorului total este interschimbabil prin **Strategy Pattern**:
    - `Scor Simplu` — suma tuturor impacturilor
    - `Scor Medie` — media impacturilor (util pentru comparații între garderobe de dimensiuni diferite)
    - `Scor Top-3` — suma celor mai bune 3 piese (simulează impactul unei ținute selective)
- **Evenimente:**
  - Tipuri disponibile: `Gala`, `Street-Style`, `Business`.
  - Fiecare tip recomandă anumite categorii de piese (ex: Gala favorizează Haine, Bijuterii și Accesorii).
  - Utilizatorul setează un prag de succes — dacă scorul depășește pragul, influencerul devine **VIRAL**.
- **Persistența datelor:**
  - Garderoba este salvată și încărcată dintr-un fișier `garderoba.csv`, permițând continuarea sesiunii anterioare.

## Ierarhia de clase

```
PiesaVestimentara  (clasă abstractă — baza ierarhiei)
├── Haina          (material, impermeabilă)
├── Incaltaminte   (mărime, nivel confort)
├── Accesoriu      (tip, de lux)
└── Bijuterie      (metal, cantitate)
```

## Alte clase și mecanisme

- **Garderoba** — clasa de gestiune: deține colecția de piese, gestionează bugetul, orchestrează operațiile.
- **Eveniment** — encapsulează logica unui eveniment: tip, piese recomandate, multiplicator de scor.
- **TrendsetterException** — ierarhie proprie de excepții:
  - `BugetInsuficientException`
  - `PiesaInvalidaException`
  - `EvenimentInexistentException`
  - `FisierException`
- **Clone Pattern** — metodă virtuală `clone()` pentru deep copy polimorfic, folosită la copierea `Garderoba`.

## Cerințe T3 — Programare Generică și Design Patterns

### Clasă șablon — `Colectie<T>`

Clasa generică `Colectie<T>` din `Colectie.hpp` funcționează cu orice tip de date și oferă:
- `adauga(T)` — adaugă un element
- `filtreaza(Predicat)` — returnează o nouă colecție cu elementele care satisfac condiția
- `sorteaza(Comparator)` — sortează după un criteriu dat
- `elimina(Predicat)` — elimină elementele care satisfac condiția

Exemplu de utilizare cu `string`:
```cpp
Colectie<std::string> branduri;
branduri.adauga("Gucci");
branduri.adauga("Zara");
auto lux = branduri.filtreaza([](const std::string& b) { return b.size() > 4; });
```

### Funcție șablon liberă — `filtrareVector<T>`

Funcție template normală/liberă definită în `Colectie.hpp` care filtrează orice `std::vector` după un predicat:
```cpp
template <typename T, typename Predicat>
std::vector<T> filtrareVector(const std::vector<T>& sursa, Predicat p);
```

### Design Pattern 1: Factory — `PiesaFactory`

Clasa `PiesaFactory` din `PiesaFactory.hpp` centralizează crearea obiectelor derivate din `PiesaVestimentara`. Codul client nu mai include headerele claselor concrete și nu cunoaște detaliile constructorilor.

```cpp
// Creare dupa tip
auto p = PiesaFactory::creeaza("Haina", "Rochie", "Versace", 1200, 95, "Matase", "0");

// Catalog predefinit
auto p2 = PiesaFactory::rochieDeGala();
auto p3 = PiesaFactory::sneakersCasual();
```

Respectă principiul **Open-Closed** — adăugarea unei noi derivate necesită modificarea doar a Factory.

### Design Pattern 2: Strategy — `ScoreStrategy`

Interfața `ScoreStrategy` din `ScoreStrategy.hpp` permite înlocuirea algoritmului de calcul al scorului fără modificarea clasei `Garderoba`.

```cpp
// Schimba algoritmul la runtime
garderoba.setStrategy(ScoreStrategyFactory::creeaza("top3"));
```

Respectă principiile **Open-Closed** și **Dependency Inversion** din SOLID — `Garderoba` depinde de interfață, nu de implementări concrete.

## Structura proiectului

```
├── main.cpp
├── garderoba.csv              # date persistente
├── PiesaVestimentara.hpp/cpp  # clasa abstracta de baza
├── Haina.hpp/cpp
├── Incaltaminte.hpp/cpp
├── Accesoriu.hpp/cpp
├── Bijuterie.hpp/cpp
├── Garderoba.hpp/cpp          # clasa de gestiune
├── Eveniment.hpp/cpp          # logica evenimentelor
├── Exceptii.hpp               # ierarhie de exceptii
├── Colectie.hpp               # clasa sablon 
├── PiesaFactory.hpp           # Factory pattern 
└── ScoreStrategy.hpp          # Strategy pattern 
```
