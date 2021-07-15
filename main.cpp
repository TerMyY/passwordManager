#include <iostream>
#include <filesystem>
#include <fstream>
#include <vector>
#include "PasswordRecord.h"

using namespace std;
const char * MASTER_PASSWORD = "44599102";
string passwordsFolderName;
string loginDatesFolderName;
string encryptStatusFolderName;
string passwordsPath;
string loginDatesPath;
string encryptStatusPath;
string line;
ofstream passwordsFileWrite;
ifstream passwordsFileRead;
ofstream encryptStatusWrite;
ifstream encryptStatusRead;
vector<string> contents;
void show(ifstream& file);
void updateLastValidLogin();
void remove(string toDelete, int a, int b);
void sort(string toSort, int a, int b);
void encrypt();
void decrypt();
void search(string toSearch, int a, int b);
string cutString(string tocut, int a, int b);
enum Commands
{
 SHOW,
 SEARCH,
 SORT,
 ENCRYPT,
 DECRYPT,
 ADD,
 REMOVE,
 HELP,
 EXIT
};

int main()
{

    passwordsFolderName = "../passwords\\";
    loginDatesFolderName = "../loginDates\\";
    encryptStatusFolderName = "../encryptStatus\\";
    cout << "Please choose a file to open or create(only filename and its extension):" << endl;
        for(const auto & entry : filesystem::directory_iterator(passwordsFolderName))
        cout << entry.path() << endl;

    cin >> passwordsPath;

    loginDatesPath = loginDatesFolderName + "\\\\" + passwordsPath;
    encryptStatusPath = encryptStatusFolderName + "\\\\" + passwordsPath;
    passwordsPath = passwordsFolderName + "\\\\" + passwordsPath;

    cout << "Please enter master password:" << endl;

    string enteredPassword;
    passwordCheck:
    cin >> enteredPassword;

    if(enteredPassword == MASTER_PASSWORD) {

        updateLastValidLogin();
        commandCheck:
        passwordsFileWrite.close();
        passwordsFileRead.close();
        passwordsFileWrite.open(passwordsPath, ios::app);
        passwordsFileRead.open(passwordsPath);

        cout << "Insert command(Help to see them all):" << endl;
        Commands command;
        string input;
        cin >> input;
        if(input == "SHOW" || input == "Show" || input == "show")
            command = SHOW;
        else if(input == "SEARCH" || input == "Search" || input == "search")
            command = SEARCH;
        else if(input == "SORT" || input == "Sort" || input == "sort")
            command = SORT;
        else if(input == "ENCRYPT" || input == "Encrypt" || input == "encrypt")
            command = ENCRYPT;
        else if(input == "DECRYPT" || input == "Decrypt" || input == "decrypt")
            command = DECRYPT;
        else if(input == "ADD" || input == "Add" || input == "add")
            command = ADD;
        else if(input == "REMOVE" || input == "Remove" || input == "remove")
            command = REMOVE;
        else if(input == "HELP" || input == "Help" || input == "help" || input == "?")
            command = HELP;
        else if(input == "EXIT" || input == "Exit" || input == "exit")
            command = EXIT;
        else
        {
            cout << "No such command! " << endl;
            goto commandCheck;
        }

        string name;
        string categoryName;
        switch (command)
        {

            case SHOW:
            {
                show(passwordsFileRead);
                goto commandCheck;
            }

            case SEARCH:
            {
                string toSearch;
                cout << "Category name for search:" << endl;
                cin >> toSearch;
                search(toSearch, 7,8);
                goto commandCheck;
            }

            case SORT:
            {
                string toSort;
                cout << "Sort by what(Name | Category)?" << endl;
                cin >> toSort;
                if(toSort == "NAME" || toSort == "Name" || toSort == "name")
                    sort(toSort,1,2);
                if(toSort == "CATEGORY" || toSort == "Category" || toSort == "category")
                   sort(toSort,7,8);
                goto commandCheck;
            }
            case ENCRYPT:
            {
                encrypt();
                goto commandCheck;
            }
            case DECRYPT:
            {

                decrypt();
                goto commandCheck;
            }

            case ADD:
            {

                    string login;
                    string password;
                    cout << "Please specify the password's name:" << endl;
                    cin >> name;
                    cout << "Please specify the login:" << endl;
                    cin >> login;
                    cout << "Please specify the password:" << endl;
                    cin >> password;
                    cout << "Please specify password's category:" << endl;
                    cin >> categoryName;
                    Category category(categoryName);
                    PasswordRecord passwordRecord(name,login,password,category);
                    if(passwordsFileWrite.good())
                    {
                        passwordsFileWrite << passwordRecord;
                    }
                    cout << "Password record has been added." << endl;
                    goto commandCheck;

            }

            case REMOVE:
            {
                string toDelete;
                cout << "What do you want to delete(Name | Category)?" << endl;
                cin >> toDelete;
                if(toDelete == "NAME" || toDelete == "Name" || toDelete == "name")
                    remove(toDelete,1,2);
                if(toDelete == "CATEGORY" || toDelete == "Category" || toDelete == "category")
                    remove(toDelete,7,8);
                goto commandCheck;
            }
            case HELP:
            {
                cout << "SHOW\nSEARCH\nSORT\nENCRYPT\nDECRYPT\nADD\nREMOVE\nHELP\nEXIT" << endl;
                goto commandCheck;
            }

            case EXIT:
            {
                break;
            }

        }

    }
    else { cout << "Master password is incorrect, please try again." << endl; goto passwordCheck; }

}

