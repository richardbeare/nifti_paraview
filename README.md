nifti_paraview
==============

Testing and fixing the paraview nifti plugin

I started investigating the nifti plugin because I found that a
volume rendered image did not align with a mesh created using
a segmented version of the same image.

There are two potential issues. The first was that the
original plugin is broken - it mixes up use of voxels and
world coordinates, explicitly checks for values of 1 in the
sform/qform matrices. This means that images with voxel spacing
of less than 1mm will be incorrectly flipped. Also there is a fair bit
of repeated code.

The second issue is that nifti files can have a transformation
specified in their header. Paraview ignores this. Issues can be
avoided by resampling the image externally.

This patch fixes the problems with incorrect flipping, not extra
transforms. Perhaps we can deal with extra transforms later.

The other change I've made is in the naming of the data array. The
name is now based on the image filename, which will hopefully allow
multiple images with different colormaps.

I've explored loading of .nii.gz files - there seem to be problems
with the way some of the vtknifti files have been set up wrt to
ZLIB. There may be newer versions in VTK now. Something for the future.

Tests:
======

There are a series of test images, all derived from standard brain atlas
images that occupy the same space. They have different axis flipping, voxel
spacing and axis ordering. However the data in paraview should appear
in the same space. Loading these images with old versions of the plugin
will demonstrate a series of issues. 

In addition, I've annoted some of the images with hand drawn text, and
created a mesh object corresponding to this text (using itksnap).

Loading the mesh object and an image volume containing the annotation should
produce a scene with the mesh and volume rendering components overlaid.

Images are as follows - decompress before attempting to load:

MNI152_T1_0.5mm_anot.nii.gz - the standard 0.5 mm average brain with text.
MNI152_T1_0.5mm_anot_A.nii.gz - version with x and y axes flipped.
MNI152_T1_0.5mm_anot_B.nii.gz - version with y and z axes swapped.
MNI152_T1_2mm_brain.nii.gz - the standard template at 2mm resolution
rMNI152_T1_2mm_brain.nii.gz - the standard template resliced so that the y axis has 0.5mm voxels. 
MNI152_T1_2mm_brain_B.nii.gz - with z and y axes swapped.
RL_mask_dil.nii.gz - the text image (at 0.5mm)
RL_mask_2mm.nii.gz - the 2mm version of the text image.



--------------------------
Plugin files:

vtkNIfTIReader.h
vtkNIfTIReader.cxx

These go into

Plugins/AnalyzeNIfTIReaderWriter/

And replace files of the same name.

