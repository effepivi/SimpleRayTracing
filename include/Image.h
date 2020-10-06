#ifndef Image_h
#define Image_h


/**
********************************************************************************
*
*   @file       Image.h
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
#include <string>


//==============================================================================
/**
*   @class  Image
*   @brief  Image is a class to manage 2D RGB images.
*/
//==============================================================================
class Image
//------------------------------------------------------------------------------
{
//******************************************************************************
public:
    //--------------------------------------------------------------------------
    /// Default Constructor
    //--------------------------------------------------------------------------
    Image();


    //--------------------------------------------------------------------------
    /// Copy constructor
    /*
    *   @param anImage  the image to copy
    */
    //--------------------------------------------------------------------------
    Image(const Image& anImage);


    //--------------------------------------------------------------------------
    /// Constructor using a JPEG file name
    /*
    *   @param aFileName    the name of the JPEG file
    */
    //--------------------------------------------------------------------------
    Image(const char* aFileName);


    //--------------------------------------------------------------------------
    /// Constructor using a JPEG file name
    /*
    *   @param aFileName    the name of the JPEG file
    */
    //--------------------------------------------------------------------------
    Image(const std::string& aFileName);


    //--------------------------------------------------------------------------
    /// Destructor
    //--------------------------------------------------------------------------
    ~Image();


    //--------------------------------------------------------------------------
    /// Copy operator
    /*
    *   @param anImage  the image to copy
    */
    //--------------------------------------------------------------------------
    Image& operator=(const Image& anImage);


    //--------------------------------------------------------------------------
    /// Release memory
    //--------------------------------------------------------------------------
    void destroy();


    //--------------------------------------------------------------------------
    /// Load an image from a JPEG file
    /*
    *   @param aFileName    the name of the JPEG file
    */
    //--------------------------------------------------------------------------
    void loadJPEGFile(const char* aFileName);


    //--------------------------------------------------------------------------
    /// Load an image from a JPEG file
    /*
    *   @param aFileName    the name of the JPEG file
    */
    //--------------------------------------------------------------------------
    void loadJPEGFile(const std::string& aFileName);


    //--------------------------------------------------------------------------
    /// Accessor on the image size (in number of pixels)
    /*
    *   @param aWidth   the image width
    *   @param aHeight   the image height
    */
    //--------------------------------------------------------------------------
    void getSize(unsigned int& aWidth, unsigned int& aHeight) const;


    //--------------------------------------------------------------------------
    /// Accessor on the image width (in number of pixels)
    /*
    *   @return the image width
    */
    //--------------------------------------------------------------------------
    unsigned int getWidth() const;


    //--------------------------------------------------------------------------
    /// Accessor on the image height (in number of pixels)
    /*
    *   @return the image height
    */
    //--------------------------------------------------------------------------
    unsigned int getHeight() const;


    //--------------------------------------------------------------------------
    /// Accessor on the raw pixel values
    /*
    *   @return the raw pixel values
    */
    //--------------------------------------------------------------------------
    unsigned char* getData() const;


//******************************************************************************
protected:
    //--------------------------------------------------------------------------
    /// Allocate memory
    /*
    *   @param aWidth   the image width (in number of pixels)
    *   @param aHeight  the image height (in number of pixels)
    */
    //--------------------------------------------------------------------------
    void setSize(unsigned int aWidth, unsigned int aHeight);


    /// The pixel data
    unsigned char*         m_p_pixel_data;


    /// The image width (in number of pixels)
    unsigned int   m_width;


    /// The image height (in number of pixels)
    unsigned int   m_height;
};


#include "Image.inl"


#endif
