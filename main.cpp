/*
 * This is the console executable, that uses the BullCow class
 * This acts as the view in the MVC pattern, and is responsible
 * for all user interaction. For game logic see FBullCowGame class
 */
#pragma once

// Prepare Dependencies
#include <iostream>
#include <string>
#include <stdbool.h>

#include "main.h"
#include "FBullCowGame.h"

// Get ready for using Unreal
using int32 = int;
using FText = std::string;

// Declare constants
FBullCowGame BCGame;

// Game entry point
int main()
{
	bool bPlayAgain = false;
	do {
		PrintIntro();
		Reset();
		PlayGame();
		bPlayAgain = QueryPlayAgain();
	} while (bPlayAgain);
	
	return 0;
}

void PrintASCII()
{
	std::cout << "\n";
	std::cout << "         BULLS                 &             COWS                     \n\n";
	std::cout << "       /|     |\\                                                     \n";
	std::cout << "      / \\     / \\                        __n_______n__              \n";
	std::cout << "     _\\_/_____\\_/_                      / /         \\ \\           \n";
	std::cout << "    / /         \\ \\                     | | ()   () | |             \n";
	std::cout << "    | | ()   () | |                     \\_\\         /_/             \n";
	std::cout << "    \\_\\         /_/                        |  O O  |                \n";
	std::cout << "       |  O O  |                           \\_uuuuu_/                 \n";
	std::cout << "       \\_uuuuu_/                                                     \n\n\n";
}

// Introduce the game
static void PrintIntro()
{
	std::cout << "\nWelcome to Bulls and Cows, a fun word game!\n";
	PrintASCII();
	std::cout << "A fun puzzle game where I choose an isogram\n";
	std::cout << "(word with no repeating letters)";
    std::cout << " and you try to guess it!\n";
}

// Get the user's desired difficulty and ensure input is valid
int32 GetValidDifficulty()
{
	EWordStatus DifficultyStatus = EWordStatus::INVALID_STATUS;
	int32 NumDifficulty = -1;

	// Loop through until receiving valid input
	do
	{
		std::cout << "Choose a difficulty (easy, medium, hard): ";
		FString UserDifficulty;
		std::getline(std::cin, UserDifficulty);

		switch (UserDifficulty[0])
		{
		case 'e':
			NumDifficulty = 0;
			DifficultyStatus = EWordStatus::OK;
			break;
		case 'm':
			NumDifficulty = 1;
			DifficultyStatus = EWordStatus::OK;
			break;
		case 'h':
			NumDifficulty = 2;
			DifficultyStatus = EWordStatus::OK;
			break;
		default:
			std::cout << "ERR: Invalid input, please enter [e]asy, [m]edium, or [h]ard\n";
			DifficultyStatus = EWordStatus::INVALID_INPUT;
			break;
		}
	} while (DifficultyStatus != EWordStatus::OK);
	return NumDifficulty;
}

// Get a valid word based on the inputed desired length
FString GetValidWord()
{
	EWordStatus LengthStatus = EWordStatus::INVALID_STATUS;
	FString Word;
	do {
		std::cout << "Choose a length (short, medium, long): ";
		FString UserLength;
		std::getline(std::cin, UserLength);

		// Make sure input is valid
		switch (UserLength[0])
		{
		case 's':
			Word = IsoEasy[rand() % 15];
			LengthStatus = EWordStatus::OK;
			break;
		case 'm':
			Word = IsoMedium[rand() % 15];
			LengthStatus = EWordStatus::OK;
			break;
		case 'l':
			Word = IsoHard[rand() % 15];
			LengthStatus = EWordStatus::OK;
			break;
		default:
			std::cout << "ERR: Invalid input, please enter [s]hort, [m]edium, or [l]ong\n";
			LengthStatus = EWordStatus::INVALID_INPUT;
			break;
		}
	} while (LengthStatus != EWordStatus::OK);
	return Word;
}

// Reset the game
void Reset()
{

	FString Word = GetValidWord();
	int32 Difficulty = GetValidDifficulty();
	BCGame.Reset(Word, Difficulty);
	std::cout << "Can you guess the " << BCGame.GetHWLength();
	std::cout << " letter isogram that I'm thinking of?\n\n";
}

// Begin the game loop
static void PlayGame()
{
	// Instantiate a new game
	int32 MaxTries = BCGame.GetMaxTries();

	// Loop while the game is not won and there are more guesses
	// TODO use while loop instead of for once validating
	while (!BCGame.GetGameWon() && BCGame.GetCurrentTry() <= MaxTries) {
		FText Guess = GetValidGuess(); // TODO make loop checking valid guess
		
		// Submit valid guess to game and recieve counts
		FBullCowCount BullCowCount = BCGame.SubmitGuess(Guess);

		std::cout << "Bulls = " << BullCowCount.Bulls << ", ";
		std::cout << "Cows = " << BullCowCount.Cows << "\n\n";
	}

	// Present win/loss message
	PrintSummary();
}

// Get the user's valid guess
static FText GetValidGuess()
{
	EGuessStatus Status = EGuessStatus::INVALID_STATUS;
	FText Guess = "";
	// Keep looping until getting no errors
	do {
		//Get a guess from the player
		int32 CurrentTry = BCGame.GetCurrentTry();
		int32 MaxTries = BCGame.GetMaxTries();
		std::cout << "(Try #" << CurrentTry << " of " << MaxTries << ") Enter your guess: ";
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		// Print error messages
		switch (Status)
		{
		case EGuessStatus::NOT_ISOGRAM:
			std::cout << "ERR: Not an isogram, please enter a word with no repeating letters\n";
			break;
		case EGuessStatus::NOT_LOWERCASE:
			std::cout << "ERR: Uppercase string, please use lowercase letters\n";
			break;
		case EGuessStatus::WRONG_LENGTH:
			std::cout << "ERR: Wrong length, please enter a " << BCGame.GetHWLength() << " letter word\n";
			break;
		default:
			// Assumes guess was valid
			break;
		}
	} while (Status != EGuessStatus::OK);
	return Guess;
}

// Asks the user if they want to play again
bool QueryPlayAgain()
{
	// Asks for replay
	FText Replay = "";
	std::cout << "Want to play again?: ";
	std::getline(std::cin, Replay);
	std::cout << "\n";

	char c = tolower(Replay[0]);

	// Tests if replay response is valid
	while (c != 'y' && c != 'n') {
		std::cout << "ERR: Invalid input please enter (y)es or (n)o\n";
		std::cout << "Want to play again?: ";
		std::getline(std::cin, Replay);
		c = tolower(Replay[0]);
		std::cout << "\n";
	}
	return c == 'y';
}

void PrintSummary()
{
	if (BCGame.GetGameWon())
	{
		std::cout << "       /|     |\\          \n";
		std::cout << "      / \\     / \\        \n";
		std::cout << "     _\\_/_____\\_/_       \n";
		std::cout << "    / /         \\ \\      \n";
		std::cout << "    | | ()   () | |        \n";
		std::cout << "    \\_\\         /_/      \n";
		std::cout << "       |  O O  |           \n";
		std::cout << "       \\_uuuuu_/          \n\n";
		std::cout << "Congratulations! You won!!\n";
	}
	else
	{
		std::cout << "     __n_______n__       \n";
		std::cout << "    / /         \\ \\      \n";
		std::cout << "    | |  X   X  | |        \n";
		std::cout << "    \\_\\         /_/      \n";
		std::cout << "       |  O O  |           \n";
		std::cout << "       \\_uuuuu_/          \n\n";
		std::cout << "You ran out of turns. Better luck next time!\n";
	}
}
