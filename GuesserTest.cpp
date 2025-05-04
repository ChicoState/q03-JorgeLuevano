/**
 * Unit Tests for the class
 * Submit this file only
 * Jorge G. Luevano
**/

#include <gtest/gtest.h>
#include "Guesser.h"

class GuesserTest : public ::testing::Test
{
	protected:
		GuesserTest(){} //constructor runs before each test
		virtual ~GuesserTest(){} //destructor cleans up after tests
		virtual void SetUp(){} //sets up before each test (after constructor)
		virtual void TearDown(){} //clean up after each test, (before destructor)
};


// 	//want to check to see if distance is correct,
// 	//want to check if guess's remaining is correct
// 	//want to check if we are locked out
// 	//want to check 
// 	//this is probably different TEST() functions as we want it to be regression,
// 	//could be that distance was broken but the rest are not,
// 	//check each one at a time


TEST(GuesserTest, correct_guess_everything_perfect)
{
	//
	Guesser object("correct");
	ASSERT_TRUE(object.match("correct"));
	ASSERT_EQ(3,object.remaining());
}

TEST(GuesserTest, incorrectGuessDistanceDecrements)
{
	//
	Guesser object("booger");
	ASSERT_FALSE(object.match("tooger"));
	ASSERT_EQ(2,object.remaining());
}

TEST(GuesserTest, incorrectGuessWithLockedGuesser)
{
	//
	Guesser object("ghost");
	ASSERT_FALSE(object.match("rider"));
	ASSERT_FALSE(object.match("ghost"));//on second guess, its locked cuz distance is more than 2
	ASSERT_EQ(1,object.remaining()); //should still decrement
}

TEST(GuesserTest, remainingOfOne)
{
	//
	Guesser object("ghost");
	object.match("ghozt");//2 remaining
	object.match("ghoct");//1 remaining
	ASSERT_EQ(1,object.remaining());

}

TEST(GuesserTest, lockedOutTooManyIncorrectGuess)
{
	//
	Guesser object("ghost");
	object.match("ghozt");//2 remaining
	object.match("ghoct");//1 remaining
	object.match("ghopt");//0 remaining
	ASSERT_EQ(0,object.remaining());
	ASSERT_FALSE(object.match("ghost"));//should be locked
}

TEST(GuesserTest, correctGuessResetsRemaining)
{
	//
	Guesser object("ghost");
	object.match("ghozt");//2 remaining
	ASSERT_EQ(2,object.remaining());
	object.match("ghost");//3 remaining
	ASSERT_EQ(3,object.remaining());
}

TEST(GuesserTest, longGuessIsShrunk)
{
	//
	Guesser object("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa32nomorefromhere");
	ASSERT_TRUE(object.match("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"));//
}

TEST(GuesserTest, longGuessLocksDueToDistanceOverTheCap)
{
	//
	Guesser object("aaaaaaaaaa");//10
	ASSERT_FALSE(object.match("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"));//100
	ASSERT_EQ(2, object.remaining());
	ASSERT_FALSE(object.match("aaaaaaaaaa"));//also is false cuz locked out
	ASSERT_EQ(1, object.remaining());
}

TEST(GuesserTest, guessShorterThanSecret)
{
	//
	Guesser object("ghost");
	ASSERT_FALSE(object.match("g"));
	ASSERT_EQ(2, object.remaining());
}

TEST(GuesserTest, checkAutoLock)
{
	Guesser object("ghost");
	ASSERT_FALSE(object.match("ghosy"));
	ASSERT_EQ(2, object.remaining());
	ASSERT_FALSE(object.match("ghosr"));
	ASSERT_EQ(1, object.remaining());
	ASSERT_FALSE(object.match("ghosr"));
	ASSERT_EQ(0, object.remaining());
	ASSERT_FALSE(object.match("ghosr"));
	ASSERT_EQ(0, object.remaining());
}

TEST(GuesserTest, correctGuessAfterWrong)
{
	// /
	Guesser object("ghost");
	ASSERT_FALSE(object.match("ghosy"));
	ASSERT_EQ(2, object.remaining());
	ASSERT_TRUE(object.match("ghost"));
	ASSERT_EQ(3, object.remaining());
}

TEST(GuesserTest, constructorCutoffCheck)
{
	// /
	Guesser object("verylongnamethatisusedfortestingpurposes");
	ASSERT_TRUE(object.match("verylongnamethatisusedfortesting"));
	ASSERT_FALSE(object.match("verylongnamethatisusedfortestingpurposes"));
}

TEST(GuesserTest, bruteForceCheck)
{
	// /
	Guesser object("password");
	ASSERT_FALSE(object.match("letmeindude"));
	ASSERT_FALSE(object.match("secret"));
	ASSERT_EQ(1,object.remaining());
}

TEST(GuesserTest, specialCharacterMatch)
{
	// /
	Guesser object("p@$$   W0rd!`");
	ASSERT_TRUE(object.match("p@$$   W0rd!`"));
	ASSERT_EQ(3,object.remaining());
}

TEST(GuesserTest, specialCharacterDecrement)
{
	// /
	Guesser object("p@$$   W0rd!`");
	ASSERT_FALSE(object.match("p@$$   W0rD!`"));
	ASSERT_EQ(2,object.remaining());
}

TEST(GuesserTest, emptyStringMatch)
{
	// /
	Guesser object("");
	ASSERT_TRUE(object.match(""));
	ASSERT_EQ(3,object.remaining());
}

TEST(GuesserTest, emptyStringGuessThenMatch)
{
	// /
	Guesser object("");
	ASSERT_FALSE(object.match(" "));
	ASSERT_EQ(2,object.remaining());
	ASSERT_TRUE(object.match(""));
	ASSERT_EQ(3,object.remaining());
}

TEST(GuesserTest, lockInMiddleOfGuess)
{
	// /
	Guesser object("password");
	ASSERT_FALSE(object.match("Password"));
	ASSERT_EQ(2,object.remaining());
	ASSERT_FALSE(object.match("passworD"));
	ASSERT_EQ(1,object.remaining());
	ASSERT_FALSE(object.match("passworDDDDD!!!!"));
	ASSERT_EQ(0,object.remaining());
}

TEST(GuesserTest, shortGuess)
{
	// /
	Guesser object("abcde");
	ASSERT_FALSE(object.match("ab"));
	ASSERT_EQ(2,object.remaining());
	ASSERT_FALSE(object.match("abcde"));
}

TEST(GuesserTest, tooManyGuesses)
{
	// /
	Guesser object("ghost");
	object.match("Ghost");
	object.match("ghosT");
	object.match("ghOst");
	ASSERT_FALSE(object.match("ghost"));
	ASSERT_EQ(0,object.remaining());
}

TEST(GuesserTest, offByExactlyTwo)
{
	// /
	Guesser object("abcde");
	ASSERT_FALSE(object.match("abc"));
	ASSERT_EQ(2,object.remaining());
	ASSERT_TRUE(object.match("abcde"));
}

TEST(GuesserTest, longGuessCorrectFormatting)
{
	// /
	Guesser object("verylongnamethatisusedfortestingpurposes");
	ASSERT_FALSE(object.match("verylongnamethatisusedfortestingpurposes"));
	ASSERT_EQ(2,object.remaining());
	ASSERT_FALSE(object.match("verylongnamethatisusedfortesting"));
}
