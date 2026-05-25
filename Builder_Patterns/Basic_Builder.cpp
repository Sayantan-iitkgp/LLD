#include <bits/stdc++.h>
using namespace std;

// BASIC BUILDER DESIGN PATTERN

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
    friend class HTTP_Request_Builder; // Allow the builder to access private members

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

// Once a request is made using builder , it can't be changed because all the parameters and constructor of HTTP_Request class are private
// and only builder can access them. So we can say that the object created by builder is immutable.
// Also before setting it buider checks if the parameter is already set or not , if it is already set then it won't change it.
// So we can say that builder also provides immutability to the object it creates.

class HTTP_Request_Builder
{
private:
    HTTP_Request *request;

public:
    HTTP_Request_Builder()
    {
        request = new HTTP_Request();
    }

    HTTP_Request_Builder set_URL(string url)
    {
        if (request->url.empty())
        {
            request->url = url;
        }
        return *this;
    }

    HTTP_Request_Builder set_Method(string method)
    {
        if (request->method.empty())
        {
            request->method = method;
        }
        return *this;
    }

    HTTP_Request_Builder set_Body(string body)
    {
        if (request->body.empty())
        {
            request->body = body;
        }
        return *this;
    }

    HTTP_Request_Builder add_Header(string key, string value)
    {
        if (request->headers.find(key) == request->headers.end())
        {
            request->headers[key] = value;
        }
        return *this;
    }

    HTTP_Request_Builder add_Query_Param(string key, string value)
    {
        if (request->queryParams.find(key) == request->queryParams.end())
        {
            request->queryParams[key] = value;
        }
        return *this;
    }

    HTTP_Request_Builder set_Timeout(int timeout)
    {
        if (request->timeout <= 0)
        {
            request->timeout = timeout;
        }
        return *this;
    }

    HTTP_Request *build()
    {
        // Validating This HTTP Request Object Before Returning
        if (request->url.empty())
        {
            throw runtime_error("URL cannot be empty");
        }

        return request;
    }
};

//Building using Director Class
//Some known BUilding methods are done by Director class.
class HTTP_Request_Director{
public:
    static HTTP_Request* create_POST_Request(string url, string body, map<string, string> headers, map<string, string> queryParams, int timeout)
    {
        HTTP_Request_Builder builder;
        builder.set_URL(url)
               .set_Method("POST")
               .set_Body(body)
               .set_Timeout(timeout);

        for (const auto& header : headers) {
            builder.add_Header(header.first, header.second);
        }

        for (const auto& param : queryParams) {
            builder.add_Query_Param(param.first, param.second);
        }

        return builder.build();
    }

    static HTTP_Request* create_GET_Request(string url){
        HTTP_Request_Builder builder;
        builder.set_URL(url)
               .set_Method("GET");

        return builder.build();
    }
};

int main()
{

    // Using the Builder to create an HTTP Request
    // If a HTTP Request is build , any parameter of this can't be changed because every params and constructor are private and only builder can access them. So we can say that the object created by builder is immutable.
    //Chaining the builder methods to set the parameters of the HTTP Request and then building the request object
    HTTP_Request *request = HTTP_Request_Builder()
                                .set_URL("https://example.com/api/data")
                                .set_Method("POST")
                                .set_Body("{\"name\":\"John Doe\",\"age\":30}")
                                .add_Header("Content-Type", "application/json")
                                .add_Query_Param("api_key", "123456")
                                .set_Timeout(5000)
                                .build();

    //But Order  doesn't matter in this pattern.
    HTTP_Request *request2 = HTTP_Request_Builder()
                                 .set_Method("GET")
                                 .add_Header("Accept", "application/json")
                                 .set_URL("https://example.com/api/data")
                                 .add_Query_Param("api_key", "123456")
                                 .set_Timeout(3000)
                                 .build();

    HTTP_Request *request3 = HTTP_Request_Director::create_POST_Request("https://example.com/api/data", "{\"name\":\"John Doe\",\"age\":30}", {{"Content-Type", "application/json"}}, {{"api_key", "123456"}}, 5000);
    HTTP_Request *request4 = HTTP_Request_Director::create_GET_Request("https://example.com/api/data");

    
    request->execute();
    delete request;
    request2->execute();
    delete request2;
    request3->execute();
    delete request3;
    request4->execute();
    delete request4;
    return 0;
}