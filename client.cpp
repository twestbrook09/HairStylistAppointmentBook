#include "client.h"

Client::Client(std::string name, std::string phoneNum) : _name{name}, _phone{phoneNum} { }

std::string Client::name() {
	return _name;
}

std::string Client::phone() {
	return _phone;
}

std::ostream& operator<<(std::ostream& ost, Client& client) {
	ost << std::setw(20) << std::left << client.name();
	ost << std::setw(client.phone().length()) << client.phone() + "\n";
	return ost;
}

bool Client::operator==(Client& rhs) {
	if(this->name() == rhs.name() && this->phone() == rhs.phone()) {
		return true;
	}
	else {
		return false;
	}
}
