#pragma once

#include <array>

int main();

std::array<std::string, 15> IsoEasy =
{
	"balcony", "shower", "pencil",
	"newly", "super", "axe",
	"jump", "perks", "move",
	"quiche", "guard", "special",
	"english", "freaky", "isogram"
};
std::array<std::string, 15> IsoMedium =
{
	"countryside", "disgrace", "facetious",
	"disgraceful", "personality", "palindromes",
	"nefarious", "dangerous", "disgraceful",
	"campground", "flowchart", "hypnotize",
	"exhausting", "demographics", "considerably"
};
std::array<std::string, 15> IsoHard =
{
	"misconjugate", "housewarming", "unforgivable",
	"unprofitable", "documentary", "consumptively",
	"flamethrowing", "hypnotizables", "metalworkings",
	"subordinate", "troublemaking", "misconjugated",
	"unproblematic", "dermatoglyphics", "hydropneumatics"
};

// Initialize the functions
void PrintASCII();
void PrintIntro();
int GetValidDifficulty();
std::string GetValidWord();
void Reset();
void PlayGame();
std::string GetValidGuess();
bool QueryPlayAgain();
void PrintSummary();