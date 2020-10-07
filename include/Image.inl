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
//------------------------------------------------
{
    // Load a JPEG file
    loadJPEGFile(aFileName);
}


//----------------------------------------
inline Image::Image(unsigned int aWidth,
                    unsigned int aHeight):
//----------------------------------------
        m_p_pixel_data(0),
        m_width(0),
        m_height(0)
//----------------------------------------
{
    setSize(aWidth, aHeight);
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


//-----------------------------------------------------------
inline void Image::saveJPEGFile(const std::string& aFileName)
//-----------------------------------------------------------
{
    saveJPEGFile(aFileName.data());
}


//----------------------------------------------------------
inline void Image::saveTGAFile(const std::string& aFileName)
//----------------------------------------------------------
{
    saveTGAFile(aFileName.data());
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
    return m_width;
}


//------------------------------------------
inline unsigned int Image::getHeight() const
//------------------------------------------
{
    return m_height;
}


//------------------------------------------
inline unsigned char* Image::getData() const
//------------------------------------------
{
    return (m_p_pixel_data);
}



inline void Image::setPixel(unsigned int i,
                            unsigned int j,
                            unsigned char r,
                            unsigned char g,
                            unsigned char b)
{
    if (i < m_width && j < m_height)
    {
        unsigned int index = j * m_width * 3 + i * 3;
        m_p_pixel_data[index] = r;
        m_p_pixel_data[index + 1] = g;
        m_p_pixel_data[index + 2] = b;
    }
}


inline void Image::getPixel(unsigned int i,
                            unsigned int j,
                            unsigned char& r,
                            unsigned char& g,
                            unsigned char& b) const
{
    if (i < m_width && j < m_height)
    {
        unsigned int index = j * m_width * 3 + i * 3;
        r = m_p_pixel_data[index];
        g = m_p_pixel_data[index + 1];
        b = m_p_pixel_data[index + 2];
    }
}
