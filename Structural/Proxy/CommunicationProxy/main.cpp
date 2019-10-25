//
//  main.cpp
//  CommunicationProxy
//
//  Created by Aniket Bhushan on 20/10/19.
//  Copyright © 2019 Aniket Bhushan. All rights reserved.
//

#include <iostream>

struct Pingable {
    virtual ~Pingable() = default;
    virtual std::wstring ping(const std::wstring& message) = 0;
};

struct Pong : Pingable {
    std::wstring ping(const std::wstring& message) override
    {
        return message + L" pong";
    }
};

// C++ REST sdk by Microsoft : casablanca
#include <cpprest/http_client.h>
using namespace web;
using namespace http;
using namespace client;

// We want to move this Pong to may be a web server !!
struct RemotePong : Pingable {
    
    std::wstring ping(const std::wstring& message) override
    {
        http_client client(U("http://localhost:9149/"));
        uri_builder builder(U("/api/pingpong/"));
        builder.append(message);
        
        pplx::task<std::wstring> task = client.request(methods::GET, builder.to_string())
        .then([=](http_response r)
              {
                  return r.extract_string();
              });
        
        task.wait();
        return task.get();
    }
};

void tryit(Pingable& p)
{
    std::wcout << p.ping(L"ping") << "\t";
}

int main(int argc, const char * argv[]) {
    
    //    Pong pp;
    RemotePong pp;
    for (size_t i=0; i<10; ++i) {
        tryit(pp);
    }
    
    return 0;
}
