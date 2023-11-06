#pragma once

#include <thread>
#include <functional>

using namespace std;

#define await ++

class future final
{
    template<class RT, class ...ATS>
    class task final
    {

    private:
        thread* task_thread;

    private:
        RT result = 0;

    private:
        bool can_detach = true;

    public:
        task(function<RT(ATS...)> target, ATS ... args)
        {
            auto task = [this, target, args...]() -> void { result = target(args...); };
            this->task_thread = new thread(task);
        }

        ~task()
        {
            if (this->can_detach) this->task_thread->detach();
            delete task_thread;
        }

    public:
        RT operator ++()
        {
            this->can_detach = false;
            this->task_thread->join();
            return result;
        }
    };

public:
    template<class RT, class ...ATS>
    static task<RT, ATS...> async(RT(*target)(ATS...), ATS ... args)
    {
        return task<RT, ATS...>(target, args...);
    }

    template<class ...ATS>
    static task<char, ATS...> async(void(*target)(ATS...), ATS ... args)
    {
        function<char(ATS...)> wrap = [target](ATS ... args) -> char { target(args...); return 0; };
        return task<char, ATS...>(wrap, args...);
    }
};