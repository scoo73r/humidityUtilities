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

    //enhanmentFactors over water and ice
    const double _efaw = 2.2;
    const double _efbw = 0.0383;
    const double _efcw = 6.4;

    const double _efai = 7.2;
    const double _efbi = 0.0320;
    const double _efci = 5.9;

    //air pressure in millibars
    double _airPressure = 1010.0;

    double f1(double temp);
    double f2(double vaporPressure, bool aboveFreezing);
    double enhancmentFactor(double temp);
    double enhancmentFactor(double temp, double a, double b, double c);

    double f1(double temp, double a, double b, double c, double d);
    double f2(double vaporPressure, double a, double b, double c, double d);

    double convertCelsiusToKelvin(double tempatureCelsius);
    double convertKelvinToCelsius(double tempatureKelvin);

public:
    void setAirPressure(double airPressure);
    double getAirPressure();
    double getSaturationPressure(double tempatureCelsius);

    double getDewPointFromVaporPressure(double vaporPressure, bool aboveFreezing = true);
    double getDewPointFromMixingRatio(double mixingRatio, bool aboveFreezing = true);
    double getDewPointFromRelativeHumidity(double relativeHumidity, double tempatureCelsius);
    double getDewPointFromAbsoluteHumidity(double absoluteHumidity, double tempatureKelvin);

    double getVaporPressureFromDewPoint(double dewPoint);
    double getVaporPressureFromMixingRatio(double mixingRatio);
    double getVaporPressureFromRelativeHumidity(double relativeHumidity, double tempatureCelsius);
    double getVaporPressureFromAbsoluteHumidity(double absoluteHumidity, double tempatureKelvin);

    double getMixingRatioFromVaporPressure(double vaporPressure, double molecularWeight = 28.97);
    double getMixingRatioFromDewPoint(double dewPoint, double molecularWeight = 28.97);
    double getMixingRatioFromRelativeHumidity(double relativeHumidity, double tempatureCelsius, double molecularWeight = 28.97);
    double getMixingRatioFromAbsoluteHumidity(double absoluteHumidity, double tempatureKelvin, double molecularWeight = 28.97);

    double getRelativeHumidityFromVaporPressure(double vaporPressure, double tempatureCelsius);
    double getRelativeHumidityFromMixingRatio(double mixingRatio, double tempatureCelsius);
    double getRelativeHumidityFromDewPoint(double dewPoint, double tempatureCelsius);
    double getRelativeHumidityFromAbsoluteHumidity(double absoluteHumidity, double tempatureKelvin);

    double getAbsoluteHumidityFromVaporPressure(double vaporPressure, double tempatureKelvin);
    double getAbsoluteHumidityFromMixingRatio(double mixingRatio, double tempatureKelvin);
    double getAbsoluteHumidityFromRelativeHumidity(double relativeHumidity, double tempatureCelsius);
    double getAbsoluteHumidityFromDewPoint(double dewPoint, double tempatureKelvin);
};

#endif // humid_h
