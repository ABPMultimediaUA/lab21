#ifndef GRAPHICNODE_H
#define GRAPHICNODE_H

#include <vector>

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
            Entity* getEntity();

            GraphicNode* getParent();
            void setParent(GraphicNode* parent);

            void draw();

        private:
            Entity*                     m_entity;
            std::vector<GraphicNode*>   m_childs;
            GraphicNode*                m_parent;
    };
}

#endif // GRAPHICNODE_H
