#pragma once
#include <iostream>
#include <string>

class Employee
{
	//std::string email,    first_name, last_name; // Does not work
	//std::string first_name, last_name,  email;     // works

	// Does not work
	/*std::string email;
	std::string first_name;
	std::string last_name;*/

	// works
	std::string first_name;
	std::string last_name;
	std::string email;

public:
	Employee(const char* firstname, const char* lastname);
	std::string GetEmail();
	std::string GetFirstName();
	std::string GetLastName();
};


