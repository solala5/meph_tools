#include "runtime_meter.h"



runtime_meter::runtime_meter(string ID, long precision, ostream* os = nullptr) :
ID(ID),
inUse(false),
os(os)
{
	setPrecision(precision);
	QueryPerformanceFrequency(&frequency);
	start();
}


runtime_meter::~runtime_meter()
{
	stop();	
}

void runtime_meter::start()
{
		QueryPerformanceCounter(&begin);
}

double runtime_meter::stop()
{  
	QueryPerformanceCounter(&end);
	double interval = (double)(end.QuadPart - begin.QuadPart) * precision / frequency.QuadPart;
	return interval;
}

void runtime_meter::setPrecision(long prec)
{
	this->precision = prec;
}


string runtime_meter::precisionToString(double prec, bool longFormat)
{
	if (longFormat)
	{
		if (prec == 1) return "seconds";
		else if (prec == 1000) return "milliseconds";
		else if (prec == 1000000) return "microseconds";
		else if (prec == 1000000000) return "nanoseconds";
		else if (prec == (1 / 60.0)) return "minutes";
		else if (prec == (1 / 3600.0)) return "hours";
		else if (prec == (1 / 86400.0)) return "days";
	}
	else
	{
		if (prec == 1) return "s";
		else if (prec == 1000) return "ms";
		else if (prec == 1000000) return "µs";
		else if (prec == 1000000000) return "ns";
		else if (prec == (1 / 60.0)) return "m";
		else if (prec == (1 / 3600.0)) return "h";
		else if (prec == (1 / 86400.0)) return "d";
	}
}

void runtime_meter::streamInterval(const double& interval)
{
	if (os)
	{
		*os << "Runtime Measurement : " << ID << " | " << interval << " " << precisionToString(precision);
	}
}
