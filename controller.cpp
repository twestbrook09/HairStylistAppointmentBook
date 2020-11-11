#include "controller.h"

Controller::Controller() { }

/////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////COMMAND LINE INTERFACE////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////



////////
//Menus

	//Main Menu//
//////////////////////
int Controller::main_menu() {
	int cmd = -1;
	_cli_view.splash();
	while(cmd != 0) {
		_cli_view.main_menu();
		cmd = get_int("Command? ", 0, 2);
		_cli_view.splash();
		if(std::cin) {
			switch(cmd) {
				case 1: login(); break;
				case 2: register_stylist(); break;
				case 0: std::cout << "Bye!" << std::endl; break;
				default: std::cerr << "Invalid command\n";
			}
		}

		else {
			std::cerr << "\n";
			exit(0);
		}
	}
}

	//Stylist Menu//
//////////////////////
void Controller::cli() {
	int cmd = -1;
	_cli_view.splash();
	while(cmd != 0) {
		std::cout << "Current stylist: " << *_current_stylist;
		if(_current_stylist->num_books()) 
			std::cout << "Current book: " << _current_stylist->current_book();
		else
			std::cout << "Current book: N/A\n";
		_cli_view.stylist_menu();
		cmd = get_int("Command? ", 0, 3);
		_cli_view.splash();
		if(std::cin) {
			switch(cmd) {
				case 1: appointments_menu(); break;
				case 2: clients_menu(); break;
				case 3: appointment_books_menu(); break;
				case 0: std::cout << "Bye, " << _current_stylist->name() << "!" << std::endl; break;
				default: std::cerr << "Invalid command\n";
			}
		}

		else {
			std::cerr << "\n";
			exit(0);
		}
	}
}

 //Appointments Menu//
//////////////////////
void Controller::appointments_menu() {
	int cmd = -1;
	while(cmd != 0) {
		_cli_view.appointments_main_menu();
		cmd = get_int("Command? ");
		if(std::cin) {
			switch(cmd) {
				case 1: _cli_view.add_appointment(); add_appointment(); break;
				case 2: _cli_view.list_appointments(); _current_stylist->list_appointments(); break;
				case 3: _cli_view.list_appointments(); cancel_appointment(); break; //cancel appointment
				case 4: _cli_view.list_appointments(); reschedule_appointment(); break; //reschedule appointment
				case 0: _cli_view.splash(); break;
				default: std::cerr << "Invalid command\n";
			}
		}

		else {
			std::cerr << "\n";
			exit(0);
		}
	}
}

	//Client Menu//
//////////////////////
void Controller::clients_menu() {
	int cmd = -1;
	while(cmd != 0) {
		_cli_view.clients_main_menu();
		cmd = get_int("Command? ");
		if(std::cin) {
			switch(cmd) {
				case 1: add_client(); break;
				case 2: _cli_view.clients(); _current_stylist->list_clients(); break;
				case 3: remove_client(); break;
				case 0: _cli_view.splash(); break;
				default: std::cerr << "Invalid command\n";
			}
		}

		else {
			std::cerr << "\n";
			exit(0);
		}
	}
}

//Appointment Book Menu//
////////////////////////
void Controller::appointment_books_menu() {
	int cmd = -1;
	while(cmd != 0) {
		_cli_view.appointment_books_main_menu();
		cmd = get_int("Command? ");
		if(std::cin) {
			switch(cmd) {
				case 1: _cli_view.new_appointment_book(); _current_stylist->add_appointment_book(); break;
				case 2: _cli_view.list_appointment_books(); _current_stylist->list_books(); break;
				case 3: _cli_view.list_appointment_books(); change_current_book(); break;
				case 4: _cli_view.list_appointment_books(); delete_appointment_book(); break;
				case 0: _cli_view.splash(); break;
				default: std::cerr << "Invalid command\n";
			}
		}

		else {
			std::cerr << "\n";
			exit(0);
		}
	}

}


