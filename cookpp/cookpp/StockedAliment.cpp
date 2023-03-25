#include "StockedAliment.h"

const std::string StockedAliment::format = "%Y-%m-%d"; 
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




StockedAliment::StockedAliment(const StockedAliment& c)
{
	this->obtainedDate = obtainedDate;
	this->spoilRate = spoilRate;
	this->calculateSpoilDate();
}
StockedAliment::~StockedAliment()
{
	OutputDebugStringA("StockedAliment Destroyed \n");
}





const std::string StockedAliment::getObtainedDate() const
{

	return this->time_tToStr(this->obtainedDate);
}

void StockedAliment::setObtainedDate(time_t obtainedDate)
{
	this->calculateSpoilDate();
	this->obtainedDate = obtainedDate;
}




const int StockedAliment::getSpoilRateInDays() const
{
	return (this->spoilRate * 86400);
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
time_t StockedAliment::strTotime_t(std::string strDate) const
{
	bool is_dst = false;
	std::tm t = { 0 };
	t.tm_isdst = is_dst ? 1 : 0;
	std::istringstream ss(strDate);
	ss >> std::get_time(&t, this->format.c_str());
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
