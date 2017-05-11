import csv
import ROOT
import re


def caltm(prtm,tm):
	if tm[5:7]=="02" :
		tmp=((int(tm[5:7])-int(prtm[5:7]))*2678400)+((int(tm[8:10])-int(prtm[8:10]))*86400)+((int(tm[11:13])-int(prtm[11:13]))*3600)+((int(tm[14:16])-int(prtm[14:16]))*60)+(int(tm[17:19])-int(prtm[17:19]))
	if tm[5:7]=="03" :
		if tm[2:4]=="16" : tmp=((int(tm[5:7])-int(prtm[5:7]))*2505600)+((int(tm[8:10])-int(prtm[8:10]))*86400)+((int(tm[11:13])-int(prtm[11:13]))*3600)+((int(tm[14:16])-int(prtm[14:16]))*60)+(int(tm[17:19])-int(prtm[17:19]))
		if tm[2:4]=="17" : tmp=((int(tm[5:7])-int(prtm[5:7]))*2419200)+((int(tm[8:10])-int(prtm[8:10]))*86400)+((int(tm[11:13])-int(prtm[11:13]))*3600)+((int(tm[14:16])-int(prtm[14:16]))*60)+(int(tm[17:19])-int(prtm[17:19]))
	if tm[5:7]=="04" :
		tmp=((int(tm[5:7])-int(prtm[5:7]))*2678400)+((int(tm[8:10])-int(prtm[8:10]))*86400)+((int(tm[11:13])-int(prtm[11:13]))*3600)+((int(tm[14:16])-int(prtm[14:16]))*60)+(int(tm[17:19])-int(prtm[17:19]))
	if tm[5:7]=="05" :
		tmp=((int(tm[5:7])-int(prtm[5:7]))*2592000)+((int(tm[8:10])-int(prtm[8:10]))*86400)+((int(tm[11:13])-int(prtm[11:13]))*3600)+((int(tm[14:16])-int(prtm[14:16]))*60)+(int(tm[17:19])-int(prtm[17:19]))
	return tmp



centerdata = open("Center.csv","r")

r = csv.reader(centerdata,delimiter=",")

stationlist=[]

for i in r:
	if i[1]!="":
		stationlist.append(i[1][:2]+i[1][3:])

centerdata.close()


year=["2016","2017"]
month=["02","03","04"]
day=[]

for a in range(1,32):
	if a < 10 :
		day.append("0%d"%a)
	else :
		day.append("%d"%a)

outputFile=ROOT.TFile("station.root","UPDATE")

for tyear in year :
	hist3=ROOT.TH1D("(x:day,y:spendtime)%s"%tyear,"%s"%tyear,60,0,60)
	for tmonth in month :
		for tday in day :
			try:
				busdata = open("./602/CSV/%s/%s-%s-%s_602.csv"%(tyear,tyear,tmonth,tday))
			except IOError:
				print("find error => %s-%s-%s.csv"%(tyear,tmonth,tday))
				continue
			print("%s-%s-%s.csv"%(tyear,tmonth,tday))
			t = csv.reader(busdata,delimiter=",")

			checknumber = 0

			stationindex=[]
			stationindexname={}
			histindex=[]
			stationcheck=0
			link={}

			for n in t:
				if checknumber == 1 :
					for a in stationindex :
						if n[int(a[0])] != '' and n[int(a[1])] != '' :
							link[a][0][int(n[int(a[0])][11:13])]+=caltm(n[int(a[0])],n[int(a[1])])
							link[a][1][int(n[int(a[0])][11:13])]+=1

				if checknumber == 0 :
					for m in n:
						if m[-6:-1] in stationlist:
							if stationcheck - n.index(m) == -1 :
								stationindex.append((stationcheck,n.index(m),m[-6:-1]))
								stationindexname[(stationcheck,n.index(m))]=(n[stationcheck][:-7],m[:-7])
							stationcheck = n.index(m)
							histindex.append(m[-6:-1])
					checknumber = 1
					for m in stationindex:
						link[m]=[[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]]
		

			hist=ROOT.TH1D("(x:station, y:spendtime)%s-%s-%s"%(tyear,tmonth,tday),"%s-%s-%s"%(tyear,tmonth,tday),3,0,3)
			hist2=ROOT.TH1D("(x:o'clock, y:spendtime)%s-%s-%s"%(tyear,tmonth,tday),"%s-%s-%s"%(tyear,tmonth,tday),24,0,24)

			for m in histindex :
				hist.Fill(m,0)

			hist.LabelsDeflate()
			e = 0
			for m in stationindex :
				a = 0
				b = 0
				for n in range(0,24):
					a += link[m][0][n]
					b += link[m][1][n]
				if b != 0 : hist.Fill(m[2],a/b)
				if b != 0 : e += a/b
			hist3.Fill("%s-%s-%s"%(tyear,tmonth,tday),e)

			hist.Write()

			for n in range(0,24):
				c=0
				d=0
				for m in stationindex :
					c += link[m][0][n]
					d += link[m][1][n]
				if d != 0 : hist2.Fill(n,c/d)

			hist2.Write()

	hist3.LabelsDeflate()
	hist3.Write()			


outputFile.Close()