/////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////COMMANDS//////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////


////////////////
//Login/Register

void Controller::login() {
	if(num_stylists()) {
		std::cout << "Which stylist would you like to login as?\n\n";
		for(int i = 0; i < _stylists.size(); ++i) {
			std::cout << (i+1) << ": " << *(_stylists[i]);
		}
		std::cout << "\n";
	}
	else {
		_cli_view.splash();
		std::cout << "You must register a stylist first!" << std::endl;
		return;
	}

	int response = get_int("Cmd? ", 1, _stylists.size());
	if(std::cin) {
		std::cout << "Please enter password: ";
		std::string password;
		std::getline(std::cin, password);
		if(password == _stylists[response-1]->password()) {
			_current_stylist = _stylists[response-1];
			cli();
		}
		else {
			_cli_view.splash();
			std::cout << "Incorrect password.";
			return;
		}
	}
}

void Controller::register_stylist() {
	std::string name;
	std::string password;
	_cli_view.splash();
	std::cout << "What is the new stylist's name?\n";
	std::getline(std::cin, name);
	if(name.size()) {
		_cli_view.splash();
		std::cout << "Enter new password: ";
		std::getline(std::cin, password);
		if(password.size()) {
			std::shared_ptr<Stylist> stylist (new Stylist(name, password));
			stylist->add_appointment_book();
			stylist->change_appointment_book(0);
			_stylists.push_back(stylist);
			_cli_view.splash();
			std::cout << "Stylist added!\n";
			return;
		}
		else {
			std::cout << "You must enter a password!";
		}
	}
	else {
		std::cout << "Exiting...";
		return;
	}
	
}

///////////////
//Appointments
void Controller::add_appointment() {
	if(_current_stylist->num_clients()) {
		int year, month, day;
		struct std::tm time = std::tm();
		std::string description;
		_current_stylist->list_clients();
		int cmd = get_int("Choose client: ", 1, _current_stylist->num_clients());
		while(true) {
			//get date from user
			std::cout << "Enter Appointment details:\n";
			month = get_int("\tMonth: ", 1, 12);
			if(month < 1) {
				std::cout << "Add appointment cancelled." << std::endl;
				break;
			}
			day = get_int("\tDay: ", 1, 31);
			if(day < 1) {
				std::cout << "Add appointment cancelled." << std::endl;
				break;
			}
			//get time from user
			std::cout << "Enter time of appointment (24H format): ";
			bool inputFail = false;
			std::cin >> std::get_time(&time, "%R");
			int count = 0;
			while(std::cin.fail()) {
				count++;
				if(count > 3) {
					std::cout << "Invalid time format. Add appointment cancelled." << std::endl;
					inputFail = true;
					break;
				}
				std::cin.clear();
				std::cin.ignore(65535, '\n');
				std::cout << "Invalid time format. Enter time as HH:MM (24H format): ";
				std::cin >> std::get_time(&time, "%R");
			}
			if(inputFail) {
				break;
			}
			std::cin.clear();
			std::cin.ignore(65535, '\n');
			//get description from user
			std::cout << "Enter description of appointment ('exit' to exit): ";
			std::getline(std::cin, description);
			if(description == "exit") {
				break;
			}
			else if(description.size()) {
				time.tm_year = _current_stylist->get_book_year() - 1900;
				time.tm_mon = month - 1;
				time.tm_mday = day;
				mktime(&time);
				_current_stylist->add_appointment(cmd-1, time, description);
				break;
			}
			else {
				time.tm_year = _current_stylist->get_book_year() - 1900;
				time.tm_mon = month - 1;
				time.tm_mday = day;
				mktime(&time);
				_current_stylist->add_appointment(cmd-1, time, "N/A");
				break;
			}
			
		}
	}
}

