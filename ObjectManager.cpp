#include "ObjectManager.h"
#include "Object.h"


void ObjectManager::RenderObjects(int index, int numBarsToDraw, double minValue, double maxValue)
{
    for (unsigned int i = 0; i < objects.size(); ++ i)
    {
        if (objects[i]->IsInScreen(index, numBarsToDraw))
            objects[i]->Render(index, numBarsToDraw, minValue, maxValue);
    }
}