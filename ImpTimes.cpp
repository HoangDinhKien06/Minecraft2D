#include "ImpTimes.h"
ImpTimer::ImpTimer()
{
    start_tick_=0;
    pau_tick_=0;
    is_paued_=false;
    is_started_=false;
}
ImpTimer::~ImpTimer()
{

}
void ImpTimer::start()
{
    is_started_=true;
    is_paued_=false;
    start_tick_=SDL_GetTicks();
}
void ImpTimer::stop()
{
    is_paued_=false;
    is_started_=false;
}
void ImpTimer::paued()
{
    if(is_started_==true&& is_paued_==false)
    {
        is_paued_=true;
        pau_tick_=SDL_GetTicks()-start_tick_;
    }
}
void ImpTimer::unpaused()
{
    if(is_paued_==true)
    {
        is_paued_=false;
        start_tick_=SDL_GetTicks()-pau_tick_;
        pau_tick_=0;
    }
}
int ImpTimer::get_ticks()
{
    if(is_started_==true)
    {
        if(is_paued_==true)
        {
            return pau_tick_;
        }
        else{
            return SDL_GetTicks()-start_tick_;
        }
    }
    return 0;
}
bool ImpTimer::is_started()
{
    return is_started_;
}
bool ImpTimer::is_paued()
{
    return is_paued_;
}
