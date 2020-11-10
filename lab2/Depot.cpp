#include "Depot.h"
bool CDepot::loadDataFromCSV(string path) {
	ifstream file;
	file.open(path);
	if (file.is_open()) {
		char str[255];
		char buf[15];
		while (file.getline(str,255)){
			//cout << str << endl;
			int i = 0, k = 0, end = strlen(str), count  = 0, index = 0;
			while (i < end) {
				if (str[i] == ';') {
					count++;
					index = i;
					switch (count)
					{
					case 1: {
						buf[k] = '\0';
						ID = atoi(buf);
						//cout << ID << endl;
						break;
					}
					case 2: {
						buf[k] = '\0';
						V_Type = atoi(buf);
						//cout << V_Type << endl;
						break;
					}case 3: {
						buf[k] = '\0';
						make = buf;
						//cout << make << endl;
						break;
					}case 4: {
						buf[k] = '\0';
						load_capacity = atof(buf);
						//cout << load_capacity << endl;
						break;
					}case 5: {
						buf[k] = '\0';
						cost_per_mile = atof(buf);
						//cout << cost_per_mile << endl;
						break;
					}case 6: {
						buf[k] = '\0';
						average_speed = atof(buf);
						//cout << average_speed << endl;
						count++;
						k = 0;
						break;
					}case 7: {
						buf[k] = '\0';
						max_distanse = atoi(buf);
						//cout << max_distanse << endl;
						break;
					}
					}
					k = 0;
					i++;
				}else {
					buf[k] = str[i];
						i++; k++;
				}
			}
			int z = 0, j = 0 ;
			while (index != end) {
				buf[k] = str[index];
				index++; k++;
			}
			buf[k] = '\0';
			max_distanse = atoi(buf);
			//cout << max_distanse << endl;
			//cout << endl;
			if (V_Type == 0) 
				AddCar(ID,V_Type,max_distanse,average_speed,load_capacity,cost_per_mile,make);
			if (V_Type == 1) {
				if (make == "Diezel") {
					AddTrain(ID, V_Type, make, average_speed, load_capacity, cost_per_mile, max_distanse);
				}
				else {
					AddTrain(ID, V_Type, make, average_speed, load_capacity, cost_per_mile);
				}
			}

		}
		return true;
	}
	return false;
}
 
void CCar:: Display() {
	cout << "ID:" << id << endl;
	cout << "type transport:" << v_type << endl;
	cout << "make:" << make << endl;
	cout << "load capacity:" << load_capacity << endl;
	cout << "cost per mile:" << cost_per_mile << endl;
	cout << "avarage speed:" << average_speed << endl;
	cout << "max distance :" << max_distance<<"\n" << endl;
}

void CTrain::Display() {
	cout << "ID:" << id << endl;
	cout << "type transport:" << v_type << endl;
	cout << "type:" << type << endl;
	cout << "load capacity:" << load_capacity << endl;
	cout << "cost per mile:" << cost_per_mile << endl;
	cout << "avarage speed:" << average_speed << endl;
	if( type == "Diezel")
		cout << "max distance :" << max_distance  << endl;
	cout << endl;
}

void CDepot::ShowAll() {
	cout << "ShowAll:" << endl;
	list<CVehicle*>::iterator itr;
	
	for ( itr = vehicles.begin(); itr != vehicles.end(); itr++) {
		CVehicle* tmp;
		tmp = *itr;
		tmp->Display();
	}
}


CVehicle* CDepot::AddCar(int ID, int V_Type, int max_distanse, double average_speed, double load_capacity, double cost_per_mile, string make) {
	CCar* tmp =new CCar(ID,V_Type,make,average_speed,load_capacity,cost_per_mile, max_distanse);
	if (!tmp)
		return NULL;
	CVehicle* db = tmp;
	if (!db)
		return NULL;
	vehicles.push_back(db);
	return db;
}

double CCar::CalculateCost (int weight, int dist) {
	if (dist > max_distance)
		return -1;
	return weight * dist * cost_per_mile;
}
double CCar::CalculateTime(int dist) {
	if (dist > max_distance)
		return -1;
	return dist / average_speed;
}
double CTrain::CalculateTime(int dist) {
	if (type == "Diezel" && dist > max_distance) return -1;
	return dist / average_speed;
}
double CTrain::CalculateCost(int weight, int dist) {
	if (type == "Diezel" && dist > max_distance) return -1;
	return weight * dist * cost_per_mile;
}
CVehicle *CDepot:: AddTrain(int _id, int _v_type, string  type, double _average_speed, double _load_capacity, double _cost_per_mile, int maxdistance) {
	CTrain* tmp = new CTrain( _id,  _v_type,  type,  _average_speed, _load_capacity, _cost_per_mile, maxdistance);
	if (!tmp)
		return NULL;
	CVehicle *db = tmp;
	if (!db)
		return NULL;
	vehicles.push_back(db);
	return db;
}
bool CDepot:: RemoveVehicle(int id){
	list<CVehicle*>::iterator itr;
	for (itr = vehicles.begin(); itr != vehicles.end(); itr++) {
		CVehicle* tmp;
		tmp = *itr;
		if (tmp->GetId() == id) {
			vehicles.erase(itr);
			return true;
		}
	}
	return false;
}

