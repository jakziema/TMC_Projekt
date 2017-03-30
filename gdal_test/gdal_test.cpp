// gdal_test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "gdal_priv.h"
#include "gdal.h"
#include "cpl_conv.h"
#include <iostream>
#include "ogrsf_frmts.h"


int main()

{
	OGRRegisterAll();

	OGRDataSource       *poDS;

	poDS = OGRSFDriverRegistrar::Open("map.shp", FALSE);
	if (poDS == NULL)
	{
		printf("Open failed.\n");
		exit(1);
	}

	OGRLayer  *poLayer;
	int layers;
	//layers = poDS->GetLayerCount();
	poLayer = poDS->GetLayer(0);
	//printf("Layers: %i ", layers);

	
	//poLayer = poDS->GetLayerByName("bridge");


	OGRFeature *poFeature;

	poLayer->ResetReading();
	while ((poFeature = poLayer->GetNextFeature()) != NULL)
	{
		OGRFeatureDefn *poFDefn = poLayer->GetLayerDefn();
		int iField;

		for (iField = 0; iField < poFDefn->GetFieldCount(); iField++)
		{
			OGRFieldDefn *poFieldDefn = poFDefn->GetFieldDefn(iField);

			if (poFieldDefn->GetType() == OFTInteger)
				printf("%d,", poFeature->GetFieldAsInteger(iField));
			else if (poFieldDefn->GetType() == OFTReal)
				printf("%.3f,", poFeature->GetFieldAsDouble(iField));
			else if (poFieldDefn->GetType() == OFTString)
				printf("%s,", poFeature->GetFieldAsString(iField));
			else
				printf("%s,", poFeature->GetFieldAsString(iField));
		}

		OGRGeometry *poGeometry;

		poGeometry = poFeature->GetGeometryRef();
		if (poGeometry != NULL
			&& wkbFlatten(poGeometry->getGeometryType()) == wkbPolygon)
		{
			OGRPolygon *poPoly = (OGRPolygon *)poGeometry;
			//poPoly->
				//mini xml
			const char * name = poFeature->GetFieldAsString("NAME_1");
			printf("A: %f  n: %s\n", (float)poPoly->get_Area(),name);
		}
		else
		{
			printf("no point geometry\n");
		}
		OGRFeature::DestroyFeature(poFeature);
	}

	OGRDataSource::DestroyDataSource(poDS);
	
}


