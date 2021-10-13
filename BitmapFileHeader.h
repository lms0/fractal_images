
#ifndef BITMAPFILEHEADER_H_ // prevents multiple include files
#define BITMAPFILEHEADER_H_ // these are statements on the preprocessing language (ifndef, define, endinf)
// if not defined, pastes following code:

#include <cstdint> // to ensure code compatibilty for 4 bytes int

using namespace std;


namespace caveofprogramming 
{
#pragma pack(push, 2) // aligns the following struct in memory in 2 bytes, avoids extra padding

	struct BitmapFileHeader {
		char header[2]{'B','M'};
		int32_t fileSize;           // ensure compatibility 
		int32_t reserved{ 0 };
		int32_t dataOffset;
	};
#pragma pack(pop)

}


#endif // !BITMAPFILEHEADER_H_
