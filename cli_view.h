#ifndef __CLI_VIEW_H
#define __CLI_VIEW_H
//#include "appointment_book.h"
#include <iostream>

class Cli_View {

	public:
		Cli_View();
		void splash();
		void main_menu();
		void stylist_menu();
		void clients();
		void new_appointment_book();
		void list_appointment_books();
		void add_appointment();
		void list_appointments();
		void appointments_main_menu();
		void clients_main_menu();
		void appointment_books_main_menu();
		void add_client();
		void remove_client();

};




#endif