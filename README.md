# 3-oji-užduotis

Funkcijos:
```
template <class T> void Vector<T>::clear(){
    iterator it = avail;
    while (it != data) alloc.destroy(--it);
    alloc.deallocate(data, limit - data);
    data = limit = avail = nullptr;
}
```

Spartos analizė užpildant std::vector ir mano sukurtą vektorių 10000, 100000, 1000000, 10000000 ir 100000000 dydžio int'ais:
| Tipas | 10000 | 100000 | 1000000 | 10000000 | 100000000 |
| --- | --- | --- | --- | --- | --- |
| std::vector | 0 | 0.0019971 | 0.0199794 | 0.188328 | 1.81993 |
| sukurtas vector | 0 | 0.0019983 | 0.0199817 | 0.20515 | 2.04444 |
