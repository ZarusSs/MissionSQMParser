#include "MissionSQMStructures/MissionEntities.h"

std::string MissionEntities::toString(int indentLevel) const
{
	std::stringstream outStream;

	auto indStr{ indent(indentLevel) };
	auto declIndStr{ indent(indentLevel - 1) };

	outStream << declIndStr << "class Entities\n";
	outStream << declIndStr << "{\n";
	outStream << indStr << "items=" << items << ";\n";

	for (short i{}; i < items; ++i)
	{
		auto currentIndex{ missionEntities.at(i).index() };

		switch (currentIndex)
		{
			case 0:
			{
				break;
			}
			case 1:
			{
				auto &entity{ std::get<GroupEntity>(missionEntities.at(i)) };
				outStream << entity.toString(indentLevel + 1, i);
				break;
			}
			case 2:
			{
				auto &entity{ std::get<LogicEntity>(missionEntities.at(i)) };
				outStream << entity.toString(indentLevel + 1, i);
				break;
			}
			case 3:
			{
				auto &entity{ std::get<MarkerEntity>(missionEntities.at(i)) };
				outStream << entity.toString(indentLevel + 1, i);
				break;
			}
			case 4:
			{
				auto &entity{ std::get<ObjectEntity>(missionEntities.at(i)) };
				outStream << entity.toString(indentLevel + 1, i);
				break;
			}
			case 5:
			{
				auto &entity{ std::get<TriggerEntity>(missionEntities.at(i)) };
				outStream << entity.toString(indentLevel + 1, i);
				break;
			}
			default:
			{
				break;
			}
		}
	}

	outStream << declIndStr << "};\n";

	return outStream.str();
}

bool MissionEntities::entityIdMatch(const EntityVariant &entityVariant, int entityId) const
{
	auto entityIndex{ entityVariant.index() };

	switch (entityIndex)
	{
		case 2:
			return std::get<LogicEntity>(entityVariant).getId() == entityId;
		case 3:
			return std::get<MarkerEntity>(entityVariant).getId() == entityId;
		case 4:
			return std::get<ObjectEntity>(entityVariant).getId() == entityId;
		case 5:
			return std::get<TriggerEntity>(entityVariant).getId() == entityId;
		default:
			return false;
	}
}

void MissionEntities::removeEntity(int id)
{
	// Check all entities id, except Group ones
	auto it{ std::remove_if(
			missionEntities.begin(),
			missionEntities.end(),
			[this, id](const EntityVariant &entityVariant) {
				return entityIdMatch(entityVariant, id);
			}
	) };
	if (it != missionEntities.end())
	{
		missionEntities.erase(it, missionEntities.end());
		--items;
		return;
	}

	// Check all groups for unit with required id
	it = std::remove_if(
			missionEntities.begin(),
			missionEntities.end(),
			[id](const EntityVariant &entityVariant) {
				if (entityVariant.index() == 1)
				{
					auto groupEntity{ std::get<GroupEntity>(entityVariant) };
					groupEntity.removeUnitFromGroup(id);
					return groupEntity.isGroupEmpty();
				}
				return false;
			}
	);

	if (it != missionEntities.end())
	{
		missionEntities.erase(it, missionEntities.end());
		--items;
		return;
	}
}
