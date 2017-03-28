#ifndef NAVGRAPHEDGE_H
#define NAVGRAPHEDGE_H

class NavGraphEdge
{
    public:

        NavGraphEdge();
        NavGraphEdge(int f, int t, float c);

        virtual ~NavGraphEdge();

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

#endif // NAVGRAPHEDGE_H
