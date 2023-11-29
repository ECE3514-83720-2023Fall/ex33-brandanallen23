#include "catch.hpp"

#include "hash_dictionary.hpp"

#include <iostream> // for debugging
#include <sstream>  // for std::ostringstream
#include <string>   // for std::string

typedef unsigned int KeyType;
typedef std::string ValueType;
typedef std::size_t (*FunctionType)(const KeyType &key);
typedef HashDictionary<KeyType, ValueType, FunctionType> DictionaryType;

std::size_t hash(const KeyType &key) { return key; }

TEST_CASE("Basic Tests", "[Dictionary]") {
	//To DO
	DictionaryType dict(hash);

  REQUIRE(dict.isEmpty());
  REQUIRE(dict.size() == 0);

  REQUIRE_NOTHROW(dict.add(1, "one"));
  REQUIRE(dict.get(1) == "one");

  REQUIRE_NOTHROW(dict.add(2, "two"));
  REQUIRE_NOTHROW(dict.add(3, "three"));
  REQUIRE_NOTHROW(dict.add(4, "four"));
  REQUIRE_NOTHROW(dict.add(5, "five"));
  REQUIRE_NOTHROW(dict.add(2, "six"));

  REQUIRE(dict.get(2) == "six");

  REQUIRE_NOTHROW(dict.remove(2));
  REQUIRE_NOTHROW(dict.remove(4));
  REQUIRE_THROWS(dict.get(2));

  REQUIRE(dict.contains(5));
  REQUIRE(dict.get(5) == "five");

  REQUIRE_NOTHROW(dict.remove(1));
  REQUIRE_NOTHROW(dict.remove(3));
  REQUIRE_NOTHROW(dict.remove(5));
  
}

TEST_CASE("Test large Dictionary", "[Dictionary]") {
	//To Do
	DictionaryType dict(hash);

  for (KeyType i = 0; i < 5000; i++) {
    REQUIRE_NOTHROW(dict.add(i, "test"));
  }
	REQUIRE_THROWS(dict.get(5001));
	REQUIRE(dict.get(4987) == "test");

	for (KeyType k = 0; k <= 2500; k++) {
		REQUIRE_NOTHROW(dict.remove(k));
		REQUIRE_FALSE(dict.contains(k));
		REQUIRE_THROWS(dict.get(k));
  	}
		REQUIRE_THROWS(dict.get(1500));

		REQUIRE_FALSE(dict.contains(1250));

	
}

