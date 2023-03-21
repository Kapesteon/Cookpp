#include "InfoNutri.h"


const std::vector<std::string> InfoNutri::keys({ "perAmount", "calories","fat","cholesterol","sodium","carbohydrate","protein"});


InfoNutri::InfoNutri()
{

    for (int i = 0; i < 8; i++) {
        values[keys[i]] = 0;

    }
 
}

InfoNutri::InfoNutri(std::map<std::string, double>& param)
{

}

InfoNutri::InfoNutri(double* tab)
{
    int sizeRequired = 7 * 8; //7 attributes, 8 bytes for a double

    if (int(sizeof(tab)) != sizeRequired) {
        std::cout << "Size required : " << sizeRequired;
        std::cout << "Size given : " << int(sizeof(tab));
        throw std::invalid_argument("Wrong Size of argument");
    }

    for (int i = 0; i < 8; i++) {
        values[keys[i]] = *tab + i * 8;
    }
}

InfoNutri::InfoNutri(InfoNutri& c)
{
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

std::map<std::string, double>* InfoNutri::getInfoNutri()
{
    return nullptr;
}
