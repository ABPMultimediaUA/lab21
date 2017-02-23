#ifndef GRAPHICNODE_H
#define GRAPHICNODE_H

#include <vector>

namespace dwe
{
    class Entity;

    class GraphicNode
    {
        public:
            GraphicNode();
            ~GraphicNode();

            unsigned int addChild(GraphicNode* n);
            unsigned int removeChild(const GraphicNode* n);

            bool setEntity(dwe::Entity* e);
            Entity* getEntity();
            GraphicNode* getParent();

            void draw();

        private:
            Entity*                     m_entity;
            std::vector<GraphicNode*>   m_childs;
            GraphicNode*                m_parent;
    };
}

#endif // GRAPHICNODE_H
