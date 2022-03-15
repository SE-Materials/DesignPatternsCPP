#include "Employee.h"



Employee::Employee(const char* firstname, const char* lastname) :
	first_name(firstname),
	last_name(lastname),
	email(first_name + "." + last_name + "@class.com")
{
}

std::string Employee::GetEmail()
{
	return email;
}

std::string Employee::GetFirstName()
{
	return first_name;
}

std::string Employee::GetLastName()
{
	return last_name;
}


