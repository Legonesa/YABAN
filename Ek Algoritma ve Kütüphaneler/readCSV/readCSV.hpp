
/*      Bu CSV dosyalarını okumak için takımımız tarafından geliştirilen bir kütüphanedir.        
                      Bu kütüphane YABAN Projesi için geliştirilmiştir.                     */

#ifndef READCSV_HPP
#define READCSV_HPP
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <variant>

class DataSet {
public:
    DataSet(const char* fileName); // Dosyayı açar.
    void readCSV(); // Dosyayı okur.
    void readCSVinRange(int begin, int end); // Belirli bir satır aralığını okur.
    void readCSVRow(int row); // Bir satırı okur.
    void readCSVCategory(std::string category); // Bir kategoriyi okur.
    void readCSVCategoryinRange(std::string category, int begin, int end); // Bir kategorideki belirli bir satır aralığını okur.
    void readCSVCategoryinRow(std::string category, int row); // Bir kategorideki satırı okur.
    long double getValueNum(std::string category, int row); // Okunmuş değerlerden birisini verir. (Sayısal değer.)
    std::string getValueStr(std::string category, int row); // Okunmuş değerlerden birisini verir. (Metinsel değer.)
    std::string getCategoryName(int CategoryIndex); // Belirtilen sıradaki kategorinin ismini verir.
    void freeMemory(); // Hafızayı boşaltır.
private:
    const char* file;
    std::map<std::string, std::map<int, std::string>> values;
};

#endif