void Controller::cancel_appointment() {
	if(_current_stylist->num_appointments()) {
		_current_stylist->list_appointments();
		int index;
		index = get_int("\nWhich appointment would you like to cancel?\n", 1, _current_stylist->num_appointments());
		_cli_view.splash();
		_current_stylist->cancel_appointment(index-1);
		std::cout << "Appointment Cancelled!";
	}
	else {
		_cli_view.splash();
		std::cout << "You do not have any appointments set up yet!" << std::endl;
	}
}

void Controller::reschedule_appointment() {
	if(_current_stylist->num_appointments()) {
		_current_stylist->list_appointments();
		int index;
		std::string date, time, description;
		index = get_int("\nWhich appointment would you like to reschedule?\n", 1, _current_stylist->num_appointments());
		_cli_view.splash();
		while(true) {
			//get date from user
			std::cout << "Enter new date of appointment ('exit' to exit): ";
			bool dateValidated = false;
			while(!dateValidated) {
				std::getline(std::cin, date);
				if(date == "exit") {
					break;
				}
				else if(date.size()) {
					dateValidated = dateValidation(date);
				}
			}
			if(date == "exit") {
				std::cout << "Reschedule cancelled." << std::endl;
				break;
			}

			std::cout << "Enter new time of appointment ('exit' to exit): ";
			bool timeValidated = false;
			while(!timeValidated) {
				std::getline(std::cin, time);
				if(time == "exit") {
					break;
				}
				else if(time.size()) {
					timeValidated = timeValidation(time);
				}
			}
			if(time == "exit") {
				std::cout << "Reschedule cancelled." << std::endl;
				break;
			}

			std::cout << "Enter description of appointment ('exit' to exit): ";
			std::getline(std::cin, description);
			if(description == "exit") {
				std::cout << "Reschedule cancelled." << std::endl;
				break;
			}
			else if(description.size()) {
				std::shared_ptr<Date> d = date_to_int(date, time);
				//_current_stylist->reschedule_appointment(index-1, d, description);
				std::cout << "Appointment Rescheduled!" << std::endl;
				break;
			}
			else {
				std::shared_ptr<Date> d = date_to_int(date, time);
				//_current_stylist->reschedule_appointment(index-1, d, "N/A");
				std::cout << "Appointment Rescheduled!" << std::endl;
				break;
			}
		}
		
	}
}


//////////
//Clients

void Controller::add_client() {
	std::string name;
	std::string phone_number;
	_cli_view.add_client();
	while(true) {
		std::cout << "Enter name ('exit' to exit): ";
		std::getline(std::cin, name);
		if(name.size()) {
			if(name == "exit") {
				_cli_view.splash();
				break;
			}
			std::cout << "Enter phone number ('exit' to exit): ";
			std::getline(std::cin, phone_number);
			if(phone_number.size()) {
				if(phone_number == "exit") {
					_cli_view.splash();
					break;
				}
				_current_stylist->add_client(name, phone_number);
				std::cout << "Client added!\n\n" << "Would you like to add another?" << std::endl;
				std::cout << "1 - Yes\n2 - No\n";
				int cmd = get_int("Command? ", 1, 2);
				if(cmd == 1) {
					continue;
				}
				else if(cmd == 2) {
					_cli_view.splash();
					break;
				}
				else {
					std::cout << "Invalid command, going back to menu.";
					_cli_view.splash();
					break;
				}
			}
			else {
				continue;
			}
		}
		else {
			continue;
		}
	}
	
}

//bug when removing client who has an appointment set!!
void Controller::remove_client() {

	if(_current_stylist->num_clients()) {
		_cli_view.remove_client();
		_current_stylist->list_clients();

		int index;
		index = get_int("\nWhich client would you like to remove?\n", 1, _current_stylist->num_clients());
		_cli_view.splash();
		_current_stylist->remove_client(index-1);
		std::cout << "Client removed!";

	}
	else {
		_cli_view.splash();
		std::cout << "You must add clients first!" << std::endl;
	}

}

