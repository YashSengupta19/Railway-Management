// CONTRIBUTION : Yash, Kandarp. Train files are made by Aditya.

#include "functions.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int price1=0; // PRICE OF TICKET (PER PERSON)
int p1=0; // USED TO TRAVERSE arr1[][] ARRAY

void manageBooking(char username[]);
void new_booking(char username[]);
void update_booking(char username[]);
int handleBookingsFile(int mode, long train_id, char *source, char *destination, char *name, char *username);

// To connect all the functions regarding booking
void manageBooking(char username[])
{
	printf("\nPlease enter a valid choice : \n");
	printf("1 : Book new ticket\n");
	printf("2 : Update existing ticket\n");

	int opt;
	scanf("%d", &opt);

	// Call teh appropriate function
	switch (opt)
	{
		case 1 :
			new_booking(username);
			break;

		case 2 :
			update_booking(username);
			break;
	}
}

// To book a new ticket
void new_booking(char username[])
{
    char *start=malloc(20*sizeof(char)); // USED TO STORE THE DEPARTING STATION
    char *destination=malloc(20*sizeof(char));// USED TO STORE ARRIVAL STATION
    char *arr[]={"12283.txt","12657.txt","12834.txt","12906.txt","20608.txt","22461.txt","22692.txt"};// FILE STORING ALL THE TRAIN_SCHEDULE FILES
    char *arr1[30][11]; // ARRAY TO STORE THE TRAIN DETAILS OF ALL POSSIBLE TRAINS
    printf("Enter Start: ");
    scanf("%s",start);
    printf("Enter Destination: ");
    scanf("%s",destination);

    int start_check;
    int destination_check;
    int flag = 0; // TO CHECK WHETHER ANY TRAIN EXISTS OR NOT FOR THE GIVEN ROUTE

    // LOOP THE ARRAY
    for(int file_no=0;file_no<7;file_no++)
    {
	start_check = 0;
	destination_check = 0;

        FILE *ptr=fopen(arr[file_no],"r");
        fscanf(ptr,"%*[^\n]");
        fscanf(ptr,"%*s");
        int count=0,i=0;
        char *places[20]; // ARRAY STORING THE STATIONS A PARTICULAR TRAIN PASSES
        char *train_details[11]; // ARRAY STORING TRAIN DETAILS OF A PARTICULAR TRAIN
        char train_number[20]; //STORES THE TRAIN NUMBER
        char train_name[30]; // STORES THE TRAIN NAME
	    char departure_station[20]; //STORES THE DEPARTURE STATION
        char distance[4]; // SOTRES THE DISTANCE
	    char arrival_station[20]; //STORES THE ARRIVAL STATION
        char departure_time[20]; //STORES DEPARTURE TIME
        char arrival_time[20]; //STORES THE ARRIVAL TIME
        char date1[15]; //STORES THE DATE OF DEPARTURE
    	char date2[15]; //STORES THE DATE OF ARRIVAL
	    char booking_date[20]; // SOTRES THE BOOKING DATE
       
       	int sum = 0;	

        // LOOP STORES ALL THE STATIONS OF A PARTICULAR TRAIN IN THE places ARRAY 
        while (!feof(ptr))
        {
            char *string=malloc(20*sizeof(char));
            fscanf(ptr,"%s",string);
            if (count%6==0)
            {
                places[i]=string;
                i+=1;
            }
            count+=1;
        }
        rewind(ptr);
        // CHECKING IF THE PARTICULAR TRAIN ACTUALLY PASSES THROUGH THE start AND destination
        int j,k;
        int start_check;// RETURNS TRUE WHEN THE start STATION IS IN THE FILE
        int destination_check;// RETURNS TRUE WHEN THE destination STATION IS IN THE FILE

        for (j=0;j<count/6;j++)
        {
            if (strcmp(places[j],start)==0) 
            {
                start_check=1;
                break;
            }
        }
        if (start_check==1)
        {
            for (k=j+1;k<count/6;k++)
            {
                if (strcmp(places[k],destination)==0)
                {
 	                destination_check = 1;
		            flag = 1; // TRAIN EXISTS FOR GIVEN ROUTE

                    // DISPLAYING THE POSSIBLE TRAINS
                    char *string1=malloc(20*sizeof(char));// READS TWO STRINGS
                    char *string2=malloc(20*sizeof(char));// AT A TIME FROM THE FILE
                    fscanf(ptr,"%[^\n]%*c",string1);
		            strcpy(train_name, string1);
                    fscanf(ptr,"%s",string1);
                    strcpy(train_number,string1);
		            printf("%s ", string1);

		            // PRINT THE DETAILS OF THE ROUTE
                    while (1)
                    {
                        sum=0;
                        fscanf(ptr,"%s %s",string1,string2);
                        if (strcmp(string1,start)==0)
                        {
                            strcpy(departure_station,string1);

                            if (strcmp(string2,destination)==0)
                            {
                                strcpy(arrival_station,string2);
                                printf("Leaves: %s ",string1);
                                fscanf(ptr,"%s",string1);
                                printf("Departure Time: %s ",string1);
                                strcpy(departure_time,string1);
                                printf("Arrives: %s ",string2);
                                fscanf(ptr,"%s",string1);
                                printf("Arrival Time: %s ",string1);
                                strcpy(arrival_time,string1);
                                fscanf(ptr,"%s",string1);
                                sum+=atoi(string1);
                                price1=sum;
                                fscanf(ptr," %s",string1);
                                printf("D.O.D= %s ",string1);
                                strcpy(date1,string1);
                                printf("D.O.A= %s ",string1);
				                strcpy(date2,string1);
                                printf("Price= %d\n",sum);
                                break;
                            }
                            else
                            {
                                printf("Leaves: %s ",string1);
                                fscanf(ptr,"%s",string1);
                                printf("Departure Time: %s ",string1);
                                strcpy(departure_time,string1);
                                fscanf(ptr,"%*s");
                                fscanf(ptr,"%s",string1);
                                sum+=atoi(string1);
                                fscanf(ptr,"%s",string1);
                                printf("D.O.D= %s ",string1);
                                strcpy(date1,string1);
                                int count=0;
                                while (1)
                                {
                                    fscanf(ptr,"%s",string1);
                                    count+=1;
                                    if (count%6==5)
                                    {
                                        sum+=atoi(string1);
                                    }
                                    if (strcmp(string1,destination)==0)
                                    {
                                        printf("Arrives: %s ",string1);  
                                        strcpy(arrival_station,string1); 
                                        fscanf(ptr,"%*s");
                                        fscanf(ptr,"%s",string1);
                                        printf("Arrival Time: %s ",string1);
                                        strcpy(arrival_time,string1);
                                        fscanf(ptr,"%s",string1);
                                        sum+=atoi(string1);
                                        price1=sum;
                                        fscanf(ptr,"%s",string1);
                                        printf("D.O.A= %s ",string1);
					                    strcpy(date2, string1);
                                        printf("Price= %d\n",sum);
                                        break;
                                    }

                                }
                                break;
                            }
                        }
                        
                    }

		            if (start_check == 1 && destination_check == 1)
		            {
                        // STORING THE DETAILS IN train_details ARRAY
                        train_details[0] = train_number;
                        train_details[1] = train_name;
                        train_details[2] = departure_station;
                        train_details[3] = arrival_station;
                        train_details[4] = malloc(5 * sizeof(char));
                        sprintf(train_details[4], "%d", sum);
                        train_details[5] = departure_time;
                        train_details[6] = arrival_time;
                        train_details[7] = date1;
                        train_details[8] = date2;
                        train_details[9] = malloc(5 * sizeof(char));
                        sprintf(train_details[9], "%d", (int)(sum * 100.0 / 172));			
                        train_details[10] = __DATE__; // DATE OF BOOKING

                        // COPYING IN arr1
                        for (int ind = 0; ind < 11; ++ind)
                        {
                            int l = strlen(train_details[ind]);
                            arr1[p1][ind] = malloc(l * sizeof(char));

                            strcpy(arr1[p1][ind], train_details[ind]);
                        }

                        p1+=1;
		            }
                }
            }
        }
    
        fclose(ptr);
    }

    // BOOKING THE TRAIN
    if (flag == 1)
    {
    printf("\n");
    printf("Enter the train number you want to book:");
    char *str=malloc(11*sizeof(char));    
    scanf("%s",str);          // STORES THE TRAIN NUMBER
    FILE *ptr2=fopen("Passenger_Bookings.txt","r");
    FILE *ptr3=fopen("Temp.txt","w"); // Temp.txt STORES ALL THE INFORMATION TO BE ADDED TO Passenger_Bookings.txt
    
    char food[3];
    printf("\nDo you want to pre-order food ? (YES/NO) : ");
    scanf("%s", food);

    for (int t=0;t<p1;t++)
    {
        if (strcmp(arr1[t][0],str)==0) // WRITE TRAIN DETAILS OF THOSE TRAINS WHOSE TRAIN NUMBER MATCHES WITH THE ONE ENTERED BY USER
        {
            fprintf(ptr3,"%s %s %s %s %s %s %s %s %s %s %s %s\n",arr1[t][0],arr1[t][1],arr1[t][2],arr1[t][3],arr1[t][4],arr1[t][5], arr1[t][6], arr1[t][7], arr1[t][8], arr1[t][9], food, arr1[t][10]);
	        fprintf(ptr3,"-\n");
            break;
        }
    }
    
    // ENTERING THE DETAILS OF PASSENGERS
    printf("Choose number of passengers:");
    int n;
    scanf("%d",&n);
    char *Name,*Gender;
    int Age;
    Name=malloc(20*sizeof(char));
    Gender=malloc(20*sizeof(char));
    for(int i=0;i<n;i++)
    {
        printf("Enter name:");
        scanf("%s",Name); 
        printf("Enter Age:");
        scanf("%d",&Age);     
        printf("Enter Gender:");
        scanf("%s",Gender);
        fprintf(ptr3,"%s %d %s\n",Name,Age,Gender);
    }
    fprintf(ptr3,"-\n");
    printf("\nPAY %d\n", (int)(price1 * 100.0 / 172 * n));
    printf("Your Booking is confirmed\n");
    fclose(ptr3);

    // WRITE CONTENTS IN A NEW FILE AND DELETE THE OLD Passenger_Bookings.txt

    char *string2 = malloc(100 * sizeof(char));

    FILE *ptr4 = fopen("new_file", "w");

    fscanf(ptr2, "%[^\n]%*c", string2);

    while (!feof(ptr2))
    {
	fprintf(ptr4, "%s\n", string2);

	if (strcmp(string2, username) == 0)
	{
		fscanf(ptr2, "%[^\n]%*c", string2);
		fprintf(ptr4, "%s\n", string2);

		ptr3 = fopen("Temp.txt", "r");

		for (int i = 0; i < n+3; ++i)
		{
			fscanf(ptr3, "%[^\n]%*c", string2);
			fprintf(ptr4, "%s\n", string2);
		}

		fclose(ptr3);
	}

	fscanf(ptr2, "%[^\n]%*c", string2);
    }

    fclose(ptr2);

    remove("Temp.txt");
    remove("Passenger_Bookings.txt");
    rename("new_file", "Passenger_Bookings.txt");
    }

    // IF NO TRAINS EXIST FOR GIVEN ROUTE
    else
	    printf("\nSorry, no trains exist for this route.\n");
}
// To update an already existing booking
void update_booking(char username[])
{
	// Print the available options to user
	printf("\nPlease select an option : \n");
	printf("1 : Cancel full booking\n");
	printf("2 : Cancel booking of individual person\n");

	// Take input of option
	int opt;
	scanf("%d", &opt);

	long train_id; // ID of the required train
	char *source = malloc(20 * sizeof(char)); // Source station for the train
	char *destination = malloc(20 * sizeof(char)); // Destination Station for the train

	// Take input of id, source station, and destination station
	printf("\nEnter train id, source station, and destination : ");
	scanf("%ld %s %s", &train_id, source, destination);

	// We call the function handleBookingsFile to make the necessary changes to the booking, depending on the value of opt

	if (opt == 1)
	{
		if (handleBookingsFile(1, train_id, source, destination, "", username))
			printf("\nYour booking has been cancelled. You will get the refund in 5-7 working days.\n");

		else
			printf("\nGiven booking does not exist.\n");
	}

	else if (opt == 2)
	{
		// Take input of name of person, whose ticket has to be cancelled
		char *name = malloc(15 * sizeof(char));
		printf("Enter name of person whose ticket has to be cancelled : ");
		scanf("%s", name);

		if (handleBookingsFile(2, train_id, source, destination, name, username))
			printf("\nThe ticket of %s has been cancelled. You will get the refund in 5-7 working days\n", name);

		else
			printf("\nGiven booking does not exist.\n");
	}
}

