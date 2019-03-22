#include "catch.hpp"
#include "../src/UserInput.h"

SCENARIO("When taking well formatted input passed directly from main")
{
	GIVEN("Filename alone")
	{
		CommandList expected = CommandList();
		UserInput input = UserInput();

		std::vector<std::string> args = { "filename", "example.txt" };
		bool properlyFormatted = input.parse(args);
		CHECK(properlyFormatted);

		CommandList received = input.generateCommandList();
		expected.setFilename("example.txt");
		bool objectEquality = received == expected;
		REQUIRE(objectEquality);
	}

	GIVEN("Size and filename")
	{
		CommandList expected = CommandList();
		UserInput input = UserInput();

		std::vector<std::string> args = { "size", "55", "55", "filename", "example.txt" };
		bool properlyFormatted = input.parse(args);
		CHECK(properlyFormatted);

		CommandList received = input.generateCommandList();
		expected.setSize(55.0f, 55.0f);
		expected.setFilename("example.txt");
		bool objectEquality = received == expected;
		REQUIRE(objectEquality);
	}

	GIVEN("Depth and filename")
	{
		CommandList expected = CommandList();
		UserInput input = UserInput();

		std::vector<std::string> args = { "maxdepth", "0", "filename", "example.txt" };
		bool properlyFormatted = input.parse(args);
		CHECK(properlyFormatted);

		CommandList received = input.generateCommandList();
		expected.setDepth(0.0f);
		expected.setFilename("example.txt");
		bool objectEquality = received == expected;
		REQUIRE(objectEquality);
	}

	GIVEN("Size and depth and filename")
	{
		CommandList expected = CommandList();
		UserInput input = UserInput();

		std::vector<std::string> args = { "filename", "example.txt", "maxdepth", "0", "size", "55", "55" };
		bool properlyFormatted = input.parse(args);
		CHECK(properlyFormatted);

		CommandList received = input.generateCommandList();
		expected.setSize(55.0f, 55.0f);
		expected.setDepth(0.0f);
		expected.setFilename("example.txt");
		bool objectEquality = received == expected;
		REQUIRE(objectEquality);
	}

	GIVEN("Just filename and a bunch of junk")
	{
		CommandList expected = CommandList();
		UserInput input = UserInput();

		std::vector<std::string> args = { "size", "foo", "5454134914", "0x00", "filename", "example.txt", "bar", "length", "100", "width", "100", "qwertyuiop!!", "^[a-zA-Z]" };
		bool properlyFormatted = input.parse(args);
		CHECK(properlyFormatted);

		CommandList received = input.generateCommandList();
		expected.setFilename("example.txt");
		bool objectEquality = received == expected;
		REQUIRE(objectEquality);
	}
}

