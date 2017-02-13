#ifndef PATHPLANNING_H
#define PATHPLANNING_H



class Pathplanning
{
    public:

        Pathplanning(Enemy *owner);

        virtual ~Pathplanning();

        void CreatePathToPosition(dwe::vec2f TargetPos, std::list<dwe::vec2f& path);

    protected:

    private:

        Enemy* m_pOwner;

        const NavGraph& m_NavGraph;

        dwe::vec2f targetPosition;

        int GetClosestNodeToPosition(dwe::vec2f pos)const;
};


#endif
