#include "database.h"

#include <string>

Database::Database(std::string dbname, std::string fullpath)
{

}

Database Database::createEmpty(std::string dbname)
{
    return Database("test", "test");
}


std::string Database::getDirectory()
{
    return "test";
}
