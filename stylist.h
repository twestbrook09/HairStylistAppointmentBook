#ifndef __STYLIST_H
#define __STYLIST_H

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <memory>
#include "client.h"
#include "appointment_book.h"

class Stylist {

	public:
		Stylist(std::string name, std::string password);
		std::string name() const;
		std::string password() const;
		void add_client(std::string name, std::string phone);
		void list_clients();
		int num_clients() const;
		void remove_client(int index);
		void add_appointment_book();
		void list_books();
		int num_books();
		void change_appointment_book(int index);
		void delete_appointment_book(int index);
		void add_appointment(int index, struct std::tm time, std::string description);
		void list_appointments();
		void cancel_appointment(int index);
		//void reschedule_appointment(int index, std::shared_ptr<Date> date, std::string description);
		int num_appointments();
		Appointment_Book& current_book();
		int get_book_year();

	private:
		std::string _name;
		std::string _password;
		std::vector<std::shared_ptr<Client>> _clientele;
		std::vector<std::shared_ptr<Appointment_Book>> _books;
		std::shared_ptr<Appointment_Book> _current_book;
};
std::ostream& operator<<(std::ostream& ost, const Stylist& stylist);




#endif