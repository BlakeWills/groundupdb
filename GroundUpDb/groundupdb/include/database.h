#ifndef DATABASE_H
#define DATABASE_H

#include <string>

#include <filesystem>

class Database
{
public:
    Database(std::string dbname, std::string fullpath);

    // Instance db management functions
    std::string getDirectory(void);
    void destroy();

    // Instance key-value functions
    void setKeyValue(std::string key, std::string value);
    std::string getKeyValue(std::string key);

    // Static management functions
    static Database createEmpty(std::string dbname);
    static Database load(std::string dbname);

protected:
    std::string m_name;
    std::string m_fullpath;

private:
    std::filesystem::path getKeyValueFilePath(std::string key);
};

#endif // DATABASE_H
