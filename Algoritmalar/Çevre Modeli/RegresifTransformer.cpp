
/*     Bu takımımız tarafından geliştirilen bir Transformer kütüphanesidir.
                Bu kütüphane YABAN Projesi için geliştirilmiştir.
             (Bu versionda Matrix kütüphanesi entegre edilmemiştir.)
    (Matrix kütüphanesinin entegre edildiği versiyon geliştirme aşamasındadır.!)       */

#include <iostream>
#include "RegresifTransformer.hpp"
#include <string>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <vector>
#include <cassert>
#include <random>

// Temeli oluşturur ve dataseti kaydeder.
RegresifTransformer::RegresifTransformer(const char* DataSetName, int SizeOfData, int data_batch) {
    Data = new DataSet(DataSetName);
    DataSize = SizeOfData; batch_size = data_batch;
}

// Değerleri etiketler. (Sözlükler oluşturur.)
void RegresifTransformer::TokenizeData(){
    std::vector<std::string> vocap1, vocap2;
    int readRow = 0;
    while (true) {
        if (readRow + batch_size < DataSize) {
            Data->readCSVinRange(readRow + 1, readRow + batch_size);
            readRow += batch_size;
            for (int b = (readRow + 1) - batch_size; b <= readRow; b++) {
                std::string word = Data->getValueStr(Data->getCategoryName(1), b);
                std::string flood = "";
                for (int i = 0; i < word.length(); i++) {
                    if (word[i] != ' ' && word[i] != ',' && word[i] != '!' && word[i] != '?' && word[i] != '.' && word[i] != ';')
                        flood = flood + (char)std::tolower(word[i]);
                    else {
                        int isThere = false;
                        for (int a = 0; a < vocap1.size(); a++) {
                            if (vocap1[a] == flood) { isThere = true; break; }
                        }
                        if (isThere == false && flood != ""){
                            vocap1.push_back(flood);
                        }
                        if (word[i] != ' ') {
                            flood = word[i];
                            isThere = false;
                            for (int a = 0; a < vocap1.size(); a++) {
                                if (vocap1[a] == flood) { isThere = true; break; }
                            }
                            if (isThere == false) vocap1.push_back(flood);
                        }
                        flood = "";
                    }
                }
                if (word[word.length() - 1] != ' ' && word[word.length() - 1] != ',' && word[word.length() - 1] != '!' && word[word.length() - 1] != '?' && word[word.length() - 1] != '.' && word[word.length() - 1] != ';') {
                    int isThere = false;
                    for (int a = 0; a < vocap1.size(); a++) {
                        if (vocap1[a] == flood) { isThere = true; break; }
                    }
                    if (isThere == false) {
                        vocap1.push_back(flood);
                    }
                    flood = "";
                }
            }
            for (int b = (readRow + 1) - batch_size; b <= readRow; b++) {
                std::string word = Data->getValueStr(Data->getCategoryName(2), b);
                std::string flood = "";
                for (int i = 0; i < word.length(); i++) {
                    if (word[i] != ' ' && word[i] != ',' && word[i] != '!' && word[i] != '?' && word[i] != '.' && word[i] != ';')
                        flood = flood + (char)std::tolower(word[i]);
                    else {
                        int isThere = false;
                        for (int a = 0; a < vocap2.size(); a++) {
                            if (vocap2[a] == flood) { isThere = true; break; }
                        }
                        if (isThere == false && flood != "") vocap2.push_back(flood);
                        if (word[i] != ' ') {
                            flood = word[i];
                            isThere = false;
                            for (int a = 0; a < vocap2.size(); a++) {
                                if (vocap2[a] == flood) { isThere = true; break; }
                            }
                            if (isThere == false) vocap2.push_back(flood);
                        }
                        flood = "";
                    }
                }
                if (word[word.length() - 1] != ' ' && word[word.length() - 1] != ',' && word[word.length() - 1] != '!' && word[word.length() - 1] != '?' && word[word.length() - 1] != '.' && word[word.length() - 1] != ';') {
                    int isThere = false;
                    for (int a = 0; a < vocap2.size(); a++) {
                        if (vocap2[a] == flood) { isThere = true; break; }
                    }
                    if (isThere == false) vocap2.push_back(flood);
                    flood = "";
                }
            }
            Data->freeMemory();
        }
        else {
            Data->readCSVinRange(readRow + 1, DataSize);
            for (int b = readRow + 1; b <= DataSize; b++) {
                std::string word = Data->getValueStr(Data->getCategoryName(1), b);
                std::string flood = "";
                for (int i = 0; i < word.length(); i++) {
                    if (word[i] != ' ' && word[i] != ',' && word[i] != '!' && word[i] != '?' && word[i] != '.' && word[i] != ';')
                        flood = flood + (char)std::tolower(word[i]);
                    else {
                        int isThere = false;
                        for (int a = 0; a < vocap1.size(); a++) {
                            if (vocap1[a] == flood) { isThere = true; break; }
                        }
                        if (isThere == false && flood != "") vocap1.push_back(flood);
                        if (word[i] != ' ') {
                            flood = word[i];
                            isThere = false;
                            for (int a = 0; a < vocap1.size(); a++) {
                                if (vocap1[a] == flood) { isThere = true; break; }
                            }
                            if (isThere == false) vocap1.push_back(flood);
                        }
                        flood = "";
                    }
                }
                if (word[word.length() - 1] != ' ' && word[word.length() - 1] != ',' && word[word.length() - 1] != '!' && word[word.length() - 1] != '?' && word[word.length() - 1] != '.' && word[word.length() - 1] != ';') {
                    int isThere = false;
                    for (int a = 0; a < vocap1.size(); a++) {
                        if (vocap1[a] == flood) { isThere = true; break; }
                    }
                    if (isThere == false) vocap1.push_back(flood);
                    flood = "";
                }
            }
            for (int b = readRow + 1; b <= DataSize; b++) {
                std::string word = Data->getValueStr(Data->getCategoryName(2), b);
                std::string flood = "";
                for (int i = 0; i < word.length(); i++) {
                    if (word[i] != ' ' && word[i] != ',' && word[i] != '!' && word[i] != '?' && word[i] != '.' && word[i] != ';')
                        flood = flood + (char)std::tolower(word[i]);
                    else {
                        int isThere = false;
                        for (int a = 0; a < vocap2.size(); a++) {
                            if (vocap2[a] == flood) { isThere = true; break; }
                        }
                        if (isThere == false && flood != "") vocap2.push_back(flood);
                        if (word[i] != ' ') {
                            flood = word[i];
                            isThere = false;
                            for (int a = 0; a < vocap2.size(); a++) {
                                if (vocap2[a] == flood) { isThere = true; break; }
                            }
                            if (isThere == false) vocap2.push_back(flood);
                        }
                        flood = "";
                    }
                }
                if (word[word.length() - 1] != ' ' && word[word.length() - 1] != ',' && word[word.length() - 1] != '!' && word[word.length() - 1] != '?' && word[word.length() - 1] != '.' && word[word.length() - 1] != ';') {
                    int isThere = false;
                    for (int a = 0; a < vocap2.size(); a++) {
                        if (vocap2[a] == flood) { isThere = true; break; }
                    }
                    if (isThere == false) vocap2.push_back(flood);
                    flood = "";
                }
            }
            Data->freeMemory();
            break;
        }
    }
    vocap1.push_back("<EOS>");
    vocap2.push_back("<EOS>");
    vocap1.push_back("<PAD>");
    vocap2.push_back("<PAD>");
    std::cout << std::endl << "First Vocap Size: " << vocap1.size() << std::endl;
    std::cout << "Second Vocap Size: " << vocap2.size() << std::endl << std::endl;
    for (int i = 0; i < vocap1.size(); i++) {
        tokenizedVocap1[vocap1.at(i)] = i;
    }
    for (int i = 0; i < vocap2.size(); i++) {
        tokenizedVocap2[vocap2.at(i)] = i;
    }
    std::cout << "First Vocap Tokenized: " << std::endl;
    for (int i = 0; i < vocap1.size(); i++) {
        std::cout << vocap1.at(i) << " : " << tokenizedVocap1.at(vocap1.at(i)) << "    ";
    }
    std::cout << std::endl << std::endl << "Second Vocap Tokenized: " << std::endl;
    for (int i = 0; i < vocap2.size(); i++) {
        std::cout << vocap2.at(i) << " : " << tokenizedVocap2.at(vocap2.at(i)) << "    ";
    }
}

// Etiketlenmiş verileri konumlarına göre eğitir ve vektörlere çevirir.
void RegresifTransformer::Embedding(int embedSize, int epoch, long double learningRate, int attentionSize){
    EmbedSize = embedSize;
    if(EmbedSize % attentionSize == 0)
        AttentionLayerSize = attentionSize;
    else std::cout<<"Your Attention Size should divide your EmbedSize!" << std::endl;
    int layerMap[3] = { tokenizedVocap1.size(), EmbedSize, tokenizedVocap1.size() };
    EmbedWeightsVocap1 = new long double** [2];
    // Ağırlık değişkenleri oluşturulur.
    for (int i = 0; i < 2; i++) {
        EmbedWeightsVocap1[i] = new long double* [layerMap[i]];
        for (int j = 0; j < layerMap[i]; j++) {
            EmbedWeightsVocap1[i][j] = new long double[layerMap[i + 1]];
        }
    }
    long double** EmbedNeurons;
    long double* EmbedENeurons;
    EmbedNeurons = new long double* [3];
    EmbedENeurons = new long double[EmbedSize];
    for (int i = 0; i < EmbedSize; i++)
        EmbedENeurons[i] = 0;
    // Nöron değişkenleri oluşturulur.
    for (int i = 0; i < 3; i++) {
        EmbedNeurons[i] = new long double[layerMap[i]];
        for (int j = 0; j < layerMap[i]; j++)
            EmbedNeurons[i][j] = 0;
    }
    // Ağırlıklara rastgele değerler atanır.
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < layerMap[i]; j++) {
            for (int k = 0; k < layerMap[i + 1]; k++)
                EmbedWeightsVocap1[i][j][k] = GetRandValue(-0.5, 0.5);
        }
    }
    //Eğitim
    std::map<int, std::vector<int>> ClassifiedWords;
    int readRow = 0;
    // Değerleri sınıflandırır.
    while (true) {
        std::vector <std::string> words;
        if (readRow + batch_size < DataSize) {
            Data->readCSVCategoryinRange(Data->getCategoryName(1), readRow + 1, readRow + batch_size);
            readRow += batch_size;
            for (int b = (readRow + 1) - batch_size; b <= readRow; b++) {
                std::string word;
                std::string flood;
                bool EvAlRi;
                int countree;
                word = Data->getValueStr(Data->getCategoryName(1), b);
                flood = "";
                EvAlRi = true;
                countree = 0;
                for (int i = 0; i < word.length(); i++) {
                    if (word[i] != ' ' && word[i] != ',' && word[i] != ':')
                        flood = flood + (char)std::tolower(word[i]);
                    else {
                        if(flood != ""){
                            if(i == word.length()-1) EvAlRi = false;
                            if(countree % 2 == 0)
                                words.push_back(flood);
                            flood = "";
                            countree++;
                        }
                        if(word[i] == ','){
                            if(countree % 2 != 0)
                                countree++;
                        }
                    }
                }
                if (EvAlRi) {
                    if(countree % 2 == 0) words.push_back(flood);
                    flood = "";
                }
                for (int i = 0; i < words.size(); i++) {
                    int firstWord, secondWord;
                    firstWord = tokenizedVocap1.at(words.at(i));
                    if (i + 1 >= words.size()) secondWord = tokenizedVocap1.at("<EOS>");
                    else secondWord = tokenizedVocap1.at(words.at(i + 1));
                    bool isThWo = false;
                    bool isThWo2 = false;
                    int currentIndex = 0;
                    for (auto it = ClassifiedWords.begin(); it != ClassifiedWords.end(); ++it) {
                        currentIndex++;
                        if (it->first == firstWord) {
                            isThWo2 = true;
                            break;
                        }
                    }
                    if (!isThWo2) ClassifiedWords[firstWord];
                    for (int h = 0; h < ClassifiedWords.at(firstWord).size(); h++) {
                        if (ClassifiedWords.at(firstWord).at(h) == secondWord) isThWo = true;
                    }
                    if (!isThWo) ClassifiedWords.at(firstWord).push_back(secondWord);
                }
                words.clear();
            }
            Data->freeMemory();
        }
        else {
            Data->readCSVCategoryinRange(Data->getCategoryName(1), readRow + 1, DataSize);
            for (int b = readRow + 1; b <= DataSize; b++) {
                std::string word;
                std::string flood;
                int countree;
                bool EvAlRi;
                word = Data->getValueStr(Data->getCategoryName(1), b);
                flood = "";
                EvAlRi = true;
                countree = 0;
                for (int i = 0; i < word.length(); i++) {
                    if (word[i] != ' ' && word[i] != ',' && word[i] != ':')
                        flood = flood + (char)std::tolower(word[i]);
                    else {
                        if(flood != ""){
                            if(i == word.length()-1) EvAlRi = false;
                            if(countree % 2 == 0)
                                words.push_back(flood);
                            flood = "";
                            countree++;
                        }
                        if(word[i] == ','){
                            if(countree % 2 != 0)
                                countree++;
                        }
                    }
                }
                if (EvAlRi) {
                    if(countree % 2 == 0) words.push_back(flood);
                    flood = "";
                }
                for (int i = 0; i < words.size(); i++) {
                    int firstWord, secondWord;
                    firstWord = tokenizedVocap1.at(words.at(i));
                    if (i + 1 >= words.size()) secondWord = tokenizedVocap1.at("<EOS>");
                    else secondWord = tokenizedVocap1.at(words.at(i + 1));
                    bool isThWo = false;
                    bool isThWo2 = false;
                    int currentIndex = 0;
                    for (auto it = ClassifiedWords.begin(); it != ClassifiedWords.end(); ++it) {
                        currentIndex++;
                        if (it->first == firstWord) {
                            isThWo2 = true;
                            break;
                        }
                    }
                    if (!isThWo2) ClassifiedWords[firstWord];
                    for (int h = 0; h < ClassifiedWords.at(firstWord).size(); h++) {
                        if (ClassifiedWords.at(firstWord).at(h) == secondWord) isThWo = true;
                    }
                    if (!isThWo) ClassifiedWords.at(firstWord).push_back(secondWord);
                }
                words.clear();
            }
            Data->freeMemory();
            break;
        }
    }
    // Eğitim
    for (int q = 0; q < epoch; q++) {
        std::cout << "Epoch: " << q + 1 << std::endl;
        long double total_loss = 0;
        long double loss_count = 0;
        long double trueCount = 0;
        for (int i = 0; i < ClassifiedWords.size(); i++) {
            for (int k = 0; k < 3; k++) {
                for (int h = 0; h < layerMap[k]; h++) {
                    EmbedNeurons[k][h] = 0;
                    if (k == 1) EmbedENeurons[h] = 0;
                }
            }
            int currentIndex = 0;
            int firstWord;
            for (auto it = ClassifiedWords.begin(); it != ClassifiedWords.end(); ++it) {
                currentIndex++;
                if (currentIndex == i + 1) {
                    firstWord = it->first;
                    break;
                }
            }
            EmbedNeurons[0][firstWord] = 1;
            for (int j = 0; j < EmbedSize; j++) {
                EmbedNeurons[1][j] = EmbedNeurons[0][firstWord] * EmbedWeightsVocap1[0][firstWord][j];
            }
            for (int j = 0; j < EmbedSize; j++) {
                for (int k = 0; k < layerMap[2]; k++)
                    EmbedNeurons[2][k] += EmbedNeurons[1][j] * EmbedWeightsVocap1[1][j][k];
            }
            std::vector<long double> ExpectedValue(layerMap[2], 0.0);
            long double expectV = 1.0 / ClassifiedWords.at(firstWord).size();
            for (int j = 0; j < ClassifiedWords.at(firstWord).size(); j++) {
                ExpectedValue[ClassifiedWords.at(firstWord).at(j)] = expectV;
            }
            std::vector<long double> softMaxOutput = softMax(layerMap[2], EmbedNeurons[2]);
            std::vector<long double> softMaxDerivatives = CrossEntropyLoss(softMaxOutput, ExpectedValue);
            total_loss += cross_entropy_loss(softMaxOutput, ExpectedValue);
            loss_count++;
            long double biggest = 0;
            int biggestAddres;
            bool ThatsTrue = false;
            for (int h = 0; h < softMaxOutput.size(); h++) {
                if (softMaxOutput.at(h) > biggest) {
                    biggest = softMaxOutput.at(h);
                    biggestAddres = h;
                }
            }
            for (int j = 0; j < ClassifiedWords.at(firstWord).size(); j++) {
                if (biggestAddres == ClassifiedWords.at(firstWord).at(j)) ThatsTrue = true;
            }
            if (ThatsTrue) trueCount++;
            for (int j = 0; j < layerMap[1]; j++) {
                for (int k = 0; k < layerMap[2]; k++) {
                    EmbedWeightsVocap1[1][j][k] -= softMaxDerivatives[k] * EmbedNeurons[1][j] * learningRate;
                    EmbedENeurons[j] += EmbedWeightsVocap1[1][j][k] * softMaxDerivatives[k];
                }
            }
            for (int k = 0; k < layerMap[1]; k++) {
                EmbedWeightsVocap1[0][firstWord][k] -= EmbedENeurons[k] * learningRate;
            }
        }
        std::cout << "Total loss: " << total_loss / loss_count << std::endl;
        std::cout << trueCount << "/" << ClassifiedWords.size() << "          %" << (trueCount / ClassifiedWords.size()) * 100 << std::endl;
    }
    delete[] EmbedENeurons;
    for (int i = 0; i < 3; i++)
        delete EmbedNeurons[i];
    delete[] EmbedNeurons;
    //!!!İkinci Sözlük!!!
    layerMap[0] = tokenizedVocap2.size(); layerMap[2] = tokenizedVocap2.size();
    EmbedWeightsVocap2 = new long double** [2];
    // Ağırlıklar için değişkenler oluşturulur.
    for (int i = 0; i < 2; i++) {
        EmbedWeightsVocap2[i] = new long double* [layerMap[i]];
        for (int j = 0; j < layerMap[i]; j++)
            EmbedWeightsVocap2[i][j] = new long double[layerMap[i + 1]];
    }
    EmbedNeurons = new long double* [3];
    EmbedENeurons = new long double[EmbedSize];
    for (int i = 0; i < EmbedSize; i++)
        EmbedENeurons[i] = 0;
    // Nöron değişkenleri oluşturur.
    for (int i = 0; i < 3; i++) {
        EmbedNeurons[i] = new long double[layerMap[i]];
        for (int j = 0; j < layerMap[i]; j++)
            EmbedNeurons[i][j] = 0;
    }
    // Ağırlıklara rastgele değerler atar.
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < layerMap[i]; j++) {
            for (int k = 0; k < layerMap[i + 1]; k++)
                EmbedWeightsVocap2[i][j][k] = GetRandValue(-0.5, 0.5);
        }
    }
    //Learn
    ClassifiedWords.clear();
    readRow = 0;
    // Değeler sınıflandırır.
    while (true) {
        std::vector <std::string> words;
        if (readRow + batch_size < DataSize) {
            Data->readCSVCategoryinRange(Data->getCategoryName(2), readRow + 1, readRow + batch_size);
            readRow += batch_size;
            for (int b = (readRow + 1) - batch_size; b <= readRow; b++) {
                std::string word;
                std::string flood;
                bool EvAlRi;
                int countree;
                word = Data->getValueStr(Data->getCategoryName(2), b);
                flood = "";
                EvAlRi = true;
                countree = 0;
                for (int i = 0; i < word.length(); i++) {
                    if (word[i] != ' ' && word[i] != ',' && word[i] != ':')
                        flood = flood + (char)std::tolower(word[i]);
                    else {
                        if(flood != ""){
                            if(i == word.length()-1) EvAlRi = false;
                            if(countree % 2 == 0)
                                words.push_back(flood);
                            flood = "";
                            countree++;
                        }
                    }
                }
                if (EvAlRi && flood != ""){
                    if(countree % 2 == 0) words.push_back(flood);
                    flood = "";
                }
                for (int i = 0; i < words.size(); i++) {
                    int firstWord, secondWord;
                    firstWord = tokenizedVocap1.at(words.at(i));
                    if (i + 1 >= words.size()) secondWord = tokenizedVocap1.at("<EOS>");
                    else secondWord = tokenizedVocap1.at(words.at(i + 1));
                    bool isThWo = false;
                    bool isThWo2 = false;
                    int currentIndex = 0;
                    for (auto it = ClassifiedWords.begin(); it != ClassifiedWords.end(); ++it) {
                        currentIndex++;
                        if (it->first == firstWord) {
                            isThWo2 = true;
                            break;
                        }
                    }
                    if (!isThWo2) ClassifiedWords[firstWord];
                    for (int h = 0; h < ClassifiedWords.at(firstWord).size(); h++) {
                        if (ClassifiedWords.at(firstWord).at(h) == secondWord) isThWo = true;
                    }
                    if (!isThWo) ClassifiedWords.at(firstWord).push_back(secondWord);
                }
                words.clear();
            }
            Data->freeMemory();
        }
        else {
            Data->readCSVCategoryinRange(Data->getCategoryName(2), readRow + 1, DataSize);
            for (int b = readRow + 1; b <= DataSize; b++) {
                std::string word;
                std::string flood;
                bool EvAlRi;
                int countree;
                word = Data->getValueStr(Data->getCategoryName(2), b);
                flood = "";
                EvAlRi = true;
                countree = 0;
                for (int i = 0; i < word.length(); i++) {
                    if (word[i] != ' ' && word[i] != ',' && word[i] != ':')
                        flood = flood + (char)std::tolower(word[i]);
                    else {
                        if(flood != ""){
                            if(i == word.length()-1) EvAlRi = false;
                            if(countree % 2 == 0)
                                words.push_back(flood);
                            flood = "";
                            countree++;
                        }
                    }
                }
                if (EvAlRi) {
                    if(countree % 2 == 0) words.push_back(flood);
                    flood = "";
                }
                for (int i = 0; i < words.size(); i++) {
                    int firstWord, secondWord;
                    firstWord = tokenizedVocap2.at(words.at(i));
                    if (i + 1 >= words.size()) secondWord = tokenizedVocap2.at("<EOS>");
                    else secondWord = tokenizedVocap2.at(words.at(i + 1));
                    bool isThWo = false;
                    bool isThWo2 = false;
                    int currentIndex = 0;
                    for (auto it = ClassifiedWords.begin(); it != ClassifiedWords.end(); ++it) {
                        currentIndex++;
                        if (it->first == firstWord) {
                            isThWo2 = true;
                            break;
                        }
                    }
                    if (!isThWo2) ClassifiedWords[firstWord];
                    for (int h = 0; h < ClassifiedWords.at(firstWord).size(); h++) {
                        if (ClassifiedWords.at(firstWord).at(h) == secondWord) isThWo = true;
                    }
                    if (!isThWo) ClassifiedWords.at(firstWord).push_back(secondWord);
                }
                words.clear();
            }
            Data->freeMemory();
            break;
        }
    }
    for (int q = 0; q < epoch; q++) {
        std::cout << "Epoch: " << q + 1 << std::endl;
        long double total_loss = 0;
        long double loss_count = 0;
        long double trueCount = 0;
        for (int i = 0; i < ClassifiedWords.size(); i++) {
            //Reset values
            for (int k = 0; k < 3; k++) {
                for (int h = 0; h < layerMap[k]; h++) {
                    EmbedNeurons[k][h] = 0;
                    if (k == 1) EmbedENeurons[h] = 0;
                }
            }
            int currentIndex = 0;
            int firstWord;
            // İlk değer belirlenir.
            for (auto it = ClassifiedWords.begin(); it != ClassifiedWords.end(); ++it) {
                currentIndex++;
                if (currentIndex == i + 1) {
                    firstWord = it->first;
                    break;
                }
            }
            //Feedforward (İleri yayılım)
            EmbedNeurons[0][firstWord] = 1;
            for (int j = 0; j < EmbedSize; j++) {
                EmbedNeurons[1][j] = EmbedNeurons[0][firstWord] * EmbedWeightsVocap2[0][firstWord][j];
            }
            for (int j = 0; j < EmbedSize; j++) {
                for (int k = 0; k < layerMap[2]; k++) {
                    EmbedNeurons[2][k] += EmbedNeurons[1][j] * EmbedWeightsVocap2[1][j][k];
                }
            }
            std::vector<long double> ExpectedValue(layerMap[2], 0.0);
            long double expectV = 1.0 / ClassifiedWords.at(firstWord).size();
            for (int j = 0; j < ClassifiedWords.at(firstWord).size(); j++) {
                ExpectedValue[ClassifiedWords.at(firstWord).at(j)] = expectV;
            }
            std::vector<long double> softMaxOutput = softMax(layerMap[2], EmbedNeurons[2]);
            std::vector<long double> softMaxDerivatives = CrossEntropyLoss(softMaxOutput, ExpectedValue);
            total_loss += cross_entropy_loss(softMaxOutput, ExpectedValue);
            loss_count++;
            long double biggest = 0;
            int biggestAddres;
            bool ThatsTrue = false;
            for (int h = 0; h < softMaxOutput.size(); h++) {
                if (softMaxOutput.at(h) > biggest) {
                    biggest = softMaxOutput.at(h);
                    biggestAddres = h;
                }
            }
            for (int j = 0; j < ClassifiedWords.at(firstWord).size(); j++) {
                if (biggestAddres == ClassifiedWords.at(firstWord).at(j)) ThatsTrue = true;
            }
            if (ThatsTrue) trueCount++;
            //BACKPROPAGATION (Geri yayılım.)
            // Ağırlıkları günceller.
            for (int j = 0; j < layerMap[1]; j++) {
                for (int k = 0; k < layerMap[2]; k++) {
                    EmbedWeightsVocap2[1][j][k] -= softMaxDerivatives[k] * EmbedNeurons[1][j] * learningRate;
                    EmbedENeurons[j] += EmbedWeightsVocap2[1][j][k] * softMaxDerivatives[k];
                }
            }
            for (int k = 0; k < layerMap[1]; k++) {
                EmbedWeightsVocap2[0][firstWord][k] -= EmbedENeurons[k] * learningRate;
            }
        }
        std::cout << "Total loss: " << total_loss / loss_count << std::endl;
        std::cout << trueCount << "/" << ClassifiedWords.size() << "          %" << (trueCount / ClassifiedWords.size()) * 100 << std::endl;
    }
    delete[] EmbedENeurons;
    for (int i = 0; i < 3; i++)
        delete[] EmbedNeurons[i];
    delete[] EmbedNeurons;
}

