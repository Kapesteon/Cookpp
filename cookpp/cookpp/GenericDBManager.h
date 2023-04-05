#pragma once
#include <fstream>
#include <stdlib.h>
#include <string>
#include <memory>
#include <iostream>



class GenericDBManager
{
	private:

		std::string filepath;
		static const std::streamsize classSize;
	public:
		std::fstream stream;

		GenericDBManager();
		GenericDBManager(std::string filepath);
		GenericDBManager(GenericDBManager &c);
		~GenericDBManager();

		void setFilePath(std::string filepath);
		std::string getFilepath() const;
		bool open();
		bool close();
		virtual bool write(void *,int pos) = 0;
		virtual bool read(void *, int pos) = 0;

};