SCENARIO("When taking malformed input directly from main")
{
	GIVEN("Just depth")
	{
		UserInput input = UserInput();
		std::vector<std::string> args = { "maxdepth", "500" };
		bool properlyFormatted = input.parse(args);
		REQUIRE_FALSE(properlyFormatted);
	}
	
	GIVEN("Just size")
	{
		UserInput input = UserInput();
		std::vector<std::string> args = { "size", "25", "100" };
		bool properlyFormatted = input.parse(args);
		REQUIRE_FALSE(properlyFormatted);
	}

	GIVEN("Depth and size")
	{
		UserInput input = UserInput();
		std::vector<std::string> args = { "size", "25", "100", "maxdepth", "30" };
		bool properlyFormatted = input.parse(args);
		REQUIRE_FALSE(properlyFormatted);
	}

	GIVEN("Invalid filename")
	{
		UserInput input = UserInput();
		std::vector<std::string> args = { "filename", "index.html" };
		bool properlyFormatted = input.parse(args);
		REQUIRE_FALSE(properlyFormatted);
	}

	GIVEN("Filename and size with one argument")
	{
		UserInput input = UserInput();
		std::vector<std::string> args = { "filename", "example.txt", "size", "25" };
		bool properlyFormatted = input.parse(args);
		REQUIRE_FALSE(properlyFormatted);
	}
	
	GIVEN("Filename and size with no arguments")
	{
		UserInput input = UserInput();
		std::vector<std::string> args = { "filename", "example.txt", "size"};
		bool properlyFormatted = input.parse(args);
		REQUIRE_FALSE(properlyFormatted);
	}

	GIVEN("Filename and depth with no argument")
	{
		UserInput input = UserInput();
		std::vector<std::string> args = { "filename", "example.txt", "maxdepth"};
		bool properlyFormatted = input.parse(args);
		REQUIRE_FALSE(properlyFormatted);
	}

	GIVEN("Filename and size and depth with no argument")
	{
		UserInput input = UserInput();
		std::vector<std::string> args = { "filename", "example.txt", "size", "24", "200", "maxdepth"};
		bool properlyFormatted = input.parse(args);
		REQUIRE_FALSE(properlyFormatted);
	}

	GIVEN("Filename and size with one argument and depth with no argument")
	{
		UserInput input = UserInput();
		std::vector<std::string> args = { "filename", "example.txt", "size", "24", "maxdepth"};
		bool properlyFormatted = input.parse(args);
		REQUIRE_FALSE(properlyFormatted);
	}

	GIVEN("Filename and size with no arguments and depth with no argument")
	{
		UserInput input = UserInput();
		std::vector<std::string> args = { "filename", "example.txt", "size", "maxdepth"};
		bool properlyFormatted = input.parse(args);
		REQUIRE_FALSE(properlyFormatted);
	}

	GIVEN("Filename and size with one argument and valid depth")
	{
		UserInput input = UserInput();
		std::vector<std::string> args = { "filename", "example.txt", "size", "42", "maxdepth", "2" };
		bool properlyFormatted = input.parse(args);
		REQUIRE_FALSE(properlyFormatted);
	}

	GIVEN("Filename and size with no arguments and valid depth")
	{
		UserInput input = UserInput();
		std::vector<std::string> args = { "filename", "example.txt", "size", "maxdepth", "2" };
		bool properlyFormatted = input.parse(args);
		REQUIRE_FALSE(properlyFormatted);
	}

	GIVEN("Filename with no argument and depth with no argument and size with no arguments")
	{
		UserInput input = UserInput();
		std::vector<std::string> args = { "filename", "maxdepth", "size" };
		bool properlyFormatted = input.parse(args);
		REQUIRE_FALSE(properlyFormatted);
	}

	GIVEN("Filename with no argument and size with no arguments and depth with no argument")
	{
		UserInput input = UserInput();
		std::vector<std::string> args = { "filename", "size", "maxdepth" };
		bool properlyFormatted = input.parse(args);
		REQUIRE_FALSE(properlyFormatted);
	}

	GIVEN("Depth with no argument and filename with no argument and size with no arguments")
	{
		UserInput input = UserInput();
		std::vector<std::string> args = { "maxdepth", "filename", "size" };
		bool properlyFormatted = input.parse(args);
		REQUIRE_FALSE(properlyFormatted);
	}

	GIVEN("Depth with no argument and size with no arguments and filename with no argument")
	{
		UserInput input = UserInput();
		std::vector<std::string> args = { "maxdepth", "size", "filename" };
		bool properlyFormatted = input.parse(args);
		REQUIRE_FALSE(properlyFormatted);
	}

	GIVEN("Size with no arguments and filename with no argument and depth with no argument")
	{
		UserInput input = UserInput();
		std::vector<std::string> args = { "size", "filename", "maxdepth"};
		bool properlyFormatted = input.parse(args);
		REQUIRE_FALSE(properlyFormatted);
	}

	GIVEN("Size with no arguments and depth with no argument and filename with no argument")
	{
		UserInput input = UserInput();
		std::vector<std::string> args = { "size", "maxdepth", "filename"};
		bool properlyFormatted = input.parse(args);
		REQUIRE_FALSE(properlyFormatted);
	}

	GIVEN("Filename and more than maximum allowed length of input")
	{
		UserInput input = UserInput();
		std::vector<std::string> args = { "filename", "example.txt", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "" };
		REQUIRE_THROWS(input.parse(args));
	}
}