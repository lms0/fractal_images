#pragma once

#include<iostream>
#include<string>
#include<vector>
#include "ZoomList.h"
#include "Bitmap.h"
#include "Mandelbrot.h"
#include "RGB.h"


using namespace std;

namespace caveofprogramming {

class FractalCreator
{
	int m_width{ 0 };
	int m_height{ 0 };
	Bitmap m_bitmap;
	ZoomList m_zoomList;
	unique_ptr<int[]> m_histogram;
	unique_ptr<int[]> m_pixelIterations;
	
	vector<int> m_ranges;
	vector<RGB> m_colors;
	vector<int> m_pixelsPerRange;
	bool m_bGotFirstRange{ false };

	void calculateIteration();
	void drawFractal();
	void calculateRangeTotals();
	void writeBitmap(string name);

public:
	FractalCreator(int width, int height);
	int getRange(int iterations) const;
	void addRange(double rangeEnd, const RGB& rgb);
	void addZoom(const Zoom& zoom);
	virtual ~FractalCreator();
	void run(string name);
};

}