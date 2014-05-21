/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkNIfTIReader.h

  Copyright (c) Joseph Hennessey
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
// .NAME vtkNIfTIReader - read NIfTI files
// .SECTION Description
// vtkNIfTIReader is a source object that reads NIfTI files.
// It should be able to read most any NIfTI file
//
// .SECTION See Also
// vtkNIfTIWriter vtkAnalyzeReader vtkAnalyzeWriter

#ifndef __vtkNIfTIReader_h
#define __vtkNIfTIReader_h

#include "vtkImageReader.h"

#define NIFTI_HEADER_ARRAY "vtkNIfTIReaderHeaderArray"
#define POINT_SPACE_ARRAY "vtkPointSpace"
#define VOLUME_ORIGIN_DOUBLE_ARRAY "vtkVolumeOrigin"
#define VOLUME_SPACING_DOUBLE_ARRAY "vtkVolumeSpacing"

class vtkDataArray;
class vtkUnsignedCharArray;
class vtkFieldData;

class vtkNIfTIReader : public vtkImageReader
{
public:
  static vtkNIfTIReader *New();
  vtkTypeMacro(vtkNIfTIReader,vtkImageReader);
  virtual void PrintSelf(ostream& os, vtkIndent indent);

  // Description: is the given file name a png file?
  virtual int CanReadFile(const char* fname);

  // Description:
  // Get the file extensions for this format.
  // Returns a string with a space separated list of extensions in
  // the format .extension
  virtual const char* GetFileExtensions()
  {
    return ".nii .img .hdr";
  }

  // Description:
  // Return a descriptive name for the file format that might be useful in a GUI.
  virtual const char* GetDescriptiveName()
  {
    return "NIfTI";
  }

  char * GetFileName(){return(FileName);};
  unsigned int getImageSizeInBytes(){return(imageSizeInBytes);};

protected:
  vtkNIfTIReader();
  ~vtkNIfTIReader();

  virtual void ExecuteInformation();
  virtual void ExecuteDataWithInformation(vtkDataObject *output, vtkInformation* outInfo);

private:
  vtkNIfTIReader(const vtkNIfTIReader&);  // Not implemented.
  void operator=(const vtkNIfTIReader&);  // Not implemented.

  unsigned int numberOfDimensions;
  unsigned int imageSizeInBytes;
  unsigned int Type;
  int width;
  int height;
  int depth;

  double dataTypeSize;
  double **q;
  double **s;
  int sform_code;
  int qform_code;
  int niftiType;

  vtkUnsignedCharArray *niftiHeader;
  unsigned char * niftiHeaderUnsignedCharArray;
  int niftiHeaderSize;

  // information to do with axis permutation and flipping
  int inIncrements[3];
  int outIncrements[3];
  double inExtent[6];
  double outExtent[6];
  double inSpacing[3];

  int inDim[3];
  int outDim[3];
  double inOriginOffset[3];
  double flippedOriginOffset[3];
  double outPreFlippedOriginOffset[3];
  double outPostFlippedOriginOffset[3];
  double outNoFlipOriginOffset[3];
  double outOriginOffset[3];
  double outSpacing[3];

  int InPlaceFilteredAxes[3];
  int flipAxis[3];
  int flipIndex[3];
  int inStride[3];
  int outStride[3];

  bool flipNeeded;
  bool permuteNeeded;
};
#endif
