#ifndef __APPOINTMENT_H
#define __APPOINTMENT_H

#include "client.h"
#include "date.h"
#include <string>
#include <iostream>
#include <iomanip>
#include <memory>
#include <ctime>
#include <chrono>

class Appointment {
	
	public:
		// Appointment(Client& client, std::shared_ptr<Date> date, std::string description);
		Appointment(Client& client, struct std::tm time, std::string description);
		//Date& date() const;
		int month() const;
		int day() const;
		int year() const;
		struct std::tm* time();
		//void reschedule_appointment(std::shared_ptr<Date> date, std::string description);
		void reschedule_appointment(std::string description);
		std::string description() const;
		Client& client() const;
		std::string client_name() const;
		bool operator<(Appointment& rhs);
		//std::shared_ptr<Date> _date;


	private:
		struct std::tm _time;
		std::string _description;
		Client& _client;



};
std::ostream& operator<<(std::ostream& ost, Appointment& appointment);





#endif