#pragma once

// Include dependencies
#include "FBullCowGame.h"
#include <map>

// Get prepared to use unreal
#define TMap std::map

// Constructs new Bull Cow Game
FBullCowGame::FBullCowGame() {}
FBullCowGame::~FBullCowGame() {}

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHWLength() const { return MyHiddenWord.length(); }
int32 FBullCowGame::GetMaxTries() const { return MaxTries; }

// Set/Reset the new game based on Word and Difficulty
void FBullCowGame::Reset(FString Word, int32 Difficulty)
{
	// Set hidden word
	MyHiddenWord = Word;

	// Set the MaxTries dependent on difficulty
	switch (Difficulty)
	{
	case 0:
		MaxTries = Word.length();
		break;
	case 1:
		MaxTries = Word.length() - (Word.length() / 4);
		break;
	case 2:
		MaxTries = Word.length() - (Word.length() / 3);
		break;
	default:
		MaxTries = 0;
		break;
	}

	MyCurrentTry = 1;
	bIsGameWon = false;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess))
	{
		return EGuessStatus::NOT_ISOGRAM; // Checks if the guess is an isogram
	}
	else if (!IsLower(Guess))
	{
		return EGuessStatus::NOT_LOWERCASE;  // Checks if the guess is lowecase
	}
	else if (Guess.length() != GetHWLength())
	{
		return EGuessStatus::WRONG_LENGTH;  // Checks if the guess is the proper length
	} 
	
	return EGuessStatus::OK;
}

// Checks if the guess is all lower case
bool FBullCowGame::IsLower(FString &Guess) const
{
	for (auto Letter : Guess)
	{
		if (isupper(Letter))
		{
			return false;
		}
	}
	return true;
}

// Checks if the game has been won
bool FBullCowGame::GetGameWon() const
{
	return bIsGameWon;
}

// Check if passed user guess is an isogram
bool FBullCowGame::IsIsogram(FString Guess) const
{
	// Treat 0 and 1 letter words as isograms
	if (Guess.length() < 2) return true;

	// setup our map
	TMap<char, bool> LetterSeen;
	for (auto Letter : Guess)
	{
		Letter = tolower(Letter);
		if (!LetterSeen[Letter])
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	return true;
}

// Recieves a valid Guess increments turn and returns count
FBullCowCount FBullCowGame::SubmitGuess(FString Guess)
{
	// Increment turn number
	MyCurrentTry++;

	// Setup return variable
	FBullCowCount BullCowCount;

	int32 const HIDDEN_WORD_LENGTH = MyHiddenWord.length();
	// Loop through all letters in the guess
	for (int32 i = 0; i != HIDDEN_WORD_LENGTH; i++)
	{
		if (Guess[i] == MyHiddenWord[i]) 
		{
			BullCowCount.Bulls++;
		}
		else
		{
			// Compares letters against hidden word
			for (int32 j = 0; j != HIDDEN_WORD_LENGTH; j++)
			{
				if (Guess[i] == MyHiddenWord[j])
				{
					BullCowCount.Cows++;
				}
			}
		}
	}
	// If all letters are bulls the game is won
	if (BullCowCount.Bulls == HIDDEN_WORD_LENGTH)
	{
		bIsGameWon = true;
	}
	return BullCowCount;
}