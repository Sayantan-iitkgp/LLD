#include <bits/stdc++.h>
using namespace std;

// ABSTRACT CLASS. DOC_ELEMENT is the main abstraction layer for different types of elements(like text, image, video etc) in a particular Document of this Document-Editor
class Doc_element
{
public:
    virtual void render(string &rendered) = 0;
};

// TEXT element
class Text : public Doc_element
{
private:
    string text;

public:
    Text(string text)
    {
        this->text = text;
    }

    void render(string &rendered)
    {
        rendered += text;
        rendered += "\n";
    }
};

// IMAGE ELEMENT
class Image : public Doc_element
{
private:
    string path;

public:
    Image(string path)
    {
        this->path = path;
    }

    void render(string &rendered)
    {
        rendered += "[IMAGE_PATH : " + path + " ] ";
        rendered += "\n";
    }
};

// Document class is aggregating all of its Doc_Elements
class Document
{
private:
    vector<Doc_element *> elements;
    string rendered = "";

public:
    void add_element(Doc_element *element)
    {
        elements.push_back(element);
    }

    string render()
    {
        if (rendered.size() > 0)
        {
            return rendered;
        }
        for (size_t i = 0; i < elements.size(); i++)
        {
            elements[i]->render(rendered);
        }

        if (rendered.size() == 0)
        {
            return "THERE IS NOTHING TO RENDER";
        }
        return rendered;
    }
};

// Persistance Class. This is also a abstraction layer between different saving classes
class Persistance
{
public:
    virtual void save(string data) = 0;
};

// File_Storage for saving data in File
class File_Storage : public Persistance
{

public:
    void save(string data)
    {
        ofstream file("Document.txt");

        if (file.is_open())
        {
            file << data;
            file.close();
            cout << "Document is saved." << endl;
        }
    }
};

// DB Storage for saving data in Database
class DB_Storage : public Persistance
{
public:
    void save(string data)
    {
        cout << data << endl;
        cout << "Data is saved in Database" << endl;
    }
};

// MAIN DOCUMENT-EDITOR CLASS. IT IS DIRECTLY INTERACTING WITH CLIENT
class Doc_Editor
{
private:
    Document *Doc = new Document();
    Persistance *Pt;

public:
    Doc_Editor(Persistance *Pt)
    {
        this->Pt = Pt;
    }

    void Add_Text(string text)
    {
        Doc->add_element(new Text(text));
    }

    void Add_Image(string path)
    {
        Doc->add_element(new Image(path));
    }

    void save()
    {
        string data = Doc->render();
        Pt->save(data);
    }

    void render()
    {
        string rendered = Doc->render();
        cout << rendered << endl;
    }
};

// MAIN FUNCTION ACTING AS CLIENT
int main()
{
    Doc_Editor *My_Doc_Editor = new Doc_Editor(new File_Storage());
    My_Doc_Editor->Add_Text("Hello World");
    My_Doc_Editor->Add_Text("Codeforces");
    My_Doc_Editor->Add_Image("London.jpg");
    My_Doc_Editor->Add_Text("LeetCoding");
    My_Doc_Editor->Add_Image("Melbourn.png");
    My_Doc_Editor->render();
    My_Doc_Editor->save();
    return 0;
}
