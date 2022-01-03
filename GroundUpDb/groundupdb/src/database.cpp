#include "database.h"

#include <iostream>
#include <fstream>
#include <filesystem>

using std::string;
using namespace groundupdb;

namespace fs = std::filesystem;

Database::Database(string dbname, string fullpath)
    : m_name(dbname), m_fullpath(fullpath)
{

}

Database Database::createEmpty(string dbname)
{
    fs::path basedir = ".groundupdb";
    if(!fs::exists(basedir))
    {
        fs::create_directory(basedir);
    }

    fs::path dbfolder = basedir / dbname;
    if(!fs::exists(dbfolder))
    {
        fs::create_directory(dbfolder);
    }

    return Database(dbname, dbfolder.u8string());
}

void Database::setKeyValue(string key, string value)
{
    std::ofstream os;
    fs::path path = Database::getKeyValueFilePath(key);

    os.open(path, std::ios::out | std::ios::trunc);
    os << value;
    os.close();
}

string Database::getKeyValue(string key)
{
    std::ifstream is;
    fs::path path = Database::getKeyValueFilePath(key);
    string value;

    is.open(path, std::ios::in);

    // determine stream length to ensure our striung is big enough - read to end, then get the current position.
    // "g" in "seekg" and "tellg" stands for get. An output filestream has "seekp" and "tellp", where "p" stands for put
    is.seekg(0, std::ios::end);
    int len = is.tellg();
    value.reserve(len);

    // read the value into the string - go back to thee start and then read.
    is.seekg(0, std::ios::beg);
    value.assign(std::istreambuf_iterator<char>(is), std::istreambuf_iterator<char>());

    return value;
}

fs::path Database::getKeyValueFilePath(string key)
{
    return fs::path(m_fullpath) / (key + "_string.kv");
}

string Database::getDirectory()
{
    return m_fullpath;
}

void Database::destroy()
{
    if(fs::exists(m_fullpath))
    {
        fs::remove_all(m_fullpath);
    }
}

Database Database::load(std::string dbname)
{
    fs::path dbpath = fs::path(".groundupdb") / dbname;

    if(!fs::exists(dbpath))
    {
        throw std::runtime_error("Requested database does not exist");
    }

    return Database(dbname, dbpath.u8string());
}
