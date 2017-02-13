#ifndef WAYPOINT_H
#define WAYPOINT_H


class Waypoint
{
    public:

        Waypoint(){};

        Waypoint(int idx, dwe::vec3f);

        virtual ~Waypoint();

        int getIndex() const;
        void setIndex(int idx);

        dwe::vec2f getPosition() const;
        void setPosition(dwe::vec2f pos);

    protected:

    private:

        int index;
        dwe::vec3f position;
};

#endif // WAYPOINT_H
