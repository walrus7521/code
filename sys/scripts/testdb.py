#!/usr/bin/python


Results = { "PASS": 1, "FAIL": 2, "INFO": 3 }

Status = { "COMPLETE": 1, "IN_PROGRESS": 2, "ABORTED": 3 }

class Machine:
    Id = 0
    Name = ""
    RAM_KB = 0
    Location = 0
    OS = 0
    Active = 0
    LastUpdated = ""

class Controller:
    Id = 0
    Name = ""
    HW_Rev = ""
    FW_Rev = ""
    Mfr = ""
    Active = 0
    LastUpdated = ""

class Drive:
    Id = 0
    Mfr = ""
    Model = ""
    SerialNum = ""
    HW_Rev = ""
    FW_Rev = ""
    PCIBusId = 0
    Active = 0
    LastUpdated = ""

class System:
    Id = 0
    MachineId = 0
    ControllerId = 0
    DriveId = 0
    LastUpdated = ""

class Location:
    Id = 0
    Name = ""
    Active = 0

class Run:
    Id = 0
    Name = ""
    NumScripts = 0
    StartTime = ""
    EndTime = ""
    ProjectId = 0
    LastUpdated = ""


