#pragma once

#include "stringUtils/stringFuncs.h"

#include <string>
#include <sstream>
#include <optional>

enum class EntityType
{
	Group,
	Object,
	Marker,
	Logic,
	Trigger,
	Unknown
};

class BaseEntity
{
	std::string dataType;
	int id;
	double atlOffset;
public:
	[[nodiscard]] std::string getDataType() const
	{
		return dataType;
	}

	[[nodiscard]] int getId() const
	{
		return id;
	}

	[[nodiscard]] double getAtlOffset() const
	{
		return atlOffset;
	}

	void setDataType(std::string_view valueToSet)
	{
		dataType = std::string{valueToSet};
	}

	void setId(int valueToSet)
	{
		id = valueToSet;
	}

	void setAtlOffset(double valueToSet)
	{
		atlOffset = valueToSet;
	}

	std::string& getDataTypeRef()
	{
		return dataType;
	}

	int& getIdRef()
	{
		return id;
	}

	double& getAtlOffsetRef()
	{
		return atlOffset;
	}

	virtual ~BaseEntity() = 0;
};