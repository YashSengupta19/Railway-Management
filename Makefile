railway_system : main.o CheckStatus.o booking.o ticket.o login_register.o
	gcc main.o CheckStatus.o booking.o ticket.o login_register.o -o railway_system

main.o : main.c
	gcc -c main.c

CheckStatus.o : CheckStatus.c
	gcc -c CheckStatus.c

booking.o : booking.c
	gcc -c booking.c

ticket.o : ticket.c
	gcc -c ticket.c

login_register.o : login_register.c
	gcc -c login_register.c
