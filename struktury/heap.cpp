#include "heap.hh"
#include <iostream>

void Heap::heapify_up(size_t i) {
  while (i > 0) {
    size_t rodzic = (i - 1) / 2;
    if (dane[i] <= dane[rodzic]) {
      break; //własność kopca przywrócona
    }
    Pair mem = dane[i];
    dane[i] = dane[rodzic];
    dane[rodzic] = mem;
    i = rodzic;
  }
}

void Heap::heapify_down(size_t i) {
  size_t rodzic = i;
  size_t l = 2 * i + 1; //lewe dziecko = 2*i + 1
  size_t p = 2 * i + 2; //prawe = 2*i + 2
 
  if (l < dane.get_size() && dane[l] > dane[rodzic])
    rodzic = l;
 
  if (p < dane.get_size() && dane[p] > dane[rodzic])
    rodzic = p;
  //teraz najwiekszy z tych trzech jest faktycznie jako rodzic, tylko zamienic
    
  //jesli i to nie rodzic to jest zle
  if (rodzic != i) {
    Pair mem = dane[i];
    dane[i] = dane[rodzic];
    dane[rodzic] = mem;
    
    //rekurencyjnie, jakby nowe dziecko dodane na largest naruszalo poddrzewo ponizej
    heapify_down(rodzic);
  }
}

void Heap::insert(Pair val) {
  dane.push_back(val);
  heapify_up(dane.get_size()-1);
}

Pair Heap::extract_max() {
  Pair rezultat = dane[0];
  dane[0] = dane[dane.get_size()-1];
  dane[dane.get_size()-1] = rezultat;
  dane.remove_back();
  if(dane.get_size() > 0)
    heapify_down(0);

  return rezultat;
}

Pair& Heap::find_max() {
  return dane[0];
}

Pair* Heap::find(const wchar_t* val) {
  if(val == nullptr) return nullptr;
  
  for(size_t i = 0; i < dane.get_size(); ++i) {
    if (wcsncmp(dane[i].get_val(), val, VAL_SIZE) == 0) {
      return &dane[i];
    }
  }
  
  return nullptr;
}

void Heap::decrease_key(const wchar_t* val, int i) {
  Pair* zmieniany = find(val);
  if(zmieniany != nullptr)
    zmieniany->set_key(zmieniany->get_key()-i);
}

void Heap::increase_key(const wchar_t* val, int i) {
  decrease_key(val, -i);
}

void Heap::modify_key(const wchar_t* val, int k) {
  for (size_t i = 0; i < size(); ++i) {
    if (wcsncmp(dane[i].get_val(), val, VAL_SIZE) == 0) {
      int stary_klucz = dane[i].get_key();
      dane[i].set_key(k);
      if (k > stary_klucz) //nowy wiekszy, wiec trzeba go przesunac w gore
        heapify_up(i);
      else
        heapify_down(i);
      return;
    }
  }
}

void Heap::build(DynamicArray<Pair>& tablica) {
  dane = tablica;
  //od ostatniego nie-liścia do korzenia
  for (int i = dane.get_size()/2 - 1; i >= 0; --i) {
    heapify_down(i);
  }
}

void Heap::build(std::initializer_list<Pair> lista) {
  dane = DynamicArray<Pair>(); //czyszczonko

  //do danych
  for (const Pair& para : lista) {
    dane.push_back(para);
  }

  //kopcowanie
  for (int i = dane.get_size() / 2 - 1; i >= 0; --i) {
    heapify_down(i);
  }
}
