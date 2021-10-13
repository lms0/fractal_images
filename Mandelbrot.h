#pragma once

namespace caveofprogramming{

class Mandelbrot
{
public:
	static const int MAX_ITERATIONS = 1000;

public:
	static int getIterations(double x, double y);
};

}