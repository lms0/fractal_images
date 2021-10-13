#pragma once
namespace caveofprogramming {

struct Zoom {
		int x{ 0 };
		int y{ 0 };
		double scale{ 1.0 };
		Zoom() {};
		Zoom(int x, int y, double s) :
		x(x), y(y), scale(s) {
		}
};


}