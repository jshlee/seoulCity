import csv

nodeID = ["113000489","113000424","113000423"]
#nodeID = [113000413,113000412,118000490]
#nodeID = [113000489,113000424,113000423,]

busdata = open("./BUS_63data/2017/4/602/20170401_100100087_602_1.000000_63.csv")
csv = csv.reader(busdata,delimiter=",")

timetemp = ""

total_time = 0
total_event = 0
wait_time = 0
wait_event = 0

# 0 : ??, 1 : station , 2 : node ID, 3 : same 1, 4 : arrive time, 5 : start time, 6 : Bus ID, 7 : Bus title?,
#cursor[3][0:4] == year, cursor[3][5:7] == mont cursor[3][11:13],cursor[3][14:16],cursor[3][17:19]
for cursor in csv :
    if cursor[2] == nodeID[0] :
        timetemp = cursor[5]

    if cursor[2] == nodeID[1] :
    
    totaltime += caltm(cursor[4], cursor[5])
    totalevent += 1
