//
//  main.cpp
//  parking management
//
//

#include<ncurses.h>
#include<string>
#include<iostream>
#include<fstream>
#include<ctime>
using namespace std;

class EarnedMoney{
    private:
        int carType;
        int busType;
        int truckType;
        int bikeType;
        int cycleType;
        int total;
    public:
        EarnedMoney(){
            this->carType=0;
            this->busType=0;
            this->truckType=0;
            this->bikeType=0;
            this->cycleType=0;
            this->total=0;
        } 
        void setEarnedMoney(int carType,int busType,int truckType,int bikeType,int cycleType,int total){
            this->carType=carType;
            this->busType=busType;
            this->truckType=truckType;
            this->bikeType=bikeType;
            this->cycleType=cycleType;
            this->total=total;
        }
        void showEarnedMoney(){
            cout<<"\n--------------------------------------------------------------\n";
            cout<<setw(10)<<"Car|"<<setw(10)<<"Bus|"<<setw(10)<<"Truck|"<<setw(10)<<"Bike|"<<setw(10)<<"Cycle|"<<setw(10)<<"Total|";
            cout<<"\n--------------------------------------------------------------\n";
            cout<<setw(9)<<this->carType<<"|"<<setw(9)<<this->busType<<"|"<<setw(9)<<this->truckType<<"|"<<setw(9)<<this->bikeType<<"|"<<setw(9)<<this->cycleType<<"|"<<setw(9)<<this->total<<"|";
            cout<<"\n--------------------------------------------------------------\n";
        }
        void getAllEarnedMoney();
        void operator + (EarnedMoney &newMoney);
};

void EarnedMoney:: getAllEarnedMoney(){
    ifstream fin;
    fin.open("EarnedMoney.txt",ios_base::in|ios_base::binary);
    if(!fin){
        cout<<"\nFile Not Found";
    }
    else{
        fin.read((char*)this,sizeof(*this));
    }
}

void EarnedMoney:: operator +(EarnedMoney &newMoney){
    carType+=newMoney.carType;
    busType+=newMoney.busType;
    truckType+=newMoney.truckType;
    bikeType+=newMoney.bikeType;
    cycleType+=newMoney.cycleType;
    total+=newMoney.total;
}

class VehicleType{
    private:
        char vehicleTypeName[50];
    public:
        VehicleType(){
            strcpy(vehicleTypeName,"Vehicle");
        }
        void setVehivleType(EarnedMoney &earnedMoney){
            while(1){
                cout<<"\nSelect Vehicle Type:";
                cout<<"\n1. Car  2. Bus  3. Truck  4. Bike  5. Cycle\n";
                int vehicleType;
                cin>>vehicleType;
                if(vehicleType==1){
                    strcpy(this->vehicleTypeName,"Car");
                    earnedMoney.setEarnedMoney(100,0,0,0,0,100);
                    break;
                }
                else if(vehicleType==2){
                    strcpy(vehicleTypeName,"Bus");
                    earnedMoney.setEarnedMoney(0,200,0,0,0,200);
                    break;
                }
                else if(vehicleType==3){
                    strcpy(vehicleTypeName,"Truck");
                    earnedMoney.setEarnedMoney(0,0,400,0,0,400);
                    break;
                }
                else if(vehicleType==4){
                    strcpy(vehicleTypeName,"Bike");
                    earnedMoney.setEarnedMoney(0,0,0,50,0,50);
                    break;
                }
                else if(vehicleType==5){
                    strcpy(vehicleTypeName,"Cycle");
                    earnedMoney.setEarnedMoney(0,0,0,0,20,20);
                    break;
                }
                else{
                    cout<<"\nInvalid Choice:";
                }
            }
        }
        void showVehicleType(){
            cout<<"Type: "<<vehicleTypeName<<setw(6)<<" | ";
            }
};

