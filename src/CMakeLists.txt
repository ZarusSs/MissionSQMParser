aux_source_directory(entities ENTITIES_SRC_FILES)
aux_source_directory(MissionSQMStructures MISSIONSQM_SRC_FILES)
aux_source_directory(stringUtils UTILS_SRC_FILES)

add_library(
        parserSQM
        STATIC
        Parser.cpp
        ${ENTITIES_SRC_FILES}
        ${MISSIONSQM_SRC_FILES}
        ${UTILS_SRC_FILES}
)

target_include_directories(
        parserSQM
        PUBLIC
        ${INCLUDE_DIR}
)