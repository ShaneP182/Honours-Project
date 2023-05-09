// A stochastic grammar for use in the L system.
#pragma once

#include "CoreMinimal.h"
#include "LRule.h"

/**
 * 
 */
class PROCEDURALLIGHTNING_API LGrammar
{
public:
	// Constructor and destructor.
	LGrammar(FString axiom, TArray<FString> rules);
	~LGrammar();

	// Iterate through the string.
	void Iterate(int its);

	// Returns the resulting string.
	FString GetResult();
protected:
	// The string to be iterated through.
	FString Condition;

	// An array to store the rules.
	TArray<LRule> RulesArray;

	// Combined probability values of the rules array.
	float TotalProbability;
};
