#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <iostream>
#include <vector>
#include <memory>
#include <fstream>
#include <chrono>
#include <time.h>
#include <list>

using std::cout;
using std::endl;
using std::uninitialized_fill;
using std::uninitialized_copy;

template <class T> class Vector {
    public:
	typedef T* iterator;
	typedef const T* const_iterator;
	typedef size_t size_type;
	typedef T value_type;

    // Konstruktoriai:
	Vector() { create(); } // create - uz atminties isskyrima
	explicit Vector(size_type n, const T& val = T{}) { create(n, val); }

    // Kopijavimo konstruktorius:
    Vector(const Vector& v){create(v.begin(), v.end());}

    // Priskyrimo operatorius:
    Vector& operator=(const Vector&);

    // Destruktorius:
    ~Vector() {uncreate();}

    // Indeksavimas:
    T& operator[](size_type i) {return data[i];}
    const T& operator[](size_type i) const {return data[i];}

    // Funkcijos:

    void push_back(const T& val) {
        if (avail == limit) 
		    grow();				   // jei reikia, isskiriama vietos
	    unchecked_append(val); // ideda nauja elementa
    }
    

    void pop_back(){
        alloc.destroy(--avail);
    }

    void clear() {
        iterator it = avail;
        while (it != data) alloc.destroy(--it);
        alloc.deallocate(data, limit - data);
        data = limit = avail = nullptr;
    }

    void assign (size_type size, const T& val) {
    uncreate();
    create(size, val);
    }

    void reserve(size_type size){
    if(size>capacity()){
     grow(size);
    }
    }

    // Funkcijos grąžinančios iteratorius:
    size_type size() const {return avail - data;}
    iterator begin() { return data; } 
    const_iterator begin() const { return data; } 
    iterator end() { return avail; } 
    const_iterator end() const { return avail; } 
    size_type capacity() const { return limit - data;}

    private:
	iterator data;	// pirmasis Vector elementas
	iterator avail; // pirmasis po paskutiniojo SUKONSTRUOTO Vector elementas
	iterator limit;	// pirmasis po paskutiniojo Vector elementas

	std::allocator<T> alloc; // objektas atminties valdymui

	// isskirti atminti (array) ir ja inicializuoti
	void create();
	void create(size_type, const T&);
	void create(const_iterator, const_iterator);

	// sunaikinti elementu array ir atlaisvinti atminti
	void uncreate();

	// pagalbines funkcijos push_back realizacijai
	void grow();
    void grow(size_type new_capacity);
	void unchecked_append(const T&);
};


// priskyrimo operatoriaus realizacija
template <class T>
Vector<T>& Vector<T>::operator=(const Vector& rhs) {
    // patikriname ar ne lygu
    if (&rhs != this) {
        // atlaisviname seną this objekto atmintį
        uncreate();
        // perkopijuojame elementus iš rhs į lhs (this)
        create(rhs.begin(), rhs.end());
        }
    return *this;
}

template<class T> class allocator {
    public:
    T* allocate(size_t); // išskirti `raw` atmintį
    void deallocate(T*, size_t); // atlaisvinti atmintį
    void construct(T*, const T&); // sukonstruoti 1 objektą
    void destroy(T*); // sunaikinti 1 objektą
};

// Nukopijuoja duotą reikšmę į neinicializuota atminties lauką intervale [first, last)
template<class ForwardIt, class T>
void std::uninitialized_fill(ForwardIt first, ForwardIt last, const T& value);

// Nukopijuoja elementą iš intervalo [first, last) į neinicializuota atminties lauką prasidedantį ties d_first
template<class InputIt, class ForwardIt>
ForwardIt std::uninitialized_copy(InputIt first, InputIt last, ForwardIt d_first);

template <class T> void Vector<T>::create() {
    data = avail = limit = nullptr;
}

template <class T> void Vector<T>::create(size_type n, const T& val) {
    data = alloc.allocate(n); // grąžina ptr į array pirmą elementą
     limit = avail = data + n; // sustato rodykles į vietas
     std::uninitialized_fill(data, limit, val); // inicializuoja elementus val reikšme
}

template <class T>
void Vector<T>::create(const_iterator i, const_iterator j) {
     data = alloc.allocate(j - i); // išskirti vietos j-i elementams
     limit = avail = std::uninitialized_copy(i, j, data); // nukopijuoja elementus iš intervalo
}

template <class T> void Vector<T>::uncreate() {
    if (data) {
        // sunaikinti (atbuline tvarka) sukonstruotus elementus
        iterator it = avail;
        while (it != data) alloc.destroy(--it);
            // atlaisvinti išskirtą atmintį. Turi būti data != nullptr
        alloc.deallocate(data, limit - data);
    }
    // reset'inam pointer'iuss - Vector'ius tuščias
    data = limit = avail = nullptr;
}

template <class T> void Vector<T>::grow() {
	// dvigubai daugiau vietos, nei buvo
	size_type new_size = std::max(2 * (limit - data), ptrdiff_t(1));

	// isskirti nauja vieta ir perkopijuoti egzistuojancius elementus
	iterator new_data = alloc.allocate(new_size);
	iterator new_avail = uninitialized_copy(data, avail, new_data);

	// atlaisvinti sena vieta
	uncreate();

	// reset'int rodykles i naujai isskirta vieta
	data = new_data;
	avail = new_avail;
	limit = data + new_size;
}

template <class T> void Vector<T>::grow(size_type new_capacity){
    size_type new_size = std::max(2 * capacity(), new_capacity);
    iterator new_data =alloc.allocate(new_size);
    iterator new_avail = std::uninitialized_copy(data, avail, new_data);

    uncreate();

    data=new_data;
    avail=new_avail;
    limit=data+new_size;
}

// tariame, kad `avail` point'ina i isskirta, bet neinicializuota vieta
template <class T> void Vector<T>::unchecked_append(const T& val) {
	alloc.construct(avail++, val);
}


#endif
