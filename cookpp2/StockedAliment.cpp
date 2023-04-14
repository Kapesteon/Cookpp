#include "StockedAliment.h"

const std::string StockedAliment::format = "%Y/%m/%d";

//https://en.cppreference.com/w/cpp/io/manip/get_time
//https://cplusplus.com/reference/ctime/strftime/



StockedAliment::StockedAliment()
	: Aliment()
{
	this->obtainedDate = 0;
	this->spoilRate = 0;
	this->calculateSpoilDate();
}

/*
StockedAliment::StockedAliment(std::string name, std::string type, std::string season, InfoNutri* infoNutri, double mass,time_t obtainedDate, time_t spoilRate)
	: Aliment(name,type,season,infoNutri,mass)
{
	this->obtainedDate = obtainedDate;
	this->spoilRate = spoilRate;
	this->calculateSpoilDate();
}
*/

StockedAliment::StockedAliment(const Ingredient& ingredient, double mass, time_t obtainedDate, time_t spoilRate)
	:Aliment(ingredient, mass)
{
	this->obtainedDate = obtainedDate;
	this->spoilRate = spoilRate;
	this->calculateSpoilDate();
}
StockedAliment::StockedAliment(const Ingredient& ingredient, double mass, std::string obtainedDate, int spoilRateDays)
	:Aliment(ingredient, mass)
{
	this->obtainedDate = this->strTotime_t(obtainedDate);
	this->spoilRate = spoilRateDays * 86400;
	this->calculateSpoilDate();
}




StockedAliment::StockedAliment(const Aliment& aliment, time_t obtainedDate, time_t spoilRate)
	: Aliment(aliment)
{
	this->obtainedDate = obtainedDate;
	this->spoilRate = spoilRate;
	this->calculateSpoilDate();
}
StockedAliment::StockedAliment(const Aliment& aliment, std::string obtainedDate, int spoilRateDays)
	: Aliment(aliment)
{
	this->obtainedDate = this->strTotime_t(obtainedDate);
	this->spoilRate = spoilRateDays * 86400;
	this->calculateSpoilDate();
}



/*
StockedAliment::StockedAliment(const StockedAliment& c)
	: Aliment(c)
{
	this->obtainedDate = obtainedDate;
	this->spoilRate = spoilRate;
	this->calculateSpoilDate();
}
*/





const std::string StockedAliment::getObtainedDate() const
{

	return this->time_tToStr(this->obtainedDate);
}

void StockedAliment::setObtainedDate(time_t obtainedDate)
{
	this->obtainedDate = obtainedDate;
	this->calculateSpoilDate();

}




const int StockedAliment::getSpoilRateInDays() const
{
	return (this->spoilRate / 86400);
}

void StockedAliment::setSpoilRateInDays(int spoilRate)
{
	
	this->spoilRate = spoilRate * 86400;
	this->calculateSpoilDate();
}




const std::string StockedAliment::getSpoilDate() const
{
	return  this->time_tToStr(this->spoilDate);
}



void StockedAliment::calculateSpoilDate(void)
{
	this->spoilDate = this->obtainedDate + this->spoilRate;
}





//https://stackoverflow.com/questions/321793/date-time-conversion-string-representation-to-time-t
//https://codereview.stackexchange.com/questions/277459/convert-string-to-date-c
time_t StockedAliment::strTotime_t(std::string strDate) 
{

	bool is_dst = false;
	std::tm t = {0};
	t.tm_isdst = is_dst ? 1 : 0;

	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> conv1;
	std::wstring format = conv1.from_bytes(this->format);

	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> conv2;
	std::wstring str = conv2.from_bytes(strDate);

	//a = std::wstring(&strDate);
	std::wistringstream ss(str);
	//ss.imbue(std::locale("de_DE.utf-8"));
	ss >> std::get_time(&t, format.c_str());
	return mktime(&t);

}

//https://stackoverflow.com/questions/997512/string-representation-of-time-t
std::string StockedAliment::time_tToStr(time_t time) const
{
	//std::time_t now = std::time(NULL);
	std::tm ptm;
	errno_t err = localtime_s(&ptm ,&time);
	char buffer[32];

	std::strftime(buffer, 32, this->format.c_str(), &ptm);
	return std::string(buffer);
}



StockedAliment StockedAliment::operator<(const StockedAliment& s) const
{
	if (this == &s) return *this;
	if (int(this->spoilDate) < int(s.spoilDate)){
		return s;
	}
	else {
		return *this;
	}
}



bool StockedAliment::operator==(const StockedAliment& r)
{
	{

		if (this->getMass() == r.getMass() && this->getObtainedDate() == r.getObtainedDate()) {
			return true;
		}
		else {
			return false;
		}

}


}

bool operator==(const StockedAliment& l, const StockedAliment& r)
{

	if (l.getMass() == r.getMass() && l.getObtainedDate() == r.getObtainedDate()) {
		return true;
	}
	else {
		return false;
	}

}

std::istream& operator>>(std::istream& is, StockedAliment& in)
{

	try {
		is >> static_cast<Aliment&>(in); //static cast to call Parent istream operator>>

		is >> in.spoilDate;

		is >> in.spoilRate;

		is >> in.spoilDate;

		return is;
	}
	catch (std::exception) {
		std::cout << "Couldn't recover StockedAliment from database";
		OutputDebugStringA("Couldn't recover StockedAliment from database");
		return is;
	}


	return is;

}

std::ostream& operator<<(std::ostream& os, const StockedAliment& in)
{

	try {
		os << static_cast<const Aliment&>(in)
			<< std::endl
			<< in.spoilDate
			<< std::endl
			<< in.spoilRate
			<< std::endl
			<< in.spoilDate
			<< std::endl;
		return os;
	}
	catch (std::exception) {
		std::cout << "Couldn't add StockedAliment to database";
		OutputDebugStringA("Couldn't add StockedAliment to database");
		return os;
	}
	return os;
}