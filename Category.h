#ifndef PASSWORDMANAGER_CATEGORY_H
#define PASSWORDMANAGER_CATEGORY_H

class Category
{
public:
    std::string name{};
    explicit Category(std::string name)
    { this->name = name; }
    Category()
    = default;
    bool operator == (const Category& c) const { return name == c.name; }
    bool operator != (const Category& c) const { return !operator==(c); }

};

#endif
