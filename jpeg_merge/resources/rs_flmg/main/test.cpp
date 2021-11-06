#include <stdio.h>
#include <stdlib.h>
#include "jpeg_encoder.h"

//-------------------------------------------------------------------------------
int main(int argc, char* argv[])
{
	if(argc<3)
	{
		printf("Usage: %s inputFile Compress_rate\n\tInput file must be 24bit PPM file.\n", argv[0]);
		return 1;
	}

	const char* inputFileName = argv[1];
	int compress_rate = atoi(argv[2]);

	JpegEncoder encoder;
	if(!encoder.readFromPPM(inputFileName))
	{
		printf("Reading ppm file incorrect.\n");

		return 1;
	}

  if(!encoder.encodeToJPG("./out.jpg", compress_rate))
  {
		printf("Encording JPEG file incorrect.\n");

  	return 1;
  }
	if(!encoder.encodeToJPGbw("./outbw.jpg", compress_rate))
	{
		printf("Encording JPEG file incorrect.\n");

		return 1;
	}

	return 0;
}
