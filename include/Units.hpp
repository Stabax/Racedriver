#ifndef UNITS_HPP_
#define UNITS_HPP_

#include <omniunit.hh>

//Custom unit definition
template <typename Rep = OMNI_DEFAULT_TYPE>
using millinewtonHour2PerKilometer2 = omni::Unit<omni::Dimension<-1,1,0,0,0,0,0>, Rep, typename omni::Ratio_over_value<typename omni::Ratio_power<omni::Ratio<omni::secondsPerHour, omni::E3>, 2>::type, omni::E3>::type, omni::zero>;

typedef millinewtonHour2PerKilometer2<> MillinewtonHour2PerKilometer2;

template <typename Rep = OMNI_DEFAULT_TYPE>
using millinewtonHourPerKilometer = omni::Unit<omni::Dimension<0,1,-1,0,0,0,0>, Rep, omni::Ratio<omni::secondsPerHour, omni::E6>, omni::zero>;

typedef millinewtonHourPerKilometer<> MillinewtonHourPerKilometer;

#endif /* !UNITS_HPP_ */