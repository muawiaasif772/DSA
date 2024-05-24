#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

class telephone {
    char name[10];
    char address[30];
    int pho;
public:
    void get();
    void display();
    int getpho();
};

void telephone::get() {
    cout << "\nEnter Name: ";
    cin.ignore();
    cin.getline(name, 20);
    cout << "Enter Address: ";
    cin.getline(address, 20);
    cout << "Enter Phone Number: ";
    cin >> pho;
}

void telephone::display() {
    cout << "\nName: " << name;
    cout << "\nAddress: " << address;
    cout << "\nPhone Number: " << pho;
}

int telephone::getpho() {
    return pho;
}

void write_telephone() {
    telephone tel;
    ofstream outFile;
    outFile.open("telephone.dat", ios::binary | ios::app);
    tel.get();
    outFile.write(reinterpret_cast<char*>(&tel), sizeof(telephone));
    outFile.close();
    cout << "\n\nTelephone Directory Has Been Updated...";
    cin.ignore();
    cin.get();
}

void display_all() {
    telephone tel;
    ifstream inFile;
    inFile.open("telephone.dat", ios::binary);
    if (!inFile) {
        cout << "File could not be opened! Press any key...";
        cin.ignore();
        cin.get();
        return;
    }
    cout << "\n\n\n\t\tDISPLAY ALL RECORDS!!!\n\n";
    while (inFile.read(reinterpret_cast<char*>(&tel), sizeof(telephone))) {
        tel.display();
        cout << "\n\n====================================\n";
    }
    inFile.close();
    cin.ignore();
    cin.get();
}

void display_sp(int n) {
    telephone tel;
    ifstream inFile;
    inFile.open("telephone.dat", ios::binary);
    if (!inFile) {
        cout << "File could not be opened! Press any key...";
        cin.ignore();
        cin.get();
        return;
    }
    bool ali = false;
    while (inFile.read(reinterpret_cast<char*>(&tel), sizeof(telephone))) {
        if (tel.getpho() == n) {
            tel.display();
            ali = true;
        }
    }
    inFile.close();
    if (!ali)
        cout << "\n\nRecord does not exist";
    cin.ignore();
    cin.get();
}

void modify_telephone(int n) {
    bool found = false;
    telephone tel;
    fstream File;
    File.open("telephone.dat", ios::binary | ios::in | ios::out);
    if (!File) {
        cout << "File could not be opened Press any key...";
        cin.ignore();
        cin.get();
        return;
    }
    while (!File.eof() && !found) {
        File.read(reinterpret_cast<char*>(&tel), sizeof(telephone));
        if (tel.getpho() == n) {
            tel.display();
            cout << "\n\nPlease Enter The New Details" << endl;
            tel.get();
            int pos = (-1) * static_cast<int>(sizeof(tel));
            File.seekp(pos, ios::cur);
            File.write(reinterpret_cast<char*>(&tel), sizeof(telephone));
            cout << "\n\tRecord Updated";
            found = true;
        }
    }
    File.close();
    if (!found)
        cout << "\nRecord Not Found";
    cin.ignore();
    cin.get();
}

void delete_telephone(int n) {
    telephone tel;
    ifstream inFile;
    inFile.open("telephone.dat", ios::binary);
    if (!inFile) {
        cout << "File could not be opened! Press any key...";
        cin.ignore();
        cin.get();
        return;
    }
    ofstream outFile;
    outFile.open("Temp.dat", ios::binary);
    inFile.seekg(0, ios::beg);
    while (inFile.read(reinterpret_cast<char*>(&tel), sizeof(telephone))) {
        if (tel.getpho() != n) {
            outFile.write(reinterpret_cast<char*>(&tel), sizeof(telephone));
        }
    }
    outFile.close();
    inFile.close();
    remove("telephone.dat");
    rename("Temp.dat", "telephone.dat");
    cout << "\n\tRecord Deleted...";
    cin.ignore();
    cin.get();
}

int main() {
    char ch;
    int num;
    cout.setf(ios::fixed | ios::showpoint);
    cout << setprecision(2);
    do {
        system("cls");  


        cout << "\n";
        cout << "\n\t\t1. Add Telephone Record";
        cout << "\n\t\t2. display Records";
        cout << "\n\t\t3. Search Telephone Records";
        cout << "\n\t\t4. Modify Record";
        cout << "\n\t\t5. Delete Record";
        cout << "\n\t\t6. EXIT";
        cout << "\n";
        cout << "\n\t\tPlease Enter Your Choice (1-6): ";
        cin >> ch;
        system("cls");  
        switch (ch) {
        case '1': write_telephone(); break;
        case '2': display_all(); break;
        case '3': cout << "\n\tPlease Enter Phone Number: "; cin >> num;
         display_sp(num); break;
        case '4': cout << "\n\tPlease Enter Phone Number: "; cin >> num; modify_telephone(num); break;
        case '5': cout << "\n\tPlease Enter Phone Number: "; cin >> num; delete_telephone(num); break;
        case '6': 
        exit(0);
        }
    } while (ch != '6');  

    return 0;
}