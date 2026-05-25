#include <bits/stdc++.h>
using namespace std;

// STEP BULDER DESIGN PATTERN .
// Here we will use multiple Inheritance for chaining the parameters of the HTTP request and then building the request object.
// Also some optional parameters will be set or left and final building of HTTP Request will be done.

class HTTP_Request
{
private:
    string method;
    string url;
    string body;
    map<string, string> headers;
    map<string, string> queryParams;
    int timeout;

    HTTP_Request()
    { // Private constructor to prevent direct instantiation
    }

public:
    friend class HTTP_Request_Step_Builder; // Allow the builder to access private members

    void execute()
    {
        cout << "URL: " << url << endl;

        if (!this->method.empty())
        {
            cout << "Method: " << method << endl;
        }

        if (!this->body.empty())
        {
            cout << "Body: " << body << endl;
        }

        if (!this->headers.empty())
        {
            cout << "Headers: " << endl;
            for (const auto &header : headers)
            {
                cout << header.first << ": " << header.second << endl;
            }
        }

        if (!this->queryParams.empty())
        {
            cout << "Query Parameters: " << endl;
            for (const auto &param : queryParams)
            {
                cout << param.first << ": " << param.second << endl;
            }
        }

        if (this->timeout > 0)
        {
            cout << "Timeout: " << timeout << " ms" << endl;
        }
    }
};

//Decleration of all classes for step builder pattern
class Method_Step_Builder;
class Body_Step_Builder;
class Optional_Step_Builder;


//Url_step_Builder has a Method_Step_Builder
class URl_Step_Builder
{
public:
    virtual Method_Step_Builder &set_URL(string url) = 0;
};

//Method_Step_Builder has a Body_Step_Builder
class Method_Step_Builder
{
public:
    virtual Body_Step_Builder &set_Method(string method) = 0;
};


//Body_Step_Builder has a Optional_Step_Builder
class Body_Step_Builder
{
public:
    virtual Optional_Step_Builder &set_Body(string body) = 0;
};

//Optional_Step_Builder has all optional parameters and a build function to build the HTTP Request object.
class Optional_Step_Builder
{
public:
    virtual Optional_Step_Builder &add_Header(string key, string value) = 0;
    virtual Optional_Step_Builder &add_Query_Param(string key, string value) = 0;
    virtual Optional_Step_Builder &set_Timeout(int timeout) = 0;
    virtual HTTP_Request *build() = 0;
};

//Step Builder class inheritates all the above classes and implements all the virtual functions of those classes and also have a build function to build the HTTP Request object.
//It's a proper Example of Multiple Inhertance in C++.
//According to Solid Principle , Multiple Inheritance is not a good practice but in this case , it is a trade off for better chaining of
//parameters with proper ordering and also providing immutability to the object created by builder.

class HTTP_Request_Step_Builder : public URl_Step_Builder, public Method_Step_Builder, public Body_Step_Builder, public Optional_Step_Builder
{
private:
    HTTP_Request *request;

public:
    HTTP_Request_Step_Builder()
    {
        request = new HTTP_Request();
    }

    Method_Step_Builder &set_URL(string url)
    {
        if (request->url.empty())
        {
            request->url = url;
        }
        return *this;
    }

    Body_Step_Builder &set_Method(string method)
    {
        if (request->method.empty())
        {
            request->method = method;
        }
        return *this;
    }

    Optional_Step_Builder &set_Body(string body)
    {
        if (request->body.empty())
        {
            request->body = body;
        }
        return *this;
    }

    Optional_Step_Builder &add_Header(string key, string value)
    {
        if (request->headers.find(key) == request->headers.end())
        {
            request->headers[key] = value;
        }
        return *this;
    }

    Optional_Step_Builder &add_Query_Param(string key, string value)
    {
        if (request->queryParams.find(key) == request->queryParams.end())
        {
            request->queryParams[key] = value;
        }
        return *this;
    }

    Optional_Step_Builder &set_Timeout(int timeout)
    {
        if (request->timeout <= 0)
        {
            request->timeout = timeout;
        }
        return *this;
    }

    HTTP_Request *build()
    {
        return request;
    }
};

int main()
{

    // Using the Builder to create an HTTP Request
    // If a HTTP Request is build , any parameter of this can't be changed because every params and constructor are private and only builder can access them. So we can say that the object created by builder is immutable.
    // Chaining the builder methods to set the parameters of the HTTP Request and then building the request object
    HTTP_Request *request = HTTP_Request_Step_Builder()
                                .set_URL("https://example.com/api/data")
                                .set_Method("POST")
                                .set_Body("{\"name\":\"John Doe\",\"age\":30}")
                                .add_Header("Content-Type", "application/json")
                                .add_Query_Param("api_key", "123456")
                                .build();

    // With only necessary parameters
    //Chaining of all necessary parameters in proper order and then building the request object
    HTTP_Request *request2 = HTTP_Request_Step_Builder()
                                 .set_URL("https://example.com/api/data")
                                 .set_Method("GET")
                                 .set_Body("ABCD")
                                 .build();

    request->execute();
    delete request;
    request2->execute();
    delete request2;                             
    return 0;
}
