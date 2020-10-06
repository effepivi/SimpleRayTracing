/**
 ********************************************************************************
 *
 *   @file       Image.inl
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


//----------------------------------
inline Image::Image():
//----------------------------------
        m_p_pixel_data(0),
        m_width(0),
        m_height(0)
//----------------------------------
{
}


//-----------------------------------------
inline Image::Image(const char* aFileName):
//-----------------------------------------
        m_p_pixel_data(0),
        m_width(0),
        m_height(0)
//-----------------------------------------
{
    // Load a JPEG file
    loadJPEGFile(aFileName);
}


//------------------------------------------------
inline Image::Image(const std::string& aFileName):
//------------------------------------------------
        m_p_pixel_data(0),
        m_width(0),
        m_height(0)
//-----------------------------------------
{
    // Load a JPEG file
    loadJPEGFile(aFileName);
}


//--------------------
inline Image::~Image()
//--------------------
{
    // Release the memory
    destroy();
}


//--------------------------
inline void Image::destroy()
//--------------------------
{
    // Release the memory
    if (m_p_pixel_data)
    {
        delete [] m_p_pixel_data;
        m_p_pixel_data = 0;
    }

    // Reset parameters to their default values
    m_width  = 0;
    m_height = 0;
}


//-----------------------------------------------------------
inline void Image::loadJPEGFile(const std::string& aFileName)
//-----------------------------------------------------------
{
    loadJPEGFile(aFileName.data());
}


//-----------------------------------------------------
inline void Image::getSize(unsigned int& aWidth,
                           unsigned int& aHeight) const
//-----------------------------------------------------
{
    aWidth  = m_width;
    aHeight = m_height;
}


//-----------------------------------------
inline unsigned int Image::getWidth() const
//-----------------------------------------
{
    return (m_width);
}


//------------------------------------------
inline unsigned int Image::getHeight() const
//------------------------------------------
{
    return (m_height);
}


//------------------------------------------
inline unsigned char* Image::getData() const
//------------------------------------------
{
    return (m_p_pixel_data);
}
