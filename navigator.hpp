#ifndef __NAVIGATOR_HPP__
#define __NAVIGATOR_HPP__

#include <Arduino.h>

#define MAX_URL_SIZE 32

template<typename T>
class Node {
public:
    char* tag;
    T* data;
    Node<T>** children;
    int numChildren;

    Node(const char* tag, T* data) {
        this->tag = new char[strlen(tag) + 1];
        strcpy(this->tag, tag);
        this->data = data;
        this->children = nullptr;
        this->numChildren = 0;
    }

    ~Node() {
        delete[] tag;
        delete data;
        for (int i = 0; i < numChildren; i++) {
            delete children[i];
        }
        delete[] children;
    }
    
    void addObject(T* data)
    {
        data = data;    
    }

    void addChild(Node<T>* child) {
        Node<T>** newChildren = new Node<T>*[numChildren + 1];
        for (int i = 0; i < numChildren; i++) {
            newChildren[i] = children[i];
        }
        newChildren[numChildren] = child;
        delete[] children;
        children = newChildren;
        numChildren++;
    }

    Node<T>* findChild(const char* tag) {
        for (int i = 0; i < numChildren; i++) {
            if (strcmp(children[i]->tag, tag) == 0) {
                return children[i];
            }
        }
        return nullptr;
    }
};

template<typename T>
class NavigationSystem {
public:
    Node<T>* rootNode;
    Node<T>* currentNode;
    char currentUrl[MAX_URL_SIZE];

    NavigationSystem() {
        rootNode = new Node<T>("", nullptr);
        currentNode = rootNode;
    }

    ~NavigationSystem() {
        delete rootNode;
    }

    void addNode(const char* url, T* data) {
        if(!url){return;}
        // Remove trailing slash, if present
        bool release_url = false;
        int urlLen = strlen(url);
        if (urlLen > 1 && url[urlLen - 1] == '/') {
            char* newUrl = new char[urlLen];
            strncpy(newUrl, url, urlLen - 1);
            newUrl[urlLen - 1] = '\0';
            url = newUrl;
            release_url = true;
        }
    
        Node<T>* parentNode = rootNode;
        const char* currentTag = url + 1; // skip the first slash
        while (*currentTag != '\0') {
            const char* nextSlash = strchr(currentTag, '/');
            int subTagLen = nextSlash ? nextSlash - currentTag : strlen(currentTag);
            char* subTag = new char[subTagLen + 1];
            strncpy(subTag, currentTag, subTagLen);
            subTag[subTagLen] = '\0';
            Node<T>* childNode = parentNode->findChild(subTag);
            if (childNode == nullptr) {
                bool isLeaf = nextSlash == nullptr; // check if this is a leaf node
                childNode = new Node<T>(subTag, isLeaf ? data : nullptr);
                parentNode->addChild(childNode);
            }
            parentNode = childNode;
            currentTag = nextSlash ? nextSlash + 1 : currentTag + subTagLen;
            delete[] subTag;
        }
    
        // Delete newTag, if created
        if (url && release_url) {
            delete[] url;
        }
    }

    Node<T>* navigateAbsoluteUrl(const char* url) {
        if(!url){return nullptr;}

        bool release_url = false;
        // Remove trailing slash, if present
        int urlLen = strlen(url);
        if (urlLen > 1 && url[urlLen - 1] == '/') {
            char* newUrl = new char[urlLen];
            strncpy(newUrl, url, urlLen - 1);
            newUrl[urlLen - 1] = '\0';
            url = newUrl;
            release_url = true;
        }
    
        Node<T>* pointedNode = rootNode;
        const char* currentTag = url + 1; // skip the first slash
        while (*currentTag != '\0') {
            const char* nextSlash = strchr(currentTag, '/');
            int urlLen = nextSlash ? nextSlash - currentTag : strlen(currentTag);
            char* subTag = new char[urlLen + 1];
            strncpy(subTag, currentTag, urlLen);
            subTag[urlLen] = '\0';
            Node<T>* childNode = pointedNode->findChild(subTag);
            if (childNode == nullptr) {
                delete[] subTag;
                return nullptr;
            }
            pointedNode = childNode;
            currentTag = nextSlash ? nextSlash + 1 : currentTag + urlLen;
            delete[] subTag;
        }

        strncpy(currentUrl, url, MAX_URL_SIZE);

        // Delete newUrl, if created
        if (url && release_url) {
            delete[] url;
        }
        currentNode = pointedNode;
        return pointedNode;
    }

