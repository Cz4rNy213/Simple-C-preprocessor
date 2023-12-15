# C++ Preprocessor

This simple C++ preprocessor allows you to manipulate C++ source code using common preprocessor directives. It supports the following directives:
You can customize the names of the macros you use.
In the example below, I used the following macro: 
- **#inkluduj:** as **#include:** Includes the contents of another file in your code.
- **#definiuj:** as **#define:** Defines a macro or a symbolic constant, and you can customize these names as needed.
- **#JeśliZdefiniowane** as **#ifdef:**,  **#JeśliNie** as **#else:**,  **#Zakończ:** as **#endif:**  Conditional compilation based on whether a macro is defined.

## Usage

To use the preprocessor, follow these steps:

1. Compile your main source code:
    ```bash
    g++ -o main main.cpp
    ```

2. Execute the main source code:
    ```bash
    ./main
    ```

3. Compile the result code:
    ```bash
    g++ -g -o result result.cpp
    ```

4. Execute the result code:
    ```bash
    ./result
    ```

Feel free to replace "main" and "result" with the desired names for your executable files.

# Example

## Input file:
```cpp
#inkluduj <iostream>
#definiuj PI 3
#definiuj MAX_VALUE 100


int main() {
    int radius = 5;
    double area = PI * radius * radius;
    std::cout << "Area of the circle: " << area << std::endl;
    std::cout << MAX_VALUE ;
#JeśliZdefiniowane PI
    std::cout<<"PI defined correctly"<<std::endl;
#JeśliNie 
    std::cout<<"PI not defined correctly"<<std::endl;
#Zakończ

#JeśliZdefiniowane MAXX
    std::cout<<"MAXX defined correctly"<<std::endl;
#JeśliNie 
    std::cout<<"MAXX not defined correctly"<<std::endl;
#Zakończ

#JeśliZdefiniowane MAX_VALUE
    std::cout<<"MAX_VALUE defined correctly"<<std::endl;
#JeśliNie 
    std::cout<<"MAX_VALUE not defined correctly"<<std::endl;
#Zakończ

    return 0;
}
```

## Output file:
```cpp
#include <iostream> 




int main() { 
int radius = 5; 
double area = 3 * radius * radius; 
std::cout << "Area of the circle: " << area << std::endl; 
std::cout << 100 ; 

std::cout<<"PI defined correctly"<<std::endl; 



std::cout<<"MAXX not defined correctly"<<std::endl; 



std::cout<<"MAX_VALUE defined correctly"<<std::endl; 


return 0; 
} 

```
