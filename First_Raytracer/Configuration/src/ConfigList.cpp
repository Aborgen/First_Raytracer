#include "ConfigList.h"

namespace Controll
{
	bool ConfigList::operator==(const ConfigList &other) {
		return (
			this->size == other.size  &&
			this->depth == other.depth &&
			this->filename == other.filename
			);
	}

	std::pair<float, float> ConfigList::getSize()
	{
		return size;
	}

	void ConfigList::setSize(float height, float width)
	{
		size.first = height;
		size.second = width;
	}

	float ConfigList::getDepth()
	{
		return depth;
	}

	void ConfigList::setDepth(float depth)
	{
		this->depth = depth;
	}

	std::string ConfigList::getFilename()
	{
		return filename;
	}

	void ConfigList::setFilename(std::string filename)
	{
		this->filename = filename;
	}
}