#include <humidity.h>
#include <math.h>

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

//Saturation vapor pressure (es) = f1(T) = e/RH
double Humidity::getSaturationPressure(double tempatureCelsius)
{
    return f1(tempatureCelsius);
}

double Humidity::getDewPointFromVaporPressure(double vaporPressure, bool aboveFreezing)
{
    return f2(vaporPressure, aboveFreezing);
}
double Humidity::getDewPointFromMixingRatio(double mixingRatio, bool aboveFreezing)
{
    return f2(getVaporPressureFromMixingRatio(mixingRatio), aboveFreezing);
}
double Humidity::getDewPointFromRelativeHumidity(double relativeHumidity, double tempatureCelsius)
{
    return f2(getVaporPressureFromRelativeHumidity(relativeHumidity, tempatureCelsius), tempatureCelsius > 0);
};
double Humidity::getDewPointFromAbsoluteHumidity(double absoluteHumidity, double tempatureKelvin)
{
    return f2(getVaporPressureFromAbsoluteHumidity(absoluteHumidity, tempatureKelvin), tempatureKelvin > 273.15);
}

double Humidity::getVaporPressureFromDewPoint(double dewPoint)
{
    return f1(dewPoint);
}
double Humidity::getVaporPressureFromMixingRatio(double mixingRatio)
{
    return mixingRatio * (_airPressure / (622.0e3 + mixingRatio));
}
double Humidity::getVaporPressureFromRelativeHumidity(double relativeHumidity, double tempatureCelsius)
{
    return relativeHumidity * (f1(tempatureCelsius) / 100);
}
double Humidity::getVaporPressureFromAbsoluteHumidity(double absoluteHumidity, double tempatureKelvin)
{
    return absoluteHumidity * (tempatureKelvin / 216.7);
}

double Humidity::getMixingRatioFromVaporPressure(double vaporPressure, double molecularWeight)
{
    return (18.02 / molecularWeight) * 1e6 * (vaporPressure / (_airPressure - vaporPressure));
}
double Humidity::getMixingRatioFromDewPoint(double dewPoint, double molecularWeight)
{
    return (18.02 / molecularWeight) * 1e6 * (f1(dewPoint) / (_airPressure - f1(dewPoint)));
}
double Humidity::getMixingRatioFromRelativeHumidity(double relativeHumidity, double tempatureCelsius, double molecularWeight)
{
    return (18.02 / molecularWeight) * 1e6 * relativeHumidity * (getSaturationPressure(tempatureCelsius) / (100 * _airPressure - relativeHumidity * getSaturationPressure(tempatureCelsius)));
}
double Humidity::getMixingRatioFromAbsoluteHumidity(double absoluteHumidity, double tempatureKelvin, double molecularWeight)
{
    return (18.02 / molecularWeight) * 1e6 * absoluteHumidity * (tempatureKelvin / (216.7 * _airPressure - absoluteHumidity * tempatureKelvin));
}

double Humidity::getRelativeHumidityFromVaporPressure(double vaporPressure, double tempatureCelsius)
{
    return 100 * (vaporPressure / getSaturationPressure(tempatureCelsius));
}
double Humidity::getRelativeHumidityFromMixingRatio(double mixingRatio, double tempatureCelsius)
{
    return 100 * mixingRatio * (_airPressure / ((622e3 + mixingRatio) * getSaturationPressure(tempatureCelsius)));
}
double Humidity::getRelativeHumidityFromDewPoint(double dewPoint, double tempatureCelsius)
{
    return 100 * (f1(dewPoint) / f1(tempatureCelsius));
}
double Humidity::getRelativeHumidityFromAbsoluteHumidity(double absoluteHumidity, double tempatureKelvin)
{
    return 100 * absoluteHumidity * (tempatureKelvin / (216.7 * getSaturationPressure(convertKelvinToCelsius(tempatureKelvin))));
}

double Humidity::getAbsoluteHumidityFromVaporPressure(double vaporPressure, double tempatureKelvin)
{
    return 216.7 * (vaporPressure / tempatureKelvin);
}
double Humidity::getAbsoluteHumidityFromMixingRatio(double mixingRatio, double tempatureKelvin)
{
    return 0.2167 * mixingRatio * (_airPressure / ((622.001 * mixingRatio) * tempatureKelvin));
}
double Humidity::getAbsoluteHumidityFromRelativeHumidity(double relativeHumidity, double tempatureCelsius)
{
    return 216.7 * relativeHumidity * (getSaturationPressure(tempatureCelsius) / (100 * convertCelsiusToKelvin(tempatureCelsius)));
}
double Humidity::getAbsoluteHumidityFromDewPoint(double dewPoint, double tempatureKelvin)
{
    return 216.7 * (f1(dewPoint) / tempatureKelvin);
}

double Humidity::enhancmentFactor(double temp)
{
    if (temp > 0)
    {
        return enhancmentFactor(temp, _efaw, _efbw, _efcw);
    }
    else
    {
        return enhancmentFactor(temp, _efai, _efbi, _efci);
    }
}

double Humidity::f1(double temp)
{
    if (temp > 0)
    {
        return f1(temp, _aw, _bw, _cw, _dw);
    }
    else
    {
        return f1(temp, _ai, _bi, _ci, _di);
    }
}

double Humidity::f2(double vaporPressure, bool aboveFreezing)
{
    if (aboveFreezing)
    {
        return f2(vaporPressure, _aw, _bw, _cw, _dw);
    }
    else
    {
        return f2(vaporPressure, _ai, _bi, _ci, _di);
    }
}

double Humidity::enhancmentFactor(double temp, double a, double b, double c)
{
    return 1 + 1e4 * (a + _airPressure * (b + c * 1e-6 * pow(temp, 2)));
}

double Humidity::f1(double temp, double a, double b, double c, double d)
{
    double ef = enhancmentFactor(temp);
    return ef * a * exp((b - (temp / d)) * temp / (temp + c));
}

double Humidity::f2(double vaporPressure, double a, double b, double c, double d)
{
    double s = log(vaporPressure) - log(a);
    return d / 2 * (b - s - pow((pow(b - s, 2) - 4 * c * s / d), .5));
}

void Humidity::setAirPressure(double airPressure)
{
    _airPressure = airPressure;
}

double Humidity::getAirPressure()
{
    return _airPressure;
}

double Humidity::convertCelsiusToKelvin(double tempatureCelsius)
{
    return tempatureCelsius + 273.15;
}

double Humidity::convertKelvinToCelsius(double tempatureKelvin)
{
    return tempatureKelvin - 273.15;
}