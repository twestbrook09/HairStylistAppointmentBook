CXXFLAGS += --std=c++17
ifdef debug
	CXXFLAGS += -g
endif

all: appt_book_cli

appt_book_cli: main_cli.o controller.o client.o appointment.o appointment_book.o stylist.o cli_view.o date.o *.h
	$(CXX) $(CXXFLAGS) main_cli.o controller.o stylist.o appointment.o appointment_book.o client.o cli_view.o date.o -o appt_book_cli

main_cli.o: main_cli.cpp *.h
	$(CXX) $(CXXFLAGS) -c main_cli.cpp -o main_cli.o
controller.o: controller.cpp *.h
	$(CXX) $(CXXFLAGS) -c controller.cpp -o controller.o
client.o: client.cpp *.h
	$(CXX) $(CXXFLAGS) -c client.cpp -o client.o
appointment.o: appointment.cpp *.h
	$(CXX) $(CXXFLAGS) -c appointment.cpp -o appointment.o
stylist.o: stylist.cpp *.h
	$(CXX) $(CXXFLAGS) -c stylist.cpp -o stylist.o
appointment_book.o: appointment_book.cpp *.h
	$(CXX) $(CXXFLAGS) -c appointment_book.cpp -o appointment_book.o
cli_view.o: cli_view.cpp *.h
	$(CXX) $(CXXFLAGS) -c cli_view.cpp -o cli_view.o
date.o: date.cpp *.h
	$(CXX) $(CXXFLAGS) -c date.cpp -o date.o

clean:
	rm -f *.o *.gch a.out appt_book_cli
