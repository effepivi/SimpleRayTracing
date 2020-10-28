//---------------------------------------------
void showUsage(const std::string& aProgramName)
//---------------------------------------------
{
    std::cerr << "Usage: " << aProgramName << " <option(s)>" << endl <<
        "Options:" << endl <<
        "\t-h,--help\t\t\tShow this help message" << endl <<
        "\t-t,--threads T\tSpecify the number of threads (default value: 4)" << endl << 
        "\t-s,--size IMG_WIDTH IMG_HEIGHT\tSpecify the image size in number of pixels (default values: 2048 2048)" << endl << 
        "\t-b,--background R G B\t\tSpecify the background colour in RGB, acceptable values are between 0 and 255 (inclusive) (default values: 128 128 128)" << endl << 
        "\t-j,--jpeg FILENAME\t\tName of the JPEG file (default value: test.jpg)" << endl << 
        std::endl;
}


//-------------------------------------------------------------------
void processCmd(int argc, char** argv,
                string& aFileName,
                unsigned int& aWidth, unsigned int& aHeight,
                unsigned char& r, unsigned char& g, unsigned char& b
                unsigned int& aNumberOfThreads)
//-------------------------------------------------------------------
{
    // Process the command line
    int i = 1;
    while (i < argc)
    {
        std::string arg = argv[i];
        
        if (arg == "-h" || arg == "--help")
        {
            showUsage(argv[0]);
            exit(EXIT_SUCCESS);
        }
        else if (arg == "-s" || arg == "--size")
        {
            ++i;
            if (i < argc)
            {
                aWidth = stoi(argv[i]);
            }
            else
            {
                showUsage(argv[0]);
                exit(EXIT_FAILURE);
            }
            
            ++i;
            if (i < argc)
            {
                aHeight = stoi(argv[i]);
            }
            else
            {
                showUsage(argv[0]);
                exit(EXIT_FAILURE);
            }
        }
        else if (arg == "-b" || arg == "--background")
        {
            ++i;
            if (i < argc)
            {
                r = stoi(argv[i]);
            }
            else
            {
                showUsage(argv[0]);
                exit(EXIT_FAILURE);
            }

            ++i;
            if (i < argc)
            {
                g = stoi(argv[i]);
            }
            else
            {
                showUsage(argv[0]);
                exit(EXIT_FAILURE);
            }
            
            ++i;
            if (i < argc)
            {
                b = stoi(argv[i]);
            }
            else
            {
                showUsage(argv[0]);
                exit(EXIT_FAILURE);
            }
        }
        else if (arg == "-j" || arg == "--jpeg")
        {                
            ++i;
            if (i < argc)
            {
                aFileName = argv[i];
            }
            else
            {
                showUsage(argv[0]);
                exit(EXIT_FAILURE);
            }
        }
        else if (arg == "-t" || arg == "--threads")
        {
            ++i;
            if (i < argc)
            {
                aNumberOfThreads = stoi(argv[i]);
            }
            else
            {
                showUsage(argv[0]);
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            showUsage(argv[0]);
            exit(EXIT_FAILURE);
        }
        ++i;
    }
}
