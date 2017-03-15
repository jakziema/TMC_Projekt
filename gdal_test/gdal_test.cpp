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
	double Xw, Yw, Xp, Yp, Wx, Wy, W;
	

	poDataset = (GDALDataset *)GDALOpen("C:\\Users\\Beata-MacBook\\Desktop\\TMC\\gdal_test\\landsat.tif", GA_ReadOnly);

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

		//std::cout << "Podaj wspolrzedna P: ";
		//std::cin >> Xw;
		//std::cout << "Podaj wspolrzedna L: ";
		//std::cin >> Yw;

		Xw = 13.0;
		Yw = 14.0;
		W = adfGeoTransform[1] * adfGeoTransform[5] - adfGeoTransform[4] * adfGeoTransform[2];
		Wx = adfGeoTransform[5] * (Xw - adfGeoTransform[0]) - adfGeoTransform[2] * (Yw - adfGeoTransform[3]);
		Wy = adfGeoTransform[1] * (Yw - adfGeoTransform[3]) - adfGeoTransform[4] * (Xw - adfGeoTransform[0]);

		Xp = Wx / W;
		Yp = Wy / W;
		//printf("Xp: %d\nYp: %d ", Xp, Yp);

		

	}

}

