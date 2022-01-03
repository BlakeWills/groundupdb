#include "catch.hpp"

#include <filesystem>
#include <string>

#include "groundupdb/groundupdb.h"

namespace fs = std::filesystem;

TEST_CASE("Create a new empty database","[createEmptyDB]") {

    // Story:-
    //   [Who]   As a database administrator
    //   [What]  I need to create a new empty database
    //   [Value] So I can later store and retrieve data

    SECTION("Default settings") {
        std::string dbname("myemptydb");
        Database db(GroundUpDB::createEmptyDB(dbname));

        // We know we have been successful when:-
        // 1. We have a valid database reference returned
        //   - No test -> The above would have errored
        // 2. The DB has a folder that exists on the file system
        REQUIRE(fs::is_directory(fs::status(db.getDirectory())));
        // C++17 Ref: https://en.cppreference.com/w/cpp/filesystem/is_directory

        // 3. The database folder is empty (no database files yet)
        const auto& p = fs::directory_iterator(db.getDirectory());
        REQUIRE(p == end(p)); // i.e. no contents as iterator is at the end already
        // C++17 Ref: https://en.cppreference.com/w/cpp/filesystem/directory_iterator

        db.destroy();
        REQUIRE(!fs::exists(db.getDirectory()));
    }
}

TEST_CASE("Load an existing database","[load]")
{
    SECTION("Database does not exist")
    {
        std::string dbname("myemptydb");
        REQUIRE_THROWS_AS(Database::load(dbname), std::runtime_error);
    }

    SECTION("Database exists")
    {
        std::string dbname("myemptydb");
        Database db(GroundUpDB::createEmptyDB(dbname));

        REQUIRE(fs::is_directory(db.getDirectory()));

        Database loadedDb(Database::load(dbname));
        REQUIRE(db.getDirectory() == loadedDb.getDirectory());

        loadedDb.destroy();
    }
}
