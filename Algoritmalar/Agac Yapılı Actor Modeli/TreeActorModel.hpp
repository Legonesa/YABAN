
/*     Bu takımımız tarafından geliştirilen bir Transformer kütüphanesidir.
                Bu kütüphane YABAN Projesi için geliştirilmiştir.
             (Bu versionda Matrix kütüphanesi entegre edilmemiştir.)
    (Matrix kütüphanesinin entegre edildiği versiyon geliştirme aşamasındadır.!)       */

#ifndef TREE_ACTOR_MODEL_HPP
#define TREE_ACTOR_MODEL_HPP
#include "readCSV.hpp"

enum TransformerType{
    StandartLanguageTransformer = 0,
    RegressionTransformer
};

class TreeActorModel{
private:
    TransformerType transformer_Type;
    DataSet* Data;
    int DataSize, batch_size, EmbedSize, AttentionLayerSize, maxDecoder;
    std::map<std::string, int> tokenizedVocap1, tokenizedVocap2;
    long double*** EmbedWeightsVocap1, *** EmbedWeightsVocap2;
    long double*** EncoderKeyWeights, *** EncoderValueWeights, *** EncoderQueryWeights;
    long double*** DecoderKeyWeights, *** DecoderValueWeights, *** DecoderQueryWeights,
        ***DecoderQueryWeights_, ***EncoderKeyWeights_, ***EncoderValueWeights_;
    long double** DecoderNNLayerWeights, *EncoderDecoderRegressionLayerWeights, *EncoderRegressionLayerWeights,
                EncoderDecoderRegressionBias, *EncoderRegressionBias, *DecoderRegressionLayerWeights, *DecoderRegressionBias;
    std::vector<long double> softMax(int outputLenght, long double* Outputs) const;
    long double cross_entropy_loss(const std::vector<long double>& y_pred, const std::vector<long double>& y_true) const;
    std::vector<long double> CrossEntropyLoss(std::vector<long double>& softMaxOutputs, std::vector<long double>& ExpectedValues) const;
    long double sigmoid(long double i) const; long double dSigmoid(long double i) const;
    double GetRandValue(double min, double max) const; // Rastgele değer oluşturur.
    long double positionalEncoding(int seqLen, int wordPosition, int embedPos) const;
    std::vector<long double> predictEmbed(int wordToken, int vocap) const;
    long double mean2ErrDerr(long double predicted, long double trueValue) const;
    void TreeActorModel::DecoderLayer(int count, int NextWord, int max_seq, std::vector<int> Sentence0, std::vector<int> Sentence1, std::map<int, long double> CategoryValue1, long double ***EncoderValues, long double ***EncoderKeys);
public:
    TreeActorModel(const char* DataSetName, int SizeOfData, int data_batch,
                TransformerType type);
    ~TreeActorModel();
    void TokenizeData(); // Verileri etiketler.
    void Embedding(int EmbedSize, int epoch, long double learningRate, int attentionSize); // Etiketlenmiş verileri konumlarına göre eğitir ve vektörlere çevirir.
    void Learn(int epoch, long double learningRate, int max_seq, int maxDecoder); // Eğitim
};

#endif