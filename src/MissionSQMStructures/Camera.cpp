#include "MissionSQMStructures/Camera.h"

std::string Camera::toString(int indentLevel) const
{
	std::stringstream outStream;

	auto indStr{ indent(indentLevel) };
	auto declIndStr{ indent(indentLevel - 1) };

	outStream << declIndStr << "class Camera\n";
	outStream << declIndStr << "{\n";
	outStream << indStr << "pos[]=" << strArray<double>(pos) << ";\n";
	outStream << indStr << "dir[]=" << strArray<double>(dir) << ";\n";
	outStream << indStr << "up[]=" << strArray<double>(up) << ";\n";
	outStream << indStr << "aside[]=" << strArray<double>(aside) << ";\n";
	outStream << declIndStr << "};\n";

	return outStream.str();
}

