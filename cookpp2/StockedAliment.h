#pragma once 
#include "Aliment.h" 
#include <time.h> 
#include <ctime>
#include <iomanip>
#include <sstream>
#include <chrono>
#include <codecvt>
#include <string>

class StockedAliment : public Aliment
{
private:
	const static std::string format;

	std::time_t obtainedDate;
	std::time_t spoilRate;
	std::time_t spoilDate;

public:
	StockedAliment();
	//StockedAliment(std::string name, std::string type, std::string season, InfoNutri* infoNutri, double mass, time_t obtainedDate, time_t spoilRate);
	StockedAliment(const Ingredient& ingredient, double mass, time_t obtainedDate, time_t spoilRate);
	StockedAliment(const Ingredient& ingredient, double mass, std::string obtainedDate, int spoilRateDays);
	StockedAliment(const Aliment& aliment, time_t obtainedDate, time_t spoilRate);
	StockedAliment(const Aliment& aliment, std::string obtainedDate, int spoilRateDays);
	StockedAliment(const StockedAliment& c);
	~StockedAliment();

	const std::string getObtainedDate() const;
	void setObtainedDate(time_t obtainedDate);



	const int getSpoilRateInDays() const;
	void setSpoilRateInDays(int spoilRate) ;

	const std::string getSpoilDate() const;
	void calculateSpoilDate(void);

	time_t strTotime_t(std::string strDate);
	std::string time_tToStr(time_t time) const ;

	StockedAliment operator< (const StockedAliment& s) const;
	friend bool operator==(const StockedAliment& l, const StockedAliment& r);
	bool operator==(const StockedAliment& r);


	friend std::istream& operator >>(std::istream& is, StockedAliment& in);
	friend std::ostream& operator <<(std::ostream& os, const StockedAliment& in);
};


