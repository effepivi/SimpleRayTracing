/**
 ********************************************************************************
 *
 *   @file       Image.cxx
 *
 *   @brief      Class to manage 2D RGB images.
 *
 *   @version    1.0
 *
 *   @date       06/10/2020
 *
 *   @author     Dr Franck P. Vidal
 *
 ********************************************************************************
 */


//******************************************************************************
//  Include
//******************************************************************************
#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <stdio.h>
#include <jerror.h>
#include <jpeglib.h>

#ifndef __Image_h
#include "Image.h"
#endif

//----------------------------------------------------------
Image::Image(const Image& anImage):
//----------------------------------------------------------
        m_p_pixel_data(0),
        m_width(anImage.m_width),
        m_height(anImage.m_height)
//----------------------------------------------------------
{
    // The image size is set and there is some data to copy
    if (m_width && m_height && anImage.m_p_pixel_data)
    {
        // Allocate memory
        m_p_pixel_data = new unsigned char[3 * m_width * m_height];

        // Copy the data
        memcpy(m_p_pixel_data, anImage.m_p_pixel_data, sizeof(unsigned char) * 3 * m_width * m_height);
    }
}


//-------------------------------------------
Image& Image::operator=(const Image& anImage)
//-------------------------------------------
{
    // Release the memory
    destroy();

    // The image size is set and there is some data to copy
    if (anImage.m_width && anImage.m_height && anImage.m_p_pixel_data)
    {
        // Allocate memory
        setSize(anImage.m_width, anImage.m_height);

        // Copy the data
        memcpy(m_p_pixel_data,
                anImage.m_p_pixel_data,
                sizeof(unsigned char) * 3 * anImage.m_width * anImage.m_height);
    }

    // Copy the image properties
    m_width = anImage.m_width;
    m_height = anImage.m_height;

    // Return the current image
    return (*this);
}


//---------------------------------------------
void Image::loadJPEGFile(const char* aFileName)
//---------------------------------------------
{
    // Allocate and initialize a JPEG decompression object
    struct jpeg_decompress_struct cinfo;
    struct jpeg_error_mgr jerr;
    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_decompress(&cinfo);

    // Specify the source of the compressed data (eg, a file)
    FILE* p_input_file(fopen(aFileName, "rb"));
    if (!p_input_file)
    {
        std::stringstream error_message;
        error_message << "Cannot open the file " << aFileName << ", in File " << __FILE__ <<
            ", in Function " << __FUNCTION__ <<
            ", at Line " << __LINE__;

        throw std::runtime_error(error_message.str());
    }
    jpeg_stdio_src(&cinfo, p_input_file);

    // Call jpeg_read_header() to obtain image info
    if (!JPEG_HEADER_OK == jpeg_read_header(&cinfo, TRUE))
    {
        std::string error_message;
        error_message += "Cannot read file \"";
        error_message += aFileName;
        error_message += "\".";

        throw error_message;
    }

    // Set parameters for decompression
/*    cinfo.dct_method = JDCT_IFAST;
    cinfo.do_fancy_upsampling = FALSE;
    cinfo.two_pass_quantize = FALSE;
    cinfo.dither_mode = JDITHER_ORDERED;
    cinfo.scale_num = 1;
    cinfo.scale_denom = 8;
    */
    // Start decompression
    jpeg_start_decompress(&cinfo);

    // Save the size of the image
    unsigned int width(cinfo.output_width);
    unsigned int height(cinfo.output_height);
    setSize(width, height);

    // Decompress data
    JSAMPROW row_pointer[1];        // pointer to a single row
    int row_stride;                 // physical row width in buffer

    if (cinfo.out_color_space == JCS_RGB)
    {
        row_stride = m_width * 3;   // JSAMPLEs per row in image_buffer
    }
    else if (cinfo.out_color_space == JCS_GRAYSCALE)
    {
        row_stride = m_width;   // JSAMPLEs per row in image_buffer
    }
    // Unknown colour space
    else
    {
        std::stringstream error_message;
        error_message << " in File " << __FILE__ <<
            ", in Function " << __FUNCTION__ <<
            ", at Line " << __LINE__;

        throw std::runtime_error(error_message.str());
    }

    while (cinfo.output_scanline < cinfo.output_height)
    {
        row_pointer[0] = & m_p_pixel_data[cinfo.output_scanline * row_stride];
        jpeg_read_scanlines(&cinfo, row_pointer, 1);
    }

    // Finish decompression
    jpeg_finish_decompress(&cinfo);

    // Release the JPEG decompression object
    jpeg_destroy_decompress(&cinfo);
}



