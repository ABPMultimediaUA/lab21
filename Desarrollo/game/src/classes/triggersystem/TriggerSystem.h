#ifndef TRIGGERSYSTEM_H
#define TRIGGERSYSTEM_H

#include <vector>

class Trigger;

class TriggerSystem
{
    public:

        TriggerSystem();

        virtual ~TriggerSystem();

        void Update();

        void Add(Trigger* newTrigger);

        void Remove(int i);

    protected:

    private:

        std::vector<Trigger*> m_triggers;
};

#endif // TRIGGERSYSTEM_H
