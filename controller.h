#ifndef __CONTROLLER_H
#define __CONTROLLER_H

#include <vector>
#include <iostream>
#include <climits>
#include <cfloat>
#include <algorithm>
#include <memory>
#include <regex>
#include <string>
#include <sstream>
#include "cli_view.h"
#include "stylist.h"

class Controller {

	public:
		Controller();
		int main_menu();
			void login();
			void register_stylist();
		void cli();
			void appointments_menu();
				void add_appointment();
				void cancel_appointment();
				void reschedule_appointment();
			void clients_menu();
				void add_client();
				void remove_client();
			void appointment_books_menu();
				void change_current_book();
				void delete_appointment_book();


		int num_stylists();		

	protected:
		int get_int(std::string prompt, int min = INT_MIN, int max = INT_MAX);
		std::shared_ptr<Date> date_to_int(std::string date, std::string time);
		bool dateValidation(std::string date);
		bool timeValidation(std::string time);

	private:
		Cli_View _cli_view;
		std::vector<std::shared_ptr<Stylist>> _stylists;
		std::shared_ptr<Stylist> _current_stylist;


};


#endif