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
    virtual std::string getDirectory(void);
    virtual void destroy();

    // Instance key-value functions
    virtual void setKeyValue(std::string key, std::string value);
    virtual std::string getKeyValue(std::string key);

    // Static management functions
    static const std::unique_ptr<IDatabase> createEmpty(std::string dbname);
    static const std::unique_ptr<IDatabase> load(std::string dbname);
};

}

#endif // DATABASE_H
