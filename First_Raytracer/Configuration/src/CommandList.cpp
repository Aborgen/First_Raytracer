#include "CommandList.h"

namespace Controll
{
	bool CommandList::operator==(const CommandList &other) {
		return (
			this->size == other.size  &&
			this->depth == other.depth &&
			this->filename == other.filename
			);
	}

	std::pair<float, float> CommandList::getSize()
	{
		return size;
	}

	void CommandList::setSize(float height, float width)
	{
		size.first = height;
		size.second = width;
	}

	float CommandList::getDepth()
	{
		return depth;
	}

	void CommandList::setDepth(float depth)
	{
		this->depth = depth;
	}

	std::string CommandList::getFilename()
	{
		return filename;
	}

	void CommandList::setFilename(std::string filename)
	{
		this->filename = filename;
	}
}