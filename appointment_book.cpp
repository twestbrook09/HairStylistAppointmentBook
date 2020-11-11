#include "appointment_book.h"

Appointment_Book::Appointment_Book(int year) : _year{year} { }
Appointment_Book::Appointment_Book() : _year{0} { 
	int year = 0;
	std::cout << "Insert year for appointment book: " << std::endl;
	std::cin >> year;
	if(year != 0) {
		_year = year;
	}
}

void Appointment_Book::add_appointment(Client& client, struct std::tm time, std::string description) {
	std::shared_ptr<Appointment> appointment (new Appointment(client, time, description));
	_appointments.push_back(appointment);
	std::cout << "Appointment Added!" << std::endl;
	std::sort(_appointments.begin(), _appointments.end(), lessThan);

}

void Appointment_Book::list_appointments() {
	if(_appointments.size()) {
		//create columns of table
		std::cout << std::setw(23) << "Client Name";
		std::cout << std::setw(25) << "Date/Time";
		std::cout << "Description" << std::endl;
		for(int i = 0; i < _appointments.size(); ++i) {
			if(_appointments[i] != NULL) {
				std::cout << (i+1) << ": " << *(_appointments[i]);
			}
		}
	}
	else {
		std::cout << "There are no appointments set up for " << _year << std::endl;
	}
}

int Appointment_Book::num_appointments() {
	return _appointments.size();
}

void Appointment_Book::cancel_appointment(int index) {
	std::shared_ptr<Appointment> appointment = _appointments[index];
	auto it = std::find(_appointments.begin(), _appointments.end(), appointment);
	if(it != _appointments.end()) { _appointments.erase(it); }
}

// void Appointment_Book::reschedule_appointment(int index, std::shared_ptr<Date> date, std::string description) {
// 	_appointments[index]->reschedule_appointment(date, description);
// }

void Appointment_Book::reschedule_appointment(int index, std::string description) {
	_appointments[index]->reschedule_appointment(description);
}

int Appointment_Book::remove_client_appointments(Client& client, int deleted) {
	for(auto it = _appointments.begin(); it != _appointments.end();) {
		if((*it)->client() == client) {
			it = _appointments.erase(it);
			deleted++;
		}
		else {
			++it;
		}
	}
	return deleted;
}

int Appointment_Book::year() {
	return _year;
}

std::ostream& operator<<(std::ostream& ost, Appointment_Book& appointment_book) {
	ost << appointment_book.year() << "\n";
	return ost;
}

bool Appointment_Book::operator==(Appointment_Book& rhs){
	if(this->year() == rhs.year()) {
		return true;
	}
	else {
		return false;
	}
}

bool lessThan(std::shared_ptr<Appointment> lhs, std::shared_ptr<Appointment> rhs) {
	return (*lhs) < (*rhs);
}