    Node<T>* navigateRelativeUrl(const char* relativeUrl) 
    {
        char tempUrl[MAX_URL_SIZE];
        strncpy(tempUrl, currentUrl, MAX_URL_SIZE);
        if(relativeUrl[0] != "/")
        {
            strcat(tempUrl, "/");
        }
        strncat(tempUrl, relativeUrl, MAX_URL_SIZE);
        Serial.println(tempUrl);
        return navigateAbsoluteUrl(tempUrl);
    }

     Node<T>* navigateBack()
     {
        char tempUrl[MAX_URL_SIZE];
        strncpy(tempUrl, currentUrl, MAX_URL_SIZE);
        url_remove_last_tag(tempUrl, MAX_URL_SIZE);
        Serial.print("back URL:");
        Serial.println(tempUrl);
        return navigateAbsoluteUrl(tempUrl);
     }

    Node<T>* getCurrentNode() 
    {
        return currentNode;
    }

    const char * getCurrentUrl()
    {
        return currentUrl;
    }

    url_remove_last_tag(char *url, size_t maxUrlSize)
    {
        if (url == nullptr || maxUrlSize == 0)
        {
            return false;
        }
        // Find the position of the last slash
        char *lastSlash = nullptr;
        for (char *p = url; *p != '\0' && p < url + maxUrlSize; ++p)
        {
            if (*p == '/')
            {
                lastSlash = p;
            }
        }
        if (lastSlash != nullptr)
        {
            // Remove the last component
            *lastSlash = '\0';
        }
        // Remove the trailing slash if it exists
        size_t len = 0;
        for (char *p = url; *p != '\0' && p < url + maxUrlSize; ++p)
        {
            ++len;
        }
        if (len > 0 && url[len - 1] == '/')
        {
            url[len - 1] = '\0';
        }
    }
};

/*
int main() {
    NavigationSystem<int> navSystem;

    int* value1 = new int(10);
    int* value2 = new int(20);
    int* value3 = new int(30);

    navSystem.addNode("/cfg/lights/l1", value1);
    navSystem.addNode("/cfg/lights/l2", value2);
    navSystem.addNode("/cfg/pumps/p1", value3);
    navSystem.addNode("/cfg/pumps/p2", value1);
    navSystem.addNode("/about/version", value2);
    navSystem.addNode("/about/author", value3);

    Node<int>* node1 = navSystem.navigate("/cfg/lights/l1");
    if (node1 != nullptr) {
        cout << "Node found with tag " << node1->tag << " and data " << *(node1->data) << endl;
    } else {
        cout << "Node not found" << endl;
    }

    Node<int>* node2 = navSystem.navigate("/cfg/pumps/p1");
    if (node2 != nullptr) {
        cout << "Node found with tag " << node2->tag << " and data " << *(node2->data) << endl;
    } else {
        cout << "Node not found" << endl;
    }

    Node<int>* node3 = navSystem.navigate("/about/license");
    if (node3 != nullptr) {
        cout << "Node found with tag " << node3->tag << " and data " << *(node3->data) << endl;
    } else {
        cout << "Node not found" << endl;
    }
    
    Node<int>* node4 = navSystem.navigate("/cfg/pumps");
    if (node4 != nullptr) {
        cout << "Node found with tag " << node4->tag << " and data " << ((node4->data)? (*(node4->data)):0) << endl;
    } else {
        cout << "Node not found" << endl;
    }

    delete value1;
    delete value2;
    delete value3;

    return 0;
}
*/

#endif /* __NAVIGATOR_HPP__ */