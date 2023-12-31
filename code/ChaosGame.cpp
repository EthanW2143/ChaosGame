// Include important C++ libraries here
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <vector>


// Make code easier to type with "using namespace"
using namespace sf;
using namespace std;

int main()
{

//Loads the font file
sf::Font font;
if (!font.loadFromFile("planet benson 2.ttf"))
{
    cout << "Error loading font file" << endl; // Throw error instead of cout
}

sf::Text text;
text.setFont(font);
text.setString("Click on any 3 points on your screen");
text.setCharacterSize(24);
text.setFillColor(sf::Color::Red);
text.setStyle(sf::Text::Bold | sf::Text::Underlined);

	
    // Create a video mode object
	VideoMode vm(1920, 1080);
	// Create and open a window for the game
	RenderWindow window(vm, "Timber Game!!", Style::Default);

    vector<Vector2f> vertices;
    vector<Vector2f> points;

	while (window.isOpen())
	{
        /*
		****************************************
		Handle the players input
		****************************************
		*/
        Event event;
		while (window.pollEvent(event))
		{
            if (event.type == Event::Closed)
            {
				// Quit the game when the window is closed
				window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    std::cout << "the left button was pressed" << std::endl;
                    std::cout << "mouse x: " << event.mouseButton.x << std::endl;
                    std::cout << "mouse y: " << event.mouseButton.y << std::endl;

                    if(vertices.size() < 3)
                    {
                        vertices.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
                    }
                    else if(points.size() == 0)
                    {
                        ///fourth click
                        ///push back to points vector
			    text.setString("Click on a 4th point to start the game!");
			    points.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
                    }
                }
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}
        /*
		****************************************
		Update
		****************************************
		*/

        if(points.size() > 0)
        {
            ///generate more point(s)
		Vector2f lastPoint = points.back(); //At the start of the algorithm, should be 4th mouseclick
            ///select random vertex
		Vector2f randomVertex = vertices[rand() % vertices.size()];
            ///calculate midpoint between random vertex and the last point in the vector
		//Initializes a Vector2f variable midPoint with x-mid and y-mid
		Vector2f midpoint((randomVertex.x + lastPoint.x) / 2, (randomVertex.y + lastPoint.y) / 2); 
            ///push back the newly generated coord.
		points.push_back(midpoint);
        }

        /*
		****************************************
		Draw
		****************************************
		*/
        window.clear();
        for(int i = 0; i < vertices.size(); i++)
        {
	    //window.draw(text);
            RectangleShape rect(Vector2f(10,10));
            rect.setPosition(Vector2f(vertices[i].x, vertices[i].y));
            rect.setFillColor(Color::Blue);
            window.draw(rect);
        }
        for (int i = 0; i < points.size(); i++)
        {
            CircleShape circle(2);
            circle.setPosition(points[i]);
            circle.setFillColor(Color::Red);
            window.draw(circle);
         }
	window.draw(text);
        window.display();
    }
}
