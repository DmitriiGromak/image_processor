#include "apply_filters.h"
#include "image.h"
#include "parse.h"

#include <catch.hpp>

TEST_CASE("Wrong filter parameters") {
    REQUIRE_THROWS(CreateFilter({"-crop", {"1"}}));
    REQUIRE_THROWS(CreateFilter({"-crop", {"1", "2", "3"}}));
    REQUIRE_THROWS(CreateFilter({"-crop", {"2", "3.3"}}));
    REQUIRE_THROWS(CreateFilter({"-crop", {"2.2", "3"}}));
    REQUIRE_THROWS(CreateFilter({"-gs", {"1"}}));
    REQUIRE_THROWS(CreateFilter({"-neg", {"1", "0"}}));
    REQUIRE_THROWS(CreateFilter({"-sharp", {"1", "bebsa"}}));
    REQUIRE_THROWS(CreateFilter({"-sharp", {}}));
    REQUIRE_THROWS(CreateFilter({"-edge", {"1.2.3"}}));
    REQUIRE_THROWS(CreateFilter({"-blur", {"0"}}));
    REQUIRE_THROWS(CreateFilter({"-blur", {"23", "0.1"}}));
    REQUIRE_THROWS(CreateFilter({"-blur", {".23"}}));
    REQUIRE_THROWS(CreateFilter({"-crystallize", {"skayfom"}}));
    REQUIRE_THROWS(CreateFilter({"-crystallize", {"2", "3"}}));
    REQUIRE_THROWS(CreateFilter({"-crystallize", {"2.1"}}));
    REQUIRE_THROWS(CreateFilter({"royal", {"1", "1"}}));
}

TEST_CASE("Wrong files") {
    Image image;
    REQUIRE_THROWS(image.Read("pushka"));
    REQUIRE_THROWS(image.Write("strashnaya"));
}

TEST_CASE("Wrong input") {
    char* test[2];
    REQUIRE_THROWS(Parse(2, test));
}
