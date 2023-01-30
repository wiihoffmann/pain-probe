#include <Arduino.h>
#include <SPIFFS.h>

class FileManager{
    typedef uint8_t fileIndexType;
    typedef uint8_t dataFormatEnumType;

    public:
        enum fileFormat: dataFormatEnumType{PPT, TS, VAS, dataFormatEnumSize};
        FileManager();
        File makeFile(fileFormat format);
        void deleteFiles();
        fileIndexType getFileCount(fileFormat format);
        File openFile(fileFormat format, fileIndexType index);

    private:
        static fileIndexType fileIndexes[dataFormatEnumSize];
        const char* indexFileName = "/fileIndex";
        void loadFileCounts();
        void resetFileCounts();
        void getFileName(char* filename, fileFormat format, fileIndexType index); 

};