void CDepot::ShowRecordSet(list< CVehicle*> rs) {
	cout << "\nShowRecordSet:" << endl;
	list<CVehicle*>::iterator itr;
	for (itr = rs.begin(); itr != rs.end(); itr++) {
		CVehicle* tmp;
		tmp = *itr;
		tmp->Display();
	}
}
void CDepot::display(CVehicle* rs) {
	cout << "\nShow1:" << endl;
	if (rs!=NULL)
		rs->Display();
}
CVehicle* CDepot::FindCheapest(double weight, double dist) {
	list <CVehicle*>::iterator itr;
	itr = vehicles.begin();
	CVehicle* fcheep = *itr;
	CVehicle* b = *itr;
	int _weight = (int)weight;
	int _dist = (int)dist;
	int count = -1;
	double check = fcheep->CalculateCost(weight, dist);
	for (itr = vehicles.begin(); itr != vehicles.end(); itr++) {
		CVehicle* tmp = *itr;
		if (typeid(*tmp) == typeid(CCar)) {
			if (dynamic_cast<CCar*>(tmp)->dist() <= _dist) {
				if (tmp->CalculateCost( _dist , _weight) < check) {
					fcheep = tmp;
					check = tmp->CalculateCost(_weight, _dist);
					count++;
				}
			}
		}
		else
		{
			if (typeid(*tmp) == typeid(CTrain)) {
				if (dynamic_cast<CTrain*>(tmp)->dist() <= _dist) {
					if (tmp->CalculateCost(_dist, _weight) < check) {
						fcheep = tmp;
						check = tmp->CalculateCost(_weight, _dist);
						count++;
					}
				}

			}
		}

	}
	if (count == -1)
		return NULL;
	else
		return fcheep;
}

 list <CVehicle*> CDepot::VehiclesAvailable(double weight, double dist, double cost) {
	 list<CVehicle*>::iterator itr;
	 list<CVehicle*> VehAv;
	 int _weight = (int)weight;
	 int _dist = (int)dist;
	 for (itr = vehicles.begin(); itr != vehicles.end(); itr++) {
		 CVehicle* tmp = *itr;
		 if (typeid(*tmp) == typeid(CCar)) {
			 if (dynamic_cast<CCar*>(tmp)->dist() >= _dist) {
				 if ((this->cost_per_mile) * _dist * _weight <= tmp->CalculateCost(weight, dist)) {
					 VehAv.push_back(tmp);
				 }
			 }
		 }
		 else
		 {
			 if (typeid(*tmp) == typeid(CTrain)) {
				 if (dynamic_cast<CTrain*>(tmp)->dist() <= _dist) {
					 if ((this->cost_per_mile) * _dist * _weight <= tmp->CalculateCost(weight, dist)) {
						 VehAv.push_back(tmp);
					 }
				 }

			 }
		 }

	 }
	 return VehAv;
 }

void CDepot:: ChangeCostPerMile(int id, double new_cost) {
	list<CVehicle*>::iterator itr;
	int count = -1;
	for (itr = vehicles.begin(); itr != vehicles.end(); itr++) {
		CVehicle* tmp = *itr;
		if (typeid(*tmp) == typeid(CCar)) {
			if (dynamic_cast<CCar*>(tmp)->GetId() == id) {
				dynamic_cast<CCar*>(tmp)->GetCost(new_cost);
				count++;
			}
		}
		if (typeid(*tmp) == typeid(CTrain)) {
			if (dynamic_cast<CTrain*>(tmp)->GetId()== id) {
				dynamic_cast<CTrain*>(tmp)->GetCost(new_cost);
				count++;
			}
		}
	}
 }
 
list <CVehicle*> CDepot::SQL(const char* field, const char* cond, const char* value) {
	list<CVehicle*>::iterator itr;
	double _field , _value;
	_field = atof(field);
	_value = atof(value); 
	string _cond;
	list <CVehicle*> sql;
	
	for (itr = vehicles.begin(); itr != vehicles.end(); itr++) {
		CVehicle* tmp = *itr;
		if (typeid(*tmp) == typeid(CCar)) {
			if (field == "avarage_speed") {
				if (cond == "ge") {
					if (dynamic_cast<CCar*>(tmp)->Speed()>= _value) {
						sql.push_back(tmp);
					}
				}
				else {
					if (cond == "le"){
							if (dynamic_cast<CCar*>(tmp)->Speed() <= _value) {
								sql.push_back(tmp);
							}
						}
				}
			}
			else {
				if (field == "max_distance") {
					if (cond == "ge") {
						if (dynamic_cast<CCar*>(tmp)->dist() >= _value) {
							sql.push_back(tmp);
						}
					}
					else {
						if (cond == "le")
							if (dynamic_cast<CCar*>(tmp)->dist() <= _value) {
								sql.push_back(tmp);
							}
					}
				}
			}
		}
		else {
			if (typeid(*tmp) == typeid(CTrain)) {
				if (field == "avarage_speed") {
					if (cond == "ge") {
						if (dynamic_cast<CTrain*>(tmp)->Speed() >= _value) {
							sql.push_back(tmp);
						}
					}
					else {
						if (cond == "le")
							if (dynamic_cast<CTrain*>(tmp)->Speed() <= _value) {
								sql.push_back(tmp);
							}
					}
				}
				else {
					if (field == "max_distance") {
						if (cond == "ge") {
							if (dynamic_cast<CTrain*>(tmp)->dist() >= _value) {
								sql.push_back(tmp);
							}
						}
						else {
							if (cond == "le")
								if (dynamic_cast<CTrain*>(tmp)->dist() <= _value) {
									sql.push_back(tmp);
								}
						}
					}
				}
			}

		}
	}
	return sql;
}



