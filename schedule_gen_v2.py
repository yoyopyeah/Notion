import csv
import datetime
import pandas as pd



def main():
    # prompts
    print("== Generating Notion schedule ... ==")

    # Modify class schedule
    course = "MATH 340"
    code = "M340 Tutorial"
    startDate = datetime.datetime(2022, 1, 10)
    endDate = datetime.datetime(2022, 4, 12)
    weekdays = [4]
    #####

    #############
    header = []
    with open('schedule_header.txt', 'r') as f:
        header = f.readline().split(',')
        print(header)

    f = open('notion_schedule.csv', 'a')
    writer = csv.writer(f)
    writer.writerow(header)

    while startDate.weekday() not in weekdays: 
            startDate += datetime.timedelta(days=1)
    while(startDate <= endDate):
        task = code + " @" + startDate.strftime('%-m/%-d')
        # print(task)
        row = [task, course, startDate.strftime('%Y-%m-%d'), "Class"]
        writer.writerow(row)
        
        startDate += datetime.timedelta(days=1)    
        while startDate.weekday() not in weekdays: 
            startDate += datetime.timedelta(days=1)
        

    f.close()
        



if __name__ == '__main__':
    main()