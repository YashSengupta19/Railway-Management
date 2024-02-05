// CONTRIBUTION : Aditya

#include "functions.h"

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void pr();
char *p(char *nam);
void print_ticket(int index, char *arrival,char *departure,char *depart_time,char *depart_date,char *arrival_time,char *arrival_date,char *train_no,char *train_name,char *food,char *distance,char *booking_date,int n,char name[][5][15], char age[][5][3], char gender[][5][1],int price);

//to print continuous lines to divide section
void pr(){
	for(int i=0;i<130;i++)
		printf("-");
	printf("\n");
}

//to put the string in middle of 30 letter sentence
char * p(char *nam){
	char *name1=malloc(30*sizeof(char));

	strcpy(name1,"                             ");
	int m=strlen(nam);
	int x=m/2;
	int i=15-x-1;
	while (*nam!='\0'){
		name1[i]=*nam;
		i++;
		*nam++;
	}
	return name1;
}
void print_ticket(int index, char *arrival,char *departure,char *depart_time,char *depart_date,char *arrival_time,char *arrival_date,char *train_no,char *train_name,char *food,char *distance,char *booking_date,int n,char name[][5][15], char age[][5][3], char gender[][5][1],int price)
{

	pr();
	printf("\t\t\t\t\t\t\tIRCTC\n");
	pr();
	printf("\t\t\t\t\t\tELECTRONIC RESERVATION SLIP\n");
	pr();
	//to give details of arrival and departure
	printf("\t\t\tBooked from\t\t\t\t\t\t\t  To\n");
	printf("\t\t%s\t\t-------->\t      %s\n",p(departure),p(arrival));	
	printf("\t\t   Start %s %s\t\t\t\t\t\tArrival %s %s\n",depart_time,depart_date,arrival_time,arrival_date);
	pr();
	//to give detail of the train with food
	printf("\t\t\tTrain no\t\t\tTrain Name\t\t\t\t\tFood\n");
	printf("\t\t\t %s\t\t       %s\t\t\t\t%s\n\n",train_no,p(train_name),food);
	printf("\t\t\t\t\tDistance\t\t\t Booking Date\n");
	printf("\t\t\t\t\t %s km\t\t\t%s\n",distance,p(booking_date));
	pr();
	//to print passenger details
	printf("\tPassenger Details\n");
	printf("  #\t\t\t\tName\t\t\t\tAge\t\t\t\tGender\t\t\t\n");
	pr();
	for(int i=0;i<n;i++){
		printf("  %d\t\t    %s\t\t%s\t\t\t\t %c\t\t\t\n",i+1,p(name[index][i]),age[index][i],gender[index][i][0]);

	}
	pr();
	//to print train details
	printf("\tPayment Details:\n");
	printf("\t\tTicket Fare\t\t\t\t\tRs%5d\n",price*n);
	printf("\t\tIRCTC Convenience Fee(incl of GST)\t\tRs%5.0f\n",price*n*0.05);
	printf("\t\tTravel Insurance Premium(incl of GST)\t\tRs%5d\n",n*10);
	printf("\t\tTotal Fare(all inclusive)\t\t\tRs%5.0f\n",price*n*1.05+n*10);
	pr();
	//printing greeting for the customer
	printf("\t\t\t\t\t\tEnjoy and have safe journey :)\n");
	pr();
	



}
