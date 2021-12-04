#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// get the next date
char* getNextDate(char* date, int offset){
    char dd[3], mm[3], yyyy[5];
    int day, month, year;

    // split the date string into fields
    char delim[2] = "/";
    char* token;

    token = strtok(date, delim);
    month = atoi(token);
    token = strtok(NULL, delim);
    day = atoi(token);
    token = strtok(NULL, delim);
    year = atoi(token);

    // get next date
    day += offset;

    int days_per_month = 31;
    if (month == 4 || month == 6 || month == 9 || month == 11) {
        days_per_month = 30;
    } else if (month == 2) {
        days_per_month = 28;
        if (year % 4 == 0) {
            days_per_month = 29;
        }
    }
    if (day > days_per_month) {
        day = day - days_per_month;
        month++;
        if (month > 12) {
            month = 1;
            year++;
        }
    }

    // int to string
    sprintf(date, "%d/%d/%d", month, day, year);
    return date;
}


void create_csv(char* class,  char* start, char* end, int weekdays) {
    char name[20], wkday[20];
    FILE *fp;
    int i=1, offset;

    printf("\n>>> Creating NotionSchedule.csv file");

    fp=fopen("NotionSchedule.csv","w+");

    //print the 14 fields
    fprintf(fp,"Name,Class,Create time,Done,Due Date,Lecture,Notes & Review,Overdue,Prep & Download,Related to Tasks,This week & before,Type,Weekday,weekday");

    while(strcmp(start,end) <= 0) { // while start < end
        //TODO: comparition fails when 12<3
        sprintf(name, "Lecture %d", i); //TODO: change the format of name when needed
        offset = 1;
        switch (weekdays) {
            case 13:
                switch (i % 2) {
                    case 1:
                        sprintf(wkday, "Monday");
                        offset = 2;
                        break;
                    case 0:
                        sprintf(wkday, "Wednesday");
                        offset = 5;
                        break;
                    default:
                        break;
                }
                break;
            
            case 24:
                switch (i % 2) {
                case 1:
                    sprintf(wkday, "Tuesday");
                    offset = 2;
                    break;
                case 0:
                    sprintf(wkday, "Thursday");
                    offset = 5;
                    break;
                default:
                    break;
                }

            case 1234:
                switch (i % 4) {
                case 1:
                    sprintf(wkday, "Monday");
                    break;
                case 2:
                    sprintf(wkday, "Tuesday");
                    break;
                case 3:
                    sprintf(wkday, "Wednesday");
                    break;
                case 0:
                    sprintf(wkday, "Thursday");
                    offset = 4;
                    break;
                default:
                    break;
            }

            default:
                break;
        }

        i++;
        fprintf(fp,"\n%s,%s,,No,%s,No,No,,No,,,,%s,", name, class, start, wkday);
        start = getNextDate(start, offset);
    }

    printf("\n>>> Schedule creation completed.");
    fclose(fp);
}


// int get_weekday(char * str) {
//     struct tm tm;
//     memset((void *) &tm, 0, sizeof(tm));
//     if (strptime(str, "%m/%d/%Y", &tm) != NULL) {
//         time_t t = mktime(&tm);
//         if (t >= 0) {
//         return localtime(&t)->tm_wday; // Sunday=0, Monday=1, etc.
//         }
//     }
//     return -1;
// }


int main() {
    char class[20], start[20], end[20], nextDate[11];
    int startDay, weekdays;

    printf("\n== Enter the following info ==\nClass name [ABCD 101]:\n");
    scanf("%[^\n]", class);

    printf("Start date [mm/dd/yyyy]:\n");
    scanf("%s", start);

    printf("End date [mm/dd/yyyy]:\n");
    scanf("%s", end);

    printf("Weekdays [0123456]:\n");
    scanf("%d", &weekdays);

    // printf("Start weekday [0123456]:\n");
    // scanf("%d", startDay);

    create_csv(class, start, end, weekdays);

    return 0;
}