//---------------------------------------------
void Image::saveJPEGFile(const char* aFileName)
//---------------------------------------------
{

    // Allocate and initialize a JPEG compression object
    struct jpeg_compress_struct cinfo;
    struct jpeg_error_mgr jerr;
    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_compress(&cinfo);

    // Specify the destination for the compressed data (eg, a file)
    FILE* p_output_file(fopen(aFileName, "wb"));
    if (!p_output_file)
    {
        std::stringstream error_message;
        error_message << "Cannot create the file " << aFileName << ", in File " << __FILE__ <<
            ", in Function " << __FUNCTION__ <<
            ", at Line " << __LINE__;

        throw std::runtime_error(error_message.str());
    }
    jpeg_stdio_dest(&cinfo, p_output_file);

    // Set parameters for compression, including image size & colorspace
    cinfo.image_width  = m_width;   // image width in pixels
    cinfo.image_height = m_height;  // image height in pixels
    cinfo.input_components = 3;     // number of color components per pixel
    cinfo.in_color_space = JCS_RGB; // colorspace of input image

    jpeg_set_defaults(&cinfo);


    int quality = 100;
    jpeg_set_quality(&cinfo, quality, TRUE /* limit to baseline-JPEG values */);//Set quality in cinfo
   // jpeg_set_linear_quality(&cinfo, 1, TRUE);
    cinfo.dct_method = JDCT_FLOAT;

    // Start compression
    jpeg_start_compress(&cinfo, TRUE);

    // Compress data
    JSAMPROW row_pointer[1];        // pointer to a single row
    int row_stride;                 // physical row width in buffer

    row_stride = m_width * 3;   // JSAMPLEs per row in image_buffer

    while (cinfo.next_scanline < cinfo.image_height) {
        row_pointer[0] = & m_p_pixel_data[cinfo.next_scanline * row_stride];
        jpeg_write_scanlines(&cinfo, row_pointer, 1);
    }

    // Finish compression
    jpeg_finish_compress(&cinfo);

    // Release the JPEG compression object
    jpeg_destroy_compress(&cinfo);
}


//---------------------------------------------
void Image::saveTGAFile(const char* aFileName)
//---------------------------------------------
{
    // Specify the destination for the compressed data (eg, a file)
    FILE* p_output_file(fopen(aFileName, "wb"));
    if (!p_output_file)
    {
        std::stringstream error_message;
        error_message << "Cannot create the file " << aFileName << ", in File " << __FILE__ <<
            ", in Function " << __FUNCTION__ <<
            ", at Line " << __LINE__;

        throw std::runtime_error(error_message.str());
    }

  	putc(0, p_output_file);
  	putc(0, p_output_file);
  	putc(2, p_output_file);                         /* uncompressed RGB */
  	putc(0, p_output_file);
  	putc(0, p_output_file);
  	putc(0, p_output_file);
  	putc(0, p_output_file);
  	putc(0, p_output_file);
  	putc(0, p_output_file);
  	putc(0, p_output_file);           /* X origin */
  	putc(0, p_output_file);
  	putc(0, p_output_file);           /* y origin */
  	putc((m_width & 0xFF), p_output_file);
  	putc((m_width >> 8)  & 0xFF, p_output_file);
  	putc((m_height & 0xFF), p_output_file);
  	putc((m_height >> 8)  & 0xFF, p_output_file);
  	putc(24, p_output_file);                        /* 24 bit bitmap */

  	for (int row = 0; row < m_height; ++row)
  	{
          unsigned char* row_pointer = & m_p_pixel_data[m_width * (m_height - 1) * 3 - row * m_width * 3];

          for (int col = 0; col < m_width; ++col)
  		{
          	unsigned char* pixel_pointer = row_pointer + col * 3;

  			fwrite(pixel_pointer,
  					sizeof(unsigned char), 1,
  					p_output_file);

  			fwrite(pixel_pointer + 2,
  					sizeof(unsigned char), 1,
  					p_output_file);

  			fwrite(pixel_pointer + 1,
  					sizeof(unsigned char), 1,
  					p_output_file);
  		}
  	}
  	fclose(p_output_file);
}


//---------------------------------------
void Image::setSize(unsigned int aWidth,
		            unsigned int aHeight,
                    unsigned char r,
                    unsigned char g,
                    unsigned char b)
//---------------------------------------
{
    // The image size has changed
    if (aWidth != getWidth() || aHeight != getHeight())
    {
        destroy();

        m_width = aWidth;
        m_height = aHeight;

        // The new image is not empty
        if (m_width && m_height)
        {
            m_p_pixel_data = new unsigned char[3 * m_width * m_height];

            for (unsigned int i(0); i < m_width * m_height; ++i)
            {
                m_p_pixel_data[i * 3]     = r;
                m_p_pixel_data[i * 3 + 1] = g;
                m_p_pixel_data[i * 3 + 2] = b;
            }
        }
    }
}
