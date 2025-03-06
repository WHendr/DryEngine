#ifndef DRY_GRAPHICS_FAMILY_MAN_H
#define DRY_GRAPHICS_FAMILY_MAN_H

#include <QueueFamilyIndices.h>
#include "Surface.h"

namespace Dry::Graphics
{

class QueueFamilyMan
{
public:
	static void Create(Surface& surface);
	static QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);


private:
	QueueFamilyMan(Surface& surface);
	Surface* p_Surface;
	static QueueFamilyMan& GetInstance();
	static QueueFamilyMan* pos_Instance;
};

}

#endif // !DRY_GRAPHICS_FAMILY_MAN_H