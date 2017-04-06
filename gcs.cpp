#include "gcs.h"
#include <cstring>
#include <iostream>
#include <iomanip>

using namespace std;

GCS::GCS(char const * const name):
	name{strcpy(new char[strlen(name)+1], name)}
{
}

GCS::~GCS()
{
	delete [] name;
}

GCS& GCS::operator=(const GCS& gcs)
{
	this->name = strcpy(new char[strlen(gcs.name)+1], gcs.name);
	return *this;
}

GCS::GCS(const GCS& source)
{
	if(this->name)
		delete this->name;
	this->name = strcpy(new char[strlen(source.name)+1], source.name);
}

void GCS::setName(char const * const name)
{
	if(this->name)
		delete[] this->name;
	if(strcmp(name, "") == 0) {
		this->name = nullptr;
		return;
	}

	this->name = strcpy(new char[strlen(name)+ 1], name);
}

bool operator<(const GCS& gcs1, const GCS& gcs2)
{
	if (strcmp(gcs1.name, gcs2.name) == -1)
		return true;
	else
		return false;
}

bool operator==(const GCS& gcs1, const GCS& gcs2)
{
	return (strcmp(gcs1.name,gcs2.name) == 0);
	//return false;
}

ostream& operator<<(ostream& out, const GCS& gcs)
{
	out << gcs.name;
	return out;
}
