#  Proxy

**A class that is functioning s an interface to a particular resource. That resource may be remote, expensive to construct, or may require logging or some other added functionality.**

We are calling `foo.bar()` 
Now, this assumes that foo resides in the same process as bar.
What if, later on you want to put all Foo related operations into a separate process ?
- How can you avoid changing all your code ?

Proxy to rescue !
- Same interface entirely different behavior.

This is a communication proxy 
- Other : logging, virtual, guarding ...

## Standard library smart pointers

## Virtual proxy

## Communication proxy

Casablanca : C++ Rest sdk

![Libs and dlls](casablanca.png)

```cpp
#include <cpprest/http_client.h>
using namespace web;
using namespace http;
using namespace client;

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

```


## Difference between proxy and decorators

- Proxy provides an identical interface; while decorator provides an enhanced interface.
- Decorator typically aggregates (or has reference to ) what it is decorating, proxy doesn't have to.
- Proxy might not even be working with a materialized object.

## Notes

- A proxy has the same interface as the underlying object.
- To create a proxy, simply replicate the existing interface of an object.
- Add relevant functionality to the redefined member functions.
- - As well as constructor, destructor etc.
- Different proxies (communication, logging, caching etc.) having completely different behaviors.