class Vehicle:public VehicleType{
    private:
        int vehicleNo;
        char state[60];
        char description[100];
        char createdBy[50];
        char lastUpdatedBy[50];
        char createdDateTime[50];
        char lastUpdatedDateTime[50];
        char stillParked[10];
        EarnedMoney earnedMoney;
    public:
        Vehicle(){
            vehicleNo=0;
            strcpy(state,"default");
            strcpy(description,"default");
            strcpy(createdBy,"AM");
            strcpy(lastUpdatedBy,"AM");
            time_t tt;
            time(&tt);
            strcpy(createdDateTime,asctime(localtime(&tt)));
            strcpy(lastUpdatedDateTime,asctime(localtime(&tt)));
            strcpy(stillParked,"default");
        }
        void setVehicle(){
            cout<<"\nEnter The Vehicle Number: ";
            cin>>vehicleNo;
            try{
                if(vehicleNo<1000 || vehicleNo>9999){
                    throw vehicleNo;
                }
            }
            catch(int v){
                cout<<"\nEnter Valid Vehicle Number\n";
                setVehicle();
                return;
            }
            cin.ignore();
            cout<<"\nEnter The State which Vehicle Belongs To: ";
            cin.getline(state,50);
            cout<<"\nEnter The Vehicle Description: ";
            cin.getline(description,100);
            strcpy(createdBy,"AM");
            strcpy(lastUpdatedBy,"AM");
            setVehivleType(earnedMoney);
            time_t tt;
            time (&tt);
            strcpy(createdDateTime,asctime(localtime(&tt)));
            strcpy(lastUpdatedDateTime,asctime(localtime(&tt)));
            strcpy(stillParked,"Yes");
        }
        void showVehicle(){
            cout<<"\n--------------------------------------------------------------\n";
            cout<<"Vehicle No.: "<<vehicleNo<<setw(6)<<" | "<<"State: "<<state<<setw(6)<<" | "<<"Description: "<<description<<setw(6)<<" | ";
            showVehicleType();
            cout<<"Entry by: "<<createdBy<<setw(6)<<" | "<<"Updated by: "<<lastUpdatedBy<<setw(6)<<" | ";
            cout<<"Creation Time: "<<createdDateTime<<" | "<<"Updation Time: "<<lastUpdatedDateTime<<" | "<<"Parked: "<<stillParked<<endl;
            cout<<"\n--------------------------------------------------------------\n";
        }
        void addVehicle();
        void getAllVehicleList();
        void searchVehicle(int vno);
        void deleteVehicle(int vno);
        void updateVehicle(int vno);
};

void Vehicle:: addVehicle(){
    ofstream fout;
    fout.open("VehicleData.txt",ios_base::app|ios_base::binary);
    getchar();
    fout.write((char*)this,sizeof(*this));
    fout.close();

    EarnedMoney em;
    em.getAllEarnedMoney();
    this->earnedMoney+em;
    fout.open("EarnedMoney.txt",ios_base::out|ios_base::binary);
    fout.write((char*)(&this->earnedMoney),sizeof(this->earnedMoney));
    fout.close();
    cout<<"\nRecord Added Successfully\n";
}

void Vehicle:: getAllVehicleList(){
    ifstream fin;
    int nor=0;
    fin.open("VehicleData.txt",ios_base::in|ios_base::binary);
    if(!fin){
        cout<<"\nFile Not Found\n";
    }
    else{
        cout<<endl;
        fin.read((char*)this,sizeof(*this));
        while(!fin.eof()){
            this->showVehicle();
            nor++;
            fin.read((char*)this,sizeof(*this));
        }
        fin.close();
        if(nor==0){
            cout<<"\nFile Has No Record\n";
        }
    }
}

void Vehicle:: searchVehicle(int vno){
    ifstream fin;
    int nor=0;
    fin.open("VehicleData.txt",ios_base::in|ios_base::binary);
    if(!fin){
        cout<<"\nFile Not Found\n";
    }
    else{
        fin.read((char*)this,sizeof(*this));
        while(!fin.eof()){
            if(this->vehicleNo==vno){
                this->showVehicle();
                nor=1;
                break;
            }
            fin.read((char*)this,sizeof(*this));
        }
        fin.close();
        if(nor==0){
            cout<<"\nRecord Not Found\n";
        }
    }
}