// Etiketlenmiş verileri vektörlere çevirir.
std::vector<long double> RegresifTransformer::predictEmbed(int wordToken, int vocap) const {
    std::vector<long double> Values(EmbedSize, 0.0);
    if(wordToken == tokenizedVocap1.at("<PAD>") || wordToken == tokenizedVocap2.at("<PAD>")){
        for(int i = 0; i < EmbedSize; i++)
            Values[i] = LDBL_MIN;
    }
    switch (vocap){
    case 1:
        for (int i = 0; i < EmbedSize; i++)
            Values[i] = EmbedWeightsVocap1[0][wordToken][i];
        break;
    case 2:
        for (int i = 0; i < EmbedSize; i++)
            Values[i] = EmbedWeightsVocap2[0][wordToken][i];
        break;
    default:
        std::cout << "Please enter 1 or 2! Your value is OUT of RANGE: predictEmbed(int, 'int')" << std::endl;
        break;
    }
    return Values;
}

void RegresifTransformer::Learn(int epoch, long double learningRate, int max_seq){
    // Ağırlıkları oluşturur ve rastgele değerler atar.
    EncoderKeyWeights = new long double** [AttentionLayerSize];
    EncoderValueWeights = new long double** [AttentionLayerSize];
    EncoderQueryWeights = new long double** [AttentionLayerSize];
    DecoderKeyWeights = new long double** [AttentionLayerSize];
    DecoderValueWeights = new long double** [AttentionLayerSize];
    DecoderQueryWeights = new long double** [AttentionLayerSize];
    DecoderQueryWeights_ = new long double** [AttentionLayerSize];
    EncoderKeyWeights_ = new long double** [AttentionLayerSize];
    EncoderValueWeights_ = new long double** [AttentionLayerSize];
    for(int i = 0; i < AttentionLayerSize; i++){
        EncoderKeyWeights[i] = new long double *[EmbedSize/AttentionLayerSize];
        EncoderValueWeights[i] = new long double *[EmbedSize/AttentionLayerSize];
        EncoderQueryWeights[i] = new long double *[EmbedSize/AttentionLayerSize];
        DecoderKeyWeights[i] = new long double *[EmbedSize/AttentionLayerSize];
        DecoderValueWeights[i] = new long double *[EmbedSize/AttentionLayerSize];
        DecoderQueryWeights[i] = new long double *[EmbedSize/AttentionLayerSize];
        DecoderQueryWeights_[i] = new long double *[EmbedSize/AttentionLayerSize];
        EncoderKeyWeights_[i] = new long double*[EmbedSize/AttentionLayerSize];
        EncoderValueWeights_[i] = new long double*[EmbedSize/AttentionLayerSize];
        for(int j = 0; j < EmbedSize/AttentionLayerSize; j++){
            EncoderKeyWeights[i][j] = new long double[EmbedSize/AttentionLayerSize];
            EncoderValueWeights[i][j] = new long double[EmbedSize/AttentionLayerSize];
            EncoderQueryWeights[i][j] = new long double[EmbedSize/AttentionLayerSize];
            DecoderKeyWeights[i][j] = new long double[EmbedSize/AttentionLayerSize];
            DecoderValueWeights[i][j] = new long double[EmbedSize/AttentionLayerSize];
            DecoderQueryWeights[i][j] = new long double[EmbedSize/AttentionLayerSize];
            DecoderQueryWeights_[i][j] = new long double[EmbedSize/AttentionLayerSize];
            EncoderKeyWeights_[i][j] = new long double[EmbedSize/AttentionLayerSize];
            EncoderValueWeights_[i][j] = new long double[EmbedSize/AttentionLayerSize];
            for(int l = 0; l < EmbedSize/AttentionLayerSize; l++){
                EncoderKeyWeights[i][j][l] = GetRandValue(-2.0, 2.0);
                EncoderValueWeights[i][j][l] = GetRandValue(-2.0, 2.0);
                EncoderQueryWeights[i][j][l] = GetRandValue(-2.0, 2.0);
                DecoderKeyWeights[i][j][l] = GetRandValue(-2.0, 2.0);
                DecoderValueWeights[i][j][l] = GetRandValue(-2.0, 2.0);
                DecoderQueryWeights[i][j][l] = GetRandValue(-2.0, 2.0);
                DecoderQueryWeights_[i][j][l] = GetRandValue(-2.0, 2.0);
                EncoderKeyWeights_[i][j][l] = GetRandValue(-2.0, 2.0);
                EncoderValueWeights_[i][j][l] = GetRandValue(-2.0, 2.0);
            }
        }
    }
    DecoderNNLayerWeights = new long double*[EmbedSize];
    EncoderDecoderRegressionLayerWeights = new long double[EmbedSize];
    EncoderRegressionLayerWeights = new long double[EmbedSize];
    EncoderRegressionBias = new long double[EmbedSize];
    DecoderRegressionLayerWeights = new long double[EmbedSize];
    DecoderRegressionBias = new long double[EmbedSize];
    for (int i = 0; i < EmbedSize; i++){
        DecoderNNLayerWeights[i] = new long double[tokenizedVocap2.size()];
        EncoderDecoderRegressionLayerWeights[i] = GetRandValue(-2.0, 2.0);
        EncoderRegressionLayerWeights[i] = GetRandValue(-2.0, 2.0);
        EncoderDecoderRegressionBias = GetRandValue(-2.0, 2.0);
        EncoderRegressionBias[i] = GetRandValue(-2.0, 2.0);
        DecoderRegressionLayerWeights[i] = GetRandValue(-2.0,2.0);
        DecoderRegressionBias[i] = GetRandValue(-2.0,2.0);
        for(int j = 0; j < tokenizedVocap2.size(); j++)
            DecoderNNLayerWeights[i][j] = GetRandValue(-2.0, 2.0);
    }
    //std::cout << "Pass 1 : Start to Learn!" << std::endl;
    for (int q = 0; q < epoch; q++){
        std::cout<<"Epoch: " << q << std::endl;
        int readRow = 0;
        while (true){
            if (readRow + batch_size / 2 < DataSize){
                Data->readCSVinRange(readRow + 1, readRow + batch_size / 2);
                readRow += batch_size / 2;
                for (int b = (readRow + 1) - batch_size / 2; b <= readRow; b++) {
                    std::vector<int> Sentence0, Sentence1;
                    std::map<int, long double> CategoryValue0, CategoryValue1;
                    std::string word;
                    std::string flood = "";
                    bool EvAlRi;
                    int countree;
                    word = Data->getValueStr(Data->getCategoryName(1), b);
                    flood = "";
                    EvAlRi = true;
                    countree = 0;
                    //İlk kategorinin değerlerini okur.
                    for (int i = 0; i < word.length(); i++) {
                        if (word[i] != ' ' && word[i] != ':' && word[i] != ',')
                            flood = flood + (char)std::tolower(word[i]);
                        else {
                            if(flood != ""){
                                if(i == word.length() - 1) EvAlRi = false;
                                if(countree % 2 == 0)
                                    Sentence0.push_back(tokenizedVocap1.at(flood));
                                else{
                                    try {
                                        CategoryValue0[Sentence0.size()] = stold(flood);
                                    }
                                    catch (const std::invalid_argument& e) {
                                        std::cout << std::endl << "First Vocap -> " << "Values only can be num => " << "Category: " << Sentence0.size() << " Row: " << b << " Value: " << flood << std::endl;
                                        CategoryValue0[Sentence0.size()] = 0;
                                        std::cout << "Value of category saved as 0! It will not effect the result with this value!" << std::endl;
                                        std::cout << e.what() << std::endl;
                                    }
                                }
                                countree++;
                                flood = "";
                            }
                            if(word[i] == ',' && CategoryValue0[Sentence0.size()] == NULL){
                                CategoryValue0[Sentence0.size()] = 0;
                            }
                        }
                    }
                    if (EvAlRi && flood != ""){
                        if(countree % 2 == 0){
                            Sentence0.push_back(tokenizedVocap1.at(flood));
                            CategoryValue0[Sentence0.size()] = 0;
                        }
                        else{
                            try {
                                CategoryValue0[Sentence0.size()] = stold(flood);
                            }
                            catch (const std::invalid_argument& e) {
                                std::cout << std::endl << "First Vocap -> " << "Values only can be num => " << "Category: " << Sentence0.size() << " Row: " << b << " Value: " << flood << std::endl;
                                CategoryValue0[Sentence0.size()] = 0;
                                std::cout << "Value of category saved as 0! It will not effect the result with this value!" << std::endl;
                                std::cout << e.what() << std::endl;
                            }
                        }
                        flood = "";
                    }
                    countree = 0;
                    word = Data->getValueStr(Data->getCategoryName(2), b);
                    EvAlRi = true;
                    //Read vocap2 sentence
                    for (int i = 0; i < word.length(); i++) {
                        if (word[i] != ' ' && word[i] != ':' && word[i] != ',')
                            flood = flood + (char)std::tolower(word[i]);
                        else {
                            if(flood != ""){
                                if(i == word.length() - 1) EvAlRi = false;
                                if(countree % 2 == 0)
                                    Sentence1.push_back(tokenizedVocap2.at(flood));
                                else{
                                    try {
                                        CategoryValue1[Sentence1.size()] = stold(flood);
                                    }
                                    catch (const std::invalid_argument& e) {
                                        std::cout << std::endl << "Second Vocap -> " << "Values only can be num => " << "Category: " << Sentence1.size() << " Row: " << b << " Value: " << flood << std::endl;
                                        CategoryValue1[Sentence1.size()] = 0;
                                        std::cout << "Value of category saved as 0! It will not effect the result with this value!" << std::endl;
                                        std::cout << e.what() << std::endl;
                                    }
                                }
                                flood = "";
                                countree++;
                            }
                            if(word[i] == ',' && CategoryValue0[Sentence1.size()] == NULL){
                                CategoryValue1[Sentence1.size()] = 0;
                            }
                        }
                    }
                    if (EvAlRi && flood != "") {
                        if(countree % 2 == 0){
                            Sentence1.push_back(tokenizedVocap2.at(flood));
                            CategoryValue1[Sentence1.size()] = 0;
                        }
                        else{
                            try {
                                CategoryValue1[Sentence1.size()] = stold(flood);
                            }
                            catch (const std::invalid_argument& e) {
                                std::cout << std::endl << "Second Vocap -> " << "Values only can be num => " << "Category: " << Sentence1.size() << " Row: " << b << " Value: " << flood << std::endl;
                                CategoryValue1[Sentence1.size()] = 0;
                                std::cout << "Value of category saved as 0! It will not effect the result with this value!" << std::endl;
                                std::cout << e.what() << std::endl;
                            }
                        }
                        flood = "";
                    }
                    //std::cout << "Pass 2 : Got Words!" << std::endl;
                    /*                                     ENCODER_KATMANI_BAŞLANGICI                                       */
                    long double*** Queries = new long double** [Sentence0.size()];
                    long double*** Values = new long double** [Sentence0.size()];
                    long double*** Keys = new long double** [Sentence0.size()];
                    long double** SelfAttentionValues = new long double* [Sentence0.size()];
                    long double*** QueryKeyCalculations_Encoder = new long double**[Sentence0.size()];
                    std::map<int, std::vector<long double>> EmbedResults0;
                    long double*** EncoderKeys = new long double **[Sentence0.size()];
                    long double*** EncoderValues = new long double **[Sentence0.size()];
                    std::vector<std::vector<std::vector<long double>>> EncoderSelfAttentionSoftMax;
                    // Queries, Values, Keys, QueryKeyCalculations ve SelfAttentionValues değişkenlerini oluşturur.
                    for (int i = 0; i < Sentence0.size(); i++) {
                        EmbedResults0[i] = predictEmbed(Sentence0[i], 1);
                        Queries[i] = new long double*[AttentionLayerSize];
                        Values[i] = new long double*[AttentionLayerSize];
                        Keys[i] = new long double*[AttentionLayerSize];
                        EncoderValues[i] = new long double*[AttentionLayerSize];
                        EncoderKeys[i] = new long double*[AttentionLayerSize];
                        SelfAttentionValues[i] = new long double[EmbedSize];
                        for(int k = 0; k < EmbedSize; k++)
                            SelfAttentionValues[i][k] = 0;
                        QueryKeyCalculations_Encoder[i] = new long double*[AttentionLayerSize];
                        for(int k = 0; k < AttentionLayerSize; k++){
                            QueryKeyCalculations_Encoder[i][k] = new long double[AttentionLayerSize * Sentence0.size()];
                            Queries[i][k] = new long double[EmbedSize/AttentionLayerSize];
                            Values[i][k] = new long double[EmbedSize/AttentionLayerSize];
                            Keys[i][k] = new long double[EmbedSize/AttentionLayerSize];
                            EncoderValues[i][k] = new long double[EmbedSize/AttentionLayerSize];
                            EncoderKeys[i][k] = new long double[EmbedSize/AttentionLayerSize];
                            for(int l = 0; l < EmbedSize/AttentionLayerSize; l++){
                                Queries[i][k][l] = 0;
                                Values[i][k][l] = 0;
                                Keys[i][k][l] = 0;
                                EncoderValues[i][k][l] = 0;
                                EncoderKeys[i][k][l] = 0;
                            }
                            for(int l = 0; l < AttentionLayerSize * Sentence0.size(); l++)
                                QueryKeyCalculations_Encoder[i][k][l] = 0;
                        }
                    }
                    for(int k = 0; k < Sentence0.size(); k++){
                        for(int i = 0; i < EmbedSize; i++)
                            if(CategoryValue0[k] != 0)
                                EmbedResults0[k][i] += (CategoryValue0.at(k) * EncoderRegressionLayerWeights[i]) + EncoderRegressionBias[i];
                    }
                    // Pozisyonel kodlama yapılır.
                    for (int k = 0; k < Sentence0.size(); k++) {
                        for (int i = 0; i < EmbedSize; i++)
                            EmbedResults0[k][i] += positionalEncoding(k, i, EmbedSize);
                    }
                    // Querie, Value and Key'leri hesaplar.
                    for (int h = 0; h < Sentence0.size(); h++) {
                        for(int i = 0; i < AttentionLayerSize; i++){
                            for(int k = 0; k < EmbedSize/AttentionLayerSize; k++){
                                for(int l = 0; l < EmbedSize/AttentionLayerSize; l++){
                                    Queries[h][i][k] += EmbedResults0[h][(i*(EmbedSize/AttentionLayerSize))+l] * EncoderQueryWeights[i][l][k];
                                    Values[h][i][k] += EmbedResults0[h][(i*(EmbedSize/AttentionLayerSize))+l] * EncoderValueWeights[i][l][k];
                                    Keys[h][i][k] += EmbedResults0[h][(i*(EmbedSize/AttentionLayerSize))+l] * EncoderKeyWeights[i][l][k];
                                }
                            }
                        }
                    }
                    // SelfAttentionValue'ları hesaplar.
                    for(int k = 0; k < Sentence0.size(); k++){
                        std::vector<std::vector<long double>> softMaxResults;
                        for(int h = 0; h < AttentionLayerSize; h++){
                            // QueryKeyCalculations hesaplamalarını yapar.
                            for(int b = 0; b < Sentence0.size(); b++){
                                for(int a = 0; a < AttentionLayerSize; a++){
                                    for(int n = 0; n < EmbedSize/AttentionLayerSize; n++)
                                        QueryKeyCalculations_Encoder[k][h][(b* AttentionLayerSize) + a] += Queries[k][h][n] * Keys[b][a][n];
                                }
                            }
                            // SelfAttentionValue'ları hesaplar.
                            softMaxResults.push_back(softMax(Sentence0.size() * AttentionLayerSize, QueryKeyCalculations_Encoder[k][h]));
                            for(int i = 0; i < Sentence0.size(); i++){
                                for(int a = 0; a < EmbedSize/ AttentionLayerSize; a++){
                                    for(int b = 0; b < AttentionLayerSize; b++)
                                        SelfAttentionValues[k][(h*(EmbedSize/ AttentionLayerSize))+a] += Values[i][b][a] * softMaxResults[h].at((i*AttentionLayerSize)+b);
                                }
                            }
                        }
                        EncoderSelfAttentionSoftMax.push_back(softMaxResults);
                    }
                    // SelfAttentionValue'yu normalize eder.
                    for (int k = 0; k < Sentence0.size(); k++) {
                        for (int i = 0; i < EmbedSize; i++)
                            SelfAttentionValues[k][i] += EmbedResults0[k][i];
                    }
                    // Son Key and Value'ları hesaplar.
                    for (int h = 0; h < Sentence0.size(); h++) {
                        for(int i = 0; i < AttentionLayerSize; i++){
                            for(int k = 0; k < EmbedSize/AttentionLayerSize; k++){
                                for(int l = 0; l < EmbedSize/AttentionLayerSize; l++){
                                    EncoderValues[h][i][k] += SelfAttentionValues[h][(i*(EmbedSize/AttentionLayerSize))+l] * EncoderValueWeights_[i][l][k];
                                    EncoderKeys[h][i][k] += SelfAttentionValues[h][(i*(EmbedSize/AttentionLayerSize))+l] * EncoderKeyWeights_[i][l][k];
                                }
                            }
                        }
                    }
                        //std::cout << "Pass 3 : EncoderLayerEnd" << std::endl;
                    /*                                    ENCODER_KATMANI_SONU                                           */
                    /*                                   DECODER_KATMANI_BAŞLANGICI                                          */
                    std::vector<long double**> DecoderQueries;
                    std::vector<long double**> DecoderValues;
                    std::vector<long double**> DecoderKeys;
                    std::map<int, std::vector<long double>> EmbedResults1;
                    int NextWord = -1;
                    long double NextValue = 0;
                    std::vector<int> ResultSentence;
                    std::map<int, long double> ResultValues;
                    std::vector<std::vector<long double>> LossValues;
                    std::vector<long double> RegressionErr;
                    std::vector<long double*> Encoder_DecoderAttention;
                    std::vector<long double*> Decoder_SelfAttention;
                    std::vector<long double**> MaskedSelfAtQueryKeyCal;
                    std::vector<long double**> DecoderAttentionQuery;
                    std::vector<long double**> DecoderAttentionQueryKeyCal;
                    std::vector<std::vector<std::vector<long double>>> AttentionLayerSoftMaxResults;
                    std::vector<std::vector<std::vector<long double>>> MaskedSelfAttentionSoftMaxResults;
                    int coutn = 0;
                    while(NextWord != tokenizedVocap2.at("<EOS>") && coutn < max_seq){
                        coutn++;
                        Encoder_DecoderAttention.push_back(new long double[EmbedSize]);
                        Decoder_SelfAttention.push_back(new long double[EmbedSize]);
                        for(int i = 0; i < EmbedSize; i++){
                            Decoder_SelfAttention[ResultSentence.size()][i] = 0;
                            Encoder_DecoderAttention[ResultSentence.size()][i] = 0;
                        }
                        /*                          MASKED_SELF_ATTENTION_KATMANI                             */
                        //std::cout << "Pass 4 : MASKED SELF ATTENTION LAYER START" << std::endl;
                        if(NextWord == -1){
                            NextWord = tokenizedVocap2.at("<EOS>");
                            NextValue = 0;
                        }
                        EmbedResults1[ResultSentence.size()] = predictEmbed(NextWord,2);
                        for(int i = 0; i < EmbedSize; i++)
                            EmbedResults1[ResultSentence.size()][i] += (NextValue * DecoderRegressionLayerWeights[i]) + DecoderRegressionBias[i];
                        for(int i = 0; i < EmbedSize; i++)
                            EmbedResults1[ResultSentence.size()][i] += positionalEncoding(ResultSentence.size(),i,EmbedSize);
                        // Querie, Value, Key'leri oluştur.
                        DecoderQueries.push_back(new long double*[AttentionLayerSize]);
                        DecoderValues.push_back(new long double*[AttentionLayerSize]);
                        DecoderKeys.push_back(new long double*[AttentionLayerSize]);
                        // QUERIE, VALUE, KEY'leri hesaplar.
                        for(int i = 0; i < AttentionLayerSize; i++){
                            DecoderQueries[ResultSentence.size()][i] = new long double[EmbedSize/AttentionLayerSize];
                            DecoderValues[ResultSentence.size()][i] = new long double[EmbedSize/AttentionLayerSize];
                            DecoderKeys[ResultSentence.size()][i] = new long double[EmbedSize/AttentionLayerSize];
                            for(int k = 0; k < EmbedSize/AttentionLayerSize; k++){
                                DecoderQueries[ResultSentence.size()][i][k] = 0;
                                DecoderValues[ResultSentence.size()][i][k] = 0;
                                DecoderKeys[ResultSentence.size()][i][k] = 0;
                                for(int l = 0; l < EmbedSize/AttentionLayerSize; l++){
                                    DecoderQueries[ResultSentence.size()][i][k] += EmbedResults1[ResultSentence.size()][(i*(EmbedSize/AttentionLayerSize))+l] * DecoderQueryWeights[i][l][k];
                                    DecoderValues[ResultSentence.size()][i][k] += EmbedResults1[ResultSentence.size()][(i*(EmbedSize/AttentionLayerSize))+l] * DecoderValueWeights[i][l][k];
                                    DecoderKeys[ResultSentence.size()][i][k] += EmbedResults1[ResultSentence.size()][(i*(EmbedSize/AttentionLayerSize))+l] * DecoderKeyWeights[i][l][k];
                                }
                            }
                        }
                        MaskedSelfAtQueryKeyCal.push_back(new long double*[AttentionLayerSize]);
                        for(int i = 0; i < AttentionLayerSize; i++){
                            MaskedSelfAtQueryKeyCal[ResultSentence.size()][i] = new long double[(ResultSentence.size()+1)*AttentionLayerSize];
                            for(int k = 0; k < (ResultSentence.size()+1)*AttentionLayerSize; k++)
                                MaskedSelfAtQueryKeyCal[ResultSentence.size()][i][k] = 0;
                        }
                        std::vector<std::vector<long double>> SoftMaxResults0;
                        for(int h = 0; h < AttentionLayerSize; h++){
                            // QueryKeyCalculations hesaplamalarını yapar.
                            for(int b = 0; b < ResultSentence.size()+1; b++){
                                for(int a = 0; a < AttentionLayerSize; a++){
                                    for(int n = 0; n < EmbedSize/AttentionLayerSize; n++)
                                        MaskedSelfAtQueryKeyCal[ResultSentence.size()][h][(b* AttentionLayerSize) + a] += DecoderQueries[ResultSentence.size()][h][n] * DecoderKeys[b][a][n];
                                }
                            }
                            // SelfAttentionValue'ları hesaplar.
                            SoftMaxResults0.push_back(softMax((ResultSentence.size()+1) * AttentionLayerSize, MaskedSelfAtQueryKeyCal[ResultSentence.size()][h]));
                            for(int i = 0; i < ResultSentence.size()+1; i++){
                                for(int a = 0; a < EmbedSize/ AttentionLayerSize; a++){
                                    for(int b = 0; b < AttentionLayerSize; b++)
                                        Decoder_SelfAttention[ResultSentence.size()][(h*(EmbedSize/ AttentionLayerSize))+a] += DecoderValues[i][b][a] * SoftMaxResults0[h].at((i*AttentionLayerSize)+b);
                                }
                            }
                        }
                        MaskedSelfAttentionSoftMaxResults.push_back(SoftMaxResults0);
                        for(int i = 0; i < EmbedSize; i++)
                            Decoder_SelfAttention[ResultSentence.size()][i] += EmbedResults1[ResultSentence.size()][i];
                        //                         MASKED_SELF_ATTENTION_KATMANI_SONU
                        //                              ATTENTION_KATMANI_BAŞLAR
                        //std::cout << "Pass 5 : ENCODER&DECODER LAYER START" << std::endl;
                        // DecoderAttentionQuery'yi oluşturur.
                        DecoderAttentionQuery.push_back(new long double*[AttentionLayerSize]);
                        for(int i = 0; i < AttentionLayerSize; i++){
                            DecoderAttentionQuery[ResultSentence.size()][i] = new long double[EmbedSize/AttentionLayerSize];
                            for(int k = 0; k < EmbedSize/AttentionLayerSize; k++){
                                DecoderAttentionQuery[ResultSentence.size()][i][k] = 0;
                                for(int l = 0; l < EmbedSize/AttentionLayerSize; l++)
                                    DecoderAttentionQuery[ResultSentence.size()][i][k] += DecoderQueryWeights_[i][l][k] * Decoder_SelfAttention[ResultSentence.size()][(i*(EmbedSize/AttentionLayerSize))+l];
                            }
                        }
                        // DecoderAttentionQueryCalculation'ı oluşturur.
                        DecoderAttentionQueryKeyCal.push_back(new long double*[AttentionLayerSize]);
                        for(int i = 0; i < AttentionLayerSize; i++){
                            DecoderAttentionQueryKeyCal[ResultSentence.size()][i] = new long double[Sentence0.size()*AttentionLayerSize];
                            for(int k = 0; k < Sentence0.size()*AttentionLayerSize; k++)
                                DecoderAttentionQueryKeyCal[ResultSentence.size()][i][k] = 0;
                        }
                        std::vector<std::vector<long double>> softMaxResult;
                        for(int i = 0; i < AttentionLayerSize; i++){
                            for(int b = 0; b < Sentence0.size(); b++){
                                for(int n = 0; n < AttentionLayerSize; n++){
                                    for(int l = 0; l < EmbedSize/AttentionLayerSize; l++)
                                        DecoderAttentionQueryKeyCal[ResultSentence.size()][i][(b*AttentionLayerSize)+n] += DecoderAttentionQuery[ResultSentence.size()][i][l] * EncoderKeys[b][n][l];
                                }
                            }
                            softMaxResult.push_back(softMax(Sentence0.size()*AttentionLayerSize, DecoderAttentionQueryKeyCal[ResultSentence.size()][i]));
                            for(int l = 0; l < EmbedSize/AttentionLayerSize; l++){
                                for(int b = 0; b < Sentence0.size(); b++){
                                    for(int n = 0; n < AttentionLayerSize; n++)
                                        Encoder_DecoderAttention[ResultSentence.size()][(i*(EmbedSize/AttentionLayerSize)) + l] += EncoderValues[b][n][l] * softMaxResult[i].at((b*AttentionLayerSize) + n);
                                }
                            }
                        }
                        AttentionLayerSoftMaxResults.push_back(softMaxResult);
                        for(int i = 0; i < EmbedSize; i++)
                            Encoder_DecoderAttention[ResultSentence.size()][i] += Decoder_SelfAttention[ResultSentence.size()][i];
                        //                                ATTENTION_LAYER_END
                        //                      TAM_SİNİR_AĞI_KATMANI-SONRAKİ_DEĞERİ_TAHMİN_ETME
                        long double *NextWordOutput = new long double[tokenizedVocap2.size()];
                        // Normalize
                        for(int i = 0; i < tokenizedVocap2.size(); i++){
                            NextWordOutput[i] = 0;
                            for(int k = 0; k < EmbedSize; k++){
                                NextWordOutput[i] += Encoder_DecoderAttention[ResultSentence.size()][k] * DecoderNNLayerWeights[k][i];
                            }
                        }
                        long double max = -2;
                        std::vector<long double> nextWordVec = softMax(tokenizedVocap2.size(), NextWordOutput);
                        for(int i = 0; i < nextWordVec.size(); i++){
                            if(nextWordVec.at(i) >= max){
                                max = nextWordVec.at(i); NextWord = i;
                            }
                        }
                        delete[] NextWordOutput;
                        ResultSentence.push_back(NextWord);
                        //                      TAM_SİNİR_AĞI_KATMANI-SONRAKİ_DEĞERİ_TAHMİN_ETME_SONU
                        //                      REGRESYON_KATMANI_BAŞLANGICI
                        NextValue = 0;
                        for(int i = 0; i < EmbedSize; i++)
                            NextValue += (Encoder_DecoderAttention[ResultSentence.size()-1][i] * EncoderDecoderRegressionLayerWeights[i]) + EncoderDecoderRegressionBias;
                        ResultValues[ResultSentence.size()] = NextValue;
                        //                          REGRESYON_KATMANI_SONU
                        std::vector<long double> expected(tokenizedVocap2.size(), 0.0);
                        if(ResultSentence.size() <= Sentence1.size()) expected[Sentence1[ResultSentence.size()-1]] = 1.0;
                        if(ResultSentence.size() <= Sentence1.size()) RegressionErr.push_back(mean2ErrDerr(NextValue,CategoryValue1.at(ResultSentence.size())));
                        else RegressionErr.push_back(0.0);
                        LossValues.push_back(CrossEntropyLoss(nextWordVec, expected));
                        for(auto& it : tokenizedVocap2){
                            if (it.second == NextWord) {
                                std::cout << it.first << ' ';
                            }
                        }
                        std::cout << "Loss: " << cross_entropy_loss(nextWordVec, expected) << std::endl;
                    }
                    std::cout << "-------------------------------------------------------------------" << std::endl;
                    /*                                      DECODER_KATMANI_SONU                                           */
                    /*                                       BACKPROPAGATION                                            */
                    //NÖRONLAR VE SOFTMAX SONUÇLARI
                    long double ***AttentionLayerSoftMaxErr = new long double**[AttentionLayerSize];
                    long double ***AttentionSoftMaxErrorIn = new long double**[AttentionLayerSize];
                    long double **MaskedAttentionSoftMaxErr = new long double*[AttentionLayerSize];
                    long double **MaskedAttentionSoftMaxInErr = new long double*[AttentionLayerSize];
                    long double *ENeurons = new long double[EmbedSize];
                    long double **DecoderNNLayerDerr = new long double*[EmbedSize];
                    long double **DecoderAttenQueriesErr = new long double*[AttentionLayerSize];
                    long double ****EncoderDecoderKeysErr = new long double***[AttentionLayerSize];
                    long double ****EncoderDecoderValuesErr = new long double***[AttentionLayerSize];
                    long double **MaskedAttentionResultErr = new long double *[AttentionLayerSize];
                    long double **MaskedAttentionValueErr = new long double *[ResultSentence.size()*AttentionLayerSize];
                    long double **MaskedAttentionKeyErr = new long double *[ResultSentence.size()*AttentionLayerSize];
                    long double **MaskedAttentionQueryErr = new long double *[AttentionLayerSize];
                    long double **EncoderKeyErr = new long double *[Sentence0.size()*AttentionLayerSize];
                    long double **EncoderValueErr = new long double *[Sentence0.size()*AttentionLayerSize];
                    long double **EncoderQueryErr = new long double *[AttentionLayerSize];
                    long double *EncoderSelfAttentionErr = new long double [EmbedSize];
                    long double **EncoderSelfAttentionSoftMaxErr = new long double *[AttentionLayerSize];
                    long double **EncoderSelfAttentionSoftMaxInErr = new long double *[AttentionLayerSize];
                    // AĞIRLIKLAR
                    long double ***MaskedAttentionQueryWeightErr = new long double **[AttentionLayerSize];
                    long double ***MaskedAttentionValueWeightErr = new long double **[AttentionLayerSize];
                    long double ***MaskedAttentionKeyWeightErr = new long double **[AttentionLayerSize];
                    long double ***DecoderQueryWeights_Err = new long double **[AttentionLayerSize];
                    long double ***EncoderDecoderValueWeights_Err = new long double **[AttentionLayerSize];
                    long double ***EncoderDecoderKeyWeights_Err = new long double **[AttentionLayerSize];
                    long double ***EncoderKeyWeightsErr = new long double **[AttentionLayerSize];
                    long double ***EncoderValueWeightsErr = new long double **[AttentionLayerSize];
                    long double ***EncoderQueryWeightsErr = new long double **[AttentionLayerSize];
                    long double *EncoderDecoderRegressionLayerWeightsErr = new long double[EmbedSize];
                    long double EncoderDecoderRegressionBiasErr = 0;
                    long double *EncoderRegressionLayerWeightsErr = new long double[EmbedSize];
                    long double *EncoderRegressionLayerBiasErr = new long double[EmbedSize];
                    long double *DecoderRegressionLayerWeightsErr = new long double[EmbedSize];
                    long double *DecoderRegressionLayerBiasErr = new long double[EmbedSize];
                    long double *EncoderEmbedErr = new long double[EmbedSize];
                    long double *DecoderEmbedErr = new long double[EmbedSize];
                    for(int i = 0; i < Sentence0.size()*AttentionLayerSize; i++){
                        EncoderKeyErr[i] = new long double[EmbedSize/AttentionLayerSize];
                        EncoderValueErr[i] = new long double[EmbedSize/AttentionLayerSize];
                        for(int l = 0; l < EmbedSize/AttentionLayerSize; l++){
                            EncoderKeyErr[i][l] = 0;
                            EncoderValueErr[i][l] = 0;
                        }
                    }
                    for(int i = 0; i < ResultSentence.size()*AttentionLayerSize; i++){
                        MaskedAttentionValueErr[i] = new long double[EmbedSize/AttentionLayerSize];
                        MaskedAttentionKeyErr[i] = new long double[EmbedSize/AttentionLayerSize];
                        for(int l = 0; l < EmbedSize/AttentionLayerSize; l++){
                            MaskedAttentionValueErr[i][l] = 0;
                            MaskedAttentionKeyErr[i][l] = 0;
                        }
                    }
                    for(int i = 0; i < AttentionLayerSize; i++){
                        AttentionLayerSoftMaxErr[i] = new long double *[Sentence0.size()];
                        AttentionSoftMaxErrorIn[i] = new long double *[Sentence0.size()];
                        EncoderDecoderValuesErr[i] = new long double **[Sentence0.size()];
                        EncoderDecoderKeysErr[i] = new long double **[Sentence0.size()];
                        DecoderAttenQueriesErr[i] = new long double [EmbedSize/AttentionLayerSize];
                        MaskedAttentionResultErr[i] = new long double [EmbedSize/AttentionLayerSize];
                        MaskedAttentionQueryErr[i] = new long double [EmbedSize/AttentionLayerSize];
                        MaskedAttentionSoftMaxErr[i] = new long double [ResultSentence.size()*AttentionLayerSize];
                        MaskedAttentionSoftMaxInErr[i] = new long double [ResultSentence.size()*AttentionLayerSize];
                        EncoderQueryErr[i] = new long double[EmbedSize/AttentionLayerSize];
                        EncoderSelfAttentionSoftMaxErr[i] = new long double[Sentence0.size()*AttentionLayerSize];
                        EncoderSelfAttentionSoftMaxInErr[i] = new long double[Sentence0.size()*AttentionLayerSize];
                        for(int l = 0; l < ResultSentence.size()*AttentionLayerSize; l++){
                            MaskedAttentionSoftMaxErr[i][l] = 0;
                            MaskedAttentionSoftMaxInErr[i][l] = 0;
                        }
                        for(int l = 0; l < EmbedSize/AttentionLayerSize; l++){
                            EncoderQueryErr[i][l] = 0;
                            MaskedAttentionQueryErr[i][l] = 0;
                            MaskedAttentionResultErr[i][l] = 0;
                            DecoderAttenQueriesErr[i][l] = 0;
                        }
                        for(int l = 0; l < Sentence0.size(); l++){
                            AttentionLayerSoftMaxErr[i][l] = new long double[AttentionLayerSize];
                            AttentionSoftMaxErrorIn[i][l] = new long double[AttentionLayerSize];
                            EncoderDecoderValuesErr[i][l] = new long double*[AttentionLayerSize];
                            EncoderDecoderKeysErr[i][l] = new long double*[AttentionLayerSize];
                            for(int k = 0; k < AttentionLayerSize; k++){
                                AttentionLayerSoftMaxErr[i][l][k] = 0;
                                AttentionSoftMaxErrorIn[i][l][k] = 0;
                                EncoderDecoderValuesErr[i][l][k] = new long double[EmbedSize/AttentionLayerSize];
                                EncoderDecoderKeysErr[i][l][k] = new long double[EmbedSize/AttentionLayerSize];
                                for(int n = 0; n < EmbedSize/AttentionLayerSize; n++){
                                    EncoderDecoderValuesErr[i][l][k][n] = 0;
                                    EncoderDecoderKeysErr[i][l][k][n] = 0;
                                }
                            }
                        }
                        for(int l = 0; l < Sentence0.size()*AttentionLayerSize; l++){
                            EncoderSelfAttentionSoftMaxErr[i][l] = 0;
                            EncoderSelfAttentionSoftMaxInErr[i][l] = 0;
                        }
                    }
                    for(int i = 0; i < EmbedSize; i++){
                        EncoderSelfAttentionErr[i] = 0;
                        ENeurons[i] = 0;
                        DecoderNNLayerDerr[i] = new long double[tokenizedVocap2.size()];
                        EncoderDecoderRegressionLayerWeightsErr[i] = 0;
                        EncoderRegressionLayerWeightsErr[i] = 0;
                        EncoderRegressionLayerBiasErr[i] = 0;
                        DecoderRegressionLayerWeightsErr[i] = 0;
                        DecoderRegressionLayerBiasErr[i] = 0;
                        EncoderEmbedErr[i] = 0;
                        for(int l = 0; l < tokenizedVocap2.size(); l++){
                            DecoderNNLayerDerr[i][l] = 0;
                        }
                    }
                    for(int i = 0; i < AttentionLayerSize; i++){
                        MaskedAttentionQueryWeightErr[i] = new long double*[EmbedSize/AttentionLayerSize];
                        MaskedAttentionValueWeightErr[i] = new long double*[EmbedSize/AttentionLayerSize];
                        MaskedAttentionKeyWeightErr[i] = new long double*[EmbedSize/AttentionLayerSize];
                        DecoderQueryWeights_Err[i] = new long double*[EmbedSize/AttentionLayerSize];
                        EncoderDecoderValueWeights_Err[i] = new long double*[EmbedSize/AttentionLayerSize];
                        EncoderDecoderKeyWeights_Err[i] = new long double*[EmbedSize/AttentionLayerSize];
                        EncoderKeyWeightsErr[i] = new long double *[EmbedSize/AttentionLayerSize];
                        EncoderValueWeightsErr[i] = new long double *[EmbedSize/AttentionLayerSize];
                        EncoderQueryWeightsErr[i] = new long double *[EmbedSize/AttentionLayerSize];
                        for(int k = 0; k < EmbedSize/AttentionLayerSize; k++){
                            MaskedAttentionQueryWeightErr[i][k] = new long double[EmbedSize/AttentionLayerSize];
                            MaskedAttentionValueWeightErr[i][k] = new long double[EmbedSize/AttentionLayerSize];
                            MaskedAttentionKeyWeightErr[i][k] = new long double[EmbedSize/AttentionLayerSize];
                            DecoderQueryWeights_Err[i][k] = new long double[EmbedSize/AttentionLayerSize];
                            EncoderDecoderValueWeights_Err[i][k] = new long double[EmbedSize/AttentionLayerSize];
                            EncoderDecoderKeyWeights_Err[i][k] = new long double[EmbedSize/AttentionLayerSize];
                            EncoderKeyWeightsErr[i][k] = new long double[EmbedSize/AttentionLayerSize];
                            EncoderValueWeightsErr[i][k] = new long double[EmbedSize/AttentionLayerSize];
                            EncoderQueryWeightsErr[i][k] = new long double[EmbedSize/AttentionLayerSize];
                            for(int l = 0; l < EmbedSize/AttentionLayerSize; l++){
                                MaskedAttentionQueryWeightErr[i][k][l] = 0;
                                MaskedAttentionValueWeightErr[i][k][l] = 0;
                                MaskedAttentionKeyWeightErr[i][k][l] = 0;
                                DecoderQueryWeights_Err[i][k][l] = 0;
                                EncoderDecoderKeyWeights_Err[i][k][l] = 0;
                                EncoderDecoderValueWeights_Err[i][k][l] = 0;
                                EncoderKeyWeightsErr[i][k][l] = 0;
                                EncoderValueWeightsErr[i][k][l] = 0;
                                EncoderQueryWeightsErr[i][k][l] = 0;
                            }
                        }
                    }
                    // LOSS HESAPLAMASI
                    long double *Loss = new long double [tokenizedVocap2.size()];
                    for(int i = 0; i < tokenizedVocap2.size(); i++)
                        Loss[i] = 0;
                    for(int i = 0; i < LossValues.size(); i++){
                        for(int l = 0; l < tokenizedVocap2.size(); l++)
                            Loss[l] += LossValues[i][l] / LossValues.size();
                    }
                    for(int i = 0; i < tokenizedVocap2.size(); i++){
                        std::cout << "Loss " << i << ":" << Loss[i] << std::endl;
                    }
                    long double RegLoss = 0;
                    for(int i = 0; i < ResultSentence.size(); i++)
                        RegLoss += RegressionErr[i] / ResultSentence.size();
                    for(int i = 0; i < EmbedSize; i++)
                        ENeurons[i] += RegLoss * EncoderDecoderRegressionLayerWeights[i];
                    for(int i = 0; i < ResultSentence.size(); i++){
                        for(int j = 0; j < EmbedSize; j++)
                            EncoderDecoderRegressionLayerWeightsErr[j] += (Encoder_DecoderAttention[i][j]/ResultSentence.size()) * RegLoss;
                    }
                    EncoderDecoderRegressionBiasErr = RegLoss;
                    /*                                      FULL_NN_KATMANI-SONRAKİ_DEĞERİ_TAHMİN_ETME_GERİ_YAYILIM_BAŞLANGICI                                         */
                    for(int i = 0; i < EmbedSize; i++){
                        for(int j = 0; j < tokenizedVocap2.size(); j++)
                            ENeurons[i] += DecoderNNLayerWeights[i][j] * Loss[j];
                    }
                    for(int i = 0; i < ResultSentence.size(); i++){
                        for(int j = 0; j < EmbedSize; j++){
                            for(int k = 0; k < tokenizedVocap2.size(); k++)
                                DecoderNNLayerDerr[j][k] += (Encoder_DecoderAttention[i][j]/ResultSentence.size()) * Loss[k];
                        }
                    }
                    /*                                       FULL_NN_KATMANI-SONRAKİ_DEĞERİ_TAHMİN_ETME_GERİ_YAYILIM_SONU                                           */
                    /*                                              ATTENTION_KATMANI_BACKPROPAGATION_BAŞLANGICI                                                    */
                    // DECODER ATTENTION SOFTMAX'E HATA DAĞITIMI
                    // DECODER ATTENTION ENCODER SON VALUE'LARA HATA DAĞITIMI
                    for(int j = 0; j < AttentionLayerSize; j++){
                        for(int l = 0; l < Sentence0.size(); l++){
                            for(int k = 0; k < AttentionLayerSize; k++){
                                for(int n = 0; n < EmbedSize/AttentionLayerSize; n++)
                                    AttentionLayerSoftMaxErr[j][l][k] += (EncoderValues[l][k][n] / Sentence0.size()) * ENeurons[(j*(EmbedSize/AttentionLayerSize))+n];
                            }
                        }
                    }
                    for(int i = 0; i < ResultSentence.size(); i++){
                        for(int j = 0; j < AttentionLayerSize; j++){
                            for(int l = 0; l < Sentence0.size(); l++){
                                for(int k = 0; k < AttentionLayerSize; k++){
                                    for(int n = 0; n < EmbedSize/AttentionLayerSize; n++)
                                        EncoderDecoderValuesErr[j][l][k][n] += ENeurons[(k*(EmbedSize/AttentionLayerSize))+n] * (AttentionLayerSoftMaxResults[i][j][(l*AttentionLayerSize)+k]/(AttentionLayerSize*ResultSentence.size()));
                                }
                            }
                        }
                    }
                    for(int j = 0; j < AttentionLayerSize; j++){
                        for(int l = 0; l < Sentence0.size(); l++){
                            for(int k = 0; k < AttentionLayerSize; k++){
                                for(int n = 0; n < EmbedSize/AttentionLayerSize; n++){
                                    for(int h = 0; h < EmbedSize/AttentionLayerSize; h++){
                                        EncoderSelfAttentionErr[(k *(EmbedSize/AttentionLayerSize))+h] += (EncoderDecoderValuesErr[j][l][k][n]/Sentence0.size()) * EncoderValueWeights_[k][h][n];
                                    }
                                }
                            }
                        }
                    }
                    // DECODER ATTENTION QUERY-KEY HESAPLAMALARINA HATA DAĞITIMI
                    long double additionF = 0;
                    for(int i = 0; i < ResultSentence.size(); i++){
                        for(int j = 0; j < AttentionLayerSize; j++){
                            for(int h = 0; h < Sentence0.size(); h++){
                                for(int f = 0; f < AttentionLayerSize; f++)
                                    additionF += AttentionLayerSoftMaxErr[j][h][f] * (AttentionLayerSoftMaxResults[i][j][(h*AttentionLayerSize)+f]/(AttentionLayerSize*ResultSentence.size()));
                            }
                        }
                    }
                    for(int i = 0; i < ResultSentence.size(); i++){
                        for(int j = 0; j < AttentionLayerSize; j++){
                            for(int l = 0; l < Sentence0.size(); l++){
                                for(int k = 0; k < AttentionLayerSize; k++)
                                    AttentionSoftMaxErrorIn[j][l][k] += (AttentionLayerSoftMaxResults[i][j][(l*AttentionLayerSize)+k]/(AttentionLayerSize*ResultSentence.size())) * (AttentionLayerSoftMaxErr[j][l][k] - additionF);
                            }
                        }
                    }
                    // DECODER ATTENTION ENCODER SON KEY'E HATA DAĞITIMI
                    for(int i = 0; i < ResultSentence.size(); i++){
                        for(int j = 0; j < AttentionLayerSize; j++){
                            for(int l = 0; l < Sentence0.size(); l++){
                                for(int k = 0; k < AttentionLayerSize; k++){
                                    for(int v = 0; v < EmbedSize/AttentionLayerSize; v++)
                                        EncoderDecoderKeysErr[j][l][k][v] += AttentionSoftMaxErrorIn[j][l][k] * (DecoderAttentionQuery[i][j][v]/ResultSentence.size());
                                }
                            }
                        }
                    }
                    for(int j = 0; j < AttentionLayerSize; j++){
                        for(int l = 0; l < Sentence0.size(); l++){
                            for(int k = 0; k < AttentionLayerSize; k++){
                                for(int v = 0; v < EmbedSize/AttentionLayerSize; v++){
                                    for(int h = 0; h < EmbedSize/AttentionLayerSize; h++){
                                        EncoderSelfAttentionErr[(k*(EmbedSize/AttentionLayerSize))+h] += EncoderDecoderKeysErr[j][l][k][v] * EncoderKeyWeights_[k][h][v];
                                    }
                                }
                            }
                        }
                    }
                    // DECODER ATTENTION DECODER QUERY'YE HATA DAĞITIMI
                    for(int j = 0; j < AttentionLayerSize; j++){
                        for(int l = 0; l < EmbedSize/AttentionLayerSize; l++){
                            for(int v = 0; v < Sentence0.size(); v++){
                                for(int k = 0; k < AttentionLayerSize; k++)
                                    DecoderAttenQueriesErr[j][l] += (EncoderKeys[v][k][l]/Sentence0.size()) * AttentionSoftMaxErrorIn[j][v][k];
                            }
                        }
                    }
                    // AĞIRLIKLARA HATA DAĞITIMI
                    for(int i = 0; i < ResultSentence.size(); i++){
                        for(int j = 0; j < AttentionLayerSize; j++){
                            for(int l = 0; l < EmbedSize/AttentionLayerSize; l++){
                                for(int v = 0; v < EmbedSize/AttentionLayerSize; v++)
                                    DecoderQueryWeights_Err[j][l][v] += (Decoder_SelfAttention[i][(j*(EmbedSize/AttentionLayerSize))+l]/ResultSentence.size())*DecoderAttenQueriesErr[j][v];
                            }
                        }
                    }
                    for(int j = 0; j < AttentionLayerSize; j++){
                        for(int f = 0; f < Sentence0.size(); f++){
                            for(int l = 0; l < AttentionLayerSize; l++){
                                for(int v = 0; v < EmbedSize/AttentionLayerSize; v++){
                                    for(int d = 0; d < EmbedSize/AttentionLayerSize; d++){
                                        EncoderDecoderKeyWeights_Err[l][v][d] += (SelfAttentionValues[f][(l*(EmbedSize/AttentionLayerSize) + v)]/Sentence0.size()) * EncoderDecoderKeysErr[j][f][l][d];
                                        EncoderDecoderValueWeights_Err[l][v][d] += (SelfAttentionValues[f][(l*(EmbedSize/AttentionLayerSize) + v)]/Sentence0.size()) * EncoderDecoderValuesErr[j][f][l][d];
                                    }
                                }
                            }
                        }
                    }
                    // MASKED SELF ATTENTION DEĞERİNE HATA DAĞITIMI
                    for(int j = 0; j < AttentionLayerSize; j++){
                        for(int l = 0; l < EmbedSize/AttentionLayerSize; l++){
                            for(int h = 0; h < EmbedSize/AttentionLayerSize; h++)
                                MaskedAttentionResultErr[j][l] += DecoderAttenQueriesErr[j][h]*DecoderQueryWeights_[j][l][h];
                        }
                    }
                    /*                                                  ATTENTION_KATMANI_BACKPROPAGATION_SONU                                                         */
                    /*                                       DECODER_MASKED_SELF_ATTENTION_KATMANI_BACKPROPAGATION_BAŞLANGICI                                              */
                    //std::cout << "Pass 7 : BACKPROPAGATION MASKED" << std::endl;
                    //  DECODER MASKED ATTENTION VALUE VE SOFTMAX'E HATA DAĞITIMI
                    for(int i = 0; i < ResultSentence.size(); i++){
                        for(int j = 0; j < AttentionLayerSize; j++){
                            for(int l = 0; l < AttentionLayerSize; l++){
                                for(int c = 0; c < i+1; c++){
                                    for(int h = 0; h < EmbedSize/AttentionLayerSize; h++){
                                        MaskedAttentionValueErr[(c*AttentionLayerSize)+l][h] += (MaskedSelfAttentionSoftMaxResults[i][j][(c * AttentionLayerSize)+l]/(ResultSentence.size()*AttentionLayerSize))*MaskedAttentionResultErr[l][h];
                                        MaskedAttentionSoftMaxErr[j][(c*AttentionLayerSize)+l] += MaskedAttentionResultErr[l][h] * (DecoderValues[c][l][h]/ResultSentence.size()); /// TODO: Check this code later! Should it be in this for loop? int i ?
                                    }
                                }
                            }
                        }
                    }
                    // DECODER MASKED ATTENTION QUERY-KEY HESAPLAMALINA HATA DAĞITIMI
                    // TODO: CHECK THIS CODE TOO. THIS CODE WRITTEN BY LOOKING TO UPSIDE CODES.
                    long double AddF = 0;
                    for(int i = 0; i < ResultSentence.size(); i++){
                        for(int j = 0; j < AttentionLayerSize; j++){
                            for(int v = 0; v < AttentionLayerSize; v++){
                                for(int h = 0; h < i+1; h++){
                                    AddF += MaskedAttentionSoftMaxErr[j][(h*AttentionLayerSize)+v] * (MaskedSelfAttentionSoftMaxResults[i][j][(h * AttentionLayerSize)+v]/(ResultSentence.size()*AttentionLayerSize));
                                }
                            }
                        }
                    }
                    for(int i = 0; i < ResultSentence.size(); i++){
                        for(int j = 0; j < AttentionLayerSize; j++){
                            for(int l = 0; l < AttentionLayerSize; l++){
                                for(int c = 0; c < i+1; c++){
                                    MaskedAttentionSoftMaxInErr[j][(c * AttentionLayerSize)+l] += (MaskedSelfAttentionSoftMaxResults[i][j][(c*AttentionLayerSize)+l]/(ResultSentence.size()*AttentionLayerSize))*(MaskedAttentionSoftMaxErr[j][(c*AttentionLayerSize)+l]-AddF);
                                }
                            }
                        }
                    }
                    // DECODER MASKED ATTENTION QUERY'YE HATA DAĞITIMI
                    for(int i = 0; i < ResultSentence.size(); i++){
                        for(int j = 0; j < AttentionLayerSize; j++){
                            for(int l = 0; l < EmbedSize/AttentionLayerSize; l++){
                                for(int v = 0; v < i+1; v++){
                                    for(int h = 0; h < AttentionLayerSize; h++)
                                        MaskedAttentionQueryErr[j][l] += (MaskedAttentionSoftMaxInErr[j][(v * AttentionLayerSize)+h]/ResultSentence.size())*(DecoderKeys[v][h][l]/ResultSentence.size());
                                }
                            }
                        }
                    }
                    // DECODER MASKED ATTENTION KEY'E HATA DAĞITIMI
                    for(int i = 0; i < ResultSentence.size(); i++){
                        for(int j = 0; j < AttentionLayerSize; j++){
                            for(int c = 0; c < i+1; c++){
                                for(int l = 0; l < AttentionLayerSize; l++){
                                    for(int h = 0; h < EmbedSize/AttentionLayerSize; h++){
                                        MaskedAttentionKeyErr[(c*AttentionLayerSize)+l][h] += (MaskedAttentionSoftMaxInErr[j][(c*AttentionLayerSize)+l]/ResultSentence.size())*(DecoderQueries[i][j][h]/ResultSentence.size());
                                    }
                                }
                            }
                        }
                    }
                    //DECODER REGRESYON KATMANINA HATA DAĞITIMI
                    for(int i = 0; i < EmbedSize; i++){
                        for(int j = 0; j < AttentionLayerSize; j++){
                            for(int l = 0; l < EmbedSize/AttentionLayerSize; l++)
                                DecoderEmbedErr[i] += MaskedAttentionQueryErr[j][l] * DecoderQueryWeights[j][i][l];
                        }
                        for(int c = 0; c < ResultSentence.size(); c++){
                            for(int l = 0; l < AttentionLayerSize; l++){
                                for(int h = 0; h < EmbedSize/AttentionLayerSize; h++){
                                    DecoderEmbedErr[i] += MaskedAttentionKeyErr[(c*AttentionLayerSize)+l][h] * DecoderKeyWeights[l][i][h];
                                    DecoderEmbedErr[i] += MaskedAttentionValueErr[(c*AttentionLayerSize)+l][h] * DecoderValueWeights[l][i][h];
                                }
                            }
                        }
                    }
                    for(int i = 0; i < EmbedSize; i++){
                        for(int l = 0; l < ResultSentence.size()+1; l++)
                            DecoderRegressionLayerWeightsErr[i] += DecoderEmbedErr[i] * (ResultValues.at(l)/ResultSentence.size());
                        DecoderRegressionLayerBiasErr[i] += DecoderEmbedErr[i];
                    }
                    // DECODER MASKED SELF ATTENTION AĞIRLIKLARA HATA DAĞITIMI
                    for(int i = 0; i < ResultSentence.size(); i++){
                        for(int j = 0; j < AttentionLayerSize; j++){
                            for(int k = 0; k < EmbedSize/AttentionLayerSize; k++){
                                for(int l = 0; l < EmbedSize/AttentionLayerSize; l++)
                                    MaskedAttentionQueryWeightErr[j][k][l] += MaskedAttentionQueryErr[j][l] * (EmbedResults1[i][(j*(EmbedSize/AttentionLayerSize))+k]/ResultSentence.size());
                            }
                            for(int c = 0; c < ResultSentence.size(); c++){
                                for(int k = 0; k < EmbedSize/AttentionLayerSize; k++){
                                    for(int l = 0; l < EmbedSize/AttentionLayerSize; l++){
                                        MaskedAttentionValueWeightErr[j][k][l] += MaskedAttentionValueErr[(c * AttentionLayerSize)+j][l] * (EmbedResults1[i][(j*(EmbedSize/AttentionLayerSize))+k]/ResultSentence.size());
                                        MaskedAttentionKeyWeightErr[j][k][l] += MaskedAttentionKeyErr[(c * AttentionLayerSize)+j][l] * (EmbedResults1[i][(j*(EmbedSize/AttentionLayerSize))+k]/ResultSentence.size());
                                    }
                                }
                            }
                        }
                    }
                    /*                                        DECODER_MASKED_SELF_ATTENTION_KATMANI_BACKPROPAGATION_SONU                                               */
                    /*                                              ENCODER_SELF_ATTENTION_KATMANI_BACKPROPAGATION_BAŞLANGICI                                                  */
                    //std::cout << "Pass 8 : BACKPROPAGATION SELF ATTENTION" << std::endl;
                    // ENCODER ATTENTION VALUE VE SOFTMAX'E HATA DAĞITIMI
                    for(int i = 0; i < Sentence0.size(); i++){
                        for(int k = 0; k < AttentionLayerSize; k++){
                            for(int c = 0; c < Sentence0.size(); c++){
                                for(int l = 0; l < AttentionLayerSize; l++){
                                    for(int h = 0; h < EmbedSize/AttentionLayerSize; h++){
                                        EncoderSelfAttentionSoftMaxErr[k][(c* AttentionLayerSize) + l] += (Values[c][l][h]/Sentence0.size()) * EncoderSelfAttentionErr[(l*(EmbedSize/AttentionLayerSize))+h];
                                        EncoderValueErr[(c*AttentionLayerSize)+l][h] += (EncoderSelfAttentionSoftMax[i][k][(c*AttentionLayerSize)+l]/(Sentence0.size()*AttentionLayerSize)) * EncoderSelfAttentionErr[(l*(EmbedSize/AttentionLayerSize))+h];
                                    }
                                }
                            }
                        }
                    }
                    // ENCODER ATTENTION QUERY-KEY HESAPLAMALARINA HATA DAĞITIMI
                    long double AddF0 = 0;
                    for(int i = 0; i < Sentence0.size(); i++){
                        for(int k = 0; k < AttentionLayerSize; k++){
                            for(int v = 0; v < AttentionLayerSize; v++){
                                for(int h = 0; h < Sentence0.size(); h++)
                                    AddF0 += EncoderSelfAttentionSoftMaxErr[k][(h * AttentionLayerSize)+v] * (EncoderSelfAttentionSoftMax[i][k][(h * AttentionLayerSize)+v]/Sentence0.size());
                            }
                        }
                    }
                    for(int i = 0; i < Sentence0.size(); i++){
                        for(int k = 0; k < AttentionLayerSize; k++){
                            for(int l = 0; l < AttentionLayerSize; l++){
                                for(int c = 0; c < Sentence0.size(); c++){
                                    EncoderSelfAttentionSoftMaxInErr[k][(c * AttentionLayerSize)+l] += (EncoderSelfAttentionSoftMax[i][k][(c * AttentionLayerSize)+l]/(Sentence0.size()*AttentionLayerSize)) * (EncoderSelfAttentionSoftMaxErr[k][(c * AttentionLayerSize)+l] - AddF0);
                                }
                            }
                        }
                    }
                    // ENCODER ATTENTION QUERY'YE HATA DAĞITIMI
                    for(int k = 0; k < AttentionLayerSize; k++){
                        for(int l = 0; l < EmbedSize/AttentionLayerSize; l++){
                            for(int v = 0; v < Sentence0.size(); v++){
                                for(int h = 0; h < AttentionLayerSize; h++)
                                    EncoderQueryErr[k][l] += (EncoderSelfAttentionSoftMaxInErr[k][(v * AttentionLayerSize)+h]/Sentence0.size()) * (Keys[v][h][l]/Sentence0.size());
                            }
                        }
                    }
                    // ENCODER ATTENTION KEY'E HATA DAĞITIMI
                    for(int i = 0; i < Sentence0.size(); i++){
                        for(int k = 0; k < AttentionLayerSize; k++){
                            for(int c = 0; c < Sentence0.size(); c++){
                                for(int l = 0; l < AttentionLayerSize; l++){
                                    for(int h = 0; h < EmbedSize/AttentionLayerSize; h++)
                                        EncoderKeyErr[(c*AttentionLayerSize)+l][h] += (EncoderSelfAttentionSoftMaxInErr[k][(c*AttentionLayerSize)+l]/Sentence0.size()) * (Values[i][k][h]/Sentence0.size());
                                }
                            }
                        }
                    }
                    // ENCODER REGRESYON KATMANINA HATA DAĞITIMI
                    for(int i = 0; i < EmbedSize; i++){
                        for(int k = 0; k < AttentionLayerSize; k++){
                            for(int l = 0; l < EmbedSize/AttentionLayerSize; l++)
                                EncoderEmbedErr[i] += EncoderQueryErr[k][l] * EncoderQueryWeights[k][i][l];
                        }
                        for(int k = 0; k < Sentence0.size(); k++){
                            for(int l = 0; l < AttentionLayerSize; l++){
                                for(int h = 0; h < EmbedSize/AttentionLayerSize; h++){
                                    EncoderEmbedErr[i] += EncoderValueErr[(k*AttentionLayerSize)+l][h] * EncoderValueWeights[l][i][h];
                                    EncoderEmbedErr[i] += EncoderKeyErr[(k*AttentionLayerSize)+l][h] * EncoderKeyWeights[l][i][h];
                                }
                            }
                        }
                    }
                    for(int i = 0; i < EmbedSize; i++){
                        for(int l = 0; l < Sentence0.size()+1; l++)
                            EncoderRegressionLayerWeightsErr[i] += EncoderEmbedErr[i] * (CategoryValue0.at(l)/Sentence0.size());
                        EncoderRegressionLayerBiasErr[i] += EncoderEmbedErr[i];
                    }
                    // ENCODER AĞIRLIKLARA HATA DAĞITIMI
                    for(int i = 0; i < Sentence0.size(); i++){
                        for(int k = 0; k < AttentionLayerSize; k++){
                            for(int l = 0; l < EmbedSize/AttentionLayerSize; l++){
                                for(int n = 0; n < EmbedSize/AttentionLayerSize; n++)
                                    EncoderQueryWeightsErr[k][l][n] += EncoderQueryErr[k][n] * (EmbedResults0[i][(k * (EmbedSize/AttentionLayerSize)) + l]/Sentence0.size());
                            }
                            for(int c = 0; c < Sentence0.size(); c++){
                                for(int l = 0; l < EmbedSize/AttentionLayerSize; l++){
                                    for(int n = 0; n < EmbedSize/AttentionLayerSize; n++){
                                        EncoderValueWeightsErr[k][l][n] += EncoderValueErr[(c * AttentionLayerSize)+k][n] * (EmbedResults0[i][(k*(EmbedSize/AttentionLayerSize))+l]/Sentence0.size());
                                        EncoderKeyWeightsErr[k][l][n] += EncoderKeyErr[(c * AttentionLayerSize)+k][n] * (EmbedResults0[i][(k*(EmbedSize/AttentionLayerSize))+l]/Sentence0.size());
                                    }
                                }
                            }
                        }
                    }
                    /*                                               ENCODER_SELF_ATTENTION_KATMANI_BACKPROPAGATION_SONU                                                  */
                    // AĞIRLIKLARI GÜNCELLE
                    for(int i = 0; i < AttentionLayerSize; i++){
                        for(int k = 0; k < EmbedSize/AttentionLayerSize; k++){
                            for(int l = 0; l < EmbedSize/AttentionLayerSize; l++){
                                EncoderQueryWeights[i][k][l] -= EncoderQueryWeightsErr[i][k][l] * learningRate;
                                EncoderValueWeights[i][k][l] -= EncoderValueWeightsErr[i][k][l] * learningRate;
                                EncoderKeyWeights[i][k][l] -= EncoderKeyWeightsErr[i][k][l] * learningRate;
                                DecoderQueryWeights[i][k][l] -= MaskedAttentionQueryWeightErr[i][k][l] * learningRate;
                                DecoderValueWeights[i][k][l] -= MaskedAttentionValueWeightErr[i][k][l] * learningRate;
                                DecoderKeyWeights[i][k][l] -= MaskedAttentionKeyWeightErr[i][k][l] * learningRate;
                                DecoderQueryWeights_[i][k][l] -= DecoderQueryWeights_Err[i][k][l] * learningRate;
                                EncoderKeyWeights_[i][k][l] -= EncoderDecoderKeyWeights_Err[i][k][l] * learningRate;
                                EncoderValueWeights_[i][k][l] -= EncoderDecoderValueWeights_Err[i][k][l] * learningRate;
                                /*std::cout << " EncoderQueryWeights(" << i << "." << k << "." << l << "): " << EncoderQueryWeights[i][k][l] << " EncoderQueryWeightsErr(" << i << "." << k << "." << l << "): " << EncoderQueryWeightsErr[i][k][l] << std::endl;
                                std::cout << " EncoderValueWeights(" << i << "." << k << "." << l << "): " << EncoderValueWeights[i][k][l] << " EncoderValueWeightsErr(" << i << "." << k << "." << l << "): " << EncoderValueWeightsErr[i][k][l] << std::endl;
                                std::cout << " EncoderKeyWeights(" << i << "." << k << "." << l << "): " << EncoderKeyWeights[i][k][l] << " EncoderKeyWeightsErr(" << i << "." << k << "." << l << "): " << EncoderKeyWeightsErr[i][k][l] << std::endl;
                                std::cout << " DecoderQueryWeights(" << i << "." << k << "." << l << "): " << DecoderQueryWeights[i][k][l] << " MaskedAttentionQueryWeightErr(" << i << "." << k << "." << l << "): " << MaskedAttentionQueryWeightErr[i][k][l] << std::endl;
                                std::cout << " DecoderValueWeights(" << i << "." << k << "." << l << "): " << DecoderValueWeights[i][k][l] << " MaskedAttentionValueWeightErr(" << i << "." << k << "." << l << "): " << MaskedAttentionValueWeightErr[i][k][l] << std::endl;
                                std::cout << " DecoderKeyWeights(" << i << "." << k << "." << l << "): " << DecoderKeyWeights[i][k][l] << " MaskedAttentionKeyWeightErr(" << i << "." << k << "." << l << "): " << MaskedAttentionKeyWeightErr[i][k][l] << std::endl;
                                std::cout << " DecoderQueryWeights_(" << i << "." << k << "." << l << "): " << DecoderQueryWeights_[i][k][l] << " DecoderQueryWeights_Err(" << i << "." << k << "." << l << "): " << DecoderQueryWeights_Err[i][k][l] << std::endl;
                                std::cout << " EncoderKeyWeights_(" << i << "." << k << "." << l << "): " << EncoderKeyWeights_[i][k][l] << " EncoderDecoderKeyWeights_Err(" << i << "." << k << "." << l << "): " << EncoderDecoderKeyWeights_Err[i][k][l] << std::endl;
                                std::cout << " EncoderValueWeights_(" << i << "." << k << "." << l << "): " << EncoderValueWeights_[i][k][l] << " EncoderDecoderValueWeights_Err(" << i << "." << k << "." << l << "): " << EncoderDecoderValueWeights_Err[i][k][l] << std::endl;*/
                            }
                        }
                    }
                    for(int i = 0; i < EmbedSize; i++){
                        EncoderDecoderRegressionLayerWeights[i] -= EncoderDecoderRegressionLayerWeightsErr[i] * learningRate;
                        EncoderRegressionLayerWeights[i] -= EncoderRegressionLayerWeightsErr[i] * learningRate;
                        EncoderRegressionBias[i] -= EncoderRegressionLayerBiasErr[i] * learningRate;
                        DecoderRegressionLayerWeights[i] -= DecoderRegressionLayerWeightsErr[i] * learningRate;
                        DecoderRegressionBias[i] -= DecoderRegressionLayerBiasErr[i] * learningRate;
                    }
                    EncoderDecoderRegressionBias -= EncoderDecoderRegressionBias * learningRate;
                    std::cout << " EncoderQueryWeights(" << 0 << "." << 0 << "." << 0 << "): " << EncoderQueryWeights[0][0][0] << " EncoderQueryWeightsErr(" << 0 << "." << 0 << "." << 0 << "): " << EncoderQueryWeightsErr[0][0][0] << std::endl;
                    std::cout << " EncoderValueWeights(" << 0 << "." << 0 << "." << 0 << "): " << EncoderValueWeights[0][0][0] << " EncoderValueWeightsErr(" << 0 << "." << 0 << "." << 0 << "): " << EncoderValueWeightsErr[0][0][0] << std::endl;
                    std::cout << " EncoderKeyWeights(" << 0 << "." << 0 << "." << 0 << "): " << EncoderKeyWeights[0][0][0] << " EncoderKeyWeightsErr(" << 0 << "." << 0 << "." << 0 << "): " << EncoderKeyWeightsErr[0][0][0] << std::endl;
                    std::cout << " DecoderQueryWeights(" << 0 << "." << 0 << "." << 0 << "): " << DecoderQueryWeights[0][0][0] << " MaskedAttentionQueryWeightErr(" << 0 << "." << 0 << "." << 0 << "): " << MaskedAttentionQueryWeightErr[0][0][0] << std::endl;
                    std::cout << " DecoderValueWeights(" << 0 << "." << 0 << "." << 0 << "): " << DecoderValueWeights[0][0][0] << " MaskedAttentionValueWeightErr(" << 0 << "." << 0 << "." << 0 << "): " << MaskedAttentionValueWeightErr[0][0][0] << std::endl;
                    std::cout << " DecoderKeyWeights(" << 0 << "." << 0 << "." << 0 << "): " << DecoderKeyWeights[0][0][0] << " MaskedAttentionKeyWeightErr(" << 0 << "." << 0 << "." << 0 << "): " << MaskedAttentionKeyWeightErr[0][0][0] << std::endl;
                    std::cout << " DecoderQueryWeights_(" << 0 << "." << 0 << "." << 0 << "): " << DecoderQueryWeights_[0][0][0] << " DecoderQueryWeights_Err(" << 0 << "." << 0 << "." << 0 << "): " << DecoderQueryWeights_Err[0][0][0] << std::endl;
                    std::cout << " EncoderKeyWeights_(" << 0 << "." << 0 << "." << 0 << "): " << EncoderKeyWeights_[0][0][0] << " EncoderDecoderKeyWeights_Err(" << 0 << "." << 0 << "." << 0 << "): " << EncoderDecoderKeyWeights_Err[0][0][0] << std::endl;
                    std::cout << " EncoderValueWeights_(" << 0 << "." << 0 << "." << 0 << "): " << EncoderValueWeights_[0][0][0] << " EncoderDecoderValueWeights_Err(" << 0 << "." << 0 << "." << 0 << "): " << EncoderDecoderValueWeights_Err[0][0][0] << std::endl;
                    for(int k = 0; k < ResultSentence.size(); k++){
                        for(int l = 0; l < EmbedSize; l++){
                            for(int v = 0; v < tokenizedVocap2.size(); v++){
                                DecoderNNLayerWeights[l][v] -= DecoderNNLayerDerr[l][v] * learningRate;
                                //std::cout << " DecoderNNLayerWeights(" << l << "." << v << "): " << DecoderNNLayerWeights[l][v] << " DecoderNNLayerDerr(" << l << "." << v << "): " << DecoderNNLayerDerr[l][v] << std::endl;
                            }
                        }
                    }
                    // DEĞİŞKENLERİ SİLER /// TODO: SOME OF THEM SHOULDN'T BE TEMPORARY!
                    for(int i = 0; i < DecoderQueries.size(); i++){
                        for(int k = 0; k < AttentionLayerSize; k++){
                            delete[] DecoderQueries[i][k];
                            delete[] DecoderValues[i][k];
                            delete[] DecoderKeys[i][k];
                            delete[] MaskedSelfAtQueryKeyCal[i][k];
                            delete[] DecoderAttentionQuery[i][k];
                            delete[] DecoderAttentionQueryKeyCal[i][k];
                        }
                        delete[] DecoderQueries[i];
                        delete[] DecoderValues[i];
                        delete[] DecoderKeys[i];
                        delete[] MaskedSelfAtQueryKeyCal[i];
                        delete[] Encoder_DecoderAttention[i];
                        delete[] Decoder_SelfAttention[i];
                        delete[] DecoderAttentionQuery[i];
                        delete[] DecoderAttentionQueryKeyCal[i];
                    }
                    for(int i = 0; i < Sentence0.size(); i++){
                        for(int l = 0; l < AttentionLayerSize; l++){
                            delete[] Queries[i][l];
                            delete[] Values[i][l];
                            delete[] Keys[i][l];
                            delete[] QueryKeyCalculations_Encoder[i][l];
                            delete[] EncoderKeys[i][l];
                            delete[] EncoderValues[i][l];
                        }
                        delete[] Queries[i];
                        delete[] Values[i];
                        delete[] Keys[i];
                        delete[] SelfAttentionValues[i];
                        delete[] QueryKeyCalculations_Encoder[i];
                        delete[] EncoderKeys[i];
                        delete[] EncoderValues[i];
                    }
                    for(int i = 0; i < AttentionLayerSize; i++){
                        for(int k = 0; k <EmbedSize/AttentionLayerSize; k++){
                            delete[] MaskedAttentionQueryWeightErr[i][k];
                            delete[] MaskedAttentionValueWeightErr[i][k];
                            delete[] MaskedAttentionKeyWeightErr[i][k];
                            delete[] DecoderQueryWeights_Err[i][k];
                            delete[] EncoderDecoderValueWeights_Err[i][k];
                            delete[] EncoderDecoderKeyWeights_Err[i][k];
                            delete[] EncoderKeyWeightsErr[i][k];
                            delete[] EncoderValueWeightsErr[i][k];
                            delete[] EncoderQueryWeightsErr[i][k];
                        }
                        delete[] MaskedAttentionQueryWeightErr[i];
                        delete[] MaskedAttentionValueWeightErr[i];
                        delete[] MaskedAttentionKeyWeightErr[i];
                        delete[] DecoderQueryWeights_Err[i];
                        delete[] EncoderDecoderValueWeights_Err[i];
                        delete[] EncoderDecoderKeyWeights_Err[i];
                        delete[] EncoderKeyWeightsErr[i];
                        delete[] EncoderValueWeightsErr[i];
                        delete[] EncoderQueryWeightsErr[i];
                        delete[] EncoderSelfAttentionSoftMaxErr[i];
                        delete[] EncoderSelfAttentionSoftMaxInErr[i];
                        delete[] EncoderQueryErr[i];
                    }
                    for(int i = 0; i < ResultSentence.size()*AttentionLayerSize; i++){
                        delete[] MaskedAttentionValueErr[i];
                        delete[] MaskedAttentionKeyErr[i];
                    }
                    for(int i = 0; i < AttentionLayerSize; i++){
                        for(int l = 0; l < Sentence0.size(); l++){
                            for(int k = 0; k < AttentionLayerSize; k++){
                                delete[] EncoderDecoderValuesErr[i][l][k];
                                delete[] EncoderDecoderKeysErr[i][l][k];
                            }
                            delete[] AttentionSoftMaxErrorIn[i][l];
                            delete[] AttentionLayerSoftMaxErr[i][l];
                            delete[] EncoderDecoderValuesErr[i][l];
                            delete[] EncoderDecoderKeysErr[i][l];
                        }
                        delete[] MaskedAttentionQueryErr[i];
                        delete[] MaskedAttentionResultErr[i];
                        delete[] MaskedAttentionSoftMaxErr[i];
                        delete[] MaskedAttentionSoftMaxInErr[i];
                        delete[] DecoderAttenQueriesErr[i];
                        delete[] AttentionSoftMaxErrorIn[i];
                        delete[] AttentionLayerSoftMaxErr[i];
                        delete[] EncoderDecoderValuesErr[i];
                        delete[] EncoderDecoderKeysErr[i];
                    }
                    for(int i = 0; i < EmbedSize; i++)
                        delete[] DecoderNNLayerDerr[i];
                    delete[] EncoderDecoderRegressionLayerWeightsErr;
                    delete[] EncoderRegressionLayerWeightsErr;
                    delete[] EncoderRegressionLayerBiasErr;
                    delete[] DecoderRegressionLayerWeightsErr;
                    delete[] DecoderRegressionLayerBiasErr;
                    delete[] Queries;
                    delete[] Values;
                    delete[] Keys;
                    delete[] SelfAttentionValues;
                    delete[] QueryKeyCalculations_Encoder;
                    delete[] EncoderKeys;
                    delete[] EncoderValues;
                    delete[] AttentionLayerSoftMaxErr;
                    delete[] AttentionSoftMaxErrorIn;
                    delete[] MaskedAttentionSoftMaxErr;
                    delete[] MaskedAttentionSoftMaxInErr;
                    delete[] ENeurons;
                    delete[] DecoderNNLayerDerr;
                    delete[] DecoderAttenQueriesErr;
                    delete[] EncoderDecoderKeysErr;
                    delete[] EncoderDecoderValuesErr;
                    delete[] MaskedAttentionResultErr;
                    delete[] MaskedAttentionValueErr;
                    delete[] MaskedAttentionKeyErr;
                    delete[] MaskedAttentionQueryErr;
                    delete[] EncoderKeyErr;
                    delete[] EncoderQueryErr;
                    delete[] EncoderSelfAttentionErr;
                    delete[] EncoderSelfAttentionSoftMaxErr;
                    delete[] EncoderSelfAttentionSoftMaxInErr;
                    delete[] MaskedAttentionQueryWeightErr;
                    delete[] MaskedAttentionValueWeightErr;
                    delete[] MaskedAttentionKeyWeightErr;
                    delete[] DecoderQueryWeights_Err;
                    delete[] EncoderDecoderValueWeights_Err;
                    delete[] EncoderDecoderKeyWeights_Err;
                    delete[] EncoderKeyWeightsErr;
                    delete[] EncoderValueWeightsErr;
                    delete[] EncoderQueryWeightsErr;
                }
                Data->freeMemory();
            }
            else {
                Data->readCSVinRange(readRow + 1, DataSize);
                for (int b = readRow + 1; b <= DataSize; b++) {
                    std::vector<int> Sentence0, Sentence1;
                    std::map<int, long double> CategoryValue0, CategoryValue1;
                    std::string word;
                    std::string flood = "";
                    bool EvAlRi;
                    int countree;
                    word = Data->getValueStr(Data->getCategoryName(1), b);
                    flood = "";
                    EvAlRi = true;
                    countree = 0;
                    //İlk kategorinin değerlerini okur.
                    for (int i = 0; i < word.length(); i++) {
                        if (word[i] != ' ' && word[i] != ':' && word[i] != ',')
                            flood = flood + (char)std::tolower(word[i]);
                        else {
                            if(flood != ""){
                                if(i == word.length() - 1) EvAlRi = false;
                                if(countree % 2 == 0)
                                    Sentence0.push_back(tokenizedVocap1.at(flood));
                                else{
                                    try {
                                        CategoryValue0[Sentence0.size()] = stold(flood);
                                    }
                                    catch (const std::invalid_argument& e) {
                                        std::cout << std::endl << "First Vocap -> " << "Values only can be num => " << "Category: " << Sentence0.size() << " Row: " << b << " Value: " << flood << std::endl;
                                        CategoryValue0[Sentence0.size()] = 0;
                                        std::cout << "Value of category saved as 0! It will not effect the result with this value!" << std::endl;
                                        std::cout << e.what() << std::endl;
                                    }
                                }
                                countree++;
                                flood = "";
                            }
                            if(word[i] == ',' && CategoryValue0[Sentence0.size()] == NULL){
                                CategoryValue0[Sentence0.size()] = 0;
                            }
                        }
                    }
                    if (EvAlRi && flood != ""){
                        if(countree % 2 == 0){
                            Sentence0.push_back(tokenizedVocap1.at(flood));
                            CategoryValue0[Sentence0.size()] = 0;
                        }
                        else{
                            try {
                                CategoryValue0[Sentence0.size()] = stold(flood);
                            }
                            catch (const std::invalid_argument& e) {
                                std::cout << std::endl << "First Vocap -> " << "Values only can be num => " << "Category: " << Sentence0.size() << " Row: " << b << " Value: " << flood << std::endl;
                                CategoryValue0[Sentence0.size()] = 0;
                                std::cout << "Value of category saved as 0! It will not effect the result with this value!" << std::endl;
                                std::cout << e.what() << std::endl;
                            }
                        }
                        flood = "";
                    }
                    countree = 0;
                    word = Data->getValueStr(Data->getCategoryName(2), b);
                    EvAlRi = true;
                    //Read vocap2 sentence
                    for (int i = 0; i < word.length(); i++) {
                        if (word[i] != ' ' && word[i] != ':' && word[i] != ',')
                            flood = flood + (char)std::tolower(word[i]);
                        else {
                            if(flood != ""){
                                if(i == word.length() - 1) EvAlRi = false;
                                if(countree % 2 == 0)
                                    Sentence1.push_back(tokenizedVocap2.at(flood));
                                else{
                                    try {
                                        CategoryValue1[Sentence1.size()] = stold(flood);
                                    }
                                    catch (const std::invalid_argument& e) {
                                        std::cout << std::endl << "Second Vocap -> " << "Values only can be num => " << "Category: " << Sentence1.size() << " Row: " << b << " Value: " << flood << std::endl;
                                        CategoryValue1[Sentence1.size()] = 0;
                                        std::cout << "Value of category saved as 0! It will not effect the result with this value!" << std::endl;
                                        std::cout << e.what() << std::endl;
                                    }
                                }
                                flood = "";
                                countree++;
                            }
                            if(word[i] == ',' && CategoryValue0[Sentence1.size()] == NULL){
                                CategoryValue1[Sentence1.size()] = 0;
                            }
                        }
                    }
                    if (EvAlRi && flood != "") {
                        if(countree % 2 == 0){
                            Sentence1.push_back(tokenizedVocap2.at(flood));
                            CategoryValue1[Sentence1.size()] = 0;
                        }
                        else{
                            try {
                                CategoryValue1[Sentence1.size()] = stold(flood);
                            }
                            catch (const std::invalid_argument& e) {
                                std::cout << std::endl << "Second Vocap -> " << "Values only can be num => " << "Category: " << Sentence1.size() << " Row: " << b << " Value: " << flood << std::endl;
                                CategoryValue1[Sentence1.size()] = 0;
                                std::cout << "Value of category saved as 0! It will not effect the result with this value!" << std::endl;
                                std::cout << e.what() << std::endl;
                            }
                        }
                        flood = "";
                    }
                    //std::cout << "Pass 2 : Got Words!" << std::endl;
                    /*                                     ENCODER_KATMANI_BAŞLANGICI                                       */
                    long double*** Queries = new long double** [Sentence0.size()];
                    long double*** Values = new long double** [Sentence0.size()];
                    long double*** Keys = new long double** [Sentence0.size()];
                    long double** SelfAttentionValues = new long double* [Sentence0.size()];
                    long double*** QueryKeyCalculations_Encoder = new long double**[Sentence0.size()];
                    std::map<int, std::vector<long double>> EmbedResults0;
                    long double*** EncoderKeys = new long double **[Sentence0.size()];
                    long double*** EncoderValues = new long double **[Sentence0.size()];
                    std::vector<std::vector<std::vector<long double>>> EncoderSelfAttentionSoftMax;
                    // Queries, Values, Keys, QueryKeyCalculations ve SelfAttentionValues değişkenlerini oluşturur.
                    for (int i = 0; i < Sentence0.size(); i++) {
                        EmbedResults0[i] = predictEmbed(Sentence0[i], 1);
                        Queries[i] = new long double*[AttentionLayerSize];
                        Values[i] = new long double*[AttentionLayerSize];
                        Keys[i] = new long double*[AttentionLayerSize];
                        EncoderValues[i] = new long double*[AttentionLayerSize];
                        EncoderKeys[i] = new long double*[AttentionLayerSize];
                        SelfAttentionValues[i] = new long double[EmbedSize];
                        for(int k = 0; k < EmbedSize; k++)
                            SelfAttentionValues[i][k] = 0;
                        QueryKeyCalculations_Encoder[i] = new long double*[AttentionLayerSize];
                        for(int k = 0; k < AttentionLayerSize; k++){
                            QueryKeyCalculations_Encoder[i][k] = new long double[AttentionLayerSize * Sentence0.size()];
                            Queries[i][k] = new long double[EmbedSize/AttentionLayerSize];
                            Values[i][k] = new long double[EmbedSize/AttentionLayerSize];
                            Keys[i][k] = new long double[EmbedSize/AttentionLayerSize];
                            EncoderValues[i][k] = new long double[EmbedSize/AttentionLayerSize];
                            EncoderKeys[i][k] = new long double[EmbedSize/AttentionLayerSize];
                            for(int l = 0; l < EmbedSize/AttentionLayerSize; l++){
                                Queries[i][k][l] = 0;
                                Values[i][k][l] = 0;
                                Keys[i][k][l] = 0;
                                EncoderValues[i][k][l] = 0;
                                EncoderKeys[i][k][l] = 0;
                            }
                            for(int l = 0; l < AttentionLayerSize * Sentence0.size(); l++)
                                QueryKeyCalculations_Encoder[i][k][l] = 0;
                        }
                    }
                    for(int k = 0; k < Sentence0.size(); k++){
                        for(int i = 0; i < EmbedSize; i++)
                            if(CategoryValue0[k] != 0)
                                EmbedResults0[k][i] += (CategoryValue0.at(k) * EncoderRegressionLayerWeights[i]) + EncoderRegressionBias[i];
                    }
                    // Pozisyonel kodlama yapılır.
                    for (int k = 0; k < Sentence0.size(); k++) {
                        for (int i = 0; i < EmbedSize; i++)
                            EmbedResults0[k][i] += positionalEncoding(k, i, EmbedSize);
                    }
                    // Querie, Value and Key'leri hesaplar.
                    for (int h = 0; h < Sentence0.size(); h++) {
                        for(int i = 0; i < AttentionLayerSize; i++){
                            for(int k = 0; k < EmbedSize/AttentionLayerSize; k++){
                                for(int l = 0; l < EmbedSize/AttentionLayerSize; l++){
                                    Queries[h][i][k] += EmbedResults0[h][(i*(EmbedSize/AttentionLayerSize))+l] * EncoderQueryWeights[i][l][k];
                                    Values[h][i][k] += EmbedResults0[h][(i*(EmbedSize/AttentionLayerSize))+l] * EncoderValueWeights[i][l][k];
                                    Keys[h][i][k] += EmbedResults0[h][(i*(EmbedSize/AttentionLayerSize))+l] * EncoderKeyWeights[i][l][k];
                                }
                            }
                        }
                    }
                    // SelfAttentionValue'ları hesaplar.
                    for(int k = 0; k < Sentence0.size(); k++){
                        std::vector<std::vector<long double>> softMaxResults;
                        for(int h = 0; h < AttentionLayerSize; h++){
                            // QueryKeyCalculations hesaplamalarını yapar.
                            for(int b = 0; b < Sentence0.size(); b++){
                                for(int a = 0; a < AttentionLayerSize; a++){
                                    for(int n = 0; n < EmbedSize/AttentionLayerSize; n++)
                                        QueryKeyCalculations_Encoder[k][h][(b* AttentionLayerSize) + a] += Queries[k][h][n] * Keys[b][a][n];
                                }
                            }
                            // SelfAttentionValue'ları hesaplar.
                            softMaxResults.push_back(softMax(Sentence0.size() * AttentionLayerSize, QueryKeyCalculations_Encoder[k][h]));
                            for(int i = 0; i < Sentence0.size(); i++){
                                for(int a = 0; a < EmbedSize/ AttentionLayerSize; a++){
                                    for(int b = 0; b < AttentionLayerSize; b++)
                                        SelfAttentionValues[k][(h*(EmbedSize/ AttentionLayerSize))+a] += Values[i][b][a] * softMaxResults[h].at((i*AttentionLayerSize)+b);
                                }
                            }
                        }
                        EncoderSelfAttentionSoftMax.push_back(softMaxResults);
                    }
                    // SelfAttentionValue'yu normalize eder.
                    for (int k = 0; k < Sentence0.size(); k++) {
                        for (int i = 0; i < EmbedSize; i++)
                            SelfAttentionValues[k][i] += EmbedResults0[k][i];
                    }
                    // Son Key and Value'ları hesaplar.
                    for (int h = 0; h < Sentence0.size(); h++) {
                        for(int i = 0; i < AttentionLayerSize; i++){
                            for(int k = 0; k < EmbedSize/AttentionLayerSize; k++){
                                for(int l = 0; l < EmbedSize/AttentionLayerSize; l++){
                                    EncoderValues[h][i][k] += SelfAttentionValues[h][(i*(EmbedSize/AttentionLayerSize))+l] * EncoderValueWeights_[i][l][k];
                                    EncoderKeys[h][i][k] += SelfAttentionValues[h][(i*(EmbedSize/AttentionLayerSize))+l] * EncoderKeyWeights_[i][l][k];
                                }
                            }
                        }
                    }
                        //std::cout << "Pass 3 : EncoderLayerEnd" << std::endl;
                    /*                                    ENCODER_KATMANI_SONU                                           */
                    /*                                   DECODER_KATMANI_BAŞLANGICI                                          */
                    std::vector<long double**> DecoderQueries;
                    std::vector<long double**> DecoderValues;
                    std::vector<long double**> DecoderKeys;
                    std::map<int, std::vector<long double>> EmbedResults1;
                    int NextWord = -1;
                    long double NextValue = 0;
                    std::vector<int> ResultSentence;
                    std::map<int, long double> ResultValues;
                    std::vector<std::vector<long double>> LossValues;
                    std::vector<long double> RegressionErr;
                    std::vector<long double*> Encoder_DecoderAttention;
                    std::vector<long double*> Decoder_SelfAttention;
                    std::vector<long double**> MaskedSelfAtQueryKeyCal;
                    std::vector<long double**> DecoderAttentionQuery;
                    std::vector<long double**> DecoderAttentionQueryKeyCal;
                    std::vector<std::vector<std::vector<long double>>> AttentionLayerSoftMaxResults;
                    std::vector<std::vector<std::vector<long double>>> MaskedSelfAttentionSoftMaxResults;
                    int coutn = 0;
                    while(NextWord != tokenizedVocap2.at("<EOS>") && coutn < max_seq){
                        coutn++;
                        Encoder_DecoderAttention.push_back(new long double[EmbedSize]);
                        Decoder_SelfAttention.push_back(new long double[EmbedSize]);
                        for(int i = 0; i < EmbedSize; i++){
                            Decoder_SelfAttention[ResultSentence.size()][i] = 0;
                            Encoder_DecoderAttention[ResultSentence.size()][i] = 0;
                        }
                        /*                          MASKED_SELF_ATTENTION_KATMANI                             */
                        //std::cout << "Pass 4 : MASKED SELF ATTENTION LAYER START" << std::endl;
                        if(NextWord == -1){
                            NextWord = tokenizedVocap2.at("<EOS>");
                            NextValue = 0;
                        }
                        EmbedResults1[ResultSentence.size()] = predictEmbed(NextWord,2);
                        for(int i = 0; i < EmbedSize; i++)
                            EmbedResults1[ResultSentence.size()][i] += (NextValue * DecoderRegressionLayerWeights[i]) + DecoderRegressionBias[i];
                        for(int i = 0; i < EmbedSize; i++)
                            EmbedResults1[ResultSentence.size()][i] += positionalEncoding(ResultSentence.size(),i,EmbedSize);
                        // Querie, Value, Key'leri oluştur.
                        DecoderQueries.push_back(new long double*[AttentionLayerSize]);
                        DecoderValues.push_back(new long double*[AttentionLayerSize]);
                        DecoderKeys.push_back(new long double*[AttentionLayerSize]);
                        // QUERIE, VALUE, KEY'leri hesaplar.
                        for(int i = 0; i < AttentionLayerSize; i++){
                            DecoderQueries[ResultSentence.size()][i] = new long double[EmbedSize/AttentionLayerSize];
                            DecoderValues[ResultSentence.size()][i] = new long double[EmbedSize/AttentionLayerSize];
                            DecoderKeys[ResultSentence.size()][i] = new long double[EmbedSize/AttentionLayerSize];
                            for(int k = 0; k < EmbedSize/AttentionLayerSize; k++){
                                DecoderQueries[ResultSentence.size()][i][k] = 0;
                                DecoderValues[ResultSentence.size()][i][k] = 0;
                                DecoderKeys[ResultSentence.size()][i][k] = 0;
                                for(int l = 0; l < EmbedSize/AttentionLayerSize; l++){
                                    DecoderQueries[ResultSentence.size()][i][k] += EmbedResults1[ResultSentence.size()][(i*(EmbedSize/AttentionLayerSize))+l] * DecoderQueryWeights[i][l][k];
                                    DecoderValues[ResultSentence.size()][i][k] += EmbedResults1[ResultSentence.size()][(i*(EmbedSize/AttentionLayerSize))+l] * DecoderValueWeights[i][l][k];
                                    DecoderKeys[ResultSentence.size()][i][k] += EmbedResults1[ResultSentence.size()][(i*(EmbedSize/AttentionLayerSize))+l] * DecoderKeyWeights[i][l][k];
                                }
                            }
                        }
                        MaskedSelfAtQueryKeyCal.push_back(new long double*[AttentionLayerSize]);
                        for(int i = 0; i < AttentionLayerSize; i++){
                            MaskedSelfAtQueryKeyCal[ResultSentence.size()][i] = new long double[(ResultSentence.size()+1)*AttentionLayerSize];
                            for(int k = 0; k < (ResultSentence.size()+1)*AttentionLayerSize; k++)
                                MaskedSelfAtQueryKeyCal[ResultSentence.size()][i][k] = 0;
                        }
                        std::vector<std::vector<long double>> SoftMaxResults0;
                        for(int h = 0; h < AttentionLayerSize; h++){
                            // QueryKeyCalculations hesaplamalarını yapar.
                            for(int b = 0; b < ResultSentence.size()+1; b++){
                                for(int a = 0; a < AttentionLayerSize; a++){
                                    for(int n = 0; n < EmbedSize/AttentionLayerSize; n++)
                                        MaskedSelfAtQueryKeyCal[ResultSentence.size()][h][(b* AttentionLayerSize) + a] += DecoderQueries[ResultSentence.size()][h][n] * DecoderKeys[b][a][n];
                                }
                            }
                            // SelfAttentionValue'ları hesaplar.
                            SoftMaxResults0.push_back(softMax((ResultSentence.size()+1) * AttentionLayerSize, MaskedSelfAtQueryKeyCal[ResultSentence.size()][h]));
                            for(int i = 0; i < ResultSentence.size()+1; i++){
                                for(int a = 0; a < EmbedSize/ AttentionLayerSize; a++){
                                    for(int b = 0; b < AttentionLayerSize; b++)
                                        Decoder_SelfAttention[ResultSentence.size()][(h*(EmbedSize/ AttentionLayerSize))+a] += DecoderValues[i][b][a] * SoftMaxResults0[h].at((i*AttentionLayerSize)+b);
                                }
                            }
                        }
                        MaskedSelfAttentionSoftMaxResults.push_back(SoftMaxResults0);
                        for(int i = 0; i < EmbedSize; i++)
                            Decoder_SelfAttention[ResultSentence.size()][i] += EmbedResults1[ResultSentence.size()][i];
                        //                         MASKED_SELF_ATTENTION_KATMANI_SONU
                        //                              ATTENTION_KATMANI_BAŞLAR
                        //std::cout << "Pass 5 : ENCODER&DECODER LAYER START" << std::endl;
                        // DecoderAttentionQuery'yi oluşturur.
                        DecoderAttentionQuery.push_back(new long double*[AttentionLayerSize]);
                        for(int i = 0; i < AttentionLayerSize; i++){
                            DecoderAttentionQuery[ResultSentence.size()][i] = new long double[EmbedSize/AttentionLayerSize];
                            for(int k = 0; k < EmbedSize/AttentionLayerSize; k++){
                                DecoderAttentionQuery[ResultSentence.size()][i][k] = 0;
                                for(int l = 0; l < EmbedSize/AttentionLayerSize; l++)
                                    DecoderAttentionQuery[ResultSentence.size()][i][k] += DecoderQueryWeights_[i][l][k] * Decoder_SelfAttention[ResultSentence.size()][(i*(EmbedSize/AttentionLayerSize))+l];
                            }
                        }
                        // DecoderAttentionQueryCalculation'ı oluşturur.
                        DecoderAttentionQueryKeyCal.push_back(new long double*[AttentionLayerSize]);
                        for(int i = 0; i < AttentionLayerSize; i++){
                            DecoderAttentionQueryKeyCal[ResultSentence.size()][i] = new long double[Sentence0.size()*AttentionLayerSize];
                            for(int k = 0; k < Sentence0.size()*AttentionLayerSize; k++)
                                DecoderAttentionQueryKeyCal[ResultSentence.size()][i][k] = 0;
                        }
                        std::vector<std::vector<long double>> softMaxResult;
                        for(int i = 0; i < AttentionLayerSize; i++){
                            for(int b = 0; b < Sentence0.size(); b++){
                                for(int n = 0; n < AttentionLayerSize; n++){
                                    for(int l = 0; l < EmbedSize/AttentionLayerSize; l++)
                                        DecoderAttentionQueryKeyCal[ResultSentence.size()][i][(b*AttentionLayerSize)+n] += DecoderAttentionQuery[ResultSentence.size()][i][l] * EncoderKeys[b][n][l];
                                }
                            }
                            softMaxResult.push_back(softMax(Sentence0.size()*AttentionLayerSize, DecoderAttentionQueryKeyCal[ResultSentence.size()][i]));
                            for(int l = 0; l < EmbedSize/AttentionLayerSize; l++){
                                for(int b = 0; b < Sentence0.size(); b++){
                                    for(int n = 0; n < AttentionLayerSize; n++)
                                        Encoder_DecoderAttention[ResultSentence.size()][(i*(EmbedSize/AttentionLayerSize)) + l] += EncoderValues[b][n][l] * softMaxResult[i].at((b*AttentionLayerSize) + n);
                                }
                            }
                        }
                        AttentionLayerSoftMaxResults.push_back(softMaxResult);
                        for(int i = 0; i < EmbedSize; i++)
                            Encoder_DecoderAttention[ResultSentence.size()][i] += Decoder_SelfAttention[ResultSentence.size()][i];
                        //                                ATTENTION_LAYER_END
                        //                      TAM_SİNİR_AĞI_KATMANI-SONRAKİ_DEĞERİ_TAHMİN_ETME
                        long double *NextWordOutput = new long double[tokenizedVocap2.size()];
                        // Normalize
                        for(int i = 0; i < tokenizedVocap2.size(); i++){
                            NextWordOutput[i] = 0;
                            for(int k = 0; k < EmbedSize; k++){
                                NextWordOutput[i] += Encoder_DecoderAttention[ResultSentence.size()][k] * DecoderNNLayerWeights[k][i];
                            }
                        }
                        long double max = -2;
                        std::vector<long double> nextWordVec = softMax(tokenizedVocap2.size(), NextWordOutput);
                        for(int i = 0; i < nextWordVec.size(); i++){
                            if(nextWordVec.at(i) >= max){
                                max = nextWordVec.at(i); NextWord = i;
                            }
                        }
                        delete[] NextWordOutput;
                        ResultSentence.push_back(NextWord);
                        //                      TAM_SİNİR_AĞI_KATMANI-SONRAKİ_DEĞERİ_TAHMİN_ETME_SONU
                        //                      REGRESYON_KATMANI_BAŞLANGICI
                        NextValue = 0;
                        for(int i = 0; i < EmbedSize; i++)
                            NextValue += (Encoder_DecoderAttention[ResultSentence.size()-1][i] * EncoderDecoderRegressionLayerWeights[i]) + EncoderDecoderRegressionBias;
                        ResultValues[ResultSentence.size()] = NextValue;
                        //                          REGRESYON_KATMANI_SONU
                        std::vector<long double> expected(tokenizedVocap2.size(), 0.0);
                        if(ResultSentence.size() <= Sentence1.size()) expected[Sentence1[ResultSentence.size()-1]] = 1.0;
                        if(ResultSentence.size() <= Sentence1.size()) RegressionErr.push_back(mean2ErrDerr(NextValue,CategoryValue1.at(ResultSentence.size())));
                        else RegressionErr.push_back(0.0);
                        LossValues.push_back(CrossEntropyLoss(nextWordVec, expected));
                        for(auto& it : tokenizedVocap2){
                            if (it.second == NextWord) {
                                std::cout << it.first << ' ';
                            }
                        }
                        std::cout << "Loss: " << cross_entropy_loss(nextWordVec, expected) << std::endl;
                    }
                    std::cout << "-------------------------------------------------------------------" << std::endl;
                    /*                                      DECODER_KATMANI_SONU                                           */
                    /*                                       BACKPROPAGATION                                            */
                    //NÖRONLAR VE SOFTMAX SONUÇLARI
                    long double ***AttentionLayerSoftMaxErr = new long double**[AttentionLayerSize];
                    long double ***AttentionSoftMaxErrorIn = new long double**[AttentionLayerSize];
                    long double **MaskedAttentionSoftMaxErr = new long double*[AttentionLayerSize];
                    long double **MaskedAttentionSoftMaxInErr = new long double*[AttentionLayerSize];
                    long double *ENeurons = new long double[EmbedSize];
                    long double **DecoderNNLayerDerr = new long double*[EmbedSize];
                    long double **DecoderAttenQueriesErr = new long double*[AttentionLayerSize];
                    long double ****EncoderDecoderKeysErr = new long double***[AttentionLayerSize];
                    long double ****EncoderDecoderValuesErr = new long double***[AttentionLayerSize];
                    long double **MaskedAttentionResultErr = new long double *[AttentionLayerSize];
                    long double **MaskedAttentionValueErr = new long double *[ResultSentence.size()*AttentionLayerSize];
                    long double **MaskedAttentionKeyErr = new long double *[ResultSentence.size()*AttentionLayerSize];
                    long double **MaskedAttentionQueryErr = new long double *[AttentionLayerSize];
                    long double **EncoderKeyErr = new long double *[Sentence0.size()*AttentionLayerSize];
                    long double **EncoderValueErr = new long double *[Sentence0.size()*AttentionLayerSize];
                    long double **EncoderQueryErr = new long double *[AttentionLayerSize];
                    long double *EncoderSelfAttentionErr = new long double [EmbedSize];
                    long double **EncoderSelfAttentionSoftMaxErr = new long double *[AttentionLayerSize];
                    long double **EncoderSelfAttentionSoftMaxInErr = new long double *[AttentionLayerSize];
                    // AĞIRLIKLAR
                    long double ***MaskedAttentionQueryWeightErr = new long double **[AttentionLayerSize];
                    long double ***MaskedAttentionValueWeightErr = new long double **[AttentionLayerSize];
                    long double ***MaskedAttentionKeyWeightErr = new long double **[AttentionLayerSize];
                    long double ***DecoderQueryWeights_Err = new long double **[AttentionLayerSize];
                    long double ***EncoderDecoderValueWeights_Err = new long double **[AttentionLayerSize];
                    long double ***EncoderDecoderKeyWeights_Err = new long double **[AttentionLayerSize];
                    long double ***EncoderKeyWeightsErr = new long double **[AttentionLayerSize];
                    long double ***EncoderValueWeightsErr = new long double **[AttentionLayerSize];
                    long double ***EncoderQueryWeightsErr = new long double **[AttentionLayerSize];
                    long double *EncoderDecoderRegressionLayerWeightsErr = new long double[EmbedSize];
                    long double EncoderDecoderRegressionBiasErr = 0;
                    long double *EncoderRegressionLayerWeightsErr = new long double[EmbedSize];
                    long double *EncoderRegressionLayerBiasErr = new long double[EmbedSize];
                    long double *DecoderRegressionLayerWeightsErr = new long double[EmbedSize];
                    long double *DecoderRegressionLayerBiasErr = new long double[EmbedSize];
                    long double *EncoderEmbedErr = new long double[EmbedSize];
                    long double *DecoderEmbedErr = new long double[EmbedSize];
                    for(int i = 0; i < Sentence0.size()*AttentionLayerSize; i++){
                        EncoderKeyErr[i] = new long double[EmbedSize/AttentionLayerSize];
                        EncoderValueErr[i] = new long double[EmbedSize/AttentionLayerSize];
                        for(int l = 0; l < EmbedSize/AttentionLayerSize; l++){
                            EncoderKeyErr[i][l] = 0;
                            EncoderValueErr[i][l] = 0;
                        }
                    }
                    for(int i = 0; i < ResultSentence.size()*AttentionLayerSize; i++){
                        MaskedAttentionValueErr[i] = new long double[EmbedSize/AttentionLayerSize];
                        MaskedAttentionKeyErr[i] = new long double[EmbedSize/AttentionLayerSize];
                        for(int l = 0; l < EmbedSize/AttentionLayerSize; l++){
                            MaskedAttentionValueErr[i][l] = 0;
                            MaskedAttentionKeyErr[i][l] = 0;
                        }
                    }
                    for(int i = 0; i < AttentionLayerSize; i++){
                        AttentionLayerSoftMaxErr[i] = new long double *[Sentence0.size()];
                        AttentionSoftMaxErrorIn[i] = new long double *[Sentence0.size()];
                        EncoderDecoderValuesErr[i] = new long double **[Sentence0.size()];
                        EncoderDecoderKeysErr[i] = new long double **[Sentence0.size()];
                        DecoderAttenQueriesErr[i] = new long double [EmbedSize/AttentionLayerSize];
                        MaskedAttentionResultErr[i] = new long double [EmbedSize/AttentionLayerSize];
                        MaskedAttentionQueryErr[i] = new long double [EmbedSize/AttentionLayerSize];
                        MaskedAttentionSoftMaxErr[i] = new long double [ResultSentence.size()*AttentionLayerSize];
                        MaskedAttentionSoftMaxInErr[i] = new long double [ResultSentence.size()*AttentionLayerSize];
                        EncoderQueryErr[i] = new long double[EmbedSize/AttentionLayerSize];
                        EncoderSelfAttentionSoftMaxErr[i] = new long double[Sentence0.size()*AttentionLayerSize];
                        EncoderSelfAttentionSoftMaxInErr[i] = new long double[Sentence0.size()*AttentionLayerSize];
                        for(int l = 0; l < ResultSentence.size()*AttentionLayerSize; l++){
                            MaskedAttentionSoftMaxErr[i][l] = 0;
                            MaskedAttentionSoftMaxInErr[i][l] = 0;
                        }
                        for(int l = 0; l < EmbedSize/AttentionLayerSize; l++){
                            EncoderQueryErr[i][l] = 0;
                            MaskedAttentionQueryErr[i][l] = 0;
                            MaskedAttentionResultErr[i][l] = 0;
                            DecoderAttenQueriesErr[i][l] = 0;
                        }
                        for(int l = 0; l < Sentence0.size(); l++){
                            AttentionLayerSoftMaxErr[i][l] = new long double[AttentionLayerSize];
                            AttentionSoftMaxErrorIn[i][l] = new long double[AttentionLayerSize];
                            EncoderDecoderValuesErr[i][l] = new long double*[AttentionLayerSize];
                            EncoderDecoderKeysErr[i][l] = new long double*[AttentionLayerSize];
                            for(int k = 0; k < AttentionLayerSize; k++){
                                AttentionLayerSoftMaxErr[i][l][k] = 0;
                                AttentionSoftMaxErrorIn[i][l][k] = 0;
                                EncoderDecoderValuesErr[i][l][k] = new long double[EmbedSize/AttentionLayerSize];
                                EncoderDecoderKeysErr[i][l][k] = new long double[EmbedSize/AttentionLayerSize];
                                for(int n = 0; n < EmbedSize/AttentionLayerSize; n++){
                                    EncoderDecoderValuesErr[i][l][k][n] = 0;
                                    EncoderDecoderKeysErr[i][l][k][n] = 0;
                                }
                            }
                        }
                        for(int l = 0; l < Sentence0.size()*AttentionLayerSize; l++){
                            EncoderSelfAttentionSoftMaxErr[i][l] = 0;
                            EncoderSelfAttentionSoftMaxInErr[i][l] = 0;
                        }
                    }
                    for(int i = 0; i < EmbedSize; i++){
                        EncoderSelfAttentionErr[i] = 0;
                        ENeurons[i] = 0;
                        DecoderNNLayerDerr[i] = new long double[tokenizedVocap2.size()];
                        EncoderDecoderRegressionLayerWeightsErr[i] = 0;
                        EncoderRegressionLayerWeightsErr[i] = 0;
                        EncoderRegressionLayerBiasErr[i] = 0;
                        DecoderRegressionLayerWeightsErr[i] = 0;
                        DecoderRegressionLayerBiasErr[i] = 0;
                        EncoderEmbedErr[i] = 0;
                        for(int l = 0; l < tokenizedVocap2.size(); l++){
                            DecoderNNLayerDerr[i][l] = 0;
                        }
                    }
                    for(int i = 0; i < AttentionLayerSize; i++){
                        MaskedAttentionQueryWeightErr[i] = new long double*[EmbedSize/AttentionLayerSize];
                        MaskedAttentionValueWeightErr[i] = new long double*[EmbedSize/AttentionLayerSize];
                        MaskedAttentionKeyWeightErr[i] = new long double*[EmbedSize/AttentionLayerSize];
                        DecoderQueryWeights_Err[i] = new long double*[EmbedSize/AttentionLayerSize];
                        EncoderDecoderValueWeights_Err[i] = new long double*[EmbedSize/AttentionLayerSize];
                        EncoderDecoderKeyWeights_Err[i] = new long double*[EmbedSize/AttentionLayerSize];
                        EncoderKeyWeightsErr[i] = new long double *[EmbedSize/AttentionLayerSize];
                        EncoderValueWeightsErr[i] = new long double *[EmbedSize/AttentionLayerSize];
                        EncoderQueryWeightsErr[i] = new long double *[EmbedSize/AttentionLayerSize];
                        for(int k = 0; k < EmbedSize/AttentionLayerSize; k++){
                            MaskedAttentionQueryWeightErr[i][k] = new long double[EmbedSize/AttentionLayerSize];
                            MaskedAttentionValueWeightErr[i][k] = new long double[EmbedSize/AttentionLayerSize];
                            MaskedAttentionKeyWeightErr[i][k] = new long double[EmbedSize/AttentionLayerSize];
                            DecoderQueryWeights_Err[i][k] = new long double[EmbedSize/AttentionLayerSize];
                            EncoderDecoderValueWeights_Err[i][k] = new long double[EmbedSize/AttentionLayerSize];
                            EncoderDecoderKeyWeights_Err[i][k] = new long double[EmbedSize/AttentionLayerSize];
                            EncoderKeyWeightsErr[i][k] = new long double[EmbedSize/AttentionLayerSize];
                            EncoderValueWeightsErr[i][k] = new long double[EmbedSize/AttentionLayerSize];
                            EncoderQueryWeightsErr[i][k] = new long double[EmbedSize/AttentionLayerSize];
                            for(int l = 0; l < EmbedSize/AttentionLayerSize; l++){
                                MaskedAttentionQueryWeightErr[i][k][l] = 0;
                                MaskedAttentionValueWeightErr[i][k][l] = 0;
                                MaskedAttentionKeyWeightErr[i][k][l] = 0;
                                DecoderQueryWeights_Err[i][k][l] = 0;
                                EncoderDecoderKeyWeights_Err[i][k][l] = 0;
                                EncoderDecoderValueWeights_Err[i][k][l] = 0;
                                EncoderKeyWeightsErr[i][k][l] = 0;
                                EncoderValueWeightsErr[i][k][l] = 0;
                                EncoderQueryWeightsErr[i][k][l] = 0;
                            }
                        }
                    }
                    // LOSS HESAPLAMASI
                    long double *Loss = new long double [tokenizedVocap2.size()];
                    for(int i = 0; i < tokenizedVocap2.size(); i++)
                        Loss[i] = 0;
                    for(int i = 0; i < LossValues.size(); i++){
                        for(int l = 0; l < tokenizedVocap2.size(); l++)
                            Loss[l] += LossValues[i][l] / LossValues.size();
                    }
                    for(int i = 0; i < tokenizedVocap2.size(); i++){
                        std::cout << "Loss " << i << ":" << Loss[i] << std::endl;
                    }
                    long double RegLoss = 0;
                    for(int i = 0; i < ResultSentence.size(); i++)
                        RegLoss += RegressionErr[i] / ResultSentence.size();
                    for(int i = 0; i < EmbedSize; i++)
                        ENeurons[i] += RegLoss * EncoderDecoderRegressionLayerWeights[i];
                    for(int i = 0; i < ResultSentence.size(); i++){
                        for(int j = 0; j < EmbedSize; j++)
                            EncoderDecoderRegressionLayerWeightsErr[j] += (Encoder_DecoderAttention[i][j]/ResultSentence.size()) * RegLoss;
                    }
                    EncoderDecoderRegressionBiasErr = RegLoss;
                    /*                                      FULL_NN_KATMANI-SONRAKİ_DEĞERİ_TAHMİN_ETME_GERİ_YAYILIM_BAŞLANGICI                                         */
                    for(int i = 0; i < EmbedSize; i++){
                        for(int j = 0; j < tokenizedVocap2.size(); j++)
                            ENeurons[i] += DecoderNNLayerWeights[i][j] * Loss[j];
                    }
                    for(int i = 0; i < ResultSentence.size(); i++){
                        for(int j = 0; j < EmbedSize; j++){
                            for(int k = 0; k < tokenizedVocap2.size(); k++)
                                DecoderNNLayerDerr[j][k] += (Encoder_DecoderAttention[i][j]/ResultSentence.size()) * Loss[k];
                        }
                    }
                    /*                                       FULL_NN_KATMANI-SONRAKİ_DEĞERİ_TAHMİN_ETME_GERİ_YAYILIM_SONU                                           */
                    /*                                              ATTENTION_KATMANI_BACKPROPAGATION_BAŞLANGICI                                                    */
                    // DECODER ATTENTION SOFTMAX'E HATA DAĞITIMI
                    // DECODER ATTENTION ENCODER SON VALUE'LARA HATA DAĞITIMI
                    for(int j = 0; j < AttentionLayerSize; j++){
                        for(int l = 0; l < Sentence0.size(); l++){
                            for(int k = 0; k < AttentionLayerSize; k++){
                                for(int n = 0; n < EmbedSize/AttentionLayerSize; n++)
                                    AttentionLayerSoftMaxErr[j][l][k] += (EncoderValues[l][k][n] / Sentence0.size()) * ENeurons[(j*(EmbedSize/AttentionLayerSize))+n];
                            }
                        }
                    }
                    for(int i = 0; i < ResultSentence.size(); i++){
                        for(int j = 0; j < AttentionLayerSize; j++){
                            for(int l = 0; l < Sentence0.size(); l++){
                                for(int k = 0; k < AttentionLayerSize; k++){
                                    for(int n = 0; n < EmbedSize/AttentionLayerSize; n++)
                                        EncoderDecoderValuesErr[j][l][k][n] += ENeurons[(k*(EmbedSize/AttentionLayerSize))+n] * (AttentionLayerSoftMaxResults[i][j][(l*AttentionLayerSize)+k]/(AttentionLayerSize*ResultSentence.size()));
                                }
                            }
                        }
                    }
                    for(int j = 0; j < AttentionLayerSize; j++){
                        for(int l = 0; l < Sentence0.size(); l++){
                            for(int k = 0; k < AttentionLayerSize; k++){
                                for(int n = 0; n < EmbedSize/AttentionLayerSize; n++){
                                    for(int h = 0; h < EmbedSize/AttentionLayerSize; h++){
                                        EncoderSelfAttentionErr[(k *(EmbedSize/AttentionLayerSize))+h] += (EncoderDecoderValuesErr[j][l][k][n]/Sentence0.size()) * EncoderValueWeights_[k][h][n];
                                    }
                                }
                            }
                        }
                    }
                    // DECODER ATTENTION QUERY-KEY HESAPLAMALARINA HATA DAĞITIMI
                    long double additionF = 0;
                    for(int i = 0; i < ResultSentence.size(); i++){
                        for(int j = 0; j < AttentionLayerSize; j++){
                            for(int h = 0; h < Sentence0.size(); h++){
                                for(int f = 0; f < AttentionLayerSize; f++)
                                    additionF += AttentionLayerSoftMaxErr[j][h][f] * (AttentionLayerSoftMaxResults[i][j][(h*AttentionLayerSize)+f]/(AttentionLayerSize*ResultSentence.size()));
                            }
                        }
                    }
                    for(int i = 0; i < ResultSentence.size(); i++){
                        for(int j = 0; j < AttentionLayerSize; j++){
                            for(int l = 0; l < Sentence0.size(); l++){
                                for(int k = 0; k < AttentionLayerSize; k++)
                                    AttentionSoftMaxErrorIn[j][l][k] += (AttentionLayerSoftMaxResults[i][j][(l*AttentionLayerSize)+k]/(AttentionLayerSize*ResultSentence.size())) * (AttentionLayerSoftMaxErr[j][l][k] - additionF);
                            }
                        }
                    }
                    // DECODER ATTENTION ENCODER SON KEY'E HATA DAĞITIMI
                    for(int i = 0; i < ResultSentence.size(); i++){
                        for(int j = 0; j < AttentionLayerSize; j++){
                            for(int l = 0; l < Sentence0.size(); l++){
                                for(int k = 0; k < AttentionLayerSize; k++){
                                    for(int v = 0; v < EmbedSize/AttentionLayerSize; v++)
                                        EncoderDecoderKeysErr[j][l][k][v] += AttentionSoftMaxErrorIn[j][l][k] * (DecoderAttentionQuery[i][j][v]/ResultSentence.size());
                                }
                            }
                        }
                    }
                    for(int j = 0; j < AttentionLayerSize; j++){
                        for(int l = 0; l < Sentence0.size(); l++){
                            for(int k = 0; k < AttentionLayerSize; k++){
                                for(int v = 0; v < EmbedSize/AttentionLayerSize; v++){
                                    for(int h = 0; h < EmbedSize/AttentionLayerSize; h++){
                                        EncoderSelfAttentionErr[(k*(EmbedSize/AttentionLayerSize))+h] += EncoderDecoderKeysErr[j][l][k][v] * EncoderKeyWeights_[k][h][v];
                                    }
                                }
                            }
                        }
                    }
                    // DECODER ATTENTION DECODER QUERY'YE HATA DAĞITIMI
                    for(int j = 0; j < AttentionLayerSize; j++){
                        for(int l = 0; l < EmbedSize/AttentionLayerSize; l++){
                            for(int v = 0; v < Sentence0.size(); v++){
                                for(int k = 0; k < AttentionLayerSize; k++)
                                    DecoderAttenQueriesErr[j][l] += (EncoderKeys[v][k][l]/Sentence0.size()) * AttentionSoftMaxErrorIn[j][v][k];
                            }
                        }
                    }
                    // AĞIRLIKLARA HATA DAĞITIMI
                    for(int i = 0; i < ResultSentence.size(); i++){
                        for(int j = 0; j < AttentionLayerSize; j++){
                            for(int l = 0; l < EmbedSize/AttentionLayerSize; l++){
                                for(int v = 0; v < EmbedSize/AttentionLayerSize; v++)
                                    DecoderQueryWeights_Err[j][l][v] += (Decoder_SelfAttention[i][(j*(EmbedSize/AttentionLayerSize))+l]/ResultSentence.size())*DecoderAttenQueriesErr[j][v];
                            }
                        }
                    }
                    for(int j = 0; j < AttentionLayerSize; j++){
                        for(int f = 0; f < Sentence0.size(); f++){
                            for(int l = 0; l < AttentionLayerSize; l++){
                                for(int v = 0; v < EmbedSize/AttentionLayerSize; v++){
                                    for(int d = 0; d < EmbedSize/AttentionLayerSize; d++){
                                        EncoderDecoderKeyWeights_Err[l][v][d] += (SelfAttentionValues[f][(l*(EmbedSize/AttentionLayerSize) + v)]/Sentence0.size()) * EncoderDecoderKeysErr[j][f][l][d];
                                        EncoderDecoderValueWeights_Err[l][v][d] += (SelfAttentionValues[f][(l*(EmbedSize/AttentionLayerSize) + v)]/Sentence0.size()) * EncoderDecoderValuesErr[j][f][l][d];
                                    }
                                }
                            }
                        }
                    }
                    // MASKED SELF ATTENTION DEĞERİNE HATA DAĞITIMI
                    for(int j = 0; j < AttentionLayerSize; j++){
                        for(int l = 0; l < EmbedSize/AttentionLayerSize; l++){
                            for(int h = 0; h < EmbedSize/AttentionLayerSize; h++)
                                MaskedAttentionResultErr[j][l] += DecoderAttenQueriesErr[j][h]*DecoderQueryWeights_[j][l][h];
                        }
                    }
                    /*                                                  ATTENTION_KATMANI_BACKPROPAGATION_SONU                                                         */
                    /*                                       DECODER_MASKED_SELF_ATTENTION_KATMANI_BACKPROPAGATION_BAŞLANGICI                                              */
                    //std::cout << "Pass 7 : BACKPROPAGATION MASKED" << std::endl;
                    //  DECODER MASKED ATTENTION VALUE VE SOFTMAX'E HATA DAĞITIMI
                    for(int i = 0; i < ResultSentence.size(); i++){
                        for(int j = 0; j < AttentionLayerSize; j++){
                            for(int l = 0; l < AttentionLayerSize; l++){
                                for(int c = 0; c < i+1; c++){
                                    for(int h = 0; h < EmbedSize/AttentionLayerSize; h++){
                                        MaskedAttentionValueErr[(c*AttentionLayerSize)+l][h] += (MaskedSelfAttentionSoftMaxResults[i][j][(c * AttentionLayerSize)+l]/(ResultSentence.size()*AttentionLayerSize))*MaskedAttentionResultErr[l][h];
                                        MaskedAttentionSoftMaxErr[j][(c*AttentionLayerSize)+l] += MaskedAttentionResultErr[l][h] * (DecoderValues[c][l][h]/ResultSentence.size()); /// TODO: Check this code later! Should it be in this for loop? int i ?
                                    }
                                }
                            }
                        }
                    }
                    // DECODER MASKED ATTENTION QUERY-KEY HESAPLAMALINA HATA DAĞITIMI
                    // TODO: CHECK THIS CODE TOO. THIS CODE WRITTEN BY LOOKING TO UPSIDE CODES.
                    long double AddF = 0;
                    for(int i = 0; i < ResultSentence.size(); i++){
                        for(int j = 0; j < AttentionLayerSize; j++){
                            for(int v = 0; v < AttentionLayerSize; v++){
                                for(int h = 0; h < i+1; h++){
                                    AddF += MaskedAttentionSoftMaxErr[j][(h*AttentionLayerSize)+v] * (MaskedSelfAttentionSoftMaxResults[i][j][(h * AttentionLayerSize)+v]/(ResultSentence.size()*AttentionLayerSize));
                                }
                            }
                        }
                    }
                    for(int i = 0; i < ResultSentence.size(); i++){
                        for(int j = 0; j < AttentionLayerSize; j++){
                            for(int l = 0; l < AttentionLayerSize; l++){
                                for(int c = 0; c < i+1; c++){
                                    MaskedAttentionSoftMaxInErr[j][(c * AttentionLayerSize)+l] += (MaskedSelfAttentionSoftMaxResults[i][j][(c*AttentionLayerSize)+l]/(ResultSentence.size()*AttentionLayerSize))*(MaskedAttentionSoftMaxErr[j][(c*AttentionLayerSize)+l]-AddF);
                                }
                            }
                        }
                    }
                    // DECODER MASKED ATTENTION QUERY'YE HATA DAĞITIMI
                    for(int i = 0; i < ResultSentence.size(); i++){
                        for(int j = 0; j < AttentionLayerSize; j++){
                            for(int l = 0; l < EmbedSize/AttentionLayerSize; l++){
                                for(int v = 0; v < i+1; v++){
                                    for(int h = 0; h < AttentionLayerSize; h++)
                                        MaskedAttentionQueryErr[j][l] += (MaskedAttentionSoftMaxInErr[j][(v * AttentionLayerSize)+h]/ResultSentence.size())*(DecoderKeys[v][h][l]/ResultSentence.size());
                                }
                            }
                        }
                    }
                    // DECODER MASKED ATTENTION KEY'E HATA DAĞITIMI
                    for(int i = 0; i < ResultSentence.size(); i++){
                        for(int j = 0; j < AttentionLayerSize; j++){
                            for(int c = 0; c < i+1; c++){
                                for(int l = 0; l < AttentionLayerSize; l++){
                                    for(int h = 0; h < EmbedSize/AttentionLayerSize; h++){
                                        MaskedAttentionKeyErr[(c*AttentionLayerSize)+l][h] += (MaskedAttentionSoftMaxInErr[j][(c*AttentionLayerSize)+l]/ResultSentence.size())*(DecoderQueries[i][j][h]/ResultSentence.size());
                                    }
                                }
                            }
                        }
                    }
                    //DECODER REGRESYON KATMANINA HATA DAĞITIMI
                    for(int i = 0; i < EmbedSize; i++){
                        for(int j = 0; j < AttentionLayerSize; j++){
                            for(int l = 0; l < EmbedSize/AttentionLayerSize; l++)
                                DecoderEmbedErr[i] += MaskedAttentionQueryErr[j][l] * DecoderQueryWeights[j][i][l];
                        }
                        for(int c = 0; c < ResultSentence.size(); c++){
                            for(int l = 0; l < AttentionLayerSize; l++){
                                for(int h = 0; h < EmbedSize/AttentionLayerSize; h++){
                                    DecoderEmbedErr[i] += MaskedAttentionKeyErr[(c*AttentionLayerSize)+l][h] * DecoderKeyWeights[l][i][h];
                                    DecoderEmbedErr[i] += MaskedAttentionValueErr[(c*AttentionLayerSize)+l][h] * DecoderValueWeights[l][i][h];
                                }
                            }
                        }
                    }
                    for(int i = 0; i < EmbedSize; i++){
                        for(int l = 0; l < ResultSentence.size()+1; l++)
                            DecoderRegressionLayerWeightsErr[i] += DecoderEmbedErr[i] * (ResultValues.at(l)/ResultSentence.size());
                        DecoderRegressionLayerBiasErr[i] += DecoderEmbedErr[i];
                    }
                // DECODER MASKED SELF ATTENTION AĞIRLIKLARA HATA DAĞITIMI
                    for(int i = 0; i < ResultSentence.size(); i++){
                        for(int j = 0; j < AttentionLayerSize; j++){
                            for(int k = 0; k < EmbedSize/AttentionLayerSize; k++){
                                for(int l = 0; l < EmbedSize/AttentionLayerSize; l++)
                                    MaskedAttentionQueryWeightErr[j][k][l] += MaskedAttentionQueryErr[j][l] * (EmbedResults1[i][(j*(EmbedSize/AttentionLayerSize))+k]/ResultSentence.size());
                            }
                            for(int c = 0; c < ResultSentence.size(); c++){
                                for(int k = 0; k < EmbedSize/AttentionLayerSize; k++){
                                    for(int l = 0; l < EmbedSize/AttentionLayerSize; l++){
                                        MaskedAttentionValueWeightErr[j][k][l] += MaskedAttentionValueErr[(c * AttentionLayerSize)+j][l] * (EmbedResults1[i][(j*(EmbedSize/AttentionLayerSize))+k]/ResultSentence.size());
                                        MaskedAttentionKeyWeightErr[j][k][l] += MaskedAttentionKeyErr[(c * AttentionLayerSize)+j][l] * (EmbedResults1[i][(j*(EmbedSize/AttentionLayerSize))+k]/ResultSentence.size());
                                    }
                                }
                            }
                        }
                    }
                    /*                                        DECODER_MASKED_SELF_ATTENTION_KATMANI_BACKPROPAGATION_SONU                                               */
                    /*                                              ENCODER_SELF_ATTENTION_KATMANI_BACKPROPAGATION_BAŞLANGICI                                                  */
                    //std::cout << "Pass 8 : BACKPROPAGATION SELF ATTENTION" << std::endl;
                    // ENCODER ATTENTION VALUE VE SOFTMAX'E HATA DAĞITIMI
                    for(int i = 0; i < Sentence0.size(); i++){
                        for(int k = 0; k < AttentionLayerSize; k++){
                            for(int c = 0; c < Sentence0.size(); c++){
                                for(int l = 0; l < AttentionLayerSize; l++){
                                    for(int h = 0; h < EmbedSize/AttentionLayerSize; h++){
                                        EncoderSelfAttentionSoftMaxErr[k][(c* AttentionLayerSize) + l] += (Values[c][l][h]/Sentence0.size()) * EncoderSelfAttentionErr[(l*(EmbedSize/AttentionLayerSize))+h];
                                        EncoderValueErr[(c*AttentionLayerSize)+l][h] += (EncoderSelfAttentionSoftMax[i][k][(c*AttentionLayerSize)+l]/(Sentence0.size()*AttentionLayerSize)) * EncoderSelfAttentionErr[(l*(EmbedSize/AttentionLayerSize))+h];
                                    }
                                }
                            }
                        }
                    }
                    // ENCODER ATTENTION QUERY-KEY HESAPLAMALARINA HATA DAĞITIMI
                    long double AddF0 = 0;
                    for(int i = 0; i < Sentence0.size(); i++){
                        for(int k = 0; k < AttentionLayerSize; k++){
                            for(int v = 0; v < AttentionLayerSize; v++){
                                for(int h = 0; h < Sentence0.size(); h++)
                                    AddF0 += EncoderSelfAttentionSoftMaxErr[k][(h * AttentionLayerSize)+v] * (EncoderSelfAttentionSoftMax[i][k][(h * AttentionLayerSize)+v]/Sentence0.size());
                            }
                        }
                    }
                    for(int i = 0; i < Sentence0.size(); i++){
                        for(int k = 0; k < AttentionLayerSize; k++){
                            for(int l = 0; l < AttentionLayerSize; l++){
                                for(int c = 0; c < Sentence0.size(); c++){
                                    EncoderSelfAttentionSoftMaxInErr[k][(c * AttentionLayerSize)+l] += (EncoderSelfAttentionSoftMax[i][k][(c * AttentionLayerSize)+l]/(Sentence0.size()*AttentionLayerSize)) * (EncoderSelfAttentionSoftMaxErr[k][(c * AttentionLayerSize)+l] - AddF0);
                                }
                            }
                        }
                    }
                    // ENCODER ATTENTION QUERY'YE HATA DAĞITIMI
                    for(int k = 0; k < AttentionLayerSize; k++){
                        for(int l = 0; l < EmbedSize/AttentionLayerSize; l++){
                            for(int v = 0; v < Sentence0.size(); v++){
                                for(int h = 0; h < AttentionLayerSize; h++)
                                    EncoderQueryErr[k][l] += (EncoderSelfAttentionSoftMaxInErr[k][(v * AttentionLayerSize)+h]/Sentence0.size()) * (Keys[v][h][l]/Sentence0.size());
                            }
                        }
                    }
                    // ENCODER ATTENTION KEY'E HATA DAĞITIMI
                    for(int i = 0; i < Sentence0.size(); i++){
                        for(int k = 0; k < AttentionLayerSize; k++){
                            for(int c = 0; c < Sentence0.size(); c++){
                                for(int l = 0; l < AttentionLayerSize; l++){
                                    for(int h = 0; h < EmbedSize/AttentionLayerSize; h++)
                                        EncoderKeyErr[(c*AttentionLayerSize)+l][h] += (EncoderSelfAttentionSoftMaxInErr[k][(c*AttentionLayerSize)+l]/Sentence0.size()) * (Values[i][k][h]/Sentence0.size());
                                }
                            }
                        }
                    }
                        // ENCODER REGRESYON KATMANINA HATA DAĞITIMI
                    for(int i = 0; i < EmbedSize; i++){
                        for(int k = 0; k < AttentionLayerSize; k++){
                            for(int l = 0; l < EmbedSize/AttentionLayerSize; l++)
                                EncoderEmbedErr[i] += EncoderQueryErr[k][l] * EncoderQueryWeights[k][i][l];
                        }
                        for(int k = 0; k < Sentence0.size(); k++){
                            for(int l = 0; l < AttentionLayerSize; l++){
                                for(int h = 0; h < EmbedSize/AttentionLayerSize; h++){
                                    EncoderEmbedErr[i] += EncoderValueErr[(k*AttentionLayerSize)+l][h] * EncoderValueWeights[l][i][h];
                                    EncoderEmbedErr[i] += EncoderKeyErr[(k*AttentionLayerSize)+l][h] * EncoderKeyWeights[l][i][h];
                                }
                            }
                        }
                    }
                    for(int i = 0; i < EmbedSize; i++){
                        for(int l = 0; l < Sentence0.size()+1; l++)
                            EncoderRegressionLayerWeightsErr[i] += EncoderEmbedErr[i] * (CategoryValue0.at(l)/Sentence0.size());
                        EncoderRegressionLayerBiasErr[i] += EncoderEmbedErr[i];
                    }
                    // ENCODER AĞIRLIKLARA HATA DAĞITIMI
                    for(int i = 0; i < Sentence0.size(); i++){
                        for(int k = 0; k < AttentionLayerSize; k++){
                            for(int l = 0; l < EmbedSize/AttentionLayerSize; l++){
                                for(int n = 0; n < EmbedSize/AttentionLayerSize; n++)
                                    EncoderQueryWeightsErr[k][l][n] += EncoderQueryErr[k][n] * (EmbedResults0[i][(k * (EmbedSize/AttentionLayerSize)) + l]/Sentence0.size());
                            }
                            for(int c = 0; c < Sentence0.size(); c++){
                                for(int l = 0; l < EmbedSize/AttentionLayerSize; l++){
                                    for(int n = 0; n < EmbedSize/AttentionLayerSize; n++){
                                        EncoderValueWeightsErr[k][l][n] += EncoderValueErr[(c * AttentionLayerSize)+k][n] * (EmbedResults0[i][(k*(EmbedSize/AttentionLayerSize))+l]/Sentence0.size());
                                        EncoderKeyWeightsErr[k][l][n] += EncoderKeyErr[(c * AttentionLayerSize)+k][n] * (EmbedResults0[i][(k*(EmbedSize/AttentionLayerSize))+l]/Sentence0.size());
                                    }
                                }
                            }
                        }
                    }
                    /*                                               ENCODER_SELF_ATTENTION_KATMANI_BACKPROPAGATION_SONU                                                  */
                    // AĞIRLIKLARI GÜNCELLE
                    for(int i = 0; i < AttentionLayerSize; i++){
                        for(int k = 0; k < EmbedSize/AttentionLayerSize; k++){
                            for(int l = 0; l < EmbedSize/AttentionLayerSize; l++){
                                EncoderQueryWeights[i][k][l] -= EncoderQueryWeightsErr[i][k][l] * learningRate;
                                EncoderValueWeights[i][k][l] -= EncoderValueWeightsErr[i][k][l] * learningRate;
                                EncoderKeyWeights[i][k][l] -= EncoderKeyWeightsErr[i][k][l] * learningRate;
                                DecoderQueryWeights[i][k][l] -= MaskedAttentionQueryWeightErr[i][k][l] * learningRate;
                                DecoderValueWeights[i][k][l] -= MaskedAttentionValueWeightErr[i][k][l] * learningRate;
                                DecoderKeyWeights[i][k][l] -= MaskedAttentionKeyWeightErr[i][k][l] * learningRate;
                                DecoderQueryWeights_[i][k][l] -= DecoderQueryWeights_Err[i][k][l] * learningRate;
                                EncoderKeyWeights_[i][k][l] -= EncoderDecoderKeyWeights_Err[i][k][l] * learningRate;
                                EncoderValueWeights_[i][k][l] -= EncoderDecoderValueWeights_Err[i][k][l] * learningRate;
                                /*std::cout << " EncoderQueryWeights(" << i << "." << k << "." << l << "): " << EncoderQueryWeights[i][k][l] << " EncoderQueryWeightsErr(" << i << "." << k << "." << l << "): " << EncoderQueryWeightsErr[i][k][l] << std::endl;
                                std::cout << " EncoderValueWeights(" << i << "." << k << "." << l << "): " << EncoderValueWeights[i][k][l] << " EncoderValueWeightsErr(" << i << "." << k << "." << l << "): " << EncoderValueWeightsErr[i][k][l] << std::endl;
                                std::cout << " EncoderKeyWeights(" << i << "." << k << "." << l << "): " << EncoderKeyWeights[i][k][l] << " EncoderKeyWeightsErr(" << i << "." << k << "." << l << "): " << EncoderKeyWeightsErr[i][k][l] << std::endl;
                                std::cout << " DecoderQueryWeights(" << i << "." << k << "." << l << "): " << DecoderQueryWeights[i][k][l] << " MaskedAttentionQueryWeightErr(" << i << "." << k << "." << l << "): " << MaskedAttentionQueryWeightErr[i][k][l] << std::endl;
                                std::cout << " DecoderValueWeights(" << i << "." << k << "." << l << "): " << DecoderValueWeights[i][k][l] << " MaskedAttentionValueWeightErr(" << i << "." << k << "." << l << "): " << MaskedAttentionValueWeightErr[i][k][l] << std::endl;
                                std::cout << " DecoderKeyWeights(" << i << "." << k << "." << l << "): " << DecoderKeyWeights[i][k][l] << " MaskedAttentionKeyWeightErr(" << i << "." << k << "." << l << "): " << MaskedAttentionKeyWeightErr[i][k][l] << std::endl;
                                std::cout << " DecoderQueryWeights_(" << i << "." << k << "." << l << "): " << DecoderQueryWeights_[i][k][l] << " DecoderQueryWeights_Err(" << i << "." << k << "." << l << "): " << DecoderQueryWeights_Err[i][k][l] << std::endl;
                                std::cout << " EncoderKeyWeights_(" << i << "." << k << "." << l << "): " << EncoderKeyWeights_[i][k][l] << " EncoderDecoderKeyWeights_Err(" << i << "." << k << "." << l << "): " << EncoderDecoderKeyWeights_Err[i][k][l] << std::endl;
                                std::cout << " EncoderValueWeights_(" << i << "." << k << "." << l << "): " << EncoderValueWeights_[i][k][l] << " EncoderDecoderValueWeights_Err(" << i << "." << k << "." << l << "): " << EncoderDecoderValueWeights_Err[i][k][l] << std::endl;*/
                            }
                        }
                    }
                    for(int i = 0; i < EmbedSize; i++){
                        EncoderDecoderRegressionLayerWeights[i] -= EncoderDecoderRegressionLayerWeightsErr[i] * learningRate;
                        EncoderRegressionLayerWeights[i] -= EncoderRegressionLayerWeightsErr[i] * learningRate;
                        EncoderRegressionBias[i] -= EncoderRegressionLayerBiasErr[i] * learningRate;
                        DecoderRegressionLayerWeights[i] -= DecoderRegressionLayerWeightsErr[i] * learningRate;
                        DecoderRegressionBias[i] -= DecoderRegressionLayerBiasErr[i] * learningRate;
                    }
                    EncoderDecoderRegressionBias -= EncoderDecoderRegressionBias * learningRate;
                    std::cout << " EncoderQueryWeights(" << 0 << "." << 0 << "." << 0 << "): " << EncoderQueryWeights[0][0][0] << " EncoderQueryWeightsErr(" << 0 << "." << 0 << "." << 0 << "): " << EncoderQueryWeightsErr[0][0][0] << std::endl;
                    std::cout << " EncoderValueWeights(" << 0 << "." << 0 << "." << 0 << "): " << EncoderValueWeights[0][0][0] << " EncoderValueWeightsErr(" << 0 << "." << 0 << "." << 0 << "): " << EncoderValueWeightsErr[0][0][0] << std::endl;
                    std::cout << " EncoderKeyWeights(" << 0 << "." << 0 << "." << 0 << "): " << EncoderKeyWeights[0][0][0] << " EncoderKeyWeightsErr(" << 0 << "." << 0 << "." << 0 << "): " << EncoderKeyWeightsErr[0][0][0] << std::endl;
                    std::cout << " DecoderQueryWeights(" << 0 << "." << 0 << "." << 0 << "): " << DecoderQueryWeights[0][0][0] << " MaskedAttentionQueryWeightErr(" << 0 << "." << 0 << "." << 0 << "): " << MaskedAttentionQueryWeightErr[0][0][0] << std::endl;
                    std::cout << " DecoderValueWeights(" << 0 << "." << 0 << "." << 0 << "): " << DecoderValueWeights[0][0][0] << " MaskedAttentionValueWeightErr(" << 0 << "." << 0 << "." << 0 << "): " << MaskedAttentionValueWeightErr[0][0][0] << std::endl;
                    std::cout << " DecoderKeyWeights(" << 0 << "." << 0 << "." << 0 << "): " << DecoderKeyWeights[0][0][0] << " MaskedAttentionKeyWeightErr(" << 0 << "." << 0 << "." << 0 << "): " << MaskedAttentionKeyWeightErr[0][0][0] << std::endl;
                    std::cout << " DecoderQueryWeights_(" << 0 << "." << 0 << "." << 0 << "): " << DecoderQueryWeights_[0][0][0] << " DecoderQueryWeights_Err(" << 0 << "." << 0 << "." << 0 << "): " << DecoderQueryWeights_Err[0][0][0] << std::endl;
                    std::cout << " EncoderKeyWeights_(" << 0 << "." << 0 << "." << 0 << "): " << EncoderKeyWeights_[0][0][0] << " EncoderDecoderKeyWeights_Err(" << 0 << "." << 0 << "." << 0 << "): " << EncoderDecoderKeyWeights_Err[0][0][0] << std::endl;
                    std::cout << " EncoderValueWeights_(" << 0 << "." << 0 << "." << 0 << "): " << EncoderValueWeights_[0][0][0] << " EncoderDecoderValueWeights_Err(" << 0 << "." << 0 << "." << 0 << "): " << EncoderDecoderValueWeights_Err[0][0][0] << std::endl;
                    for(int k = 0; k < ResultSentence.size(); k++){
                        for(int l = 0; l < EmbedSize; l++){
                            for(int v = 0; v < tokenizedVocap2.size(); v++){
                                DecoderNNLayerWeights[l][v] -= DecoderNNLayerDerr[l][v] * learningRate;
                                //std::cout << " DecoderNNLayerWeights(" << l << "." << v << "): " << DecoderNNLayerWeights[l][v] << " DecoderNNLayerDerr(" << l << "." << v << "): " << DecoderNNLayerDerr[l][v] << std::endl;
                            }
                        }
                    }
                    // DEĞİŞKENLERİ SİLER /// TODO: SOME OF THEM SHOULDN'T BE TEMPORARY!
                    for(int i = 0; i < DecoderQueries.size(); i++){
                        for(int k = 0; k < AttentionLayerSize; k++){
                            delete[] DecoderQueries[i][k];
                            delete[] DecoderValues[i][k];
                            delete[] DecoderKeys[i][k];
                            delete[] MaskedSelfAtQueryKeyCal[i][k];
                            delete[] DecoderAttentionQuery[i][k];
                            delete[] DecoderAttentionQueryKeyCal[i][k];
                        }
                        delete[] DecoderQueries[i];
                        delete[] DecoderValues[i];
                        delete[] DecoderKeys[i];
                        delete[] MaskedSelfAtQueryKeyCal[i];
                        delete[] Encoder_DecoderAttention[i];
                        delete[] Decoder_SelfAttention[i];
                        delete[] DecoderAttentionQuery[i];
                        delete[] DecoderAttentionQueryKeyCal[i];
                    }
                    for(int i = 0; i < Sentence0.size(); i++){
                        for(int l = 0; l < AttentionLayerSize; l++){
                            delete[] Queries[i][l];
                            delete[] Values[i][l];
                            delete[] Keys[i][l];
                            delete[] QueryKeyCalculations_Encoder[i][l];
                            delete[] EncoderKeys[i][l];
                            delete[] EncoderValues[i][l];
                        }
                        delete[] Queries[i];
                        delete[] Values[i];
                        delete[] Keys[i];
                        delete[] SelfAttentionValues[i];
                        delete[] QueryKeyCalculations_Encoder[i];
                        delete[] EncoderKeys[i];
                        delete[] EncoderValues[i];
                    }
                    for(int i = 0; i < AttentionLayerSize; i++){
                        for(int k = 0; k <EmbedSize/AttentionLayerSize; k++){
                            delete[] MaskedAttentionQueryWeightErr[i][k];
                            delete[] MaskedAttentionValueWeightErr[i][k];
                            delete[] MaskedAttentionKeyWeightErr[i][k];
                            delete[] DecoderQueryWeights_Err[i][k];
                            delete[] EncoderDecoderValueWeights_Err[i][k];
                            delete[] EncoderDecoderKeyWeights_Err[i][k];
                            delete[] EncoderKeyWeightsErr[i][k];
                            delete[] EncoderValueWeightsErr[i][k];
                            delete[] EncoderQueryWeightsErr[i][k];
                        }
                        delete[] MaskedAttentionQueryWeightErr[i];
                        delete[] MaskedAttentionValueWeightErr[i];
                        delete[] MaskedAttentionKeyWeightErr[i];
                        delete[] DecoderQueryWeights_Err[i];
                        delete[] EncoderDecoderValueWeights_Err[i];
                        delete[] EncoderDecoderKeyWeights_Err[i];
                        delete[] EncoderKeyWeightsErr[i];
                        delete[] EncoderValueWeightsErr[i];
                        delete[] EncoderQueryWeightsErr[i];
                        delete[] EncoderSelfAttentionSoftMaxErr[i];
                        delete[] EncoderSelfAttentionSoftMaxInErr[i];
                        delete[] EncoderQueryErr[i];
                    }
                    for(int i = 0; i < ResultSentence.size()*AttentionLayerSize; i++){
                        delete[] MaskedAttentionValueErr[i];
                        delete[] MaskedAttentionKeyErr[i];
                    }
                    for(int i = 0; i < AttentionLayerSize; i++){
                        for(int l = 0; l < Sentence0.size(); l++){
                            for(int k = 0; k < AttentionLayerSize; k++){
                                delete[] EncoderDecoderValuesErr[i][l][k];
                                delete[] EncoderDecoderKeysErr[i][l][k];
                            }
                            delete[] AttentionSoftMaxErrorIn[i][l];
                            delete[] AttentionLayerSoftMaxErr[i][l];
                            delete[] EncoderDecoderValuesErr[i][l];
                            delete[] EncoderDecoderKeysErr[i][l];
                        }
                        delete[] MaskedAttentionQueryErr[i];
                        delete[] MaskedAttentionResultErr[i];
                        delete[] MaskedAttentionSoftMaxErr[i];
                        delete[] MaskedAttentionSoftMaxInErr[i];
                        delete[] DecoderAttenQueriesErr[i];
                        delete[] AttentionSoftMaxErrorIn[i];
                        delete[] AttentionLayerSoftMaxErr[i];
                        delete[] EncoderDecoderValuesErr[i];
                        delete[] EncoderDecoderKeysErr[i];
                    }
                    for(int i = 0; i < EmbedSize; i++)
                        delete[] DecoderNNLayerDerr[i];
                    delete[] EncoderDecoderRegressionLayerWeightsErr;
                    delete[] EncoderRegressionLayerWeightsErr;
                    delete[] EncoderRegressionLayerBiasErr;
                    delete[] DecoderRegressionLayerWeightsErr;
                    delete[] DecoderRegressionLayerBiasErr;
                    delete[] Queries;
                    delete[] Values;
                    delete[] Keys;
                    delete[] SelfAttentionValues;
                    delete[] QueryKeyCalculations_Encoder;
                    delete[] EncoderKeys;
                    delete[] EncoderValues;
                    delete[] AttentionLayerSoftMaxErr;
                    delete[] AttentionSoftMaxErrorIn;
                    delete[] MaskedAttentionSoftMaxErr;
                    delete[] MaskedAttentionSoftMaxInErr;
                    delete[] ENeurons;
                    delete[] DecoderNNLayerDerr;
                    delete[] DecoderAttenQueriesErr;
                    delete[] EncoderDecoderKeysErr;
                    delete[] EncoderDecoderValuesErr;
                    delete[] MaskedAttentionResultErr;
                    delete[] MaskedAttentionValueErr;
                    delete[] MaskedAttentionKeyErr;
                    delete[] MaskedAttentionQueryErr;
                    delete[] EncoderKeyErr;
                    delete[] EncoderQueryErr;
                    delete[] EncoderSelfAttentionErr;
                    delete[] EncoderSelfAttentionSoftMaxErr;
                    delete[] EncoderSelfAttentionSoftMaxInErr;
                    delete[] MaskedAttentionQueryWeightErr;
                    delete[] MaskedAttentionValueWeightErr;
                    delete[] MaskedAttentionKeyWeightErr;
                    delete[] DecoderQueryWeights_Err;
                    delete[] EncoderDecoderValueWeights_Err;
                    delete[] EncoderDecoderKeyWeights_Err;
                    delete[] EncoderKeyWeightsErr;
                    delete[] EncoderValueWeightsErr;
                    delete[] EncoderQueryWeightsErr;
                }
                Data->freeMemory();
                break;
            }
        }
    }
}

