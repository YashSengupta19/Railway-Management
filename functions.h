void display_bookings(char username[]);
void check_status();

void manageBooking(char username[]);
void new_booking(char username[]);
void update_booking(char username[]);
int handleBookingsFile(int mode, long train_id, char *source, char *destination, char *name, char *username);

int isDigit(char a[]);
int *password_Validator(char password[]);
char *login_register();

void pr();
char *p(char *nam);
void print_ticket(int index, char *arrival,char *departure,char *depart_time,char *depart_date,char *arrival_time,char *arrival_date,char *train_no,char *train_name,char *food,char *distance,char *booking_date,int n,char name[][5][15], char age[][5][3], char gender[][5][1],int price);
