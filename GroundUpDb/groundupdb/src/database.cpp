#include "database.h"
#include "extensions/extdatabase.h"

#include <iostream>
#include <fstream>
#include <filesystem>

using std::string;
using namespace groundupdb;
using namespace groundupdbext;

namespace fs = std::filesystem;

// Hidden DB implementation
class EmbeddedDatabase::Impl : public IDatabase
{
public:
    Impl(string dbname, string fullpath);
    ~Impl();

    // Instance db management functions
    std::string getDirectory(void);
    void destroy();

    // Instance key-value functions
    void setKeyValue(std::string key, std::string value);
    std::string getKeyValue(std::string key);

    // Static management functions
    static const std::unique_ptr<IDatabase> createEmpty(std::string dbname);
    static const std::unique_ptr<IDatabase> load(std::string dbname);

private:
    std::string m_name;
    std::string m_fullpath;

    std::filesystem::path getKeyValueFilePath(std::string key);
};


// Embedded Database Implementation

EmbeddedDatabase::Impl::Impl(std::string dbname, std::string fullpath)
    : m_name(dbname), m_fullpath(fullpath)
{

}

EmbeddedDatabase::Impl::~Impl()
{
    ;
}

const std::unique_ptr<IDatabase> EmbeddedDatabase::Impl::createEmpty(string dbname)
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

    return std::make_unique<EmbeddedDatabase::Impl>(dbname, dbfolder.u8string());
}

const std::unique_ptr<IDatabase> EmbeddedDatabase::Impl::load(std::string dbname)
{
    fs::path dbpath = fs::path(".groundupdb") / dbname;

    if(!fs::exists(dbpath))
    {
        throw std::runtime_error("Requested database does not exist");
    }

    return std::make_unique<EmbeddedDatabase::Impl>(dbname, dbpath.u8string());
}

void EmbeddedDatabase::Impl::setKeyValue(string key, string value)
{
    std::ofstream os;
    fs::path path = EmbeddedDatabase::Impl::getKeyValueFilePath(key);

    os.open(path, std::ios::out | std::ios::trunc);
    os << value;
    os.close();
}

string EmbeddedDatabase::Impl::getKeyValue(string key)
{
    std::ifstream is;
    fs::path path = EmbeddedDatabase::Impl::getKeyValueFilePath(key);
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

fs::path EmbeddedDatabase::Impl::getKeyValueFilePath(string key)
{
    return fs::path(m_fullpath) / (key + "_string.kv");
}

string EmbeddedDatabase::Impl::getDirectory()
{
    return m_fullpath;
}

void EmbeddedDatabase::Impl::destroy()
{
    if(fs::exists(m_fullpath))
    {
        fs::remove_all(m_fullpath);
    }
}

// High level db API client

EmbeddedDatabase::EmbeddedDatabase(string dbname, string fullpath)
    : mImpl(std::make_unique<EmbeddedDatabase::Impl>(dbname, fullpath))
{

}

EmbeddedDatabase::~EmbeddedDatabase()
{
    ;
}

const std::unique_ptr<IDatabase> EmbeddedDatabase::createEmpty(string dbname)
{
    return EmbeddedDatabase::Impl::createEmpty(dbname);
}

const std::unique_ptr<IDatabase> EmbeddedDatabase::load(std::string dbname)
{
    return EmbeddedDatabase::Impl::load(dbname);
}

void EmbeddedDatabase::setKeyValue(string key, string value)
{
    mImpl->setKeyValue(key, value);
}

string EmbeddedDatabase::getKeyValue(string key)
{
    return mImpl->getKeyValue(key);
}

string EmbeddedDatabase::getDirectory()
{
    return mImpl->getDirectory();
}

void EmbeddedDatabase::destroy()
{
    mImpl->destroy();
}
