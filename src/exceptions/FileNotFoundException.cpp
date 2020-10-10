#include "FileNotFoundException.hpp"



FileNotFoundException::FileNotFoundException(const QString& filePath) :
    Exception("The file \"" + filePath + "\" could not be loaded.")
{

}
