/*
   This program is a date calculator. Users have the option to 3 date calculation functionalities. 
    1. Add days to a date 
    2. Subtract days from a date 
    3. Calculate days between two dates
    Each functionality is embedded with date validity checks and leap year checks (following the Gregorian Calendar) 
    to ensure users receive an accurate result. 
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Function prototyping
void show_menu();
bool valid_date(int mon, int day, int year);
bool is_leap_year(int year);
void add_days_to_date(int *month, int *day, int *year, int days_left_to_add);
void subtract_days_from_date(int *month, int *day, int *year, int days_left_to_subtract);
void print_new_date();
int count_days(int d1, int d2, int m1, int m2, int y1, int y2);
int day_of_year (int day, int month, int year);
int year_to_days(int y1, int y2);

//Values correspond to the number of the days in each month (starting at index 1).
int days_in_month[] = {0,31,28, 31,30,31,30,31,31,30,31,30,31};


int main() 
{
  show_menu();
}

//This function displays the menu and links to calculator functionality
void show_menu()
{
  int option;
  int mm, dd, yyyy;
  int days_left_to_subtract, days_left_to_add;
  int day1, mon1, year1, day2, mon2, year2;
  int difference;

  printf("Welcome to the date calculator!\n");
  printf("Select date calculaion you would like to calculate\n\n");

  printf("1. Add Days to a Date\n");
  printf("2. Subtract Days From a Date\n");
  printf("3. Calculate Days Between Two Dates\n\n");


  do 
  {
    printf("Enter an option\n");
    scanf(" %d", &option);
    printf("\n");
    
    switch (option) {
      case 1:
        printf("Enter a start date in the format (mm/dd/yyyy). **Year must be between 1800 and 10000**.\n"); 
        scanf(" %d/%d/%d", &mm, &dd, &yyyy);
        if(!valid_date(mm,dd,yyyy)){
          printf("Date is invalid.\n");
          break;
        }
        printf("\n");

        printf("Enter the number of days you would like to add.\n");
        scanf(" %d", &days_left_to_add);
        printf("\n");

        add_days_to_date(&mm, &dd, &yyyy, days_left_to_add);
        print_new_date(mm,dd,yyyy);
        
        break;
      case 2:
        printf("Enter a start date in the format (mm/dd/yyyy). **Year must be between 1800 and 10000**.\n"); 
        scanf(" %d/%d/%d", &mm, &dd, &yyyy);
        if(!valid_date(mm,dd,yyyy)){
          printf("Date is invalid.\n");
          break;
        }

        printf("Enter the number of days you would like to subtract from date.\n");
        scanf(" %d", &days_left_to_subtract);
        printf("\n");

        subtract_days_from_date(&mm, &dd, &yyyy, days_left_to_subtract);
        print_new_date(mm,dd,yyyy);
      break;
      case 3:
        printf("Enter start date in the format (mm/dd/yyyy). **Year must be between 1800 and 10000**.\n");
        scanf("%d/%d/%d", &mon1, &day1, &year1);
        if (!valid_date(mon1, day1, year1)){
          printf("Start date is invalid.\n");
           exit (0);
          }
        printf("Enter end date in the format (mm/dd/yyyy). **Year must be between 1800 and 10000**.\n");
        scanf("%d/%d/%d", &mon2, &day2, &year2);
        if (!valid_date(mon2, day2, year2)){
          printf("Second date is invalid.\n");
          exit (0);
        }
        difference = count_days(day1, mon1, year1, day2, mon2, year2);
        printf("It is %d days from the start date to end date, but not including the end date.\n", difference);
      break;

      default:
        printf("%d is not a valid choice. \n", option);
        printf("Try again.\n\n");

        break;
    }
  } while (!(option ==1)&&!(option==2)&&!(option==3));
}


//This function determines if user enters valid date and returns true/false 
bool valid_date(int mon, int day, int year)
{
  if (year > 1800 && year < 10000)
  {
    if (mon >= 1 && mon <= 12) 
    {
      //checks if valid date for February
      if (is_leap_year(year) && day==29){
        return true;
      } else if(day > 28)
      {
        return false;
      }
    }
    //checks for days in 30-day months
    else if (mon == 4 || mon == 6 ||mon == 9 || mon == 11)
    {
      if (day >30)
      {
        return false;
      }
    }
    //checks for days in 31-day months
    else if (day > 31){
      return false;
    }
  } else 
  {
    return false;
  }
  return true;
}


//This function determines if a year qualifies as a leap year and returns true/false
bool is_leap_year(int year)
{
  return (year % 4==0 && (year % 100 || year % 400 == 0));
}


//This function adds days to a given date 
void add_days_to_date(int *month, int *day, int *year, int days_left_to_add)
{
  int days_left_in_month;
  while(days_left_to_add>0){
    days_left_in_month = days_in_month[*month]-*day;
    if ((*month==2)&&(is_leap_year(*year))){
      days_left_in_month = days_in_month[2] + 1 - *day;
    }
    if(days_left_to_add > days_left_in_month){
      days_left_to_add -= days_left_in_month + 1;
      *day = 1;
      if (*month==12){
        *month = 1;
        *year += 1;
      } else {
        *month += 1;
      }
    } else {
      *day += days_left_to_add; 
      days_left_to_add = 0;
    }
  }
}


//This function subtracts days from a given date 
void subtract_days_from_date(int *month, int *day, int *year, int days_left_to_subtract)
{
  int days_left_in_month;

  while (days_left_to_subtract>0){
    days_left_in_month = *day -1;

    //Accounts for the extra day in a leap year
    if ((*month==3)&&(is_leap_year(*year)))
    {
      days_in_month[2] += 1;
    }

    if(days_left_to_subtract>days_left_in_month){
        days_left_to_subtract -= (days_left_in_month + 1); 
        *day = days_in_month[*month-1];

        if (*month==1){
          *month = 12;
          *year -= 1;
          *day = days_in_month[*month];
        } else {
          *month -= 1;
        }

    }else{
      *day -= days_left_to_subtract;
      days_left_to_subtract = 0;
      
    }
    //Resets the number of days in February after leap year
    days_in_month[2] = 28;
  }
}


//This function prints the new date in a more human-readable format after days are added to/subtracted from original date. 
void print_new_date(int month, int day, int year){

  printf("The new date is \n");

  switch (month)
  {
    case 1: 
      printf("January");
      break; 
    case 2: 
      printf("February");
      break; 
    case 3: 
      printf("March");
      break; 
    case 4: 
      printf("April");
      break; 
    case 5: 
      printf("May");
      break; 
    case 6: 
      printf("June");
      break; 
    case 7: 
      printf("July");
      break; 
    case 8: 
      printf("August");
      break; 
    case 9: 
      printf("September");
      break; 
    case 10: 
      printf("October");
      break; 
    case 11: 
      printf("November");
      break; 
    case 12: 
      printf("December");
      break; 
    default:
      break;
  }

  // Prints the day
  printf(" %d", day);

  // Prints the suffix for a given day
   switch (day)
   {
    case 1: case 21: case 31:
      printf("st");
      break;
    case 2: case 22: 
      printf("nd");
      break;
    case 3: case 23:
      printf("rd");
      break;
    default: 
      printf("th");
      break;
  }

  // Prints the year
  printf(", %d \n",year);
}


//This function counts the days between two dates and returns the day count
int count_days(int d1, int m1, int y1, int d2, int m2, int y2)
{
int count;
count = day_of_year(d2,m2,y2) - day_of_year(d1,m1,y1);
  if (y1 != y2)
  {
    if (y1 < y2)
    {
    //Adds days to day count if end year is greater than start year
    count+=year_to_days(y1,y2);
    } else
    {
    //Subtracts days from day count if start year is greater than end year
    count-=year_to_days(y2,y1);
    }
  }
return count;
}


//This function converts the day of month to day of year and returns the day of year. 
int day_of_year (int day, int month, int year)
{
  int dofy=0; // day of year
  int md[13] = {0,0,31,59,90,120,151,181,212,243,273,304,334}; 
  dofy = md[month]+day; //Adds days passed in previous months to current day of month

  //accounts for extra day in leap year
  if((is_leap_year(year))&&(month>2)){
    dofy += 1;
  }
  return dofy;
}


//This function converts years to days 
int year_to_days(int y1, int y2){
  int i, days;  
  days=0;

  for (i=y1;i<y2;i++){
   
    //365 days = 1 year
    days+=365;  

   //accounts for leap day in a leap year  
    if(is_leap_year(i)){    
      days+=1;
    }
  }
  return days;
}