// AKTİVASYON FONKSİYONLARI
std::vector<long double> RegresifTransformer::softMax(int outputLenght, long double* Outputs) const {
    std::vector<long double> softOut(outputLenght);
    long double sum_exp = 0.0;
    long double maxValue;
    for (int i = 0; i < outputLenght; i++) {
        if (i == 0) maxValue = *(Outputs + i);
        else if (maxValue < *(Outputs + i)) maxValue = *(Outputs + i);
    }
    for (int i = 0; i < outputLenght; i++) {
        *(Outputs + i) -= maxValue;
    }
    for (int i = 0; i < outputLenght; i++) {
        sum_exp += exp(*(Outputs + i));
    }
    for (int i = 0; i < outputLenght; i++) {
        softOut[i] = exp(*(Outputs + i)) / sum_exp;
    }
    return softOut;
}
std::vector<long double> RegresifTransformer::CrossEntropyLoss(std::vector<long double>& softMaxOutputs, std::vector<long double>& ExpectedValues) const {
    std::vector<long double> derivatives(softMaxOutputs.size());
    for (int i = 0; i < softMaxOutputs.size(); i++) {
        derivatives[i] = softMaxOutputs[i] - ExpectedValues[i];
    }
    return derivatives;
}
long double RegresifTransformer::cross_entropy_loss(const std::vector<long double>& y_pred, const std::vector<long double>& y_true) const {
    assert(y_pred.size() == y_true.size() && "Tahmin ve gerçek etiket boyutları eşit olmalıdır.");

    long double loss = 0.0;
    for (size_t i = 0; i < y_pred.size(); ++i) {
        long double pred = std::max(std::min((double)y_pred[i],1.0-(1e-12)),1e-12);
        /*if(y_pred[i] <= 0.0 || y_pred[i] >= 1.0){
            std::cout << i << ": " << y_pred[i] << " Predictions should be in range of 1 and 0!" << std::endl;
            std::exit(-1);
        }*/
        loss -= y_true[i] * log(pred) + (1 - y_true[i]) * log(1-pred);
    }
    return loss/y_pred.size();
}
long double RegresifTransformer::sigmoid(long double i) const {
    return 1 / (1 + exp((float)-i));
}
long double RegresifTransformer::dSigmoid(long double i) const {
    return (1 / (1 + exp((float)-i))) * (1 - (1 / (1 + exp((float)-i))));
}
double RegresifTransformer::GetRandValue(double min, double max) const {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<> distrib(min, max);
    return distrib(gen);
}
long double RegresifTransformer::mean2ErrDerr(long double predicted,long double trueValue) const{
    return 2*(predicted-trueValue);
}

RegresifTransformer::~RegresifTransformer() {
    int layerMap[3] = { tokenizedVocap1.size(), EmbedSize, tokenizedVocap1.size() };
    delete[] Data;
    for (int i = 0; i < 2; i++) {
        for (int k = 0; k < layerMap[i]; k++) {
            delete[] EmbedWeightsVocap1[i][k];
        }
        delete[] EmbedWeightsVocap1[i];
    }
    delete[] EmbedWeightsVocap1;
    for (int i = 0; i < 2; i++) {
        for (int k = 0; k < layerMap[i]; k++) {
            delete[] EmbedWeightsVocap2[i][k];
        }
        delete[] EmbedWeightsVocap2[i];
    }
    delete[] EmbedWeightsVocap2;
}

long double RegresifTransformer::positionalEncoding(int position, int index, int d_model) const {
    float denominator = std::pow(10000.0, (2.0 * index) / d_model);
    if (index % 2 == 0) {
        return std::sin(position / denominator);
    } else {
        return std::cos(position / denominator);
    }
}