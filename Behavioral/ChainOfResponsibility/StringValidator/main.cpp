#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <regex>
#include <algorithm>

// -----------------------------------------------------
class StringValidator {
public:
    virtual ~StringValidator() = default;
    virtual StringValidator* SetNext(StringValidator*) = 0;
    virtual std::string Validate(std::string) = 0;
};

// -----------------------------------------------------
class BaseValidator : public StringValidator {

    StringValidator* m_next;

public:
    StringValidator* SetNext(StringValidator* nextValidator) 
    {
        m_next = nextValidator;
        return m_next;
    }

    std::string Validate(std::string testString) override
    {
        if (m_next)
        {
            return m_next->Validate(testString);
        }
        return "Success";
    }
};

// ------------------------------------------------------
class NonEmptyValidator : public BaseValidator {
public:
    std::string Validate(std::string testString) override
    {
        std::cout << "Checking if empty ... " << std::endl;
        if (testString.empty())
        {
            return "Please enter a value";
        }

        return BaseValidator::Validate(testString);
    }
};

// ------------------------------------------------------
class LengthValidator : public BaseValidator {
    int m_minLength;
public:
    LengthValidator(int minLength) : m_minLength {minLength} {}

    std::string Validate(std::string testString) override {
        std::cout << "Checking if min length is " << m_minLength << "...\n";

        if (testString.size() < m_minLength) 
            return "Please enter a value longer than " + std::to_string(m_minLength);

        return BaseValidator::Validate(testString);
    }
};

// ------------------------------------------------------
class RegexValidator : public BaseValidator {
    std::string m_patternName;
    std::string m_regexString;
public:
    RegexValidator(std::string patternName, std::string regexString) : 
        m_patternName {patternName},
        m_regexString {regexString}
        {
        }

    std::string Validate(std::string testString) override {
        std::cout << "Checking if string is a valid " << m_patternName << "...\n";

        if (!std::regex_match(testString, std::regex(m_regexString))) {
            return "The value entered is not a valid " + m_patternName;
        }

        return BaseValidator::Validate(testString);
    }
};


// ------------------------------------------------------
class HistoryValidator : public BaseValidator {
    std::vector<std::string> m_historyItems;

public:
    HistoryValidator(std::vector<std::string> historyItems) : m_historyItems {historyItems}
    {}

    std::string Validate(std::string testString) override {
        std::cout << "Checking if string is in history ...\n";

        if (std::find(m_historyItems.begin(), m_historyItems.end(), testString) == m_historyItems.end())
        {
            return "Please enter a value that you have not entered before.\n";
        }

        return BaseValidator::Validate(testString);
    }
};


// ------------------------------------------------------
// ------------------------------------------------------

int main(int argc, char const *argv[])
{
    std::vector<std::string> oldPasswords {"abc123", "123456", "hello"};

    auto emailValidator = new BaseValidator();

    emailValidator
    ->SetNext(new NonEmptyValidator())
    ->SetNext(new RegexValidator("email address", "^\\w+([-+.']\\w+)*@\\w+([-.]\\w+)*\\.\\w+([-.]\\w+)*$"))
    ->SetNext(new LengthValidator(5))
    ->SetNext(new HistoryValidator(oldPasswords));
    
    std::cout << "Checking Emails ----------------" << std::endl;
    std::cout << "Input : \n" << emailValidator->Validate("") << std::endl;
    std::cout << "Input : shaun\n" << emailValidator->Validate("shaun") << std::endl;
    std::cout << "Input : shaun@test.com\n" << emailValidator->Validate("shaun@test.com") << std::endl;

    return 0;
}

