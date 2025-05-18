#include "entities/GroupEntity.h"

std::string GroupEntity::toString(int indentLevel, short entityIndex) const
{
	std::stringstream outStream;

	auto indStr{ indent(indentLevel) };
	auto declIndStr{ indent(indentLevel - 1) };

	outStream << declIndStr << "class Item" << std::to_string(entityIndex) << "\n";
	outStream << declIndStr << "{\n";
	outStream << indStr << "dataType=" << quoteStr(getDataType()) << ";\n";
	outStream << indStr << "side=" << quoteStr(side) << ";\n";
	outStream << groupUnits.toString(indentLevel + 1);
	outStream << attributes.toString(indentLevel + 1);
	outStream << indStr << "id=" << getId() << ";\n";
	outStream << indStr << "atlOffset=" << getAtlOffset() << ";\n";
	outStream << declIndStr << "};\n";

	return outStream.str();
}

bool GroupEntity::isGroupEmpty() const
{
	return groupUnits.items == 0;
}

bool GroupEntity::hasEntityWithId(const ObjectEntity &objectEntity, int id) const
{
	return objectEntity.getId() == id;
}

void GroupEntity::removeUnitFromGroup(int id)
{
	auto units{ groupUnits.units };

	auto it{ std::remove_if(
			units.begin(),
			units.end(),
			[this, id](const ObjectEntity &objectEntity) {
				return hasEntityWithId(objectEntity, id);
			}
	) };

	if (it != units.end())
	{
		units.erase(it, units.end());
		--groupUnits.items;
	}
}

void GroupEntity::setSide(const std::string &valueToSet)
{
	side = valueToSet;
}

void GroupEntity::setGroupUnits(const GroupUnits &valueToSet)
{
	groupUnits = valueToSet;
}

void GroupEntity::setAttributes(const Attributes &valueToSet)
{
	attributes = valueToSet;
}
