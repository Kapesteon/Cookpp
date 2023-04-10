#include "InfoNutri.h"

#define NUMBER_ATRIBUTES 7

#define DELIMITER_KEY_VALUE_INFONUTRI ":" //For serialization

/*
std::vector<std::string> InfoNutri::keys = { "perAmount", "calories","fat","cholesterol","sodium","carbohydrate","protein" };
*/

std::vector<std::string> InfoNutri::keys = { "perAmount", "calories","fat","cholesterol","sodium","carbohydrate","protein" };
std::array<double, NUMBER_ATRIBUTES> nutriValues = { 0,0,0,0,0,0,0 };


InfoNutri::InfoNutri()
{

    /*
    for (int i = 0; i < NUMBER_ATRIBUTES; i++) {
        values[keys[i]] = 0;

    }
    */
    for (int i = 0; i < NUMBER_ATRIBUTES; i++) {
        nutriValues.at(i) = 0;
    }
}

InfoNutri::InfoNutri(std::vector<double>& param)
{
    /*
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
    */
    if (param.size() != NUMBER_ATRIBUTES) {
        //std::cout << "Size required : " << values.size();
        std::cout << "Size given : " << param.size();
        throw std::invalid_argument("Wrong Size of argument");
    }
    else {
        for (int i = 0; i < param.size(); i++) {
            nutriValues.at(i) = param[i];
        }
    }
}

InfoNutri::InfoNutri(double *tab, size_t len)
{
    int sizeRequired = NUMBER_ATRIBUTES; //7 attributes, 8 bytes for a double

    /*
    if (len != sizeRequired) {
        std::cout << "Size required : " << sizeRequired;
        std::cout << "Size given : " << int(sizeof(*tab));
        throw std::invalid_argument("Wrong Size of argument");
    }

    for (int i = 0; i < NUMBER_ATRIBUTES; i++) {
        values[keys[i]] = tab[i];
    }
    */

    if (len != NUMBER_ATRIBUTES) {
        //std::cout << "Size required : " << values.size();
        std::cout << "Size given : " << len;
        throw std::invalid_argument("Wrong Size of argument");
    }
    else {
        for (int i = 0; i < len; i++) {
            nutriValues.at(i) = tab[i];
        }
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

    int i = 0;
    for (itr; itr < this->keys.end(); itr++) {
        this->nutriValues.at(i) = param[*(itr)];
        i++;
    }
}


InfoNutri::InfoNutri(const InfoNutri& c)
{
    this->nutriValues = c.nutriValues;
}

InfoNutri::~InfoNutri()
{
    OutputDebugStringA("InfoNutri Destroyed \n");
}



const std::array<double, NUMBER_ATRIBUTES> InfoNutri::getNutriValues() const
{
    
    return this->nutriValues;
}

const std::vector<std::string> InfoNutri::getNutriKeys()
{
    return keys;
}








std::istream& operator>>(std::istream& is, InfoNutri& in)
{
    /*
    is >> in.name;
    std::string s = "";
    is >> s;

    std::string delimiter = DELIMITER_KEY_VALUE_INFONUTRI;
    std::string key = s.substr(0, s.find(delimiter)); 
    std::string value = s.substr(s.find(delimiter)+1, s.size());
        in.values.at(key) = std::stod(value);
    */
    /*
    try {
        std::string key;
        is >> key;
        is >> in.values[key];
    }
    catch (std::exception) {
        std::cout << "Couldn't recover Ingredient from database";
        OutputDebugStringA("Couldn't recover Ingredient from database");
        return is;
    }
    */
    /*
    try {
        std::string key;
        is >> key;
        is >> key;
        in.values["calories"] = 1;
    }
    catch (std::exception) {
        std::cout << "Couldn't recover Ingredient from database";
        OutputDebugStringA("Couldn't recover Ingredient from database");
        return is;
    }
    */

    return is;

}

std::ostream& operator<<(std::ostream& os, const InfoNutri& in)
{
    /*
    os << in.name;
    for (auto const& x : in.values)
    {
        os << x.first
           << DELIMITER_KEY_VALUE_INFONUTRI
           //<< std::endl
           << x.second  // string (key) + string's value 
           << std::endl;
    }
   */

    
    return os;
}
