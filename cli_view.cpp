#include "cli_view.h"

Cli_View::Cli_View() { }

void Cli_View::splash() {
	std::string clear{"\033c"};
	std::cout << clear << R"(

            =============================
              LAVISH HAIR & LASH STUDIO
            =============================
)";
}

void Cli_View::main_menu() {
	std::cout << R"(
       1: Stylist Login
       2: Register new Stylist
       0: Exit

)";
}

void Cli_View::stylist_menu() {
	std::cout << R"(
       1: Appointments
       2: Clients
       3: Appointment Books
       0: Exit

)";
}

void Cli_View::appointments_main_menu() {

	std::cout << R"(
=================
Appointments Menu
=================

1: Add Appointment
2: List Appointments
3: Remove Appointment
4: Reschedule Appointment
0: Back

)";
}

void Cli_View::clients_main_menu() {

	std::cout << R"(
============
Clients Menu
============

1: Add Client
2: List Clients
3: Remove Client
0: Back

)";

}

void Cli_View::appointment_books_main_menu() {

	std::cout << R"(
======================
Appointment Books Menu
======================

1: Add Appointment Book
2: List Appointment Books
3: Change Appointment Book
4: Delete Appointment Book
0: Back

)";

}

void Cli_View::new_appointment_book() {
	splash();
	std::cout << R"(

====================
New Appointment Book
====================

)";
}

void Cli_View::list_appointment_books() {
	splash();
	std::cout << R"(
=========================
Appointment Books by Year
=========================
)";
}

void Cli_View::add_appointment() {
	splash();
	std::cout << R"(
=================
 Add Appointment
=================
)";
}

void Cli_View::list_appointments() {
	splash();
	std::cout << R"(
=====================
Upcoming Appointments
=====================
)";
}

void Cli_View::add_client() {

	splash();
	std::cout << R"(
==========
Add Client
==========
)";

}

void Cli_View::clients() {
	splash();
	std::cout << R"(
==============
Clientele List
==============
)";
}

void Cli_View::remove_client() {

	splash();
	std::cout << R"(
=============
Remove Client
=============
)";
}