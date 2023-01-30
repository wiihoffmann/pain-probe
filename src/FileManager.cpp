#include"FileManager.h"

FileManager::fileIndexType FileManager::fileIndexes[dataFormatEnumSize];

FileManager::FileManager(){
    if(!SPIFFS.begin(true)){
        Serial.println("An Error has occurred while mounting SPIFFS");
        return;
    }
    loadFileCounts();
}


void FileManager::loadFileCounts(){
    File indexFile = SPIFFS.open(indexFileName, FILE_READ, true);    
    
    if(indexFile.size() != dataFormatEnumSize * sizeof(fileIndexType)){
        resetFileCounts();
    }

    indexFile.seek(0);
    indexFile.readBytes((char *)fileIndexes, dataFormatEnumSize * sizeof(fileIndexType));
    indexFile.close();

    Serial.print("PPT test files: ");
    Serial.println(fileIndexes[PPT]);
    Serial.print("VAS test files: ");
    Serial.println(fileIndexes[VAS]);
    Serial.print("TS test files: ");
    Serial.println(fileIndexes[TS]);
}


void FileManager::resetFileCounts(){
    File indexFile = SPIFFS.open(indexFileName, FILE_WRITE); 
    for(uint8_t i=0; i < dataFormatEnumSize * sizeof(fileIndexType); i++){
        indexFile.write(0);
    }
    indexFile.close();

    for(int i = 0; i<dataFormatEnumSize; i++){
        fileIndexes[i] = 0;
    }
    Serial.println("file counts reset");
}


void FileManager::deleteFiles(){
    for(uint8_t format = 0; format<dataFormatEnumSize; format++){
        for(uint8_t i = 0; format<fileIndexes[i]; i++){
            char filename[1+sizeof(fileIndexType)+sizeof(dataFormatEnumType)];
            getFileName(filename, (fileFormat)format, i);
            SPIFFS.remove(filename);
        }
    }

    resetFileCounts();
}


File FileManager::makeFile( fileFormat type){
    File indexFile = SPIFFS.open(indexFileName, FILE_WRITE);
    fileIndexes[type] ++;
    indexFile.write((uint8_t*)fileIndexes, dataFormatEnumSize * sizeof(fileIndexType));
    indexFile.close();

    char filename[1+sizeof(fileIndexType)+sizeof(dataFormatEnumType)];
    getFileName(filename, type, fileIndexes[type]);

    return SPIFFS.open(filename, "w+"); // TODO: change back to W when reading no longer needed.
}


void FileManager::getFileName(char* filename, fileFormat format, fileIndexType index){
    filename[0] = '/';
    for(int8_t i = sizeof(dataFormatEnumType)-1; i >= 0; i--){
        filename[i+1] = format >> 8*i;
    }
    for(int8_t i = sizeof(fileIndexType)-1; i >= 0; i--){
        filename[i+sizeof(dataFormatEnumType)+1] = index >> 8*i;
    } 
}


