#include "stylist.h"

Stylist::Stylist(std::string name, std::string password) : _name{name}, _password{password} { }

void Stylist::add_appointment(int index, struct std::tm time, std::string description) {
	_current_book->add_appointment(*_clientele[index], time, description);
}

void Stylist::list_appointments() {
	_current_book->list_appointments();
}

void Stylist::cancel_appointment(int index) {
	_current_book->cancel_appointment(index);
}

// void Stylist::reschedule_appointment(int index, std::shared_ptr<Date> date, std::string description) {
// 	_current_book->reschedule_appointment(index, date, description);
// }

int Stylist::num_appointments() {
	return _current_book->num_appointments();
}

void Stylist::add_client(std::string name, std::string phone) {
	std::shared_ptr<Client> client (new Client(name, phone));
	_clientele.push_back(client);
}

void Stylist::list_clients() {
	if(_clientele.size()) {
		for(int i = 0; i < _clientele.size(); ++i) {
			if(_clientele[i] != NULL) {
				std::cout << (i+1) << ": " << *(_clientele[i]);
			}
		}
	}
	else {
		std::cout << "You have no clients!" << std::endl;
	}
	
}

void Stylist::remove_client(int index) {
	int deleted = 0;
	for(int i = 0; i < _books.size(); ++i) {
		deleted += _books[i]->remove_client_appointments(*_clientele[index], deleted);
	}
	std::cout << deleted << " appointments deleted for " << _clientele[index]->name() << std::endl;

	std::shared_ptr<Client> client = _clientele[index];
	auto it = std::find(_clientele.begin(), _clientele.end(), client);
	if (it != _clientele.end()) { _clientele.erase(it); }
}

int Stylist::num_clients() const {
	return _clientele.size();
}

void Stylist::add_appointment_book() {
	std::shared_ptr<Appointment_Book> book (new Appointment_Book());
	_books.push_back(book);
}

void Stylist::list_books() {
	if(_books.size()) {
		for(int i = 0; i < _books.size(); ++i) {
			if(_books[i] != NULL) {
				std::cout << (i+1) << ": " << *(_books[i]);
			}
		}
	}
}

int Stylist::num_books() {
	return _books.size();
}

void Stylist::delete_appointment_book(int index) {
	int year = _books[index]->year();
	if(*_current_book == *_books[index]) {
		if(index == 0) {
			change_appointment_book(1);
		}
		else {
			change_appointment_book(index-1);
		}
	}	
	auto it = std::find(_books.begin(), _books.end(), _books[index]);
	if (it != _books.end()) { _books.erase(it); }
	std::cout << "Appointment book deleted: " << year;

}

void Stylist::change_appointment_book(int index) {
	_current_book = _books[index];
	std::cout << "Appointment book changed to: " << *(_books[(index)]);
}

Appointment_Book& Stylist::current_book() {
	return *_current_book;
}

int Stylist::get_book_year() {
	return _current_book->year();
}

std::string Stylist::name() const {
	return _name;
}

std::string Stylist::password() const {
	return _password;
}

std::ostream& operator<<(std::ostream& ost, const Stylist& stylist) {
	ost << stylist.name() + '\n';
	return ost;
}