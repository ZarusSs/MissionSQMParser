#pragma once

#include "entities/GroupEntity.h"
#include "entities/LogicEntity.h"
#include "entities/MarkerEntity.h"
#include "entities/ObjectEntity.h"
#include "entities/TriggerEntity.h"

#include "stringUtils/stringFuncs.h"


#include <vector>
#include <variant>
#include <sstream>
#include <algorithm>

using EntityVariant = std::variant<std::monostate, GroupEntity, LogicEntity, MarkerEntity, ObjectEntity, TriggerEntity>;

struct MissionEntities
{
	short items;
	std::vector<EntityVariant> missionEntities;

	[[nodiscard]] std::string toString(int indentLevel) const;

	[[nodiscard]] bool entityIdMatch(const EntityVariant &entityVariant, int entityId) const;

	void removeEntity(int id);
};