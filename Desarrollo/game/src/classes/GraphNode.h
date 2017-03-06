#ifndef GRAPHNODE_H
#define GRAPHNODE_H

class GraphNode
{
    public:

        GraphNode();
        GraphNode(int idx);

        virtual ~GraphNode();

        int getIndex()const;
        void setIndex(int newIndex);

    protected:

        int index;

    private:
};

#endif // GRAPHNODE_H