void Vehicle:: deleteVehicle(int vno){
    ifstream fin;
    ofstream fout;
    int flag=0;
    fin.open("VehicleData.txt",ios_base::in|ios_base::binary);
    if(!fin){
        cout<<"\nFile Not Found";
    }
    else{
        fin.read((char*)this,sizeof(*this));
        fout.open("TempVehicleData.txt",ios_base::out|ios_base::binary);
        while(!fin.eof()){
            if(this->vehicleNo==vno){
                flag=1;
            }
            else{
                fout.write((char*)this,sizeof(*this));
            }
            fin.read((char*)this,sizeof(*this));
        }
        fin.close();
        fout.close();
        if(flag==0){
            cout<<"\nRecord Not Found Hence Can Not delete\n";
            remove("TempVehicleData.txt");
        }
        else{
            cout<<"\nRecord Deleted\n";
            remove("VehicleData.txt");
            rename("TempVehicleData.txt","VehicleData.txt");
        }
    }
}

void Vehicle:: updateVehicle(int vno){
    fstream foutIn;
    int flag=0;
    foutIn.open("VehicleData.txt",ios_base::in|ios_base::out|ios_base::ate|ios_base::binary);
    foutIn.seekg(0);
    if(!foutIn){
        cout<<"\nFile Not Found";
    }
    else{
        foutIn.read((char*)this,sizeof(*this));
        while(!foutIn.eof()){
            if(this->vehicleNo==vno){
                cout<<"\nUpdating The Data:";
                cout<<"\nEnter The Vehicle Number: ";
                cin>>vehicleNo;
                cin.ignore();
                cout<<"\nEnter The State which Vehicle Belongs To: ";
                cin.getline(state,50);
                cout<<"\nEnter The Vehicle Description: ";
                cin.getline(description,100);
                strcpy(createdBy,"AM");
                cout<<"\nEnter The Name Of The Person Who Edited The Record: ";
                cin.getline(lastUpdatedBy,50);
                cout<<"\nIs Vehicle Parked: ";
                cin.getline(stillParked, 10);
                time_t tt;
                time (&tt);
                strcpy(lastUpdatedDateTime,asctime(localtime(&tt)));

                foutIn.seekp(int(foutIn.tellp())-sizeof(*this));
                foutIn.write((char*)this,sizeof(*this));
                cout<<"\nRecord Updated Successfully\n";
                flag=1;
                break;
            }
            foutIn.read((char*)this,sizeof(*this));
        }
        foutIn.close();
        if(flag==0){
            cout<<"\nRecord Not Found\n";
        }
    }
}

int menu(){
    int ch;
    cout<<"\n***************    MENU     *************** ";
    cout<<"\n1. Add Vehicle";
    cout<<"\n2. Search Vehicle";
    cout<<"\n3. Delete Vehicle";
    cout<<"\n4. Update Vehicle";
    cout<<"\n5. List All Vehicle";
    cout<<"\n6. Check Earned Money";
    cout<<"\n7. Exit";
    cout<<"\nEnter Your Choice: ";
    cin>>ch;
    return(ch);
}

int main(){
    Vehicle vehicle;
    EarnedMoney earnedMoney;
    int breakInfiniteloop=0,vno;
    cout<<"             ************************************************\n\n";
    cout<<"                     Welcome to Parking Management\n\n";
    cout<<"                  \n\n";
    cout<<"             ************************************************\n\n\n";
    while(1){
        switch(menu()){
            case 1:
                vehicle.setVehicle();
                vehicle.addVehicle();
                getchar();
                break;
            case 2:
                cout<<"\nEnter The Vehicle Number To Searched: ";
                cin>>vno;
                vehicle.searchVehicle(vno);
                getchar();
                break;
            case 3:
                cout<<"\nEnter The Vehicle Number To Deleted: ";
                cin>>vno;
                vehicle.deleteVehicle(vno);
                getchar();
                break;
            case 4:
                cout<<"\nEnter The Vehicle Number To Updated: ";
                cin>>vno;
                vehicle.updateVehicle(vno);
                getchar();
                break;
            case 5:
                vehicle.getAllVehicleList();
                getchar();
                break;
            case 6:
                earnedMoney.getAllEarnedMoney();
                earnedMoney.showEarnedMoney();
                getchar();
                break;
            case 7:
                breakInfiniteloop=1;
                break;
            default:
                cout<<"\nInvalid Choice\n";
                getchar();
        }
        if(breakInfiniteloop==1){
            break;
        }
    }
    cout<<endl;
    return 0;
}
