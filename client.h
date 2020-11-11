#ifndef __CLIENT_H
#define __CLIENT_H

#include <string>
#include <iostream>
#include <iomanip>

class Client {

	public:
		Client(std::string name, std::string phoneNum);
		std::string name();
		std::string phone();
		bool operator==(Client& rhs);

	private:
		std::string _name;
		std::string _phone;
};
std::ostream& operator<<(std::ostream& ost, Client& client);




#endif
