#include "FractalCreator.h"
#include <assert.h> 

using namespace std;
using namespace caveofprogramming;

namespace caveofprogramming {

    void FractalCreator::run(string name) {

        calculateIteration();
        calculateRangeTotals();
        drawFractal();
        writeBitmap("test.bmp");
    }

    void FractalCreator::addRange(double rangeEnd, const RGB& rgb)
    {
        m_ranges.push_back(rangeEnd * Mandelbrot::MAX_ITERATIONS);
        m_colors.push_back(rgb);
        // ignore first addRange call, because it's the starting itaration = 0
        if (m_bGotFirstRange)
            m_pixelsPerRange.push_back(0);
        m_bGotFirstRange = true;

       
    }

    FractalCreator::FractalCreator(int width, int height) :
        m_width(width),
        m_height(height),
        m_bitmap(m_width, m_height),
        m_zoomList(m_width, m_height),
        m_histogram(new int[Mandelbrot::MAX_ITERATIONS]{ 0 }),
        m_pixelIterations(new int[m_width * m_height]{ 0 }) {

        // default zoom
        addZoom(Zoom(m_width / 2, m_height / 2, double(2.0) / width));

    }

	FractalCreator::~FractalCreator() {
    }

    void FractalCreator::calculateIteration() {
        pair<double, double> pair(0, 0);
        double xFractal = 0.0;
        double yFractal = 0.0;
        int iterations = 0;
        for (int y = 0; y < m_height; y++)
        {
            for (int x = 0; x < m_width; x++)
            {
                pair = m_zoomList.doZoom(x, y);
                xFractal = pair.first;
                yFractal = pair.second;

                // make histogram
                iterations = Mandelbrot::getIterations(xFractal, yFractal);
                if (iterations != Mandelbrot::MAX_ITERATIONS)
                    m_histogram[iterations]++;

                // store number of iterations per pixel
                m_pixelIterations[y * m_width + x] = iterations;

            }
        }

           
               
	}

    void FractalCreator::calculateRangeTotals() {
        // number of pixels in each range
        int rangeIndx = 0;
        for (int i = 0; i < Mandelbrot::MAX_ITERATIONS; i++)
        {
            if (i >= m_ranges[rangeIndx + 1])
            {
                rangeIndx++;
            }
            m_pixelsPerRange[rangeIndx] += m_histogram[i];
        }
        for (int value : m_pixelsPerRange) {
            cout << "range total: " << value << endl;
        }

   }

	void FractalCreator::drawFractal() {

        int total = 0;
        double hue = 0;
        int iterations = 0;
        for (int i = 0; i < Mandelbrot::MAX_ITERATIONS; i++)
        {
            total += m_histogram[i];
            
        }
        cout << "total is " << total << endl;

        for (int y = 0; y < m_height; y++)
        {
            for (int x = 0; x < m_width; x++)
            {
                iterations = m_pixelIterations[y * m_width + x];
                int range = getRange(iterations);
                int rangeTotalPixels = m_pixelsPerRange[range];
                int rangeStart = m_ranges[range];

                RGB& startColor = m_colors[range];
                RGB& endColor = m_colors[range + 1]; 
                RGB colorDiff = endColor - startColor;

                uint8_t red = 0;
                uint8_t green = 0; 
                uint8_t blue = 0;

                uint8_t color = (uint8_t)(256 * (double)iterations / Mandelbrot::MAX_ITERATIONS);

                if (iterations != Mandelbrot::MAX_ITERATIONS)
                {
                    int totalPixels = 0;
                    for (int i = rangeStart; i < iterations; i++)
                    {
                        totalPixels += (double)m_histogram[i];
                    }
                    red   = startColor.r + colorDiff.r  * (double)totalPixels / rangeTotalPixels;
                    green = startColor.g + colorDiff.g  * (double)totalPixels / rangeTotalPixels;
                    blue   = startColor.b + colorDiff.b * (double)totalPixels / rangeTotalPixels;
                    //green = pow(2, hue);
                }
                
                m_bitmap.setPixel(x, y, red, green, blue);
            }
        }
    
    }
	void FractalCreator::addZoom(const Zoom& zoom) {
        m_zoomList.add(zoom);
    }

    int FractalCreator::getRange(int iterations) const {
        int range = 0;
        // start analizing from second limit, as first limit is always 0
        for (int i = 1; i < m_ranges.size(); i++)
        {
            range = i;
            if (m_ranges[i] > iterations)
                break;
        }
        range--; 

        // assert throws a nice error if the condition is not fulfilled
        assert(range > -1);
        assert(range < m_ranges.size());

        return range;
    }

	void FractalCreator::writeBitmap(string name) {
        m_bitmap.write(name);
        cout << "wrote bitmap" << endl;
    }


}