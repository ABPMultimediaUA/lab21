#ifndef TAG_GRAPHICNODE_H
#define TAG_GRAPHICNODE_H

#include <vector>
#include "tag/Types.h"

namespace tag
{
    class Entity;

    class GraphicNode
    {
        public:
            GraphicNode();
            ~GraphicNode();

            unsigned int addChild(GraphicNode* n);
            unsigned int removeChild(const GraphicNode* n);

            bool setEntity(Entity* e);
            Entity* getEntity() const;

            GraphicNode* getParent() const;
            void setParent(GraphicNode* parent);

            bool isEmptyNode() const;

            void draw();

            vec3f getBoundingBox();

        private:
            Entity*                     m_entity;
            std::vector<GraphicNode*>   m_childs;
            GraphicNode*                m_parent;
    };
}

#endif // GRAPHICNODE_H
