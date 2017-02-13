#ifndef NAVGRAPHNODE_H
#define NAVGRAPHNODE_H

class NavGraphNode
{
    public:

        NavGraphNode(){};

        NavGraphNode(int idx, dwe::vec3f);

        virtual ~NavGraphNode();

        int getIndex() const;
        void setIndex(int idx);

        dwe::vec2f getPosition() const;
        void setPosition(dwe::vec2f pos);

    protected:

    private:

        int index;
        dwe::vec3f position;

};

#endif // NAVGRAPHNODE_H
