// pixels.cpp: 
// using SFML to load a file, manipulate its pixels, write it to disk
// Fred Martin, fredm@cs.uml.edu, Sun Mar  2 15:57:08 2014

// g++ -o pixels pixels.cpp -lsfml-graphics -lsfml-window

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "FibLFSR.hpp"
#include <vector>


void transform( sf::Image& image, FibLFSR* password);

int main(int argc, char* argv[])
{
    string inputFileName, outputFileName, seed;
    cin >> inputFileName >> outputFileName >> seed;
    sf::Image input;
    if (!input.loadFromFile(inputFileName))
		return -1;
    sf::Image output;
    if (!output.loadFromFile(inputFileName))
		return -2;
    if(seed.size() != 16)
        return -3;
    FibLFSR password(seed);
    output = input;
    cout << "input in!\n";

    transform(output, &password);    
    cout << "Transformation Complete\n";

    sf::Vector2u size1 = input.getSize();
	sf::RenderWindow window1(sf::VideoMode((size1.x), (size1.y)), "Input");
	sf::Vector2u size2 = output.getSize();
	sf::RenderWindow window2(sf::VideoMode((size2.x), (size2.y)), "output");
	
	sf::Texture texture1;
	texture1.loadFromImage(input);
	sf::Texture texture2;
	texture2.loadFromImage(output);

	sf::Sprite sprite1;
	sprite1.setTexture(texture1);
    sf::Sprite sprite2;
	sprite2.setTexture(texture2);

    while (window1.isOpen() && window2.isOpen()) {
		sf::Event event;
		while (window1.pollEvent(event)) {
			if (event.type == sf::Event::Closed){
				window1.close();
			}
		}
		while (window2.pollEvent(event)) {
			if (event.type == sf::Event::Closed){
				window2.close();
			}
		}
		window1.clear(sf::Color::White);
		window1.draw(sprite1);
		window1.display();
		window2.clear(sf::Color::White);
		window2.draw(sprite2);
		window2.display();
	}

	if (!output.saveToFile("output-file.png"))
		return -1;
    return 0;
}

void transform( sf::Image& image, FibLFSR* password){

sf::Color newColor;
    int8_t redVal, greenVal, blueVal;
    sf::Vector2u size = image.getSize();
    for(unsigned int x = 0; x < size.x; x++){
        for(unsigned int y = 0; y < size.y; y++){
            redVal = password->generate(8);
            greenVal = password->generate(8);
            blueVal = password->generate(8);
            newColor = image.getPixel(x , y);
            newColor.r = newColor.r ^ redVal;
            newColor.g = newColor.g ^ greenVal;
            newColor.b = newColor.b ^ blueVal;
            image.setPixel(x, y, newColor);
        }
    }
    return;
}