string cutString(string tocut, int a, int b)
{
    int space = 0;
    string result;
    for(int i = 0; i < tocut.size(); i++)
    {
        if(tocut[i] == ' ')
        { space++; continue; }
        if(space == a)
            result += tocut[i];
        if(space == b)
            break;
    }
    return result;
}
void sort(string toSort, int a, int b) {
    if (passwordsFileRead.good()) {
        while (getline(passwordsFileRead, line)) {
            contents.push_back(line);
        }
    }
    for (int i = 0; i < contents.size() - 1; i++) {
        string contentsSort = cutString(contents[i], a, b);
        for (int j = i+1; j < contents.size(); j++) {
            string contentsNow = cutString(contents[j], a, b);
            if (contentsSort == contentsNow) {
                string temp = contents[i + 1];
                contents[i + 1] = contents[j];
                contents[j] = temp;
            }
        }
    }

    passwordsFileWrite.close();
    passwordsFileWrite.open(passwordsPath);
    if (passwordsFileWrite.good()) {
        for (int i = 0; i < contents.size(); i++) {
            passwordsFileWrite << contents[i] << endl;
        }
    }
    else { return; }
    passwordsFileWrite.close();
    contents.clear();
}
void encrypt()
{
    string new_line;
    encryptStatusRead.open(encryptStatusPath);
    getline(encryptStatusRead,new_line);
    encryptStatusRead.close();
    if (new_line != "Encrypt status is true.") {

        if (passwordsFileRead.good()) {
            while (getline(passwordsFileRead, line)) {
                contents.push_back(line);
            }
        }
        for (int i = 0; i < contents.size(); i++) {
            for (int j = 0; j < contents[i].size(); j++) {
                contents[i][j] += 5;
            }
        }
        passwordsFileWrite.close();
        passwordsFileWrite.open(passwordsPath);
        if (passwordsFileWrite.good()) {
            for (int i = 0; i < contents.size(); i++) {
                passwordsFileWrite << contents[i] << endl;
            }
            encryptStatusWrite.open(encryptStatusPath);
            if (encryptStatusWrite.good())
                encryptStatusWrite << "Encrypt status is true.";
            encryptStatusWrite.close();
        } else { return; }
        passwordsFileWrite.close();
        contents.clear();
    }

}
void decrypt()
{
    string new_line;
    encryptStatusRead.open(encryptStatusPath);
    getline(encryptStatusRead,new_line);
    encryptStatusRead.close();
    if (new_line != "Encrypt status is false.") {


        if (passwordsFileRead.good()) {
            while (getline(passwordsFileRead, line)) {
                contents.push_back(line);
            }
        }
        for (int i = 0; i < contents.size(); i++) {
            for (int j = 0; j < contents[i].size(); j++) {
                contents[i][j] -= 5;
            }
        }
        passwordsFileWrite.close();
        passwordsFileWrite.open(passwordsPath);
        if (passwordsFileWrite.good()) {
            for (int i = 0; i < contents.size(); i++) {
                passwordsFileWrite << contents[i] << endl;
            }
            encryptStatusWrite.open(encryptStatusPath);
            if (encryptStatusWrite.good())
                encryptStatusWrite << "Encrypt status is false.";
            encryptStatusWrite.close();
        } else { return; }
        passwordsFileWrite.close();
        contents.clear();
    }
}
void remove(string toDelete, int a, int b) {

    string deleteLine;
    cout << "Enter name to delete" << endl;
    cin >> deleteLine;
    if (passwordsFileRead.good()) {
        while (getline(passwordsFileRead, line)) {
            contents.push_back(line);
        }
    }

    passwordsFileWrite.close();
    passwordsFileWrite.open(passwordsPath);
    if (passwordsFileWrite.good()) {
        for (int i = 0; i < contents.size(); i++) {
            line = cutString(contents[i], a, b);
            if (line == deleteLine)
                continue;
            passwordsFileWrite << contents[i] << endl;
        }
    }
    else { return; }
    passwordsFileWrite.close();
    contents.clear();
}

void search(string toSearch, int a, int b)
{
    if (passwordsFileRead.good()) {
        while (getline(passwordsFileRead, line)) {
            if(toSearch == cutString(line,a,b))
            cout << line << endl;
        }
    }
}

void show(ifstream& file)
{
    string line;
    if(file.good())
    {
        while(getline(file,line))
            cout << line << endl;
    }
}

void updateLastValidLogin()
{
    auto now = chrono::system_clock::to_time_t(chrono::system_clock::now());

    ofstream loginDatesFileWrite;
    ifstream loginDatesFileRead(loginDatesPath);


    if(loginDatesFileRead.good())
    {
        cout << "Last valid login:" << endl;
        show(loginDatesFileRead);
    }
    loginDatesFileWrite.open(loginDatesPath);
    loginDatesFileWrite << ctime(&now);
}

