// CONTRIBUTION : Kandarp 

#include "functions.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void display_bookings(char username[]);
void check_status();

char *train_list[10]; // To store all the different train ids, which are booked by the user
char *train_names[10]; // To store all the different train names
	
char *source[10]; // To store the source stations of the trains	
char *destination[10]; // To store the destination stations of the trains
char *distance[10]; // To store the total distance of every journey
	
char *dep_time[10]; // To store the departure times of the trains
char *arr_time[10]; // To store the arrival times of the trains
char *dep_dates[10]; // To store the departure dates of the trains
char *arr_dates[10]; // To store the arrival dates of the trains

char *food[10]; // To know whether food is pre-ordered or not
char price[10][5]; // To store the price of each journey
char *booking_dates[10]; // To store the date when the user booked the ticket

char person_name[10][5][15]; // To store the names of people
char person_age[10][5][3]; // To store the ages of people
char gender[10][5][1]; // To store the genders of people
int num_of_passengers[10]; // Total number of passengers in one booking
int in_dep_hour[10]; // To store the initial departure hour of trains

// Displays all the bookings that are made by the passenger
void display_bookings(char username[])
{
	FILE *bookings = fopen("Passenger_Bookings.txt", "r"); // Open Passenger_Bookings for reading data


	long opt; 
	printf("Enter 1 to view your bookings. ");
	scanf("%ld", &opt);

	printf("\n");

	int bookingsExist = 0; // Whether user has any bookings or not

	int i = 0; // Iteration variable
	int j; // Iteration variable
	int count = 0; // To count the total number of passengers in one booking
	
	char word[50]; // To read data from file
	fscanf(bookings, "%s", word); 

	// Read from file till end of file is not reached
	while (!feof(bookings))
	{
		// If username is found
		if (!strcmp(word, username))
		{
			fscanf(bookings, "%*s");
			fscanf(bookings, "%s", word);

			// Read data till end of booking is reached
			while (strcmp(word, "----"))
			{
				bookingsExist = 1; // Atleast one booking has been found
				
				train_list[i] = malloc(10 * sizeof(char));
				strcpy(train_list[i], word); // The train number
				printf("%d. %s ", i + 1, train_list[i]); // Print the train id

				train_names[i] = malloc(20 * sizeof(char));
				source[i] = malloc(15 * sizeof(char));
				destination[i] = malloc(15 * sizeof(char));
				distance[i] = malloc(10 * sizeof(char));

				// Read the details
				fscanf(bookings, "%s %s %s %s", train_names[i], source[i], destination[i], distance[i]);
				fscanf(bookings, "%2d", &in_dep_hour[i]); // Store the departure hour

				printf("%s %s %s\n", train_names[i], source[i], destination[i]);

				fseek(bookings, -3, SEEK_CUR);

				dep_time[i] = malloc(5 * sizeof(char));
				arr_time[i] = malloc(5 * sizeof(char));
				dep_dates[i] = malloc(10 * sizeof(char));
				arr_dates[i] = malloc(10 * sizeof(char));
				food[i] = malloc(3 * sizeof(char));

				// Read the details
				fscanf(bookings, "%s %s %s %s %s %s", dep_time[i], arr_time[i], dep_dates[i], arr_dates[i], price[i], food[i]);

				fscanf(bookings, "%[^\n]", word); // Read the booking date

				booking_dates[i] = malloc(20 * sizeof(char));

				strcpy(booking_dates[i], word); // Store the booking date

				fscanf(bookings, "%*s"); // Discard the character '-'

				fscanf(bookings, "%s", word);
				
				// Read and store the list of people
				while (1)
				{
					if (!strcmp(word, "-"))
						break;		

					fseek(bookings, -strlen(word), SEEK_CUR); // Move cursor to beginning of line

					// Read the passenger details
					fscanf(bookings, "%s %s %c", person_name[i][count], person_age[i][count], &gender[i][count][0]);

					++count;
					fscanf(bookings, "%s", word);
				}

				num_of_passengers[i] = count; // Total number of passengers in the booking

				++i; // For next booking
				count = 0; // Reset count
				fscanf(bookings, "%s", word);
			}
		}

		fscanf(bookings, "%s", word); // Read from file
	}

	fclose(bookings); // Close the file

	// If user has made no bookings till now
	if (!bookingsExist)
	{
		printf("You have no trains booked currently.\n");
		return;
	}

	// For user to check status of any one train
	printf("\nEnter 2 to view a particular booking : ");
	scanf("%ld", &opt);

	if (opt == 2)
		check_status();
}

