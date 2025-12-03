#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
#define st string 

// Composite Design Pattern

// Interface Component
class FileSystem_Item{
private:
    string name;
    //Composite will have children. Normally leaf nodes won't have children(files)
    vector<FileSystem_Item*> children;
    unordered_set<FileSystem_Item*> child_set;
    bool isFile;
public:
    FileSystem_Item(string n, bool file): name(n), isFile(file) {}

    string get_name(){
        return name;
    }
    bool is_file(){
        return isFile;
    }

    void add_item(FileSystem_Item* item){
        if(!isFile){
            children.pb(item);
            child_set.insert(item);
        }
    }

    void remove_item(FileSystem_Item* item){
        if(!isFile){
            if(child_set.find(item) != child_set.end()){
                children.erase(remove(children.begin(), children.end(), item), children.end());
                child_set.erase(item);
                cout << "Item " << item->get_name() << " removed from " << get_name() << endl;
            }
        }
    }

    void open_all(int depth = 0){
        cout << string(depth, '-') << name << (isFile ? " [File]" : " [Directory]") << endl;
        for(auto child : children){
            child->open_all(depth + 2);
        }
    }

    void ls(){
        if(!isFile){
            cout << "Contents of " << get_name() << ":" << endl;
            for(auto child : children){
                cout << "- " << child->get_name() << (child->is_file() ? " [File]" : " [Directory]") << endl;
            }
        }
    }

    FileSystem_Item* cd(string dir_name){
        if(!isFile){
            for(auto child : children){
                if(child->get_name() == dir_name && !child->isFile){
                    return child;
                }
            }
        }
        return nullptr;
    }
};

int main(){
    FileSystem_Item* root = new FileSystem_Item("root", false);
    FileSystem_Item* dir1 = new FileSystem_Item("dir1", false);
    FileSystem_Item* dir2 = new FileSystem_Item("dir2", false);
    FileSystem_Item* file1 = new FileSystem_Item("file1.txt", true);
    FileSystem_Item* file2 = new FileSystem_Item("file2.txt", true);
    FileSystem_Item* file3 = new FileSystem_Item("file3.txt", true);
    root->add_item(dir1);
    root->add_item(file1);
    dir1->add_item(dir2);
    dir1->add_item(file2);
    dir2->add_item(file3);
    root->ls();
    root->open_all();
    FileSystem_Item* current = root->cd("dir1");
    if(current){
        current->ls();
        current->open_all();
        current->remove_item(file2);
        current->ls();
    }
     


    return 0;
}