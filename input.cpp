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
