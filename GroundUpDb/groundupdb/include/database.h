#ifndef DATABASE_H
#define DATABASE_H

#include <string>

#include <filesystem>

namespace groundupdb {

class IDatabase
{
public:
    IDatabase() = default;
    virtual ~IDatabase() = default;

    // Instance db management functions
    virtual std::string getDirectory() = 0;
    virtual void destroy() = 0;

    // Instance key-value functions
    virtual void setKeyValue(std::string key, std::string value) = 0;
    virtual std::string getKeyValue(std::string key) = 0;

    // Static management functions
    static const std::unique_ptr<IDatabase> createEmpty(std::string dbname);
    static const std::unique_ptr<IDatabase> load(std::string dbname);
};

}

#endif // DATABASE_H
