#include <iostream>
#include <queue>
#include <fstream>
#include <string>
#include <ctime>
#include <iomanip>
using namespace std;

class Check 
{
private:
    int id;
    int stationNumber;
    double liters;
    int hour;
    int minute;
public:
    Check(int id, int stationNumber, double liters, int hour, int minute)
    {
        this->id = id;
        this->stationNumber = stationNumber;
        this->liters = liters;
        this->hour = hour;
        this->minute = minute;
    }
    int getId()
    {
        return id;
    }
    int getStationNumber()
    {
        return stationNumber;
    }
    double getLiters()
    {
        return liters;
    }
    int getHour()
    {
        return hour;
    }
    int getMinute()
    {
        return minute;
    }
};

class GasStation 
{
private:
    int stationNumber;
    string fuelType;
    double fuelCapacity;
    double price;
    int counter;
public:
    GasStation(int stationNumber, string fuelType, double fuelCapacity, double price)
    {
        this->stationNumber = stationNumber;
        this->fuelType = fuelType;
        this->fuelCapacity = fuelCapacity;
        this->price = price;
        this->counter = 0;
    }
    int getStationNumberionNumber()
    {
        return this->stationNumber;
    }
    string getFuelType()
    {
        return this->fuelType;
    }
    double getfuelCapacity()
    {
        return this->fuelCapacity;
    }
    double getPrice()
    {
        return this->price;
    }
    void newFillUp(double liters) 
    {
        counter++;
        fuelCapacity -=liters;
    }
    int getCount()
    {
        return counter;
    }
};

class AZS
{
private:
    GasStation** gasStations;
    queue <Check> checks;
    int statSize;
public:
    void getResult()
    {
        double averageFuel=0;
        double revenue = 0;
        int checksCount = checks.size();
        ofstream file("Result.txt", ios::out);
        while (!checks.empty())
        {
            Check c=checks.front();  
            file << "Номер клиента: " << c.getId() << endl;
            file << "Номер колонки: " << c.getStationNumber() << endl;
            file << "Марка топлива: " << gasStations[c.getStationNumber()]->getFuelType() << endl;
            file << "Объем купленного бензина: " << c.getLiters() << " Л" << endl;
            file << "Цена за литр: " << gasStations[c.getStationNumber()]->getPrice() << " руб" << endl;
            file << "Время покупки: " << c.getHour() <<"ч"<<":"<< c.getMinute() <<"м"<<endl;
            file << "ИТОГ: " << c.getLiters()*(*gasStations[c.getStationNumber()]).getPrice() << " руб" << endl;
            file << endl;
            averageFuel +=c.getLiters();
            revenue += c.getLiters()*(*gasStations[c.getStationNumber()]).getPrice();
            checks.pop(); //del
        }
        int max = 0;
        for (int i = 0; i < statSize; i++)
        {
            if (gasStations[i]->getCount() > gasStations[max]->getCount())
            {
                max = i;
            }
        }
        file <<"Наиболее часто заправляемая марка топлива: "<<gasStations[max]->getFuelType()<<endl;
        file << "Выручка АЗС за день: " << revenue << " руб" << endl;
        file << "Среднее количество топлива, заправляемого клиентами в течении 1 рабочего дня: " << averageFuel / checksCount << endl;
        file.close();
    }

    AZS(string fileName)
    {
        queue <GasStation*> g;
        fstream file(fileName, ios::in);
        string fuelType;
        double fuelCapacity;
        int stationNumber;
        double price;
        while (!file.eof())  //заход в файл и начало записи колонки
        {
            file >> fuelType >> stationNumber >> fuelCapacity >> price;
            g.push(new GasStation(stationNumber, fuelType, fuelCapacity, price));
        }
        this->statSize = g.size();  //колво колонок
        gasStations = new GasStation*[g.size()];
        for (int i = 0; i < this->statSize; i++)
        {
            gasStations[i] = g.front();
            g.pop();
        }
        file.close();
    }
    void Start(int n)
    {
        srand(time(0));
        int count = 0;
        for (int j = 0; j < 24; j++) {
            int randomMinute = rand() % 60;
            int randomMinuteTwo = rand() % 60;
            for (int k = 0; k < 60; k++)
            {
                if (randomMinute == k || randomMinuteTwo == k ) {
                    for (int i = 0; i < n; i++)
                    {
                    int p = rand() % statSize;
                    int l = (rand() % 50) + 1;
                    count++;
                    int hour = j;
                    int minute = k;
                    this->checks.push(Check(count, p, l, hour, minute));
                        if (gasStations[p]->getfuelCapacity() - l >= 0)
                        {
                            this->gasStations[p]->newFillUp(l);
                        }
                    }
                }
            }
        }
    }

};

int main(void)
{
    AZS azs("gasoline.txt");
    azs.Start(1);
    azs.getResult();
};
