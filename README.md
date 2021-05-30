# 3-oji-užduotis

1. Funkcijų assign(), push_back(), pop_back(), size(), capacity(), reserve() ir clear() testasvimas:
```
std::vector.assign(3,123): 123 123 123 
Vector.assign(3,123): 123 123 123
std::vector.push_back(5): 123 123 123 10 
Vector.push_back(5): 123 123 123 10
std::vector.pop_back(): 123 123 123
Vector.pop_back(): 123 123 123
std::vector dydis: 3
Vector dydis: 3
std::vector capacity() po reserve(50): 50
Vector capacity() po reserve(50): 50
std::vector dydis po clear(): 0
Vector dydis po clear(): 0
```

2. Spartos analizė užpildant std::vector ir mano sukurtą vektorių 10000, 100000, 1000000, 10000000 ir 100000000 dydžio int'ais:

| Tipas | 10000 | 100000 | 1000000 | 10000000 | 100000000 |
| --- | --- | --- | --- | --- | --- |
| std::vector | 0 | 0.0019971 | 0.0199794 | 0.188328 | 1.81993 |
| sukurtas vector | 0 | 0.0019983 | 0.0199817 | 0.20515 | 2.04444 |

3. Atminties perskirstymai su 100000000 dydžio failu, kai size() == capacity() įvyko 28 kartus.

4. Spartos analizė, naudojant duomenų failą su 100000 studentų įrašų:

| Tipas | Nuskaitymas | Rūšiavimas | Benrai |
| --- | --- | --- | --- |
| std::vector | 0.324573 | 0.0983918 | 1.00449 |
| sukurtas vector | 0.33669 | 0.0731757 | 0.96074 
