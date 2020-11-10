import csv
import os
csv_filename = 'cars.csv'
#coursera_week3_

class CarBase:
    def __init__(self, brand, photo_file_name, carrying):
        self.brand = brand
        self.photo_file_name = photo_file_name
        self.carrying = float(carrying)

    def get_photo_file_ext(self):
        tmp = os.path.splitext(self.photo_file_name)
        return tmp[-1]
class Car(CarBase):
    passenger_seats_count = ''
    def __init__(self, brand, photo_file_name, carrying, passenger_seats_count):
        super().__init__(brand,photo_file_name,carrying)
        self.passenger_seats_count = int(passenger_seats_count)
        Car.car_type = 'car'


class Truck(CarBase):
    car_type = 'truck'
    body_length =0.0
    body_width = 0.0
    body_height = 0.0
    def __init__(self, brand, photo_file_name, carrying, body_whl):
        try:
            tmp = body_whl.split('x')
            if (body_whl != '')  and len(tmp) == 3:
                tmp = body_whl.split('x')
                Truck.body_length = float(tmp[0])
                Truck.body_height = float(tmp[2])
                Truck.body_width = float(tmp[1])
                super().__init__(brand, photo_file_name, carrying)
                self.body_whl = body_whl
            else:
                super().__init__(brand, photo_file_name, carrying)
                self.body_whl = body_whl
                Truck.body_length = 0.0
                Truck.body_width = 0.0
                Truck.body_height = 0.0
        except ValueError:
            pass

    def get_body_volume(self):
        if(self.body_whl!=''):
            tmp = self.body_whl.split('x')
            Truck.body_length = float(tmp[0])
            Truck.body_height = float(tmp[2])
            Truck.body_width = float(tmp[1])
            return Truck.body_length*Truck.body_height*Truck.body_width
        else:
            return 0



class SpecMachine(CarBase):
    extra = ''
    def __init__(self, brand, photo_file_name, carrying, extra):
        super().__init__(brand, photo_file_name, carrying)
        SpecMachine.extra = extra
        SpecMachine.car_type = 'spec_machine'

def get_car_list(csv_filename):
    car_list = []
    try:
        with open(csv_filename) as csv_fd:
            reader = csv.reader(csv_fd, delimiter=';')
            next(reader)  # пропускаем заголовок

            for row in reader:
               try:
                   tmp = analizator(row)
                   if type(tmp) in [Car,Truck,SpecMachine]:
                       car_list.append(tmp)
               except (IOError,TypeError):
                   pass

        return car_list
    except (IOError,TypeError):
        return []


def analizator(row):
    if len(row)!=0:

        if row[0] == '':
            return 0
        elif row[0] == 'car':
            if row[1]!=''and  row[2]!=''and row[3]!= 0:
                tmp = os.path.splitext(row[3])
                if tmp[-1] in ['.jpg','.jpeg','.png','.gif']:
                    if row[5]!='' and row[4] =='' and row[6] == '' :
                        car = Car(row[1],row[3],row[5],row[2])
                      #  print(car.car_type, car.brand, car.photo_file_name, car.carrying, car.passenger_seats_count,sep='\n')
                        return car

                    else:
                        return -1
                else:
                    return -1
        elif row[0] == 'truck':
            if row[1] != '' and row[2] == '' and row[3] != 0:
                tmp = os.path.splitext(row[3])
                if tmp[-1] in ['.jpg', '.jpeg', '.png', '.gif']:
                    if row[5] != '' and row[6] == '':
                            try:
                                if row[4] == '':
                                    truck = Truck(row[1], row[3], row[5], row[4])
                                   # print(truck.car_type, truck.brand, truck.photo_file_name, truck.body_length,
                                    #      truck.body_width, truck.body_height, sep='\n')
                                    return truck
                                tmp = row[4].split('x')
                                Truck.body_length = float(tmp[0])
                                Truck.body_height = float(tmp[2])
                                Truck.body_width = float(tmp[1])
                                truck =Truck(row[1],row[3],row[5],row[4])
                               # print(truck.car_type, truck.brand, truck.photo_file_name, truck.body_length,
                                    #  truck.body_width, truck.body_height, sep='\n')
                                return truck
                            except (ValueError,TypeError):
                                return -1

                        #
                    else:
                        return -1
                else:
                    return -1
        elif row[0] == 'spec_machine':
            if row[1] != '' and row[2] == '' and row[3] != 0:
                tmp = os.path.splitext(row[3])
                if tmp[-1] in ['.jpg', '.jpeg', '.png', '.gif']:
                    if row[5] != '' and row[6] != '':

                        spec_machine = SpecMachine(row[1],row[3],row[5],row[6])
                        return spec_machine
                       # print(spec_machine.car_type, spec_machine.brand, spec_machine.carrying,spec_machine.photo_file_name, spec_machine.extra, sep = '\n')
                    else:
                        return -1
                else:
                    return -1#  print(spec_machine1.car_type, spec_machine1.brand, spec_machine1.carrying,spec_machine1.photo_file_name, spec_machine1.extra, sep='\n')

        else:
            return -1
    else:
        return -1
#test = ['car', 'Nissan xTtrail', '4', 'f1.jpeg', '', '2.5', '']
#analizator(test)
tmp = get_car_list(csv_filename)
for i in tmp:
    if type(i) == Truck:
        print(i.carrying,i.brand, i.body_whl)
# print(tmp[2].body_whl)
# print(tmp[1].brand)
# print(tmp[1].carrying)
# truck =Truck('Nissan', 't1.jpg', '2.5', '2.4x2.3x2x5')
# print(truck.body_width)
# print(truck.body_height)
# print(truck.body_length)