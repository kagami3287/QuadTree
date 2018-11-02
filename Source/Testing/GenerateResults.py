# -*- coding: utf-8 -*-
"""
Created on Sat Oct 20 23:40:36 2018

@author: rocki
"""

import pandas as pd
import numpy as np
from functools import partial
import matplotlib.pyplot as plt
from matplotlib.widgets import Slider, RadioButtons

class GenerateResults:
    def __init__(self,sDumpFilePath):
        self.data = pd.read_csv(sDumpFilePath,sep=":",header=None)
        self.data.columns = ["Operation_Type","Iters", "Atomic_Size","Capacity", "Grid_Size", "Insert_Size", "Search_Size", "Time"]
        self.AtomicSize = np.sort(np.unique(self.data["Atomic_Size"]))
        self.Capacity = np.sort(np.unique(self.data["Capacity"]))
        self.GridSize = np.sort(np.unique(self.data["Grid_Size"]))
        self.InsertSize = np.sort(np.unique(self.data["Insert_Size"]))
        self.SearchSize = np.sort(np.unique(self.data["Search_Size"]))
        self.curAtomicSizeValue = np.min(self.AtomicSize)
        self.curCapacityValue = np.min(self.Capacity)
        self.curGridSizeValue = np.min(self.GridSize)
        self.curInsertSizeValue = np.min(self.InsertSize)
        self.SearchData = self.data[self.data["Operation_Type"] == "Search"]
        self.InsertData = self.data[self.data["Operation_Type"] == "Insert"]
        self.curData = self.SearchData
        self.bSearch = True
        self.xaxis_values = [1,2,3,4,5]
        self.yaxis_values = [1,2,3,4,5]
        self.fig, self.ax = plt.subplots()
        plt.subplots_adjust(left=0.25, bottom=0.40)
        self.l, = plt.plot(self.xaxis_values, self.yaxis_values, lw=2, color='red')
        plt.draw()
        self.axIS = plt.axes([0.25, 0.05, 0.65, 0.03])
        self.sInsertSize = Slider(self.axIS, 'InsertSize', 0, len(self.InsertSize) -1,valinit=0,valfmt="%i")
        self.sInsertSize.on_changed(partial(self.setIS_slider,self.sInsertSize))
        self.sInsertSize.set_val(0.0)
        
    def OnOperationTypeSelect(self,operationType):
        if operationType == "Insert":
            self.curData = self.data.loc[self.data["Operation_Type"] == "Insert"]
            self.axIS.set_visible(False)
        else:
            self.curData = self.data.loc[self.data["Operation_Type"] == "Search"]
            self.axIS.set_visible(True)
        self.bSearch = (operationType == "Search")
        self.UpdateView()
    
    def UpdateView(self):
        selectedData = self.curData.loc[(self.curData["Atomic_Size"] == self.curAtomicSizeValue) & 
                               (self.curData["Capacity"] == self.curCapacityValue) & 
                               (self.curData["Grid_Size"] == self.curGridSizeValue)]   
        xaxisLabel = "Number of "
        yaxisLabel = "Time / "
        title = "Performace"
        if self.bSearch:
            newSelectedData = selectedData.loc[(selectedData["Insert_Size"] == self.curInsertSizeValue)]
            self.xaxis_values = np.unique(newSelectedData["Search_Size"])
            self.yaxis_values = np.zeros(len(self.xaxis_values))
            xaxisLabel += "Searches"
            yaxisLabel += "Search"
            for i in range(len(self.xaxis_values)):
                xvalue = self.xaxis_values[i]
                yvalue = np.mean(selectedData[selectedData["Search_Size"] == xvalue]["Time"])
                self.yaxis_values[i] = yvalue
        else:
            self.xaxis_values = np.unique(selectedData["Insert_Size"])
            self.yaxis_values = np.zeros(len(self.xaxis_values))
            xaxisLabel += "Inserts"
            yaxisLabel += "Insert"
            for i in range(len(self.xaxis_values)):
                xvalue = self.xaxis_values[i]
                yvalue = np.mean(selectedData[selectedData["Insert_Size"] == xvalue]["Time"])
                self.yaxis_values[i] = yvalue
        self.l.remove()
        plt.axes(self.ax)
        self.yaxis_values = self.yaxis_values/self.xaxis_values
        self.l, = plt.loglog(self.xaxis_values, self.yaxis_values, lw=1, linestyle='--', marker='p', color='red')
        plt.xlabel(xaxisLabel)
        plt.ylabel(yaxisLabel)
        plt.title(title)
        plt.xlim(self.xaxis_values[0] * pow(10,-0.2),self.xaxis_values[-1] * pow(10,0.2))
        plt.draw()         
        
    def setAS_slider(self,s,val):
        s.val = round(val)
        s.poly.xy[2] = s.val,1
        s.poly.xy[3] = s.val,0
        self.curAtomicSizeValue = self.AtomicSize[int(s.val)]
        s.valtext.set_text(self.curAtomicSizeValue)
        self.UpdateView()
        
    def setC_slider(self,s,val):
        s.val = round(val)
        s.poly.xy[2] = s.val,1
        s.poly.xy[3] = s.val,0
        self.curCapacityValue = self.Capacity[int(s.val)]
        s.valtext.set_text(self.curCapacityValue)
        self.UpdateView()
        
    def setGS_slider(self,s,val):
        s.val = round(val)
        s.poly.xy[2] = s.val,1
        s.poly.xy[3] = s.val,0
        self.curGridSizeValue = self.GridSize[int(s.val)]
        s.valtext.set_text(self.curGridSizeValue)
        self.UpdateView()
        
    def setIS_slider(self,s,val):
        s.val = round(val)
        s.poly.xy[2] = s.val,1
        s.poly.xy[3] = s.val,0
        self.curInsertSizeValue = self.InsertSize[int(s.val)]
        s.valtext.set_text(self.curInsertSizeValue)
        self.UpdateView()
    
    def CreateDisplay(self):
        rax = plt.axes([0.025, 0.8, 0.15, 0.15])
        radioSelectOperation = RadioButtons(rax, ("Search", "Insert"), active=0)
        radioSelectOperation.on_clicked(self.OnOperationTypeSelect)
        radioSelectOperation.set_active(0)
        
        axAS = plt.axes([0.25, 0.20, 0.65, 0.03])
        axC = plt.axes([0.25, 0.15, 0.65, 0.03])
        axGS = plt.axes([0.25, 0.10, 0.65, 0.03])
        
        sAtomicSize = Slider(axAS, 'AtomicSize', 0,len(self.AtomicSize)-1,valinit=0,valfmt="%1.2f")
        sAtomicSize.on_changed(partial(self.setAS_slider,sAtomicSize))
        sAtomicSize.set_val(0.0)
        
        sCapacity = Slider(axC, 'Capacity', 0,len(self.Capacity)-1,valinit=0,valfmt="%i")
        sCapacity.on_changed(partial(self.setC_slider,sCapacity))
        sCapacity.set_val(0.0)
        
        sGridSize = Slider(axGS, 'GridSize', 0,len(self.GridSize)-1,valinit=0,valfmt="%i")
        sGridSize.on_changed(partial(self.setGS_slider,sGridSize))
        sGridSize.set_val(0.0)                
        plt.show()

if __name__== "__main__":
    result = GenerateResults(r"..\\..\\Build\\Release\\timer.txt")
    result.CreateDisplay()