<div align="center">

# Arma 3 mission.sqm file parser library

## This library provides classes and funcs to parse, serialize and deserealize [Arma 3 mission.sqm](https://community.bistudio.com/wiki/Mission.sqm "BIS Wiki URL") file data, for further convenient work with it.

## Current library implemented funcs and classes:

### Class MissionSQM:
#### Stores all mission data
#### Methods:
##### MissionSQM.removeEntity(int id) - removes entity with given id from MissionSQM class object

### Class Parser
#### Static methods:
##### Parser::parseFromFile(const std::string&) - parse and deserealize data from mission file to MissionSQM class
##### Parser::writeMissionSQMToFile(MissionSQM &, const std::string &, const std::string &) - serialize data back to mission file

## TODO:
### MissionSQM.addEntity() - to add any type of entity to missionSQM class object
### Refactor parseCustomAttributes func to proper CustomAttributes mission.sqm field parsing

## Build:
### git clone https://github.com/ZarusSs/MissionSQMParser.git
### cd MissionSQMParser
### mkdir build
### cd build
### cmake ...
### make

</div>