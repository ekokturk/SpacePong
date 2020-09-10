// Copyright (C) 2020, Eser Kokturk. All Rights Reserved.

#pragma once

// Player types that will be used by the controller
enum class PlayerType
{
	PlayerHumanType = 0,
	PlayerAIType
};

// Paddle types based on their position
enum class PaddleType
{
	None = 0,
	PaddleLeft,
	PaddleRight
};


// Available component types
enum class ComponentType : int
{
	Transform = 0,
	Physics,
	BoxShape,
	CircleShape,
	Bounce,
	Score,
	PlayerController,
	AIController
};
