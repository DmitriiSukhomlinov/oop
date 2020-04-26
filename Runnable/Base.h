#pragma once

#include <string>

namespace oop {

class Printable {
public:
    virtual ~Printable();

    virtual std::string getInfo() const = 0;

};

class Named : public virtual Printable {
public:
    Named(const std::string& name);
    virtual ~Named();

    std::string getInfo() const override;

protected:
    virtual std::string getAdditionaInfo() const;

private:
    std::string name;

};

}

    