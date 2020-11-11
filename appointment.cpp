#include "appointment.h"

// Appointment::Appointment(Client& client, std::shared_ptr<Date> date, std::string description) 
// 	: _client{client}, _date{date}, _description{description} { }

Appointment::Appointment(Client& client, struct std::tm time, std::string description)
	: _client{client}, _time{time}, _description{description} { }

// void Appointment::reschedule_appointment(std::shared_ptr<Date> date, std::string description) {
// 	//_date = date;
// 	_description = description;
// 	std::cout << "Appointment for " << client_name() << "rescheduled to: " << *date << description << std::endl;
// }

void Appointment::reschedule_appointment(std::string description) {
	//_date = date;
	_description = description;
	//std::cout << "Appointment for " << client_name() << "rescheduled to: " << *date << description << std::endl;
}

// Date& Appointment::date() const {
// 	return *_date;
// }

// int Appointment::month() const {
// 	return _date->month();
// }

// int Appointment::day() const {
// 	return _date->day();
// }

// int Appointment::year() const {
// 	return _date->year();
// }

struct std::tm* Appointment::time() {
	return &_time;
}

std::string Appointment::description() const {
	return _description;
}

Client& Appointment::client() const {
	return _client;
}

std::string Appointment::client_name() const {
	return _client.name();
}

bool Appointment::operator<(Appointment& rhs) {
	time_t left, right;
	left = mktime(this->time());
	right = mktime(rhs.time());

	if(left < right) {
		return true;
	}
	else{
		return false;
	}
}

std::ostream& operator<<(std::ostream& ost, Appointment& appointment) {
	ost << std::setw(20) << std::left << appointment.client_name();
	ost << std::put_time(appointment.time(), "%a %D %I:%M %p%t") << appointment.description() + "\n";
	return ost;
}

