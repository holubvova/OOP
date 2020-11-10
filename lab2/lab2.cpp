#include <iostream>
#include "Depot.h"
using namespace std;

int main()
{
    string file = "Input.csv";
    CDepot db;
    db.loadDataFromCSV(file);
    db.ShowAll();
    db.RemoveVehicle(1);
    db.ShowAll();
    list<CVehicle*> rs = db.SQL("max_distance", "le", "450");
    db.ShowRecordSet(rs);
    db.display(db.FindCheapest(50, 10));
    db.ChangeCostPerMile(2, 800);
    db.ShowAll();
    
}
