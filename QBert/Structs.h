#pragma once
#include <memory>
#include <TextureComponent.h>

struct FieldData
{
	int Row = 0;
	int Column = 0;
	float MiddlePosX = 0;
	float MiddlePosY = 0;
	std::shared_ptr<dae::TextureComponent> pTextureComponent;
};

struct FieldDataPlayer
{
	int Row = 0;
	int Column = 0;
};

