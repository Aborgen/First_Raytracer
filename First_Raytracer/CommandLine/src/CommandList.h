#pragma once
#include <list>
#include <string>
class CommandList
{
public:
	bool operator==(const CommandList &other);

	std::pair<float, float> getSize();
	void setSize(float height, float width);
	float getDepth();
	void setDepth(float depth);
	std::string getFilename();
	void setFilename(std::string filename);

private:
	std::pair<float, float> size = std::pair<float, float>(50.0f, 50.0f);
	float depth = 1.0f;
	std::string filename;
};