// Shows the status of train, through which the user may be travelling right now
void check_status()
{
	int i; // For user to choose train
	printf("\nEnter the train number to view booking : "); // Input train number 
	scanf("%d", &i);

	i = i - 1;

	printf("\nTotal number of people : %d\n\n", num_of_passengers[i]);

	int j; // Iteration variable

	for (j = 0; j < num_of_passengers[i]; ++j)
		printf("%s %s %c\n", person_name[i][j], person_age[i][j], gender[i][j][0]);

	int opt;
	printf("\n1 : Check current status of train ");
	printf("\n2 : View Ticket \n");
	scanf("%d", &opt);

	if (opt == 1)
	{
		int dep_date; // Departure date
		char *dep_date_str = malloc(2 * sizeof(char));
	
		// Take first two digits of date
		for (j = 0; j < 2; ++j)
			dep_date_str[j] = dep_dates[i][j];

		dep_date = atoi(dep_date_str);

		int current_day; // Today's date
		printf("\nEnter today's date : "); // Taking input from user
		scanf("%2d", &current_day);

		int days_remaining = dep_date - current_day; // Number of days remaining for departure of train

		printf("\n");

		// Print number of days, if train has not yet departed
		if (days_remaining > 0)
			printf("Days Remaining : %d\n", days_remaining);

		else
		{
			// Open required train file for reading
			char *file_name = malloc(15 * sizeof(char));
			strcpy(file_name, train_list[i]);
			strcat(file_name, ".txt");

			FILE *train_file = fopen(file_name, "r");

			char word[50]; // To read from file
			fscanf(train_file, "%[^\n] %*s", word);
			printf(" You are currently travelling by %s.\n", word); // Print name of train

			int flag = 0; // Whether status has been pprinted or not
			int h, m; // Current hour and minute

			// Take input of time from user
			printf("Please enter time in hh:mm format : ");
			scanf("%2d %*c %2d", &h, &m);

			// Read until end of file is not reached
			while (!feof(train_file))
			{
				char *current_station = malloc(20 * sizeof(char)); // Station from which user has departed
				char *next_station = malloc(20 * sizeof(char)); // Station where the user is proceeding
				int dep_hour; // Departure hour for current station
				int dep_min; // Departure minute for current station
				int arr_hour; // Arrival hour for next station
				int arr_min; // Arrival minute for next station
				int date; // Date of travelling of train

				// Read data from train file
				fscanf(train_file, "%s %s %2d %*c%2d %2d %*c%2d %*s %2d%*6c", current_station, next_station, &dep_hour, &dep_min, &arr_hour, &arr_min, &date);

				// Reach till current date
				if (date != current_day)
					continue;

				// Modify the Arrival time
				if (arr_min == 0)
				{
					arr_min = 60;
					arr_hour = arr_hour - 1;
				}

				// If train has not yet departed
				if (h < in_dep_hour[i] && date == dep_date)
				{
					printf("\n%d hours remaining for departure of train.\n", in_dep_hour[i] - h);
					flag = 1;
					break;
				}
			
				// If train has not yet departed
				if (h == dep_hour && m < dep_min)
				{
					//Print the remaining time for departure
					printf("\n%d minutes remaining for departure of train.\n", dep_min - m);

					flag = 1;
					break;
				}

				// If train is currently travelling between two stations
				if (h >= dep_hour && h <= arr_hour) 
				{
					if (!(h == arr_hour && m > arr_min))
					{
						// Print the details
						printf("\nYou have departed from %s, and are travelling towards %s.\n", current_station, next_station);
						flag = 1;
						break;
					}
				}

				/* For transition in day.
			   	Example : 23:00 to 02:00 */
				if (dep_hour >= 12 && arr_hour <= 12)
				{
					if (h >= dep_hour || h <= arr_hour && m <= arr_min)
					{
						// Print the details
						printf("\nYou have departed from %s, and are travelling towards %s.\n", current_station, next_station);
						flag = 1;
						break;
					}
				}
			}

			// If nothing is printed, then the user has reached destination
			if (!flag)
			{
				printf("\nYou have arrived at your destination.\n");
				printf("\nHope you had a memorable journey!\n");
			}
		}
	}

	// Print the ticket
	else if (opt == 2)
		print_ticket(i, destination[i], source[i], dep_time[i], dep_dates[i], arr_time[i], arr_dates[i], train_list[i], train_names[i], food[i], distance[i], booking_dates[i], num_of_passengers[i], person_name, person_age, gender, atoi(price[i]));

}
