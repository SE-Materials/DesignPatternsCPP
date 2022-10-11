#include <iostream>
#include <memory>
#include <string>

enum class ErrorCode {
    NoError     = 0,
    LengthError = 1,
    MissingSymbolError = 2
};

struct Error {
    std::string message;
    ErrorCode   errCode;

    Error() : errCode {ErrorCode::NoError}, message {} {}

    Error (ErrorCode errCode, std::string message) 
    {
        errCode = errCode;
        message = message;
    }

    Error(const Error& err)
    {
        errCode = err.errCode;
        message = err.message;
    }

    Error operator=(const Error& err)
    {
        errCode = err.errCode;
        message = err.message;
    }

    bool operator==(int code) 
    {
        return (int)errCode == code;
    }

    friend std::ostream& operator<<(std::ostream& os, const Error& err)
    {
        os << "Error: " << err.message;
        return os;
    }
};

class IValidator;
using IValidatorPtr = std::shared_ptr<IValidator>;

class IValidator {
public:
    virtual IValidatorPtr SetNext(IValidatorPtr next) = 0;
    virtual Error Handle(std::string& str) = 0;    
    virtual ~IValidator() = default;
};

class BaseValidator : public IValidator {

public:

    IValidatorPtr SetNext(IValidatorPtr next) override 
    {
        m_next = next;
        return next;
    }

    Error Handle(std::string& str) override 
    {
        if (m_next != nullptr)
            return m_next->Handle(str);
        return Error();
    }

private :

    IValidatorPtr m_next;

};

class LengthValidator : public BaseValidator {

public:

    LengthValidator() : m_minlen {10} {}

    Error Handle(std::string& str) override 
    {
        int len = str.size();
        if (len >= m_minlen) return BaseValidator::Handle(str);
        else return Error(ErrorCode::LengthError, "Min length required : " + std::to_string(m_minlen));
    }

private:
    int m_minlen;
};

class AlphaNumValidator : public BaseValidator {
public:
    Error Handle(std::string& str) override 
    {
        bool hasNum {false};
        bool hasalpha {false};
        bool hasSymbols {false};

        for (auto& c : str)
        {
            if (isalpha(c)) hasalpha = true;
            else if (c >= '0' && c <= '9') hasNum = true;
            else hasSymbols = true;
        }

        if (hasalpha && hasNum && hasSymbols) return BaseValidator::Handle(str);
        else return Error(ErrorCode::MissingSymbolError, "Has missing num, alpha or symbols");
    }
};

int main()
{
    std::string password {"thisisaniket"};

    IValidatorPtr passwordValidator = 
                std::make_shared<LengthValidator>()->
        SetNext(std::make_shared<AlphaNumValidator>());
    
    Error err = passwordValidator->Handle(password);
    if (err == 0)
        std::cout << "Password validation successful!" << std::endl;
    else
        std::cout << err << std::endl;

    return 0;
}