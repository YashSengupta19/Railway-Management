// CONTRIBUTION : Aryan, Areen, Niranjan

#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>
  
int isDigit(char a[]);
int *password_Validator(char password[]);
char *login_register();

typedef struct registration
{
    char first_name[15];
    char last_name[15];
    char middle_name[15];
    long int age;
    char gender;
    char contact[10];
    char user_name[15];
    char password[15];
}reg;

//this function defines the isdigit
int isDigit(char a[])
{
    for(int i = 0; i<10;i++)
    {
        if((int)a[i] < 48 || (int)a[i] > 57)
            return 0;
    }

    return 1;
}

// This will return a pointer to an array that will represent the following
/*
    if all the following conditions are met then returnval = {1}
    OTHERWISE retunrval = {2,3,4,5,6} depending on what the user has missed 
    Eg- if the user entered in upper and lower case but no digit or special char or the length was short then:
                    returnval ={2,garbageval1 ,garbageval ,5 ,6}

*/
int *password_Validator(char password[]){
    // YOU CAN NOT PASS THE POINTER TO AN ARRAY THAT IS LOCALLY DEFINED BECAUSE AFTER THE FUNCTION
    // IS REMOVED FROM THE CALL STACK , THE LOCAL VARIABLE WILL BE LOST
    // int returnval[] = {0,0,0,0,0}; this is therefore wrong
    int *returnval = (int *)malloc(sizeof(int)*5);

    for (int i = 0; i < 5; i++)
    {
        returnval[i] = 0;
    }
    

    int flag_for_digit = 0; // will be 1 (if password has a digit) or 2 (if it's not)
    int flag_for_upCase = 0; // will be 1 or 3
    int flag_for_lowCase = 0; //will be 1 or 4
    int flag_for_specialChar = 0; //will be 1 or 5
    int flag_for_shortlen = 0; // will be 1 or 6


    for (int i = 0; i < strlen(password); i++)
    {
        if (password[i]>47 &&password[i]<58)
        {
            flag_for_digit = 1;
            break;
        }
    }


    for (int i = 0; i < strlen(password); i++)
    {
        if (password[i]>64 && password[i]<91)
        {
            flag_for_upCase = 1;
            break;
        }
    }
    for (int i = 0; i < strlen(password); i++)
    {
        if (password[i]>96 && password[i]<123)
        {
            flag_for_lowCase = 1;
            break;
        }
    }
    for (int i = 0; i < strlen(password); i++)
    {
        if ((password[i]>32 && password[i]<48 && password[i] != 39) || (password[i] > 57 && password[i] < 65) && (password[i]>90 && password[i] < 97) && (password[i]>122 && password[i] < 127))
        {
            flag_for_specialChar = 1;
            break;
        }
    }
    for (int i = 0; i < strlen(password); i++)
    {
        if( strlen(password) >= 8)
        {
            flag_for_shortlen = 1;
            break;
        }
    }
    
    if (flag_for_digit && flag_for_lowCase && flag_for_specialChar && flag_for_upCase)
    {
        returnval[0] = 1;
        return returnval;
    }
    else
    {
        if (!flag_for_digit)
        {
            returnval[0] = 2;
        }
        if (!flag_for_upCase)
        {
            returnval[1] = 3;
        }
        if (!flag_for_lowCase)
        {
            returnval[2] = 4;
        }
        if (!flag_for_specialChar)
        {
            returnval[3] = 5;
        }
        if (!flag_for_shortlen)
        {
            returnval[4] = 6;
        }
        

        return returnval;
    }
    
    
}

