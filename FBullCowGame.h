#pragma once
#include <string>
#include <array>

using FString = std::string;
using int32 = int;

// All values initalized to zero
struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus
{
	INVALID_STATUS,
	OK,
	NOT_ISOGRAM,
	WRONG_LENGTH,
	NOT_LOWERCASE
};

enum class EWordStatus
{
	INVALID_STATUS,
	OK,
	INVALID_INPUT
};

std::array<FString, 15> IsoEasy = 
{
	"balcony", "shower", "pencil",
	"newly", "super", "axe",
	"jump", "perks", "move",
	"quiche", "guard", "special",
	"english", "freaky", "isogram"
};
std::array<FString, 15> IsoMedium = 
{
	"countryside", "disgrace", "facetious",
	"disgraceful", "personality", "palindromes",
	"nefarious", "dangerous", "disgraceful",
	"campground", "flowchart", "hypnotize",
	"exhausting", "demographics", "considerably"
};
std::array<FString, 15> IsoHard = 
{
	"misconjugate", "housewarming", "unforgivable",
	"unprofitable", "documentary", "consumptively",
	"flamethrowing", "hypnotizables", "metalworkings",
	"subordinate", "troublemaking", "misconjugated",
	"unproblematic", "dermatoglyphics", "hydropneumatics"
};


class FBullCowGame
{
public:
	FBullCowGame();
	~FBullCowGame();

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHWLength() const;
	EGuessStatus CheckGuessValidity(FString guess) const;
	bool GetGameWon() const;

	void Reset(FString Word, int32 Difficulty);
	FBullCowCount SubmitGuess(FString);


private:
	bool IsIsogram(FString Guess) const;
	bool IsLower(FString &Guess) const;

	int32 MaxTries;
	int32 MyCurrentTry;
	FString MyHiddenWord;
	bool bIsGameWon;
	int32 Difficulty;
};