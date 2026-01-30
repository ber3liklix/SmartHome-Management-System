#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

class Device
{
private:
    string ID;
    string brand;
protected:
    string name;
    bool situation;
public:
    Device()
    {
        ID="";
        brand="";
        name="";
        situation=0;
    }
    Device(string i,string b,string n,bool s)
    {
        ID=i;
        brand=b;
        name=n;
        situation=s;
    }
    string getName()
    {
        return name;
    }
    string getId()
    {
        return ID;
    }
    string getBrand()
    {
        return brand;
    }
    void setBrand(string x)
    {
        brand=x;
    }
    void setId(string x)
    {
        ID=x;
    }
    void setName(string x)
    {
        name=x;
    }
    virtual void work()=0;
    void open()
    {
        cout<<"The device is opened..."<<endl;
    }
    void close()
    {
        cout<<"The device is closed..."<<endl;
    }
    virtual void print()=0;
    virtual ~Device(){}
};
class airCondition:public Device
{
private:
    int temperature;
    int mod;
    int energy;
public:
    airCondition():Device()
    {
        temperature=0;
        mod=0;
        energy=0;
    }
    airCondition(string i,string b,string n,bool a ,int t,int m,int e):Device(i,b,n,a)
    {
        temperature=t;
        mod=m;
        energy=e;
    }
    void work() override
    {
        cout<<"The mod of the air conditioner is: "<<mod<<endl;
    }
    void print() override
    {
        cout<<"The name of the air conditioner is: "<<name<<endl;
        cout<<"The temperature of the air conditioner is: "<<temperature<<endl;
    }
    void increaseTemp(int x)
    {
        if(temperature<18)
        {
            throw "Error!";
        }
        temperature+=x;
    }
    void decreaseTemp(int x)
    {
        try {
            temperature-=x;
            if(temperature<18)
            {
                throw "Error!";
            }
        } catch (const char *err) {
            cerr<<err<<endl;
        }
    }
    void changeMod(int a)
    {
        if(a<=0 || a>3)
        {
            cout<<"Your choice is wrong."<<endl;
            while(a<=0 || a>3)
            {
                cout<<"Please enter the valid mod value (1-3)"<<endl;
                cin>>a;
            }
        }
        cout<<"The mode changed successfully!"<<endl;
    }
};
class Lamp:public Device
{
private:
    int light;
    string color;
    double wat;
public:
    Lamp():Device()
    {
        light=0;
        color="";
        wat=0.0;
    }
    Lamp(string i,string b,string n,bool a,int l,string c,double w):Device(i,b,n,a)
    {
        light=l;
        color=c;
        wat=w;
    }
    void work() override
    {
        cout<<"The lamp's color is: "<<color<<endl;
        cout<<"The lamp's light level is: "<<light<<endl;
    }
    void print() override
    {
        cout<<"The name of the lamp is: "<<name<<endl;
        cout<<"The color is: "<<color<<endl;
        cout<<"The total energy consumpt is: "<<wat<<endl;
        cout<<"The light percent is: "<<light<<endl;
    }
    void file()
    {
        ofstream f("devices.txt");
        string str;
        str = "Lamp: " + getId() + " | Situation: " + color + ", " + to_string(light) + "%, " + to_string(wat) + "W";
        if (!f.is_open())
        {
            cerr<<"Error"<<endl;
        }
        f<<str<<endl;
    }
    void setLight(int newLight)
    {
        if(newLight<0 || newLight>100)
        {
            cerr<<"Error!"<<endl;
            while(newLight<0 || newLight>100)
            {
                cout<<"Enter the valid light percent: "<<endl;
                cin>>newLight;
            }
        }
        light=newLight;
    }
    void setColor(string c)
    {
        color=c;
        cout<<"The color changed succesfully to ->"<<color<<endl;
    }
    
};
class HomeControlSystem
{
private:
    vector<Device*> deviceslist;
    string log= "devices";
public:
    void addNewDevice(Device* nw)
    {
        deviceslist.push_back(nw);
    }
    void deleteDevice(string targetId)
        {
            for (auto it = deviceslist.begin(); it != deviceslist.end(); ++it)
            {
                if ((*it)->getId() == targetId)
                {
                    delete *it;
                    deviceslist.erase(it);
                    cout << "Device " << targetId << " deleted." << endl;
                    return;
                }
            }
            cout << "Device can not found." << endl;
        }
    void getList()
    {
        cout<<"\tAll Devices\t"<<endl;
        for(auto d: deviceslist)
        {
            d->print();
        }
    }
    void saveAllToLog()
    {
        ofstream f(log);
        if (!f.is_open()) {
            cerr << "Error!" << endl;
            return;
        }

        for (auto d : deviceslist) {
        
            f << "ID: " << d->getId() << " | Brand: " << d->getBrand() << " | Name: " << d->getName() << endl;
        }
        f.close();
        cout << "The all devices is saved to" << log<< endl;
    }
    ~HomeControlSystem()
    {
        for(auto d : deviceslist)
        {
            delete d;
        }
            deviceslist.clear();
        }
};
int main (void)
{
    HomeControlSystem myHome;

        cout << "Welcome to Berenis Home System!" << endl;
        Device* l1 = new Lamp("B07", "Philips", "Beren's Working Lamp", true, 75, "Sari", 12.5);
        Device* k1 = new airCondition("K01", "Mitsubishi", "Bedroom Air conditioner", false, 22, 2, 1500);

        myHome.addNewDevice(l1);
        myHome.addNewDevice(k1);
        myHome.getList();
        myHome.saveAllToLog();
        cout << "The device B07 is deleting.." << endl;
        myHome.deleteDevice("B07");
        cout << "The new list:" << endl;
        myHome.getList();

        return 0;
    
    
}
