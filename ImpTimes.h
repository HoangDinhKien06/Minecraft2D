#ifndef IMP_TIMER_H_
#define IMP_TIMER_H_
#include "CommonFunc.h"
class ImpTimer
{
public:
    ImpTimer();
    ~ImpTimer();

    void start();
    void stop();
    void paued();
    void unpaused();
    int get_ticks();

    bool is_started();
    bool is_paued();

private:
    int start_tick_;
    int pau_tick_;

    bool is_paued_;
    bool is_started_;

};
#endif
