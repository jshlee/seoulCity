import csv
import re
import ROOT
import datetime


def caltm(prtm,tm):
    dtprtm=datetime.datetime(year=int(prtm[0:4]),month=int(prtm[5:7]),day=int(prtm[8:10]),hour=int(prtm[11:13]),minute=int(prtm[14:16]),second=int(prtm[17:19]))
    dttm=datetime.datetime(year=int(tm[0:4]),month=int(tm[5:7]),day=int(tm[8:10]),hour=int(tm[11:13]),minute=int(tm[14:16]),second=int(tm[17:19]))

    dtm=dttm-dtprtm

    tmp=(dtm.days*86400)+dtm.seconds
    
    return tmp


output = ROOT.TFile("hist.root","UPDATE")

nodeID = ["123000215","123000015"]

year_list = ["2016","2017"]
month_list = ["01","02","03","04","05","06","07","08","09","10","11","12"]
day_list = []
for a in range(1,32):
    if a < 10 :
        day_list.append("0%d"%a)
    else :
        day_list.append("%d"%a)

bus_list = ["100100052_302","100100053_303","100100564_320"]

total_time = 0
total_event = 0
wait_time = 0
wait_event = 0
hist_check = 0

year = 2017
hist = ROOT.TH1D("(x:month,y:spend_time)%s"%year,"%s"%year,60,0,60)
wait_hist = ROOT.TH1D("(x:month,y:wait_time)%s"%year,"%s"%year,60,0,60)

for year in year_list :
    for month in month_list :
        for day in day_list :
            for bus in bus_list :
                try :
                    busdata = open("/pnfs/user/lmousoo/BUS_63data/%s/%s/%s/%s%s%s_%s_1.000000_63.csv" % (year, month, re.split('[_]', bus)[1], year, month, day, bus))
                except IOError :
                    print("find error => %s-%s-%s-%s" %(year,month,day,bus))
                    hist_check = 1
                    continue

                readcsv = csv.reader(busdata,delimiter=",")

                timetemp1 = ""
                timetemp2 = ""
                busID = ""

                # 0 : ??, 1 : station , 2 : node ID, 3 : same 1, 4 : arrive time, 5 : start time, 6 : Bus ID, 7 : Bus title?,
                #cursor[3][0:4] == year, cursor[3][5:7] == mont cursor[3][11:13],cursor[3][14:16],cursor[3][17:19]
                for cursor in readcsv :
                    if cursor[2] == nodeID[0] :
                        timetemp1 = cursor[5]
                        busID = cursor[6]

                    if cursor[2] == nodeID[1] and busID == cursor[6] : 
                        wait_time += caltm(cursor[4], cursor[5])
                        total_time += caltm(timetemp1,cursor[5])
                        total_event += 1
                        timetemp1 = ""
                        busID = ""

        if total_event != 0 :
            hist.Fill("%s"%(month),total_time/total_event)
            wait_hist.Fill("%s"%(month),wait_time/total_event)
#                print("%s-%s, %f"%(month,day,total_time/total_event)),
#                print(", %f"%(wait_time/wait_event))

        total_time = 0
        total_event = 0
        wait_time = 0
        wait_event = 0


hist.LabelsDeflate()
wait_hist.LabelsDeflate()

hist.Write()
wait_hist.Write()

hist.Draw()
wait_hist.Draw("same")

output.Close()

print "end"
a = input()
