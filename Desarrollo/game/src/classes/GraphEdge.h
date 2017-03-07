#ifndef GRAPHEDGE_H
#define GRAPHEDGE_H


class GraphEdge
{
    public:

        GraphEdge();
        GraphEdge(int f, int t, float c);

        virtual ~GraphEdge();

        int getFrom() const;
        void setFrom(int newIndex);

        int getTo() const;
        void setTo(int newIndex);

        float getCost() const;
        void setCost(float newCost);

    protected:

        int from;
        int to;

        float cost;

    private:
};

#endif // GRAPHEDGE_H
