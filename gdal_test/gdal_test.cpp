// gdal_test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "gdal_priv.h"
#include "cpl_conv.h"
#include <iostream>


int main()
{	
	GDALDataset *poDataset;
	GDALAllRegister();
	double adfGeoTransform[6];
	double Xp;
	double Yp;
	poDataset = (GDALDataset *)GDALOpen("C:\\Users\\Beata-MacBook\\Desktop\\TMC\\gdal_test\\test.tiff", GA_ReadOnly);

	if (poDataset == NULL) {

		printf("Dataset is null");
	}
	else {
		
		//adfGeoTransform[0] /* top left x */
		//adfGeoTransform[1] /* w-e pixel resolution */
		//adfGeoTransform[2] /* 0 */
		//adfGeoTransform[3] /* top left y */
		//adfGeoTransform[4] /* 0 */
		//adfGeoTransform[5] /* n-s pixel resolution (negative value) */
	
		printf("Nazwa sterownika: %s%s\n", poDataset->GetDriver()->GetDescription(), poDataset->GetDriver()->GetMetadataItem(GDAL_DMD_LONGNAME));
		printf("Rozmiar: %dx%d Liczba kanalow: %d\n",
			poDataset->GetRasterXSize(), poDataset->GetRasterYSize(),
			poDataset->GetRasterCount());
		if (poDataset->GetProjectionRef() != NULL)
			printf("Projection is `%s'\n", poDataset->GetProjectionRef());
		if (poDataset->GetGeoTransform(adfGeoTransform) == CE_None)
		{
			printf("Origin = (%.6f,%.6f)\n",
				adfGeoTransform[0], adfGeoTransform[3]);
			printf("Pixel Size = (%.6f,%.6f)\n",
				adfGeoTransform[1], adfGeoTransform[5]);
		}

		std::cout << "Podaj wspolrzedna x: ";
		std::cin >> Xp;
		std::cout << "Podaj wspolrzedna y: ";
		std::cin >> Yp;

	}

}

