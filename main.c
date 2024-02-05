// This is the main file.

#include "functions.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	char *username = malloc(15 * sizeof(char)); // Allocate memory for username

	strcpy(username, login_register()); // Store the username for other functions
	
	int opt;
	printf("\n1 : Check your current bookings\n");
	printf("2 : Manage your bookings\n");
	scanf("%d", &opt);

	while (opt != 1 && opt != 2)
	{
		printf("\nPlease enter a valid choice : ");
		scanf("%d", &opt);
	}

	switch (opt)
	{
		case 1 :
			display_bookings(username);
			break;

		case 2 :
			manageBooking(username);
			break;
	}
}
