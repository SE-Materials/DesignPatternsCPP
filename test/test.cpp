#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <regex>

class StringValidator {
public:
    virtual ~StringValidator() = default;
    virtual StringValidator* SetNext(StringValidator*) = 0;
    virtual std::string Validate(std::string) = 0;
};


class BaseValidator : public StringValidator {
    StringValidator* m_next;
public:
    ~BaseValidator() 
    {
        delete m_next;
    }

    StringValidator* SetNext(StringValidator* nextValidator) override
    {
        m_next = nextValidator;
        return m_next;
    }

    std::string Validate(std::string textString) override 
    {
        if (m_next != nullptr)
            return m_next->Validate(textString);
        return "Success";
    }
};

class NonEmptyValidator : public BaseValidator {

public:
    std::string Validate(std::string textString) override 
    {
        if (textString.empty())
            return "Please provide non empty string";
        return BaseValidator::Validate(textString);
    }
};

class LengthValidator : public BaseValidator {
    int m_minLength;
public:
    LengthValidator(int length) : m_minLength {length} {}
    std::string Validate(std::string textString) override {
        if (textString.length() < m_minLength) {
            return "Please provide string of length gt " + m_minLength;
        }
        return BaseValidator::Validate(textString);
    }
};

class RegexValidator : public BaseValidator {
    std::string m_patternName;
    std::string m_regexString;
public:
    RegexValidator(std::string patternName, std::string regexString) : 
    m_patternName {patternName}, m_regexString {regexString} {}

    std::string Validate(std::string textString) override {
        if (!std::regex_match(textString, std::regex(m_regexString)))
            return "The string is not a valid pattern name";
        return BaseValidator::Validate(textString);
    }
};

class HistoryValidator : public BaseValidator {
    std::vector<std::string> m_oldStrings;
public:
    HistoryValidator(std::vector<std::string> oldStrings) : m_oldStrings {oldStrings} {}
    
    std::string Validate(std::string textString) override {

        if (std::find(m_oldStrings.begin(), m_oldStrings.end(), textString) != m_oldStrings.end()) {
            return "Please enter a string not matching with past strings!";
        }
        return BaseValidator::Validate(textString);
    }
};

int main(int argc, char const *argv[])
{
    std::vector<std::string> oldEmailIds = {"12345", "aniket", "12@mail.com"};
    
    auto mailValidator = new BaseValidator();
    
    mailValidator
    ->SetNext(new NonEmptyValidator())
    ->SetNext(new LengthValidator(4))
    ->SetNext(new RegexValidator("email address", "^\\w+([-+.']\\w+)*@\\w+([-.]\\w+)*\\.\\w+([-.]\\w+)*$"))
    ->SetNext(new HistoryValidator(oldEmailIds));
    
    std::vector<std::string> emailIdsToTest = {
        "",
        "1234",
        "12@gmail.com",
        "aniket@mail.com"
    };

    for (auto emailId : emailIdsToTest)
    {
        std::cout << "Input : " << emailId << "\n" << mailValidator->Validate(emailId) << std::endl;
        std::cout << std::endl;
    }
    ;
    delete mailValidator;
    return 0;
}
