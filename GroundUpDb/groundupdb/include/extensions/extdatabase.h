#ifndef EXTDATABASE_H
#define EXTDATABASE_H

#include "database.h"

namespace groundupdbext {

using namespace groundupdb;

class EmbeddedDatabase : public IDatabase
{
public:
    EmbeddedDatabase(std::string dbname, std::string fullpath);
    ~EmbeddedDatabase();

    // Instance db management functions
    std::string getDirectory();
    void destroy();

    // Instance key-value functions
    void setKeyValue(std::string key, std::string value);
    std::string getKeyValue(std::string key);

    // Static management functions
    static const std::unique_ptr<IDatabase> createEmpty(std::string dbname);
    static const std::unique_ptr<IDatabase> load(std::string dbname);

    class Impl;

private:
    // pImpl idiom - pointer to implementation
    std::unique_ptr<Impl> mImpl;
};
}

#endif // EXTDATABASE_H
