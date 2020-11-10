#pragma once
#include <iostream>
#include <string>
#include <list>
#include <fstream>
#include <typeinfo>

using namespace std;

class CVehicle {
public:
	CVehicle() {};
	CVehicle(int _id, int _v_type, double _average_speed, double _load_capacity, double _cost_per_mile) :
		average_speed(_average_speed), load_capacity(_load_capacity),
		cost_per_mile(_cost_per_mile),
		id(_id), v_type(_v_type) {};
	virtual void Display() = 0;
	//вартість перевезення weight кг на dist км
	//якщо перевезення здійснюється вантажівкою, або дізелем і dist > //max_distance повертає -1
	virtual double CalculateCost(int weight, int dist) = 0;
	// час перевезення вантажів
	//якщо перевезення здійснюється вантажівкою або дизелем і dist > //max_distance повертає -1
	virtual	double CalculateTime(int dist) = 0;
	virtual int GetId() { return id; }
	virtual int GetCost(double cost) { cost_per_mile = cost; return cost_per_mile; };

protected:
	int v_type;//0- car, 1 - train
	int id;
	double average_speed;
	double load_capacity;
	double cost_per_mile;//вартість перевезення 1 кг на 1 милю
};

class CCar : public CVehicle {
	 double speed = average_speed;
public: 
	CCar() {};
	CCar(int _id, int _v_type, string  make, double _average_speed, double _load_capacity, double _cost_per_mile, int maxdistance) :
		CVehicle( _id,  _v_type, _average_speed, _load_capacity,  _cost_per_mile),
		max_distance(maxdistance),make(make){};
	void Display();
	double CalculateCost(int weight, int dist);
	double CalculateTime(int dist);
	double Speed() { return speed; };
	int dist() { return max_distance; };
	//Add here whatever you need
	//. . .
protected:
	int max_distance;// max distance without refueling
	string make;//manufactorer
};

class CTrain : public CVehicle {
public:
	CTrain() {};
	CTrain(int _id, int _v_type, string  type, double _average_speed, double _load_capacity, double _cost_per_mile, int maxdistance =999999) :
		CVehicle(_id, _v_type, _average_speed, _load_capacity, _cost_per_mile),
		max_distance(maxdistance), type(type) {};
	void Display();
	double CalculateTime(int dist);
	double CalculateCost(int weight, int dist);
	double Speed() { return this->average_speed; };
	double dist() { return max_distance; };
	//Add here whatever you need
	//. . .
protected:
	string type;//diesel / electrical
	int max_distance;// max distance without refueling if diesel
};

class CDepot {
	int ID = 0, V_Type = 0, max_distanse = 0;
	double average_speed = 0, load_capacity = 0, cost_per_mile = 0;
	string make;
	//add whatever you need
public:
	bool loadDataFromCSV(string path);
	CVehicle* AddCar(int ID ,int V_Type,int max_distanse,double average_speed,double load_capacity,double cost_per_mile ,string make);
	CVehicle* AddTrain(int _id, int _v_type, string  type, double _average_speed, double _load_capacity, double _cost_per_mile, int maxdistance = 9999 );
	bool RemoveVehicle(int id);
	void ShowAll();
	CVehicle* FindCheapest(double weight, double dist);
	list <CVehicle*> SQL(const char* field, const char* cond, const char* value);
	void ShowRecordSet(list< CVehicle*> rs);
	list <CVehicle*> VehiclesAvailable(double weight, double dist, double cost);
	void ChangeCostPerMile(int id, double new_cost);

	void display(CVehicle *rs);
private:
	list< CVehicle*> vehicles;
};