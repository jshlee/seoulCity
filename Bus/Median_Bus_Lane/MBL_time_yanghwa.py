import csv
import re
import ROOT

def caltm(prtm,tm):
        if tm[5:7] == "02" or tm[5:7] == "04" :
                tmp = ((int(tm[5:7])-int(prtm[5:7]))*2678400)+((int(tm[8:10])-int(prtm[8:10]))*86400)+((int(tm[11:13])-int(prtm[11:13]))*3600)+((int(tm[14:16])-int(prtm[14:16]))*60)+(int(tm[17:19])-int(prtm[17:19]))
        if tm[5:7] == "03" :
                if tm[2:4] == "16" : tmp = ((int(tm[5:7])-int(prtm[5:7]))*2505600)+((int(tm[8:10])-int(prtm[8:10]))*86400)+((int(tm[11:13])-int(prtm[11:13]))*3600)+((int(tm[14:16])-int(prtm[14:16]))*60)+(int(tm[17:19])-int(prtm[17:19]))
                if tm[2:4] == "17" : tmp = ((int(tm[5:7])-int(prtm[5:7]))*2419200)+((int(tm[8:10])-int(prtm[8:10]))*86400)+((int(tm[11:13])-int(prtm[11:13]))*3600)+((int(tm[14:16])-int(prtm[14:16]))*60)+(int(tm[17:19])-int(prtm[17:19]))
        if tm[5:7] == "05" :
                tmp = ((int(tm[5:7])-int(prtm[5:7]))*2592000)+((int(tm[8:10])-int(prtm[8:10]))*86400)+((int(tm[11:13])-int(prtm[11:13]))*3600)+((int(tm[14:16])-int(prtm[14:16]))*60)+(int(tm[17:19])-int(prtm[17:19]))
        return tmp


output = ROOT.TFile("totalhist2.root","UPDATE")

nodeID = ["118000489","113000424","113000423"] #city center direction
#nodeID = ["113000413","113000412","118000490"] #city edge direction

year_list = ["2016","2017"]
month_list = ["02","03","04"]
day_list = []
for a in range(1,32):
        if a < 10 :
                day_list.append("0%d"%a)
        else :
                day_list.append("%d"%a)
#bus_list = ["100100286_5712","100100087_602", "100100089_604", "100100330_6712"]
bus_list = ["100100087_602"]

total_time = 0
total_event = 0
wait_time = 0
wait_event = 0
hist_check = 0

#c1 = ROOT.TCanvas("c1","test",1600,1400)

for year in year_list :
#    hist = ROOT.TH1D("(x:day,y:spend_time)%s"%year,"%s"%year,60,0,60)
#    hist2 = ROOT.TH1D("(x:day,y:wait_time)%s"%year,"%s"%year,60,0,60)
    week_check = 0
    for month in month_list :
        for day in day_list :
            for bus in bus_list :
                try :
                    busdata = open("/pnfs/user/lmousoo/BUS_63data/%s/%s/%s/%s%s%s_%s_1.000000_63.csv" % (year, month, re.split('[_]', bus)[1], year, month, day, bus))
                except IOError :
                    #print("find error => %s-%s-%s-%s" %(year,month,day,bus))
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

                    if cursor[2] == nodeID[1] and busID == cursor[6] and cursor[4][0:4] == year and cursor[5][0:4] == year : 
                        if cursor[4][11:13] == "18" :
#                        if cursor[4][11:13] == "07" or cursor[4][11:13] == "08" :
                            wait_time += caltm(cursor[4], cursor[5])
                            wait_event += 1

                    if cursor[2] == nodeID[2] and busID == cursor[6] and timetemp1[0:4] == year and cursor[4][0:4] == year :
                        if cursor[4][11:13] == "18" :
#                        if cursor[4][11:13] == "07" or cursor[4][11:13] == "08" :
                            total_time += caltm(timetemp1,cursor[4])
                            total_event += 1
                        timetemp1 = ""
                        busID = ""

#            if hist_check == 0 : week_check += 1
#            if week_check == 7 :
            if total_event == 0 or wait_event == 0 : hist_check = 1
            if hist_check == 0 :
#                    hist.Fill("%s-%s"%(month,day),total_time/total_event)
                print("%s-%s, %f"%(month,day,total_time/total_event)),
#                    hist2.Fill("%s-%s"%(month,day),wait_time/wait_event)
                print(", %f"%(wait_time/wait_event))

            total_time = 0
            total_event = 0
            wait_time = 0
            wait_event = 0
            week_check = 0
                
            hist_check = 0


#    hist.LabelsDeflate()
#    hist.Write()
#    hist.Draw()
#    hist2.LabelsDeflate()
#    hist2.Write()
#    hist2.Draw("same")

#output.Close()

print "end"
a = input()
