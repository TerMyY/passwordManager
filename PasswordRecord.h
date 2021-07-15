#ifndef PASSWORDMANAGER_PASSWORDRECORD_H
#define PASSWORDMANAGER_PASSWORDRECORD_H

#include "Category.h"

class PasswordRecord
{
public:
    std::string name;
    std::string login;
    std::string password;
    Category category;



    PasswordRecord(std::string name, std::string login, std::string password, Category category)
    {

        this->name = name;
        this->login = login;
        this->password = password;
        this->category = category;

    }


    friend std::ostream& operator<<(std::ostream &out, PasswordRecord p)
    {
        out << "[ " << p.name << " | " << p.login << " | " << p.password << " | " << p.category.name << " ]" << std::endl;
        return out;
    }

};

#endif
