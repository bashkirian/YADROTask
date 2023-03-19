#pragma once

#include "../Configuration/configuration.h"

#include <string>
#include <memory>
#include <fstream>
class TapeDevice { 
public:
    virtual int read() = 0; 
    virtual void write(int value) = 0; 
    virtual void rewind() = 0; 
    virtual void shift(int offset) = 0; 
    virtual bool isended() = 0; 
    virtual configuration::Configuration getConfiguration() = 0; 
};

class TapeFile : public TapeDevice {
public:
    TapeFile() = default;
    TapeFile(const TapeFile& other);
    TapeFile(std::string filename, configuration::Configuration); 
    int read() override;
    void write(int value) override;
    void rewind() override;
    void shift(int offset) override;
    configuration::Configuration getConfiguration() override;
    bool isended() override;
private:
    std::unique_ptr<std::fstream> m_file; 
    configuration::Configuration conf; 
};