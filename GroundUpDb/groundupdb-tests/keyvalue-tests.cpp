#include "catch.hpp"

#include "groundupdb/groundupdb.h"

using std::string;

TEST_CASE("Store and retrieve a value", "[setKeyValue,getKeyValue]")
{
    SECTION("Basic set and get")
    {
        string key = "my_key";
        string value = "my_value";

        groundupdb::Database db = groundupdb::Database::createEmpty("keyvalue-tests");

        db.setKeyValue(key, value);

        REQUIRE(value == db.getKeyValue(key));

        db.destroy();
    }
}
