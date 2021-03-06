/******************************************************************************
 *
 * Project:  SEG-P1 / UKOOA P1-90 Translator
 * Purpose:  Implements OGRSEGUKOOADriver.
 * Author:   Even Rouault, even dot rouault at mines dash paris dot org
 *
 ******************************************************************************
 * Copyright (c) 2011, Even Rouault <even dot rouault at mines-paris dot org>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMSEGUKOOAS OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 ****************************************************************************/

#include "ogr_segukooa.h"
#include "cpl_conv.h"

CPL_CVSID("$Id: ogrsegukooadriver.cpp 7e07230bbff24eb333608de4dbd460b7312839d0 2017-12-11 19:08:47Z Even Rouault $")

extern "C" void RegisterOGRSEGUKOOA();

/************************************************************************/
/*                                Open()                                */
/************************************************************************/

static GDALDataset *OGRSEGUKOOADriverOpen( GDALOpenInfo* poOpenInfo )
{
    if( poOpenInfo->eAccess == GA_Update ||
        poOpenInfo->fpL == nullptr ||
        poOpenInfo->pabyHeader[0] != 'H' )
    {
        return nullptr;
    }

    OGRSEGUKOOADataSource   *poDS = new OGRSEGUKOOADataSource();

    if( !poDS->Open( poOpenInfo->pszFilename ) )
    {
        delete poDS;
        poDS = nullptr;
    }

    return poDS;
}

/************************************************************************/
/*                           RegisterOGRSEGUKOOA()                       */
/************************************************************************/

void RegisterOGRSEGUKOOA()

{
    if( GDALGetDriverByName( "SEGUKOOA" ) != nullptr )
        return;

    GDALDriver *poDriver = new GDALDriver();

    poDriver->SetDescription( "SEGUKOOA" );
    poDriver->SetMetadataItem( GDAL_DCAP_VECTOR, "YES" );
    poDriver->SetMetadataItem( GDAL_DMD_LONGNAME, "SEG-P1 / UKOOA P1/90" );
    poDriver->SetMetadataItem( GDAL_DMD_HELPTOPIC, "drv_segukooa.html" );
    poDriver->SetMetadataItem( GDAL_DCAP_VIRTUALIO, "YES" );

    poDriver->pfnOpen = OGRSEGUKOOADriverOpen;

    GetGDALDriverManager()->RegisterDriver( poDriver );
}
