// gdal_test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "gdal_priv.h"
#include "cpl_conv.h"
#include <iostream>



//zamiana pixeli na wspolrzedne kartograficzne
double * pixelToMap(double P, double L, double * adfGeoTransform) {
	double tablicaWspl[2];

	tablicaWspl[0] = adfGeoTransform[0] + adfGeoTransform[1] * P + adfGeoTransform[2] * L;
	tablicaWspl[1] = adfGeoTransform[3] + adfGeoTransform[4] * P + adfGeoTransform[5] * L;

	return tablicaWspl;

}

//operacja odwrotna  - kartograczine -> piksele
double * mapToPixel(double X, double Y, double * adfGeoTransform) {


	//liczone wyznacznikami
	double W, Wx, Wy;
	double tablicaPlx[2];

	W = adfGeoTransform[1] * adfGeoTransform[5] - adfGeoTransform[4] * adfGeoTransform[2];
	Wx = adfGeoTransform[5] * (X - adfGeoTransform[0]) - adfGeoTransform[2] * (Y - adfGeoTransform[3]);
	Wy = adfGeoTransform[1] * (Y - adfGeoTransform[3]) - adfGeoTransform[4] * (X - adfGeoTransform[0]);

	tablicaPlx[0] = Wx / W;
	tablicaPlx[1] = Wy / W;

	return tablicaPlx;
}

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

		//Tutaj prowadzacy poda wam innne punkty zamiast 10 i 15
		double * result = pixelToMap(10, 15, adfGeoTransform);
		printf("X: %0.6f, Y: %0.6f\n", result[0], result[1]);

		// to co wyjdzie w funkcji wyzej wrzucacie zamiast 441320 ...
		double* result2 = mapToPixel(441320, 3750420, adfGeoTransform);
		printf("X: %0.6f, Y: %0.6f\n", result2[0], result2[1]);


	

		

	}

}