/* Handles the booking of the person with the given username.
   int mode decides what modification has to be done with the booking.
   mode = 1 : Cancel full booking 
   mode = 2 : Cancel booking of a particular person */

int handleBookingsFile(int mode, long train_id, char *source, char *destination, char *name, char *username)
{
	FILE *bookings = fopen("Passenger_Bookings.txt", "r"); // Open bookings file for reading
	FILE *new = fopen("new_file", "w"); // Open a new file for writing from the bookings file

	int flag = 0; // To check whether given booking exists or not

	char word[100]; // To read from the bookings file, and write in the new file
	fscanf(bookings, "%[^\n]%*c", word);

	// Read and write data from bookoings file to new file
	while (1)
	{
		fprintf(new, "%s\n", word);

		// If required username is found
		if (!strcmp(word, username))
		{
			fscanf(bookings, "%[^\n]%*c", word);
			fprintf(new, "%s\n", word);

			while (1)
			{
				long id;
				char *s = malloc(20 * sizeof(char));
				char *d = malloc(20 * sizeof(char));
				char *train_name = malloc(30 * sizeof(char));

				fscanf(bookings, "%s", word);

				if (!strcmp(word, "----"))
					return flag;

				else
					fseek(bookings, -strlen(word), SEEK_CUR);

				fscanf(bookings, "%ld %s %s %s%*c", &id, train_name, s, d); // For the booking, read train id, source, and destiantion

				/* If all 3 match, then the required booking is found.
				   In mode 1, we have to skip the whole booking, and start wrriting from the next booking.
				   In mode 2, we only skip writing the name of person whose ticket has to be cancelled. */
				   
				if (id == train_id && !strcmp(s, source) && !strcmp(d, destination))
				{
					flag = 1;

					fscanf(bookings, "%[^\n]%*c", word);

					// Writing the route details, like train id, departure, arrival, departure time, etc.
					if (mode != 1)
					{
						fprintf(new, "%ld %s %s %s ", id, train_name, s, d);
						fprintf(new, "%s\n", word);
					}

					fscanf(bookings, "%[^\n]%*c", word);

					if (mode != 1)
						fprintf(new, "%s\n", word);

					// This loop writes the names of people in the new file
					while (1)
					{
						fscanf(bookings, "%s", word); // Read the name
						
						if (!strcmp(word, "-"))
						{
							if (mode != 1)
								fprintf(new, "-\n");
							
							break;
						}

						// In mode 2, only skip writing the given name.
                                                   
						if (mode == 2 && strcmp(word, name))
						{
							fprintf(new, "%s", word);
							fscanf(bookings, "%[^\n]%*c", word);
							fprintf(new, "%s\n", word);
						}

						else
							fscanf(bookings, "%*[^\n]%*c"); 
					}	
				}

				// Else, just write the data as it is in the new file
				else
				{
					// Print the details of the route
					fprintf(new, "%ld %s %s %s ", id, train_name, s, d);
					fscanf(bookings, "%[^\n]%*c", word);
					fprintf(new, "%s\n", word);

					fscanf(bookings, "%[^\n]%*c", word);
					fprintf(new, "%s\n", word);

					// This loop writes the name of people in the new file
					while (1)
					{
						fscanf(bookings, "%s", word);

						if (!strcmp(word, "-"))
						{
							fprintf(new, "-\n");
							break;
						}

						fprintf(new, "%s", word);
						fscanf(bookings, "%[^\n]%*c", word);
						fprintf(new, "%s\n", word);
					}
				}	

				fscanf(bookings, "%*c%[^\n]%*c", word);

				// "----" means end of all bookings of given username
				if (!strcmp(word, "----"))
				{
					fprintf(new, "%s\n", word);
					break;
				}

				// Else, continue reading and writing for the next route, booked by the same username
				else
					fseek(bookings, -strlen(word) - 1, SEEK_CUR);
			}
		}

		if (fscanf(bookings, "%[^\n]%*c", word) == EOF)
			break;
	}
		
	fclose(bookings); // Close the bookings file
	fclose(new); // Close the new file
 
	remove("Passenger_Bookings.txt"); // Delete the current bookings file
	rename("new_file", "Passenger_Bookings.txt"); // Rename new_file to Passenger_Bookings.txt
	
	return flag;
}

