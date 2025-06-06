#include <iostream>
#include <algorithm>
#include <fstream>
#include <cmath>
#include <locale>
#include <fstream>
#include "./struktury/hash_table.hh"
#include "testy.hh"
#include "wczytaj.hh"

int main(){
  DynamicArray<Pair> ludzie = wczytajCSV("./dane/meskie.csv");
  DynamicArray<Pair> kobiety = wczytajCSV("./dane/zenskie.csv");

  size_t arraysize = kobiety.get_size();
  for(size_t i=0;i<arraysize;i++){
    ludzie.push_back(kobiety[i]);
  }
  arraysize = ludzie.get_size();
  std::cout << "Zmergowano tablice" << std::endl;
  std::cout << ludzie.at_position(0) << std::endl;
  std::cout << ludzie[0] << std::endl;
  std::setlocale(LC_ALL, "en_US.utf8"); //dzialaaaaa dziala dziala dziala
  //z tymi haszami dziala, nie zalecalbym dawac tu tego modulo bo daje tylko maly zakres i bedzie czesto sie zapetlac
  // CuckooStrategy mapa(fnv_1, djb2, 100000);
  LinkStrategy mapa(fnv_1);
  for(size_t xxx=0;xxx<10000;xxx++) {
    mapa.insert(ludzie[xxx]);
    //plik << xxx << ";" << fnv_1(ludzie[xxx].get_val(), 100000) << std::endl;
  }
  
  // mapa._show();
  // ISTNIEJĄCE
  // std::cout << ludzie[0].get_val() << std::endl;
  for(int i = 40; i < 45; ++i) {
    std::cout << "Poszukuje " << ludzie[i] << std::endl;
    std::cout << "POZYCJA: " << mapa.search(ludzie[i].get_val()) << std::endl;
    std::cout << "Jest " << mapa.get_val(ludzie[i].get_val()) << " ludzi o imieniu: " << ludzie[i] << std::endl;
  }
  // NIEISTNIEJĄCY
  try {
    size_t elo = mapa.search(L"Arrur");
    std::cout << "POZYCJA: " << elo << std::endl;
  } catch (const std::out_of_range& err){
    std::cout << "Błąd: " << err.what() << std::endl;
  }
  try {
    int ilosc = mapa.get_val(L"Arrur");
    std::cout << "JEST " << ilosc << " Arrurów" << std::endl;
  } catch (const std::out_of_range& err){
    std::cout << "Błąd: " << err.what() << std::endl;
  }
  return 0;
}
