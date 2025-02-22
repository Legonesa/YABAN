
/*          Bu bir Model taslak dosyasıdır.     
        Model ortam ve deneye göre değişecektir.    */

#ifndef MODEL_HPP
#define MODEL_HPP

#include <utility>
#include <vector>
#include "Environment.hpp"

class Model{
    public:
        Model(){}
        virtual void fit(const std::vector<observation_t>&,
                         const std::vector<action_t>&,
                         const std::vector<float>&){}
        virtual std::pair<std::vector<float>, float> predictPolicyValue(const observation_t&){return {};}
        virtual void save(){}
};

#endif