char *login_register()
{
    //for adding the details in a register
    FILE *file;
    
    printf("***********************************************************************************************************\n\n\n");
    printf("                                             Welcome !!\n\n\n");
    printf("                This is the best and most popular site for railway bookings\n\n\n\n");
    char x[15];
    int loop = 0;

        file  = fopen("users.txt", "a");
        printf("Do you want to register(R/r) or login(L/l)       : ");
        char start;
        scanf("%c", & start);


        //an array of struct that will store the data of at max 100 users
        reg person;
       


        //when the user wants to register
        if (start == 'R' || start == 'r')
        {
            printf("\nFirst name                                       : ");
            scanf("%s", person.first_name);
            fprintf(file,"F: %s\t",person.first_name);

            printf("\nMiddle name                                      : ");
            scanf("%s", person.middle_name);
            fprintf(file,"M: %s\t",person.middle_name);

            printf("\nLast name:                                         ");
            scanf("%s", person.last_name);
            fprintf(file,"L: %s\t",person.last_name);

            printf("\nAge                                              : ");
            scanf("%ld", &person.age);
            fprintf(file,"age: %ld\t",person.age);

            printf("\nGender(M/F/O)                                    : ");
            scanf("%s", &person.gender);
            if(person.gender == 'M')
            {
                fprintf(file,"gender: male\t");
            }
            else if (person.gender == 'F')
            {
                fprintf(file,"gender: female\t");
            }
            else
            {
                fprintf(file,"gender: others\t");
            }
            

            while (1)
            {
                printf("\nEnter your contact number                        : ");
                scanf("%s", x);

                //When the contact no is not 10 digits or char                
                if(strlen(x) != 10 || !isDigit(x))
                {
                    printf("\nSorry, the this number is invalid\nPlease type again...\n\n\n");
                }
                //if the num is correct
                else
                {
                    strcpy(person.contact, x);
                    break;
                }
            }        

            printf("\nType your username                               : ");
            scanf("%s", person.user_name);
            fprintf(file,"username: %s\t", person.user_name);

            char pass1[10],pass2[10];

            do
            {    

            printf("\n\nEnter a password that must be a strong alphanumeric password that is at least 8 characters long and \n");
            printf("must be composed of both lowercase and uppercase characters and must include at least one special character\n\n");

            int flag = 0;
            do
            {
                if(flag == 0)
                {
                    printf("\nType a passsword                                : ");
                }
                else
                {
                    printf("\nEntered password did not match...");
                    printf("\nType a passsword                                : ");

                }
                scanf("%s", pass1);

                int *validation = password_Validator(pass1);
                
                if (validation[0] != 1)
                {

                    if (validation[0] == 2)
                    {
                    printf("Password is must have at least one digit");
                    }
                    if (validation[1] == 3)
                    {
                    printf("\nPassword is must have at least one uppercase character");
                        
                    }
                    if (validation[2] == 4)
                    {
                    printf("\nPassword is must have at least one lowercase character");   
                    }
                    if (validation[3] == 5)
                    {    
                    printf("\nPassword is must have at least one special character");
                    }
                    if (validation[4] == 6)
                    {
                    printf("\nPassword is too short and must be at least 8 characters long\n\n\n");
                    }

                }
                else
                {
                    break;
                }

            } while (1);


            printf("Retype your password                             : ");
            scanf("%s", pass2);  

            }while(strcmp(pass1,pass2) != 0);

        
           
            strcpy(person.password , pass1);
            fprintf(file,"password: %s\n", person.password);
            printf("\n\nCongratulations! Your account has been created successfully!!    :)\n");

            FILE *bookings = fopen("Passenger_Bookings.txt", "a");
            fprintf(bookings, "%s\n----\n----\n", person.user_name);

	    fclose(file);

	    char *user_pointer = malloc(15 * sizeof(char));

	    strcpy(user_pointer, person.user_name);

	    return user_pointer;
        }

        //When person wants to login in
        else if(start == 'L' || start == 'l')
        {
            char check_user[15];
            char check_pass[15];
            char correct_user[15];
            char correct_pass[15];
            int fact = 0;

            file = fopen("users.txt", "r");
	    
            do
            {
                
                printf("Type username : ");
                scanf("%s", check_user);
                printf("Type password : ");
                scanf("%s", check_pass);

                while (!feof(file))
                {
                    for (int count = 1; count <= 11; ++count)
                        fscanf(file, "%*s");

                    fscanf(file, "%s %*s %s", correct_user, correct_pass);

                    if (!strcmp(check_user, correct_user) && !strcmp(check_pass, correct_pass))
                    {
                        
                        printf("\nLogged in successfully.\n");
                      
			char *user_pointer = malloc(15 * sizeof(char));

			strcpy(user_pointer, check_user);
			return user_pointer;
                        
                    }
                }

                if (fact == 0)
                    printf("\nInvalid Credentials. Try again.\n\n");
                }
                while (fact == 0);
                       
        }
        loop++;
        //fclose(file);
    
}
