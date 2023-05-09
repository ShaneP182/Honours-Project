// Physics model class. 
// This model procedurally generates lightning based on a set of equations laid out in the paper 'IONIZATION IN ATMOSPHERES OF BROWN DWARFS AND EXTRASOLAR PLANETS VI: PROPERTIES OF LARGE - SCALE DISCHARGE EVENTS' by Bailey et al.
// These equations are used to create segments of lightning, which are then added to an array so that they can be rendered in the lightning generator.

#pragma once

#include "CoreMinimal.h"
#include <random>

// A struct for segments of lightning, containing all parameters necessary for the equations and rendering.
struct Segment
{
	Segment* Parent;
	FVector StartPos;
	FVector EndPos;
	FVector Direction;
	float Length;
	float Diameter;
	float Pressure;
	float Temp;
	float MinDiameter; // minimum diameter required to branch.
	float BranchAngle;
	bool HasEnded;
};

/**
 * 
 */
class PROCEDURALLIGHTNING_API PhysicsModel
{
public:
	// Constructor and destructor.
	PhysicsModel();
	~PhysicsModel();

	// Generate lightning segments.
	void GenerateSegments();

	// Returns generated lightning segments.
	TArray<Segment> GetSegments() { return LightningSegments; };

	// Set pointer to the generator's 3D mode bool.
	void Set3DMode(bool* b) { bIs3DEnabled = b; };

	// Calculates pressure based on the general barometric formula.
	float CalculatePressure(float height);

	// A multiplier used for simulating increased or decreased pressure.
	float PressureMultiplier;

	// Scale for the length of segments.
	float Scale;

	// Voltage. Affects the size of the initial segment.
	float Voltage;

	// nV - a constant used when calculating initial segment diameter.
	float ConstantnV;

	// A - a constant used when calculating the minimum diameter.
	float ConstantA;
	float ConstantADeviation;

	// Length and its deviation for normal distribution.
	float Length;
	float LengthDeviation;

	// Angle and its deviation for normal distribution.
	float Angle;
	float AngleDeviation;

	// Values used for mapping temperature to height.
	// *** //
	UE::Math::TVector2<float> heightRange;
	UE::Math::TVector2<float> tempRange;
	float StartHeight;
	float SeaLevelHeight;
	float SeaLevelTemp;
	// *** //

	// If there are too many segments, performance could drop. These variables are used to limit the amount of segments to avoid this.
	bool bUseSegmentLimit;
	int MaxSegments;

	// These are not physics-based, but improve how the lightning can look.
	float BranchChance;
	float InitialAngleRange;

	// When enabled, a fix for a bug in packaged builds is applied when generating lightning.
	bool bPackagedBuildFix;

private:
	// Array of the generated segments.
	TArray<Segment> LightningSegments;

	// Random number generator for normal distribution.
	std::default_random_engine Rand_Generator;

	// Pointer to a bool for whether 3D lightning should be enabled.
	bool* bIs3DEnabled;

	// The first segment is unique so it has its own function for generation.
	void GenerateFirstSegment(Segment& segment, float A, float lenDist);
};
