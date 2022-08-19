#include<iostream>
#include<fstream>
#include<string>
#include<conio.h>
#include<process.h>
#include<stdio.h>
using namespace std;

class Productinfo //Class
{
    int BarcodeID;
    char Name[30];
    char Brand[25];
    int Category;
    double Price;
    char Country[25];
    string Expiration;
public:
    void getdata();
    void display();
    int getPrice() { return Price; }
    int getid() { return BarcodeID; }
    int getCategory() { return Category; }
    string getExpiration() { return Expiration; }
}x;

void Productinfo::getdata()
{
    cout << "Enter Barcode Id: ";
    cin >> BarcodeID;
    cin.ignore();
    cout << "Enter Product's Name: ";
    cin.getline (Name, 30);
    cout << "Enter Product's Brand: ";
    cin >> Brand;
    cout << "Enter Product's Category:\n1.Beverages & Drinks\n2.Household & Cleaning\n3.Canned & Jarred\n4.Fats & Oils\n5.Beauty & Health\n6.Condiments & Spices\n7.Dairy & Eggs\n8.Meats & Frozen.\n9.Snacks & Sweets\n10.Fruits & Vegetables\n11.Stationary & Books \n12.Other...\nChoice:  ";
    cin >> Category;
    cout << "Enter Product's Price: ";
    cin >> Price;
    cout << "Enter Country of Manufacture: ";
    cin >> Country;
    cout << "Enter Expiratio Date: ";
    cin >> Expiration;
}
void Productinfo::display()
{
    cout << "========================================================================\n";
    cout << "Barcode Id: " << BarcodeID << "\tName: " << Name << "\n";
    cout << "Brand: " << Brand << "\tCategory: " << Category << "\tPrice: " << Price << "$" << "\n";
    cout << "Country of Manufacture: " << Country << "\tExpiration Date: " << Expiration << "\n"; 
    cout << "========================================================================\n";
}

void Menu();
void Options();
void Search();
void Add();
void Edit();
void View();
void Categorize();
void Delete();
void Bin();

int main()
{
    int n, idnum, i;
    fstream data("productinfo.txt", ios::in | ios::out | ios::binary);
    system("CLS");
    Menu();
    _getch();
    return 0;
}

void Options() //File Maintainance (Menu)
{
    cout << "\n\t[...System Menu...]\n"; 
    cout << "\t1. Search Product Information!\n";
    cout << "\t2. Add Product Information!\n";
    cout << "\t3. Edit Product Information!\n";
    cout << "\t4. View All Products Information!\n";
    cout << "\t5. Check Products By Category!\n";
    cout << "\t6. Delete Product Information!\n";
    cout << "\t7. View Deleted Product Information!\n";
    cout << "\t0. EXIT!\n";
    cout << "\nEnter Choice!: ";
}

void Menu()
{
    int ch;
    Options();
    cin >> ch;
    while (ch)
    {
        switch (ch)
        {
        case 1: Search();
            break;
        case 2: Add();
            break;
        case 3: Edit();
            break;
        case 4: View();
            break;
        case 5: Categorize();
            break;
        case 6: Delete();
            break;
        case 7: Bin();
            break;
        default: cout << "Error! Wrong Input Value, Please Enter The Correct Value!";
        }
        cout<<endl;
        system("pause");
        system("CLS");
        Options();
        cin >> ch;
    }
}

void Search() //Searching product's information by barcode id.
{
    ifstream fin("productinfo.txt", ios::in | ios::binary);
    int idnum, i = 0;
    char found = 'z';
    cout << "\nEnter Barcode Id To Search: ";
    cin >> idnum;

    while (fin.read((char*)&x, sizeof(x)))
    {
        if (x.getid() == idnum)
        {
            x.display();
            found = 'y';
        }
        i++;
    }
    if (found == 'z') 
    cout << "\nThe input barcode id. " << idnum << " is not in the system!\n";
    fin.close();
}

void Add() //Adding new product barcode id and information.
{
    char ch = 'y';
    ofstream dataout("productinfo.txt", ios::out | ios::app | ios::binary);
    while (ch == 'y' || ch == 'Y')
    {
        x.getdata();
        dataout.write((char*)&x, sizeof(x));
        cout << "\nDo you want to add more product's information? (Y/N): ";
        cin >> ch;
        system("CLS");
    }
    cout << "\nProduct Information Added!\n";
    dataout.close();
}

void Edit() //Editing existing product's information.
{
    fstream data("productinfo.txt", ios::in | ios::out | ios::binary);
    int idnum;
    char found = 'z';
    data.seekg(0);
    cout << "\nEnter the barcode id of the product's information to be edited: ";
    cin >> idnum;

    while (data)
    {
        int loc = data.tellg();
        data.read((char*)&x, sizeof(x));
        if (x.getid() == idnum)
        {
            x.getdata();
            found = 'y';
            data.seekg(loc);
            data.write((char*)&x, sizeof(x));
            cout << "\nYour proudct's information of the barcode id: " << idnum
                << " has been updated!"<<endl;
        }
    }
    if (found == 'z') 
    cout << "\nThe Category " << idnum << " is not in the system!\n";
    data.close();
}

void View() //Viewing existing product's information.
{
    ifstream fin("productinfo.txt", ios::in | ios::binary);
    while (fin.read((char*)&x, sizeof(x)))
    {
        x.display();
    }
    fin.close();
}

void Categorize() //Categorize products by Categorize.
{
    ifstream fin("productinfo.txt", ios::in | ios::binary);
    int std;
    char found = 'z';
    cout << "Enter Product's Category:\n1.Beverages & Drinks\n2.Household & Cleaning\n3.Canned & Jarred\n4.Fats & Oils\n5.Beauty & Health\n6.Condiments & Spices\n7.Dairy & Eggs\n8.Meats & Frozen.\n9.Snacks & Sweets\n10.Fruits & Vegetables\n11.Stationary & Books \n12.Other...\nChoice:  ";
    cin >> std;

    while (fin.read((char*)&x, sizeof(x)))
    {
        if (x.getCategory() == std)
        {
            x.display();
            found = 'y';
        }
    }
    if (found == 'z') 
    cout << "\nThe Category: " << std << " is not in the system!\n";
    fin.close();
}

void Delete() //Deleting existing product's information.
{
    int idnum;
    char found = 'z';
    fstream data("productinfo.txt", ios::in | ios::out | ios::binary | ios::app);
    ofstream dataout("temp.txt", ios::out | ios::binary | ios::app);
    ofstream out("bin.txt", ios::out | ios::binary | ios::app);
    cout << "\nEnter the barcode id of which product's information is to be deleted: ";
    cin >> idnum;

    while (data.read((char*)&x, sizeof(x)))
    {
        if (x.getid() == idnum)
        {
            out.write((char*)&x, sizeof(x));
            found = 'y';
        }
        else
        {
            dataout.write((char*)&x, sizeof(x));
        }
    }
    if (found == 'z')
    cout << "\nThe barcode id:" << idnum << " is not in the system!\n";
    data.close();
    dataout.close();
    remove("productinfo.txt");
    rename("temp.txt", "productinfo.txt");
}

void Bin() //Bin of deleted product's information.
{
    ifstream fin("bin.txt", ios::in | ios::binary);
    while (fin.read((char*)&x, sizeof(x)))
    {
        x.display();
    }
    fin.close();
}









