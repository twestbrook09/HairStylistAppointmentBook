#ifndef __APPOINTMENT_BOOK_H
#define __APPOINTMENT_BOOK_H

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include "appointment.h"

class Appointment_Book {

	public:
		Appointment_Book();
		Appointment_Book(int year);
		int year();
		void add_appointment(Client& client, struct std::tm time, std::string description);
		void list_appointments();
		int num_appointments();
		void cancel_appointment(int index);
		// void reschedule_appointment(int index, std::shared_ptr<Date> date, std::string description);
		void reschedule_appointment(int index, std::string description);
		int remove_client_appointments(Client& client, int deleted);
		bool operator==(Appointment_Book& rhs);

	private:
		int _year;
		std::vector<std::shared_ptr<Appointment>> _appointments;

};
std::ostream& operator<<(std::ostream& ost, Appointment_Book& appointment_book);
bool lessThan(std::shared_ptr<Appointment> lhs, std::shared_ptr<Appointment> rhs);




#endif