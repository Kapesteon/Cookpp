#include "InfoNutri.h"

#define NUMBER_ATRIBUTES 7

/*
std::vector<std::string> InfoNutri::keys = { "perAmount", "calories","fat","cholesterol","sodium","carbohydrate","protein" };
*/

std::vector<std::string> InfoNutri::keys = { "perAmount", "calories","fat","cholesterol","sodium","carbohydrate","protein" };







InfoNutri::InfoNutri()
{

    for (int i = 0; i < NUMBER_ATRIBUTES; i++) {
        values[keys[i]] = 0;

    }
 
}

InfoNutri::InfoNutri(std::vector<double>& param)
{
    if (param.size() != NUMBER_ATRIBUTES) {
        //std::cout << "Size required : " << values.size();
        std::cout << "Size given : " << param.size();
        throw std::invalid_argument("Wrong Size of argument");
    }
    else {
        for (int i = 0; i < param.size(); i++) {
            values[keys[i]] = param[i];
        }
    }
    
}

InfoNutri::InfoNutri(double *tab, size_t len)
{
    int sizeRequired = NUMBER_ATRIBUTES; //7 attributes, 8 bytes for a double

    if (len != sizeRequired) {
        std::cout << "Size required : " << sizeRequired;
        std::cout << "Size given : " << int(sizeof(*tab));
        throw std::invalid_argument("Wrong Size of argument");
    }

    for (int i = 0; i < NUMBER_ATRIBUTES; i++) {
        values[keys[i]] = tab[i];
    }
}

InfoNutri::InfoNutri(std::map<std::string, double> param)
{
    if (param.size() != this->keys.size()) {
        throw std::invalid_argument("Bad parameter size");
    }
    else {

    }

    auto itr = this->keys.begin();


    for (itr; itr < this->keys.end(); itr++) {
        this->values[(*itr)] = param[*(itr)];

    }
}

InfoNutri::InfoNutri(const InfoNutri& c)
{
    this->values = c.values;
}

InfoNutri::~InfoNutri()
{
    OutputDebugStringA("InfoNutri Destroyed \n");
}

void InfoNutri::printInfoNutri()
{

    for (auto const& x : this->values)
    {
        std::cout << x.first  // string (key)
            << ':'
            << x.second     // string's value 
            << std::endl;
    }
}

const std::map<std::string, double> InfoNutri::getNutriValues() const
{
    
    return this->values;
}


//Overloading COUT
/*
NOT USED BECAUSE NON-CONSOLE PROGRAM
*/
std::ostream& operator<<(std::ostream& os, const InfoNutri& infoNutri)
{

    for (auto const& x : infoNutri.values)
    {
        os << x.first  // string (key)
            << ':'
            << x.second     // string's value 
            << std::endl;
    }

    return os;
}

