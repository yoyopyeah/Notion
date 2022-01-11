import csv
import datetime
import pandas as pd



def main():
    # prompts
    print("== Generating Notion schedule ... ==")
    # print("Class name [A101]:")
    # course = input()

    # print("Start date [mm/dd/yyyy]:")
    # start = input()
    # startDate = datetime.strptime(start, '%m/%d/%Y')

    # print("End date [mm/dd/yyyy]")
    # end = input()
    # endDate = datetime.strptime(end, '%m/%d/%Y')

    # print("Weekdays [0123456]:")
    # weekdays = input()
    course = "COMP 421"
    code = "C421"
    startDate = datetime.datetime(2022, 1, 10)
    endDate = datetime.datetime(2022, 4, 12)
    weekdays = [1, 3]

    #############

    header = ["Task","Course","Due Date","Type"]
    f = open('notion_schedule.csv', 'a')
    writer = csv.writer(f)
    # writer.writerow(header)

    while startDate.weekday() not in weekdays: 
            startDate += datetime.timedelta(days=1)
    while(startDate <= endDate):
        task = code + " Lec @" + startDate.strftime('%-m/%-d')
        print(task)
        row = [task, course, startDate.strftime('%Y-%m-%d'), "Class"]
        writer.writerow(row)
        
        startDate += datetime.timedelta(days=1)    
        while startDate.weekday() not in weekdays: 
            startDate += datetime.timedelta(days=1)
        

    f.close()
        



if __name__ == '__main__':
    main()