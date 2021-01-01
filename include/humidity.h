#if !defined(humid_h)
#define humid_h

class Humidity
{
private:
    //Constants over Water
    const double _aw = 6.1121;
    const double _bw = 18.678;
    const double _cw = 257.14;
    const double _dw = 234.5;
    //Constants over Ice
    const double _ai = 6.1115;
    const double _bi = 23.036;
    const double _ci = 279.82;
    const double _di = 333.7;

    //Pressure level in millibars
    //Currently defaulted to just above sea level.
    double _airPressure = 1010.0;

    double f1AboveFreezing(double dp);
    double f1BelowFreezing(double dp);
    double f2AboveFreezing(double e);
    double f1BelowFreezing(double e);

public:
    Humidity();
    ~Humidity();
    /*
    DP = dew or frost point in deg C
    e = vapor pressure in millibars
    es = saturation vapor pressure in millibars
    P = pressure in millibars
    r = mixing ratio by weight in ppm
    RH = relative humidity in percent
    rho = absolute humidity in g/m3
    rhos = absolute humidity at saturation
    T = temperature in deg C
    Tk = absolute temperature in K
*/
    double getSaturationPressure(double tempatureCelsius);

    double getDewPointFromVaporPressure(double vaporPressure);
    double getDewPointFromMixingRatio(double mixingRatio);
    double getDewPointFromRelativeHumidity(double relativeHumidity);
    double getDewPointFromAbsoluteHumidity(double absoluteHumidity);

    double VaporPressureFromDewPoint(double dewPoint);
    double VaporPressureFromMixingRatio(double mixingRatio);
    double VaporPressureFromRelativeHumidity(double relativeHumidity);
    double VaporPressureFromAbsoluteHumidity(double absoluteHumidity);

    double getMixingRatioFromVaporPressure(double vaporPressure);
    double getMixingRatioFromDewPoint(double dewPoint);
    double getMixingRatioFromRelativeHumidity(double relativeHumidity);
    double getMixingRatioFromAbsoluteHumidity(double absoluteHumidity);

    double getRelativeHumidityFromVaporPressure(double vaporPressure);
    double getRelativeHumidityFromMixingRatio(double mixingRatio);
    double getRelativeHumidityFromDewPoint(double dewPoint);
    double getRelativeHumidityFromAbsoluteHumidity(double absoluteHumidity);

    double getAbsoluteHumidityFromVaporPressure(double vaporPressure);
    double getAbsoluteHumidityFromMixingRatio(double mixingRatio);
    double getAbsoluteHumidityFromRelativeHumidity(double relativeHumidity);
    double getAbsoluteHumidityFromDewPoint(double dewPoint);
};

Humidity::Humidity()
{
}

Humidity::~Humidity()
{
}

#endif // humid_h