////////////////////
//Appointment Books

void Controller::change_current_book() {
	if(_current_stylist->num_books()) {
		int index;
		std::cout << "Which book would you like to choose?" << std::endl;
		_current_stylist->list_books();
		index = get_int("Command? ", 1, _current_stylist->num_books());
		_current_stylist->change_appointment_book(index-1);
	}
}

void Controller::delete_appointment_book() {
	if(_current_stylist->num_books() > 1) {
		int index;
		std::cout << "Which book would you like to delete?" << std::endl;
		_current_stylist->list_books();
		index = get_int("Command? ", 1, _current_stylist->num_books());
		_current_stylist->delete_appointment_book(index-1);
	}
	else {
		_cli_view.splash();
		std::cout << "You only have 1 appointment book!" << std::endl;
	}
}

int Controller::num_stylists() {
	return _stylists.size();
}

/////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////TOOLS/////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////
//Data Validation

int Controller::get_int(std::string prompt, int min, int max) {
  int i;
  std::string s;
  while(true) {
    std::cout << prompt;

    // Successfully entered an integer
    if(std::cin >> i) {
        std::cin.ignore(65535, '\n');
        if (min <= i && i <= max) return i;

        // Integer was out of range
        std::cerr << "Must be between " << min << " and " << max << ".\n";
        continue;
    }

    // End of file - no more input possible
    if (std::cin.eof()) exit(0);

    // Invalid input - clear the error and buffer and display error message
    std::cin.clear();
    std::cin.ignore(65535, '\n');
    std::cerr << "That was not an integer.\n";
  }
}

bool Controller::dateValidation(std::string date) {
	std::regex re("^((0*[1-9])|(1[0-2]))[/.-]((0[1-9])|(1[0-9])|(2[0-9])|(3[0-1]))[/.-](2[0-1][0-9][0-9])$",
				std::regex::extended);
	if(std::regex_match(date, re)) {
		return true;
	}
	else {
		std::cout << "Invalid date format. Must be MM/DD/YYYY: ";
		return false;
	}
}

bool Controller::timeValidation(std::string time) {
	std::regex re("^((0*[1-9])|(1[0-2])):[0-5][0-9][ \t\r\f\v]((am)|(pm))$", std::regex::icase);
	if(std::regex_match(time, re)) {
		return true;
	}
	else {
		std::cout << "Invalid time format. Must be HH:MM AM/PM: ";
		return false;
	}
}

///////////////
//Parsing Data

std::shared_ptr<Date> Controller::date_to_int(std::string date, std::string time) {
	std::string delimiter;
	int month, day, year, hour, minute;
	std::string AmPm;
	int count = 0;
	size_t pos = 0;
	std::string token;
	
	if(date.find("/") != std::string::npos) {
		delimiter = "/";
	}
	else if(date.find(".") != std::string::npos) {
		delimiter = ".";
	}
	else {
		delimiter = "-";
	}
	//parse date
	while((pos = date.find(delimiter)) != std::string::npos) {
		token = date.substr(0, pos);
		if(count == 0) {
			month = stoi(token);
			count++;
		}
		else if(count == 1) {
			day = stoi(token);
			count++;
		}
		date.erase(0, pos + delimiter.length());
	}
	year = stoi(date);

	//parse time
	count = 0;
	if((pos = time.find(":")) != std::string::npos) {
		token = time.substr(0, pos);
		hour = stoi(token);
	}
	time.erase(0, pos + delimiter.length());
	
	if((pos = time.find(" ")) != std::string::npos) {
		token = time.substr(0, pos);
		minute = stoi(token);
	}
	time.erase(0, pos + delimiter.length());
	AmPm = time;
	std::cout << hour << " " << minute << " " << AmPm << std::endl;

	std::shared_ptr<Date> d (new Date(month, day, year, hour, minute, AmPm));
	return d;
}